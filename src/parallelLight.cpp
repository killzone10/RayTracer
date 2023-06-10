#include "parallelLight.h"

parallelLight:: parallelLight(math::vec3<double> color, math::vec3<double> direction) : Light(color, 1), 
                direction{direction}{};



math::vec3<double> parallelLight::getDirection(){
    return direction;
}
