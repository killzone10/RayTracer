#pragma once
#include "vec3.h"
#include "ray.h"

#include <cmath>
#include <memory>

class Camera {
    private:
        math::vec3<double> position{0,0,0};
        math::vec3<double> lookat{0,0,-1};
        math::vec3<double> up{0,0,0};
        int angle {45};
        int horizontal {800}; //width
        int vertical {800}; // height
        int maxBounces {1};

        // math::vec3<double>

        double ratio;
        double viewportHeight;
        double viewportWidth;

        double focal {1.0};
        math::vec3 <double> horizontalVec{};
        math::vec3 <double> verticalVec{};
        math::vec3 <double>leftCornerPos{};
        math::mat4<double> m4{};


    public:

        Camera();
        Camera(math::vec3<double> position, math::vec3<double> lookat, math::vec3<double> up,
              int angle, int horizontal, int vertical, int maxBounces);

        math::vec3<double> getPosition();
        math::vec3<double> getLookAt();
        math::vec3<double> getUp();
        int getAngle();
        int getWidth();
        int getHeight();
        int getmaxBounces();

        std::unique_ptr<Ray> getRayToPixel(double offsetHight, double offsetWidth);



};