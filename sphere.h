#pragma once
#include "surface.h"
#include <memory>
#include "vec3.h"
class Sphere : public Surface{
    private:
        double radius{0};
        math::vec3<double> position;
    public:
        Sphere(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material, double radius, math::vec3<double> position);
        void print();

        std::optional<std::shared_ptr<Intersection>> checkIntersection(Ray *ray, double t_min, double t_max);
};