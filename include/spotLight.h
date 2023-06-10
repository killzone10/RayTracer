#pragma once
#include "light.h"

class spotLight : public Light{
    private:
        math::vec3<double> position{};
        math::vec3<double> direction{};

        int alpha1{0};
        int alpha2{0};
    public:
        spotLight(math::vec3<double> color, math::vec3<double> position, math::vec3<double> direction, int alpha1, int alpha2);

  
        math::vec3<double>getPosition();
        math::vec3<double>getDirection();
};