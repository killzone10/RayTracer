#include "surface.h"


Surface::Surface(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material){
    this->transformations = std::move(transformations) ;
    this->material = std::move(material);
}

Surface::Surface(){};

void Surface::print(){
    std::cout <<"jestem surfacem" <<std::endl;
}

std::optional<std::shared_ptr<Intersection>> Surface::  checkIntersection(Ray *ray, double t_min, double t_max){
    // std::cout <<" I am in surface parent intersection" <<std::endl;
    return {};
};



 Material * Surface:: getMaterial(){
    return material.get();
}
