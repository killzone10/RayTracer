#include "pointLight.h"

pointLight:: pointLight(math::vec3<double> color, math::vec3<double> position) :Light(color, 2), 
                position{position}{};


math::vec3<double> pointLight::getPosition(){
    return position;
}