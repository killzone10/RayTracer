#include "light.h"

Light::Light(math::vec3<double> color, int id):color{color}, id{id}{};

math::vec3 <double> Light:: getColor(){
    return color;
}
