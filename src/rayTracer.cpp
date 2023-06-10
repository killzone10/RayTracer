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

            pixel_color = trace(ray.get()); // and now we have to adjst this

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

math::vec3<double> RayTracer::trace (Ray  *r){
    std::vector<std::shared_ptr<Intersection>> intersections;
    //
//     for each object in scene
//      intersection = object.intersect(ray)
    double t_min = 0;
    double t_max = 40000;

    math::vec3 <double> color (0.0, 0.0, 0.0);
    auto intersection = scene->checkGlobalIntersections(r,t_min, t_max, intersections);
    if (intersection.has_value()){
        //return something
        auto intersectionValue = intersection.value();
        auto color = intersectionValue->getColor();
        auto normal = intersectionValue->getNormal();
        normal.normalize();
        // the light components specular diffuse and ambient
        // should be done in scene
        // for each light source color +=illuminate(ray, intersection, light source)
        // math::vec3 final {normal.x() * color.x() , normal.y() * color.y() , normal.z() * color.z()  };
        color = scene->illuminate(r, intersectionValue);
        return color;

        // return value->getColor(); // COLOR
        
        // return (first*(1.0-t)) + (second * t);
        // return intersection.getColor();

    }
    else { //return background
        return scene->getbackgroudColor();
    }

}

