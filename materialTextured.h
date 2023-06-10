#pragma once
#include <string>
#include "vec3.h"
#include "material.h"

class materialTextured : public Material{
    private:
       std::string name{};
    public:
        materialTextured(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, std::string name);
        std::string getName();
        

};