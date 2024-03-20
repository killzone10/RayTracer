#include "rotateZ.h"

RotateZ::RotateZ(int theta):theta{theta}{};

void RotateZ::transform(math::mat4<double> &transformationMatrix, bool inverse){
    math::mat4<double>a;
    if (inverse){
        a.setRotationZ(math::Deg2Rad(-theta));
    }
    else{
        a.setRotationZ(math::Deg2Rad(theta));
    }
        // std::cout<<"ROTZ"<<a<<std::endl;

        // transformationMatrix =  a * transformationMatrix;
        transformationMatrix =   transformationMatrix * a;

}

