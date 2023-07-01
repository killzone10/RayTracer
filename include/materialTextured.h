#pragma once
#include <string>
#include "vec3.h"
#include "material.h"
#include "lodepng.h"

class materialTextured : public Material{
    private:
       std::string name{};
       std::vector<unsigned char> png;
       std::vector<unsigned char> image;
       unsigned width{}, height{};

    public:
        materialTextured(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, std::string name);
        std::string getName();
        void decodeTwoSteps(); 
        math::vec3<double> getPixels(double u, double v);

};