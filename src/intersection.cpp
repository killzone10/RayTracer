#include "intersection.h"


// void Intersection:: setPoint(math::vec3<double>p){
//     point = p;
// }


// void Intersection:: setNormal(math::vec3<double>n){
//     normal = n;
// }
void Intersection:: setT(double t0){
    t = t0;
}

Intersection::Intersection(math::vec3 <double> point, math::vec3 <double> normal, double t) : point {point}, normal{normal},
                            t{t}{};
Intersection::Intersection() {
    t =0;
};



void Intersection::setPoint(math::vec3<double>point){
    this->point = point;
};
void Intersection::setNormal(math::vec3<double>normal){
    this ->normal = normal;
};
void Intersection::setRoot(double root){
    this->t = root;
}

void Intersection::setMaterialCoefficients(double ka,  double kd, double ks,double exponent){
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->exponent = exponent;
}
void Intersection::setReflectanceTransmitanceRefraction(double reflectance, double transmitance, double refraction){
    this->reflectance = reflectance;
    this->transmitance = transmitance;
    this->refraction = refraction;
}

void Intersection::setColors(math::vec3<double> colors){
    this->color = colors;
}

void Intersection::setName(std::string name){
    this->name = name;
}

math::vec3<double> Intersection::getColor(){
    return color;
}
math::vec3<double> Intersection::getNormal(){
    return normal;
}
math::vec3<double> Intersection::getPosition(){
    return point;
}




double Intersection:: getRoot(){
    return t;
};
double Intersection:: getKa(){
    return ka;
};
double Intersection:: getKs(){
    return ks;
};
double Intersection:: getKd(){
    return kd;
};
double Intersection:: getExponent(){
    return exponent;
};
double Intersection:: getReflectance(){
    return reflectance;
};
double Intersection:: getTransmitance(){
    return transmitance;
};
double Intersection:: getRefraction(){
    return refraction;
};


void Intersection::setFront(Ray *r,  math::vec3<double> & directed_normal){
    auto dot = r->getDirection().dotProduct(directed_normal);
    if (dot < 0){
        isFront = true;
        normal = directed_normal; 


    }
    else{
        isFront = false;
        normal = -directed_normal;
    }

}
// void Intersection::setFront(Ray *r,  math::vec3<double> & directed_normal){
//     auto dot = r->getDirection().dotProduct(directed_normal);
//     normal = directed_normal;
    
// }


bool Intersection:: getFront(){
    return isFront;
}
