#include "surface.h"


Surface::Surface(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material){
    this->transformations = std::move(transformations) ;
    this->material = std::move(material);
    unsigned int i {0};
    // for (auto &t :this->transformations){
    //     // check which transofrmation it is
    //     // t->transform(transformationMatrix, true); //inverse
    //     // std::cout  << i << ":" << transformationMatrix <<std::endl;
    //     t->transform(m4_inverse, false); // 
    //     // std::cout  << i << "macierz_odwrotna" << m4_inverse <<std::endl;
    //     // i++;

    // }
    for (auto it = this->transformations.rbegin(); it != this->transformations.rend(); ++it) {
        auto& t = *it;
        // Perform operations on 't'
        t->transform(transformationMatrix, true); // Inverse
        // std::cout  << i << ":" << transformationMatrix <<std::endl;

        t->transform(m4_inverse, false);

    }
}

Surface::Surface(){};

void Surface::print(){
    std::cout <<"jestem surfacem" <<std::endl;
}

std::optional<std::shared_ptr<Intersection>> Surface::checkIntersection(Ray *ray, double t_min, double t_max){
    // std::cout <<" I am in surface parent intersection" <<std::endl;
    return {};
};



 Material * Surface:: getMaterial(){
    return material.get();
}
