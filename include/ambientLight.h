#pragma once
#include "light.h"

class ambientLight : public Light{
    public:
        ambientLight(math::vec3<double> color);
};