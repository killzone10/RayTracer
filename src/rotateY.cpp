#include "rotateY.h"

RotateY::RotateY(int theta):theta{theta}{};


void RotateY::transform(math::mat4<double> &transformationMatrix, bool inverse){
    math::mat4<double>a;
    if (inverse){
        a.setRotationY(math::Deg2Rad(-theta));
    }
    else{
        a.setRotationY(math::Deg2Rad(theta));
    }
        transformationMatrix =  a * transformationMatrix;
        // transformationMatrix =   transformationMatrix * a;

}

