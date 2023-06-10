#pragma once
#include <string>
#include "vec3.h"


class Material{
    private:
        // math::vec3<double> phong{};
        double ka {0};
        double ks{0};
        double kd{0};
        double exponent {0};
        double reflectance{0};
        double transmitance {0};
        double refraction {0};
    public:
        Material(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction);
        virtual double getKa();
        virtual double getKs();
        virtual double getKd();
        virtual double getExponent();
        virtual double getReflectance();
        virtual double getTransmitance();
        virtual double getRefration();
        
            
};