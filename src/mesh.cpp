#include "mesh.h"


Mesh::Mesh(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material, std::string name)
            :Surface(std::move(transformations), std::move(material)), name{name}{};

void Mesh::print(){
    std::cout<<"jestem w meshu" << name << std::endl;
}

void Mesh::setNormals(std::vector<math::vec3 <double>> normals){
    this->normals = normals;
}

void Mesh::setVertices(std::vector<math::vec3 <double>> vertices){
    this->vertices = vertices;
}
void Mesh::setTextures(std::vector<math::vec3 <double>> setTextures){
    this->textures = textures;
}



std::optional<std::shared_ptr<Intersection>> Mesh::checkIntersection(Ray *ray, double t_min, double t_max, std::vector<std::shared_ptr<Intersection>> &intersection){


    return {};
};

