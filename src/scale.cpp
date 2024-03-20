#include "scale.h"

Scale::Scale(math::vec3<double> scale):scale{scale}{};


void Scale::transform(math::mat4<double> &transformationMatrix, bool inverse){
    math::vec3<double> scaleVector {1.0/scale[0], 1.0/scale[1], 1.0/scale[2]};
    math::mat4<double>a;
    if (inverse){
        // a = transformationMatrix.scale(1.0/scale[0], 1.0/scale[1], 1.0/scale[2]);  
        a.scale(1.0/scale[0], 1.0/scale[1], 1.0/scale[2]);  

    }
    else{
        // a = transformationMatrix.scale(scale[0], scale[1], scale[2]);  
        a.scale(1.0/scale[0], 1.0/scale[1], 1.0/scale[2]);  
        // a.scale(scale[0], scale[1], scale[2]);  
        // std::cout<<"jestem w scalu  " << scale[0] <<"  " << scale[1] <<"  " <<   scale[2] <<std::endl;
  
    }

        // transformationMatrix =  a * transformationMatrix;
        transformationMatrix =   transformationMatrix * a;

}

