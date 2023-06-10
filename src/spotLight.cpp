#include "spotLight.h"
spotLight:: spotLight(math::vec3<double> color, math::vec3<double> position,
                     math::vec3<double> direction, int alpha1, int alpha2) 
                     : Light(color,3), 
                     position{position}, direction{direction}, alpha1{alpha1}, alpha2{alpha2}{};



math::vec3<double> spotLight ::getPosition(){
    return position;
};
math::vec3<double> spotLight ::getDirection(){
    return direction;
}