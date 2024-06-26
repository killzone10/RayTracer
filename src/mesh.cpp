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
    math::vec3<double> tx0;
    math::vec3<double> tx1;
    math::vec3<double> tx2;
    math::vec3<double> barycentric;
    // transforming the Rays !!
    auto newOrigin = transformationMatrix.multiply_point(ray->getOrigin());

    auto newDirection = transformationMatrix * ray->getDirection();


    std::unique_ptr<Ray> newRay = std::make_unique<Ray>(newOrigin, newDirection);
    for (int i = 0; i < vertexIndices.size(); i+=3){
        auto v0 = vertices[vertexIndices[i]];
        auto v1 = vertices[vertexIndices[i+1]];
        auto v2 = vertices [vertexIndices[i+2]];

        auto e1 = v1 - v0;
        auto e2 = v2 - v0;

        //
       
        //
        auto d = newRay->getDirection() ; // 
        // first plug t into
        auto w2 = d.crossProduct(e2); // pvec
        auto a = e1.dotProduct(w2); // det
        // if less than t_min dont count it
        if (std::abs(a) <  t_min) {
            continue;
        }
        auto f = 1.0 / a ; // inverse det
        auto s = newRay->getOrigin() - v0; // 
        auto u = f * s.dotProduct(w2);
        if (u < 0.0 || u > 1.0)
            continue;
        auto w1 = s.crossProduct(e1);
        auto v = f * newRay->getDirection().dotProduct(w1);

        if (v < 0.0 || u + v > 1.0)
            continue;
        // now we re computing T to dint the intersection point on the lin
        double t = f * e2.dotProduct(w1);
        if (t > t_min && t < closestIntersection){
            wasIntersection = true;
            closestIntersection = t;
            // calculating the t for tne newRay
            auto intersectionPoint = newRay->getMovedPoint(t);
            auto normal  = normals[normalIndices[i]];
            // transform normals TODO !!!
            normal = m4_inverse * normal;

            tx0 = textures[textureIndices[i]];
            tx1 = textures[textureIndices[i+1]];
            tx2 = textures[textureIndices[i +2]];
            barycentric = math::vec3<double>(1 - u - v, u, v);
            // auto normal  = normals[2];
            // going back to original RAY !!
            intersectionPoint = ray->getMovedPoint(t);
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

                // w1 b w2 a 
                auto u = barycentric.x() * tx0.x()
                        + barycentric.y() * tx1.x()
                        + barycentric.z() * tx2.x();

                auto v = barycentric.x() * tx0.y()
                        + barycentric.y() * tx1.y()
                        + barycentric.z() * tx2.y();

                auto c1 = texture->getPixels(u, v);
                intersection->setColors(c1);

            }

        }
  
    }
    if (wasIntersection){
        return intersection;
    }
    return {};
};

