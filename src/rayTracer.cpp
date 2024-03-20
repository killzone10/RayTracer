#include "rayTracer.h"




RayTracer::RayTracer(Scene *scene):scene{scene}{
    c = scene->getCamera();
    
}






Scene * RayTracer::getScene(){
    return scene;
}
void RayTracer::renderBlackObject(){
    std::cout <<"render black";
    render();
};


void RayTracer::print(){
    std::cout<<"Height " << c->getHeight() << " Width " << c->getWidth() << c->getPosition()<<std::endl;

}



void RayTracer:: render(){
    const int image_width = c->getWidth();
    const int image_height = c->getHeight();
    std::vector <unsigned char> colors;

    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    // int pngArray = [][];
     for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
          for (int i = 0; i < image_width; ++i) {
            auto offsetHight = double(i)/(image_width-1);
            auto offsetWidth = double(j)/(image_height-1);
            std::unique_ptr<Ray> ray = c->getRayToPixel(offsetHight, offsetWidth) ;        
            math::vec3<double> pixel_color(offsetHight, offsetWidth, 0.25); // gotta have fun there
            
            pixel_color = trace(ray.get(), c->getmaxBounces()); // and now we have to adjst this

            math::vec3<double> color = pixel_color.save_color();
            
            push_back_once(colors, color);



        }
    }
    //std filesystem add it !
    // const char *filename = scene->getOutputFile().c_str();
    std::cout<<"image_width " << image_width<< " " << image_height << std::endl;
        // std::filesystem // use this !!

    encodeOneStep(scene->getOutputFile().c_str(), colors, image_width, image_height);

}

void RayTracer::encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void RayTracer::push_back_once(std::vector<unsigned char> &colors, math::vec3<double> color ){
    colors.push_back(color.x());
    colors.push_back(color.y());
    colors.push_back(color.z());  
    colors.push_back(255);

}

math::vec3<double> RayTracer::trace (Ray  *r, int bounces){
    std::vector<std::shared_ptr<Intersection>> intersections;
    //
//     for each object in scene
//      intersection = object.intersect(ray)
    double t_min = 0.001;
    double t_max = 40000;

    math::vec3 <double> color (0.0, 0.0, 0.0);
    auto intersection = scene->checkGlobalIntersections(r, t_min, t_max, intersections); 
    // TODO ray-->getmoved_point()
    if (intersection.has_value()){
        //return something
        auto intersectionValue = intersection.value();
        auto reflectance = intersectionValue->getReflectance();
        auto transmitance = intersectionValue->getTransmitance();
        //auto color = intersectionValue->getColor();
        auto normal = intersectionValue->getNormal();
        normal.normalize();
        math::vec3<double> reflectedPart(0,0,0);
        math::vec3<double> refractedPart(0,0,0);
        // the light components specular diffuse and ambient
        // should be done in scene
        // for each light source color +=illuminate(ray, intersection, light source)
        // math::vec3 final {normal.x() * color.x() , normal.y() * color.y() , normal.z() * color.z()  };
        color = scene->illuminate(r, intersectionValue);
        if (bounces > 0 && reflectance > 0){
            // reflected_ray = get_reflected_ray();
            // reflected_color = reflectance * trace(reflectance_ray, depth - 1)
            //𝑟 = 2 ∗ −𝑑 ∗ 𝑛 ∗ 𝑛 + d
            // swap 
            auto direction = - normal*2 *(r->getDirection().dotProduct(normal)) + r->getDirection();
            std::unique_ptr<Ray> reflectedRay = std::make_unique<Ray>(intersectionValue->getPosition(), direction); // L is normalized
            auto reflectionColor = trace(reflectedRay.get(), bounces - 1);
            reflectionColor = reflectionColor * reflectance;
            reflectedPart += reflectionColor;

            
        }
        // refraction
        if (bounces > 0 && transmitance > 0){
             // reflected_ray = get_reflected_ray();
            // reflected_color = reflectance * trace(reflectance_ray, depth - 1)
            //refraction needed
            std::unique_ptr<Ray> refractionRay;
            auto refraction = intersectionValue->getRefraction();
            auto v = r->getDirection();
            v.normalize();
            //auto t_horizontal =  (v + (normal *(v.dotProduct(normal)))) * refraction;
            double coeff;
            math::vec3<double> direction;
            auto normalDir = v.dotProduct(normal); // not needed

            if (intersectionValue->getFront()){
                coeff = 1.0 / (intersectionValue->getRefraction()); // n1/ no
            }
            else {
                coeff = intersectionValue->getRefraction(); // n0 / n1
            }
            auto nestedFunction = (1.0 - (((std::pow(coeff, 2.0))) * ((1.0 - (std::pow(v.dotProduct(normal),2))))));

            
            // we have to flip n as with ray tracing in one weekend
           
            //https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel.html

            if (nestedFunction < 0 ){ // total internal reflection T II
            //https://raytracing.github.io/books/RayTracingInOneWeekend.html
                direction = v - (normal*2.0 *v.dotProduct(normal));
                direction.normalize();
                refractionRay = std::make_unique<Ray>(intersectionValue->getPosition(), direction); 
            }
            else {
                //                 vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
                //     auto cos_theta = fmin(dot(-uv, n), 1.0); we have to flip here
                //     vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n); 
                //     vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
                //     return r_out_perp + r_out_parallel;
                // }
                //https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics/refraction
                // Vec3.scale(Vec3.add(Vec3.scale(n, -c), v), r),  n*-c + v * r 
                //  Vec3.scale(n, Math.sqrt(D))  n * sqrt(D)
                auto t_vertical = -normal * (sqrt(nestedFunction));
                auto t_horizontal =  (v + (normal *(-v.dotProduct(normal)))) * coeff; // -dotproduct  because had to be flipped ! <0 
                direction  = t_horizontal + t_vertical;
                direction.normalize();
                refractionRay = std::make_unique<Ray>(intersectionValue->getPosition(), direction); 

            }

            auto refractionColor = trace(refractionRay.get(), bounces - 1);
            refractionColor = refractionColor * transmitance;
            refractedPart += refractionColor;

        }

        color = color * (1 - reflectance - transmitance) + reflectedPart + refractedPart;

        if (color.x() >1){
            color[0] = 1;
        }
        if (color.y() > 1){
            color[1] = 1;
        }
        if (color.z() > 1){
            color[2] = 1;
        }

        return color ;


    }
    else { //return background
        return scene->getbackgroudColor();
    }

}

