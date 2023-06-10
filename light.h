#pragma once
#include "vec3.h"
#include <iostream>

class Light {
    private:
        math::vec3<double> color{};
        int id {};
    public:
        Light(math::vec3<double> color, int id);
        
        virtual math::vec3 <double> getColor();
};