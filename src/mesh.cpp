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
void Mesh::setTextures(std::vector<math::vec3 <double>> textures){
    this->textures = textures;
}
void Mesh::setIndices(std::vector<unsigned int> vertexIndices,std::vector<unsigned int> textureIndices,std::vector<unsigned int> normalIndices){
    this->vertexIndices = vertexIndices;
    this->textureIndices = textureIndices;
    this->normalIndices = normalIndices;

}



std::optional<std::shared_ptr<Intersection>> Mesh::checkIntersection(Ray *ray, double t_min, double t_max){
/// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html 
//https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm  code from those site was used
    //double EPSILON = 0.00001; // TODO change to t_min
    double closestIntersection = t_max;
    std::shared_ptr<Intersection> intersection;
    bool wasIntersection {false};
    for (int i = 0; i < vertexIndices.size(); i+=3){
        auto v0 = vertices[vertexIndices[i]];
        auto v1 = vertices[vertexIndices[i+1]];
        auto v2 = vertices [vertexIndices[i+2]];

        auto e1 = v1 - v0;
        auto e2 = v2 - v0;
 
        auto d = ray->getDirection() ; // 
        // first plug t into
        auto w2 = d.crossProduct(e2); // pvec
        auto a = e1.dotProduct(w2); // det
        // if less than t_min dont count it
        if (std::abs(a) <  t_min) {
            continue;
        }
        auto f = 1.0 / a ; // inverse det
        auto s = ray->getOrigin() - v0; // 
        auto u = f * s.dotProduct(w2);
        if (u < 0.0 || u > 1.0)
            continue;
        auto w1 = s.crossProduct(e1);
        auto v = f * ray->getDirection().dotProduct(w1);

        if (v < 0.0 || u + v > 1.0)
            continue;
        // now we re computing T to dint the intersection point on the lin
        double t = f * e2.dotProduct(w1);
        if (t > t_min && t < closestIntersection){
            wasIntersection = true;
            closestIntersection = t;
            auto intersectionPoint = ray->getMovedPoint(t);
            auto normal  = normals[normalIndices[i]];
            // auto normal  = normals[2];
            intersection = std::make_shared<Intersection>(intersectionPoint, normal, t);
            //copied from the sphere
            intersection->setFront(ray, normal);
              //material
            auto m_point = getMaterial();
            //phong 
            intersection->setMaterialCoefficients(m_point->getKa(), m_point->getKd(), m_point->getKs(), m_point ->getExponent());
            intersection->setReflectanceTransmitanceRefraction(m_point->getReflectance(), m_point->getTransmitance(), m_point->getRefration());

            // CHECK WHICH TYPE OF MATERIAL !!!
            auto solid = dynamic_cast<materialSolid*>(m_point);
            if (solid != nullptr){
                intersection->setColors(solid->getColor());
            }

            auto texture = dynamic_cast<materialTextured*> (m_point);
            if (texture != nullptr){
                intersection->setName(texture->getName());
            }

        }
  
    }
    if (wasIntersection){
        return intersection;
    }
    return {};
};

