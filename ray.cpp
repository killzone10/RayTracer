#include "ray.h"


math::vec3<double> Ray:: getOrigin(){
    return origin;
}
math::vec3<double> Ray:: getDirection(){
    return direction;
}


// Ray::Ray(math::vec3<double> direction, math::vec3<double> origin, double minimumDistance, double maximumDistance)
//                             :direction{direction}, origin{origin}, minimumDistance{minimumDistance}, maximumDistance{maximumDistance}{};

Ray::Ray(math::vec3<double> origin, math::vec3<double> direction)
                            :direction{direction}, origin{origin}{};


double Ray:: getMinimumDistance(){
    return minimumDistance;
}
double Ray:: getMaximumDistance(){
    return maximumDistance;
}


math::vec3<double> Ray::getMovedPoint(double x) const{
    return origin + direction*x;
}