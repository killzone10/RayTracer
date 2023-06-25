#include "OBJLoader.h"
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
void OBJLoader::readFile(std::string fileName){
    fileName = "/scenes/" + fileName; // TODO change on c++ 17
    FILE * file = fopen(fileName.c_str(), "r");
    if( file == NULL ){
        throw std::runtime_error("eror opening a file");        
    }       
    while(true){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF){
            break; // EOF = End Of File. Quit the loop.
        }
        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 ){
            double x{0}, y{0}, z{0};

            fscanf(file, "%lf %lf %lf\n", &x, &y, &z );
            math::vec3 vec{x,y,z};

            vertices.push_back(vec);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            double x{0}, y{0}, z{0};

            fscanf(file, "%lf %lf %lf\n", &x, &y, &z );
            math::vec3 vec{x,y,z};

            textures.push_back(vec);
        }

        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            double x{0}, y{0}, z{0};

            fscanf(file, "%lf %lf \n", &x, &y );
            math::vec3 vec{x,y,z};

            normals.push_back(vec);

        }

        else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0], &vertexIndex[1], &textureIndex[1], &normalIndex[1], &vertexIndex[2], &textureIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                throw std::runtime_error("eror opening a file");        
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            textureIndices.push_back(textureIndex[0]);
            textureIndices.push_back(textureIndex[1]);
            textureIndices.push_back(textureIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
}
