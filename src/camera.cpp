#include "camera.h"

// Camera::Camera(math::vec3<double> position, math::vec3<double> lookat, math::vec3<double> up,
//                 int angle, int horizontal, int vertical, int maxBounces) :position{position}, lookat{lookat},
//                 up{up}, angle{angle}, horizontal{ horizontal},
//                 vertical{vertical}, maxBounces{maxBounces}{
//                     // have to calculate a few things needed for ray tracing
//                     // i inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html

//                     ratio = horizontal / vertical; //width/ height
//                     viewportHeight = 2.0;
//                     double tangens = tan(angle*3.1415926/180);
//                    // viewportWidth = ratio  * viewportHeight ;

//                     viewportWidth = ratio  * viewportHeight * tangens; //add this later !
//                     // math::vec3 <double> temp{viewportWidth,0,0};
//                     // math::vec3 <double> temp1{0, viewportHeight, 0};
//                     auto z = position - lookat;
//                     z.normalize();
//                     auto x = up.crossProduct(z);
//                     x.normalize();
//                     auto y = z.crossProduct(x);
//                     m4.setFromVectors(z,x,y, position);
//                     std::cout<<m4 <<std::endl;
//                     // horizontalVec = temp;
//                     // verticalVec = temp1;
//                     horizontalVec = x*viewportWidth;
//                     verticalVec = y*viewportHeight;
//                     math::vec3 <double> focalVec{0,0, focal};
//                     //leftCornerPos = (position  - (verticalVec/2) - (horizontalVec/2) -  focalVec);
//                     leftCornerPos = (position  - (verticalVec/2) - (horizontalVec/2) -  z);
//                    // leftCornerPos = m4 * position;

//                     // NEW THINGS !!


//                 };
            

// Camera::Camera(math::vec3<double> position, math::vec3<double> lookat, math::vec3<double> up,
//                 int angle, int horizontal, int vertical, int maxBounces) :position{position}, lookat{lookat},
//                 up{up}, angle{angle}, horizontal{ horizontal},
//                 vertical{vertical}, maxBounces{maxBounces}{
//                     // have to calculate a few things needed for ray tracing
//                     // i inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html


//                     ratio = vertical / horizontal; //width/ height
//                     // vertical = static_cast<int>(horizontal / ratio);
//                     // vertical = (vertical < 1) ? 1 : vertical;
//                     auto focalLenght = (position - lookat).Lenght();

//                     double theta = static_cast<double>(angle);
//                     double tangens = tan((theta)*3.1415926/180.0); 

//                    // viewportWidth = ratio  * viewportHeight ;

//                     // viewportHeight = 2.0  * focalLenght;

//                     // viewportWidth = ratio  * viewportHeight *tangens ; //add this later !

//                     // viewportWidth = 2.0   * focalLenght;

//                     // viewportHeight = ratio *tangens  *viewportWidth ; //add this later !
//                     auto viewportWidth = 2 * tangens * focalLenght;
//                     auto viewportHeight = viewportWidth / ratio;
//                     // math::vec3 <double> temp{viewportWidth,0,0};
//                     // math::vec3 <double> temp1{0, viewportHeight, 0};
//                     auto z = position - lookat;
//                     z.normalize();
//                     auto x = up.crossProduct(z);
//                     x.normalize();
//                     auto y = z.crossProduct(x);
//                     y.normalize();

//                     m4.setFromVectors(z,x,y, position);
//                     std::cout<<m4 <<std::endl;

//                     horizontalVec = x*viewportWidth;
//                     verticalVec = -y*viewportHeight;
//                     math::vec3 <double> focalVec{0,0, focal};

//                      // Calculate the horizontal and vertical delta vectors from pixel to pixel.
//                     pixel_delta_u = horizontalVec/horizontal ;
//                     pixel_delta_v = verticalVec/vertical;

//                     //leftCornerPos = (position  - (verticalVec/2) - (horizontalVec/2) -  focalVec);
//                     // leftCornerPos = (position  - (verticalVec/2) - (horizontalVec/2) -  z);

//                     // leftCornerPos = position  - x * tangens +  (y * tangens/ratio)  - z;
//                     // horizontalVec =x  *2 * tangens;
//                     // verticalVec = y *2 * tangens;

