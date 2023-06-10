#include "materialTextured.h"


materialTextured::materialTextured(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, std::string name)
                                    :Material(ka,kd,ks, exponent, reflectance, transmitance, refraction), name{name}{};

std::string materialTextured::getName(){
    return name;
}
