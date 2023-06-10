#pragma once
#include "light.h"

class pointLight : public Light{
    private:
        math::vec3<double> position{};
    public:
        pointLight(math::vec3<double> color, math::vec3<double> position);
        math::vec3<double> getPosition();
        
};