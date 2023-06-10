#pragma once
#include "light.h"

class parallelLight : public Light{
    private:
        math::vec3<double> direction{};
    public:
        parallelLight(math::vec3<double> color, math::vec3<double> direction);
        math::vec3<double>getDirection();
        
};