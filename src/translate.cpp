#include "translate.h"

Translate::Translate(math::vec3<double> translate):translate{translate}{};


void Translate::transform(math::mat4<double> &transformationMatrix, bool inverse){
    if (inverse){
        transformationMatrix.translate(-translate);
    }
    else{
        // transformationMatrix.translate(translate);// ignore for normals
    }

}

