#pragma once
#include "vec3.h"

class Ray{
    private:
        math::vec3<double> direction{};
        math::vec3<double> origin{};
        double minimumDistance{};
        double maximumDistance{};
    public:
        math::vec3<double> getOrigin();
        math::vec3<double> getDirection();
        Ray( math::vec3<double> origin, math::vec3<double> direction);
        // Ray(math::vec3<double> direction, math::vec3<double> origin, double minimumDistance, double maximumDistance);

        double getMinimumDistance();
        double getMaximumDistance();
        math::vec3<double> getMovedPoint(double x) const;
};