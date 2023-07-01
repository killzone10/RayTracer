#pragma once
#include "vec3.h"
#include <iostream>
#include <vector>
#include <memory>
#include "transform.h"
#include "material.h"
#include "intersection.h"
#include "ray.h"
#include <optional>
#include "materialSolid.h"
#include "materialTextured.h"
#include <cmath>
class Surface{
    private:
        //material
        //transform UserQueues(const UserQueues&) = delete;
        std::vector<std::unique_ptr<Transform>> transformations;
        std::unique_ptr<Material> material;

    public:
        Surface(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material);
        Surface();

        virtual void print();

        virtual std::optional<std::shared_ptr<Intersection>> checkIntersection(Ray *ray, double t_min, double t_max);


        Material * getMaterial();

};

