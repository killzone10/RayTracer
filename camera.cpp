#include "camera.h"

Camera::Camera(math::vec3<double> position, math::vec3<double> lookat, math::vec3<double> up,
                int angle, int horizontal, int vertical, int maxBounces) :position{position}, lookat{lookat},
                up{up}, angle{angle}, horizontal{ horizontal},
                vertical{vertical}, maxBounces{maxBounces}{
                    // have to calculate a few things needed for ray tracing
                    // i inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html

                    ratio = horizontal / vertical; //width/ height
                    viewportHeight = 2.0;
                    double tangens = tan(angle);
                    viewportWidth = ratio  * viewportHeight ;
                    // viewportWidth = ratio  * viewportHeight * tangens;
                    math::vec3 <double> temp{viewportWidth,0,0};
                    math::vec3 <double> temp1{0, viewportHeight, 0};
                    horizontalVec = temp;
                    verticalVec = temp1;
                    math::vec3 <double> focalVec{0,0, focal};
                    leftCornerPos = position  - (verticalVec/2) - (horizontalVec/2) -  focalVec;
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

// inspired on https://raytracing.github.io/books/RayTracingInOneWeekend.html
std::unique_ptr<Ray> Camera::getRayToPixel(double offsetHight, double offsetWidth){
                                // starting position, pixel point - position point 
                                //(leftCornerPos + (offsetHight*horizontalVec) + (offsetWidth*verticalVec) - position)
    math::vec3<double> destination{};
    destination = leftCornerPos + (horizontalVec*offsetHight) + (verticalVec*offsetWidth) - position;
    std::unique_ptr<Ray> ray = std::make_unique<Ray>(position, destination); // 

    return std::move(ray);
}
