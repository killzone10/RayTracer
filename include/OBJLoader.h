#pragma once
#include <fstream>  
#include <vector>
#include <string>
#include <exception>
#include "vec3.h"
#include <stdio.h>
#include <string.h>

class OBJLoader {
    private:
        std::vector<math::vec3<double>> vertices, textures, normals;
        std::vector< unsigned int > vertexIndices, textureIndices, normalIndices;

    public:
        void readFile(std::string input);

        std::vector<math::vec3<double>> getVertices(){
            return std::move(vertices);
        }

         std::vector<math::vec3<double>> getTextures(){
            return std::move(textures);
        }

         std::vector<math::vec3<double>> getNormals(){
            return std::move(normals);
        }

};