#pragma once
#include "surface.h"
#include <string>
#include <memory>

class Mesh : public Surface{
    private:
          std::vector<math::vec3 <double>> normals;
          std::vector<math::vec3 <double>> vertices;
          std::vector<math::vec3 <double>> textures;
          std::vector< unsigned int > vertexIndices, textureIndices, normalIndices;


    public:
        std::string name{};
        void print();
        Mesh(std::vector<std::unique_ptr<Transform>> transformations, std::unique_ptr<Material>material, std::string name);
        void setNormals(std::vector<math::vec3 <double>> normals);
        void setVertices(std::vector<math::vec3 <double>> vertices);
        void setTextures(std::vector<math::vec3 <double>> setTextures);
        void setIndices(std::vector<unsigned int> vertexIndices, std::vector<unsigned int> textureIndices,std::vector<unsigned int> normalIndices);
        std::optional<std::shared_ptr<Intersection>> checkIntersection(Ray *ray, double t_min, double t_max);

};