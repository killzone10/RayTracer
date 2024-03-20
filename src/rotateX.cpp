#include "rotateX.h"

RotateX::RotateX(int theta):theta{theta}{};


void RotateX::transform(math::mat4<double> &transformationMatrix, bool inverse){
    math::mat4<double>a;
    if (inverse){
        a.setRotationX(math::Deg2Rad(-theta));
    }
    else{
        a.setRotationX(math::Deg2Rad(theta));
    }
    // std::cout<<"ROTX"<<a<<std::endl;
        // transformationMatrix =  a * transformationMatrix;
        transformationMatrix =   transformationMatrix * a;

}

