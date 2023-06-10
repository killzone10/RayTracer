#include "material.h"


Material::Material(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction):ka{ka},
                   ks{ks},kd{kd}, exponent{exponent}, reflectance{reflectance}, transmitance {transmitance}, refraction{refraction}{};

double Material:: getKa(){
    return ka;
};
double Material:: getKs(){
    return ks;
};
double Material:: getKd(){
    return kd;
};
double Material:: getExponent(){
    return exponent;
};
double Material:: getReflectance(){
    return reflectance;
};
double Material:: getTransmitance(){
    return transmitance;
};
double Material:: getRefration(){
    return refraction;
};