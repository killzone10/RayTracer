#include "materialSolid.h"


materialSolid::materialSolid(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, math::vec3<double> color)
                                    :Material(ka, kd, ks, exponent, reflectance, transmitance, refraction), color{color}{};

math::vec3<double> materialSolid::getColor(){
    return color;
}