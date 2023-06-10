#pragma once
#include <string>
#include "vec3.h"
#include "material.h"

class materialSolid : public Material{
    private:
        math::vec3<double>color;
    public:
        materialSolid(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, math::vec3<double>color );

        math::vec3<double> getColor();

};