//                     auto viewport_upper_left = position - (z * focalLenght) - horizontalVec/2 - verticalVec/2;
//                     std::cout<<viewport_upper_left<<std::endl;
//                    // leftCornerPos = m4 * position;
//                     pixelCenter = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
//                     // NEW THINGS !!


//                 };





Camera::Camera(math::vec3<double> position, math::vec3<double> lookat, math::vec3<double> up,
                int angle, int horizontal, int vertical, int maxBounces) :position{position}, lookat{lookat},
                up{up}, angle{angle}, horizontal{ horizontal},
                vertical{vertical}, maxBounces{maxBounces}{
                    // have to calculate a few things needed for ray tracing
                    // i inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html


                    ratio = horizontal / vertical; //width/ height
                  
                    double theta = static_cast<double>(angle);
                    double tangens = tan((theta)*3.1415926/180.0); 

                    double half_width = tangens;
                    double half_height = tangens / ratio;

                    auto z = position - lookat;
                    z.normalize();
                    auto x = up.crossProduct(z);
                    x.normalize();
                    auto y = z.crossProduct(x);
                    y.normalize();



                    leftCornerPos = position - (x * half_width)  + (y * half_height ) - z;

                    horizontalVec = x * half_width *2.0 ;
                    verticalVec = y * half_height * 2.0 ;

        
                   
                };


int Camera:: getAngle(){
    return angle;
}
int Camera:: getWidth(){
    return horizontal;
}
int Camera:: getHeight(){
    return vertical;
}
int Camera:: getmaxBounces(){
    return maxBounces;
}



math::vec3<double> Camera:: getPosition(){
    return position;
}
math::vec3<double> Camera:: getLookAt(){
    return lookat;
}
math::vec3<double> Camera:: getUp(){
    return up;
}

math::vec3<double> Camera:: getPixelCenter(){
    return pixelCenter;
}
// // inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html
// std::unique_ptr<Ray> Camera::getRayToPixel(double offsetHight, double offsetWidth){
//                                 // starting position, pixel point - position point 
//                                 //(leftCornerPos + (offsetHight*horizontalVec) + (offsetWidth*verticalVec) - position)
//     math::vec3<double> destination{};
//     destination = leftCornerPos + (horizontalVec*offsetHight) + (verticalVec*offsetWidth) - position;
//     std::unique_ptr<Ray> ray = std::make_unique<Ray>(position, destination); // 

//     return std::move(ray);
// }


// // inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html
// std::unique_ptr<Ray> Camera::getRayToPixel(unsigned int i, unsigned int j){
//                                 // starting position, pixel point - position point 
//                                 //(leftCornerPos + (offsetHight*horizontalVec) + (offsetWidth*verticalVec) - position)
//     math::vec3<double> destination{};
//     // destination = leftCornerPos + (horizontalVec*offsetHight) + (verticalVec*offsetWidth) - position;
//     auto pixel_var = pixelCenter + (pixel_delta_u *i) + (pixel_delta_v *j);
//     destination = pixel_var - position;
//     // destination.normalize();
//     std::cout<<"position"<<position<<std::endl;
//     std::cout<<destination<<std::endl;
//     std::unique_ptr<Ray> ray = std::make_unique<Ray>(position, destination); // 

//     return std::move(ray);
// }



// inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html
std::unique_ptr<Ray> Camera::getRayToPixel(unsigned int i, unsigned int j){
                                // starting position, pixel point - position point 
                                //(leftCornerPos + (offsetHight*horizontalVec) + (offsetWidth*verticalVec) - position)
    math::vec3<double> destination{};
    double u = static_cast<double>(i) / horizontal;
    double v = static_cast<double>(j) / vertical;
    

    // std::cout <<"horizontal "<<horizontalVec<<std::endl;
    // std::cout <<"vertical "<<verticalVec<<std::endl;
    
    destination = leftCornerPos + (horizontalVec*u) - (verticalVec*v) - position;

    std::unique_ptr<Ray> ray = std::make_unique<Ray>(position, destination); // 

    return std::move(ray);
}



