#include "translate.h"

Translate::Translate(math::vec3<double> translate):translate{translate}{};


void Translate::transform(math::mat4<double> &transformationMatrix, bool inverse){
    math::mat4<double>a;

    if (inverse){
        a.translate(-translate);
    }
    else{
        a.translate(translate);
        // transformationMatrix.translate(translate);// ignore for normals
        //
    }
    // transformationMatrix = a * transformationMatrix;
    transformationMatrix =  transformationMatrix * a;

}

