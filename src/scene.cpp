#include "scene.h"

void Scene::setCamera(std::unique_ptr<Camera> camera){
    this->c = std::move(camera);
}

void Scene::printSurface(){
    for(auto&el :surface){
        std::cout<<typeid(el).name() <<std::endl;
        el->print();
    }
}

Camera * Scene:: getCamera(){
    return c.get();
}


 std::string Scene:: getOutputFile(){
    return outputFile; 
 }
math::vec3 <double> Scene:: getbackgroudColor(){
    return backgroundColor;
}

std::optional<std::shared_ptr<Intersection>> Scene:: checkGlobalIntersections (Ray *ray, double t_min, double t_max, std::vector<std::shared_ptr<Intersection>> &intersections){
    // scan for intersections !
    
    for (auto&s : surface){
        // modify the ray with transformations ! 
        auto intersection = s->checkIntersection(ray, t_min, t_max);
        if (intersection.has_value()){
            intersections.push_back(*intersection);
        }
    }
        
    if (intersections.empty()){
        return {};
    }

    //determine closest intersection (its the one where root is the lowest)
    std::shared_ptr<Intersection> minIntersection = chooseMinIntersection(intersections);
    return minIntersection;
}


math::vec3 <double> Scene:: illuminate(Ray *ray, std::shared_ptr<Intersection> &intersection){
    double Ks = intersection->getKs();
    double Ka = intersection->getKa();
    double Kd = intersection->getKd();
    double exponent = intersection->getExponent();

    math::vec3 <double> ambient (0,0,0);
    math::vec3 <double> diffuse (0,0,0);
    math::vec3 <double> specular (0,0,0);

    math::vec3<double> objectColor = intersection->getColor();
    math::vec3<double> lightColor (0,0,0);
    math::vec3<double> finalColor (0,0,0);
    double lambertian {0};

    double lightLenght{0};
    unsigned int i {0};
    for (auto &l : light){
        // Defines an ambient light with color (r,g,b)
        // - all objects are illuminated by this light. Note: the world can have precisely one ambient light.

        std::vector<std::shared_ptr<Intersection>> shadowIntersections;

        lightColor = l->getColor();

        auto ambientCast = dynamic_cast<ambientLight*> (l.get());
        if (ambientCast != nullptr){
                ambient += lightColor * objectColor ;
                continue;

        }
        math::vec3<double>L(0,0,0); //light vector
        math::vec3<double>N(0,0,0); // normal vector
        math::vec3<double>R(0,0,0); // reflection vector
        math::vec3<double>E(0,0,0); // specular vector ITS THE EASIEST BECAUSE ITS - RAY VECTOR
        //Defines a parallel light with color (r,g,b) - much like the sun,
        // these lights are infinitely far away, and only have a direction vector direction (x,y,z).

        auto parallelCast = dynamic_cast<parallelLight*> (l.get());
        if (parallelCast != nullptr){
            L = - parallelCast->getDirection();
            // lightLenght = 100000;     //   should be infinity there     
            lightLenght =  std::numeric_limits<float>::infinity();     //   should be infinity there     

        }
        // point is ike parallel, but not in infinity !
        // Defines a point light with color (r,g,b) and position (x,y,z).


        auto pointCast = dynamic_cast<pointLight*> (l.get());
        if (pointCast != nullptr){
            L = pointCast->getPosition() - intersection->getPosition(); // light source - origin
            lightLenght = L.Lenght();
            L.normalize();
            // this below is left vs right light
            // if (i == 0){
            //     i++;
            //     continue;
            // }
            // if ( i == 1){
            //     continue;
            // }

        }
        auto spotCast = dynamic_cast<spotLight*> (l.get());
        if (spotCast != nullptr){
            // nothing 
            continue;
        }
        // shadow ray part !! 
        std::unique_ptr<Ray> shadowRay = std::make_unique<Ray>(intersection->getPosition(), L); // L is normalized
        auto shadowIntersection = checkGlobalIntersections(shadowRay.get(), 0.00001, lightLenght, shadowIntersections);
        if (!shadowIntersection.has_value()){ 

       
            N = intersection->getNormal();
            N.normalize();
            //E = -intersection->getPosition();
            E = -ray->getDirection();
            E.normalize();
            R = ((N*2*(N.dotProduct(L))) - L); // 2 (n *I)*n - I 
            R.normalize();
            //diffuse part object color * light color * rest
            lambertian = std::max(0.0, L.dotProduct(N));
            // specular lightColor * specular part * ks
            
            double lightSpecular = pow(std::max(E.dotProduct(R), 0.0),  exponent); // check if ER or RE
            // ambient ambient * object Color 
        
            diffuse +=  lightColor * objectColor * lambertian ;  // vec 3 diffuse
            specular =  specular +  (lightColor * lightSpecular) ;  // vec 3 specular
           
        // ambient += lightColor * o=bjectColor * Ka;
        }
        i++;
    }
    diffuse = diffuse * Kd;
    specular = specular*  Ks;
    ambient = ambient *Ka;
    finalColor = diffuse + specular + ambient ;
    if (finalColor.x() > 1 ) { 
        finalColor[0] = 1;
    }
    if (finalColor.y() > 1){
        finalColor[1] = 1;
    }
    if (finalColor.z() > 1){
        finalColor[2] = 1;
    }
    // add lights !
    return finalColor;
}



std::shared_ptr<Intersection> Scene:: chooseMinIntersection(std::vector<std::shared_ptr<Intersection>> &intersections){
    std::shared_ptr<Intersection> minIntersection;
    unsigned int i =0;
    double t;
    for (auto &intersection : intersections){
        if (i == 0){
            t = intersection->getRoot();
            minIntersection = intersection;

        }
        else {
            if (intersection->getRoot() <= t){
                t = intersection->getRoot();
                minIntersection = intersection;
            }
           
        }
        i++;
         

    }
    return minIntersection;
}