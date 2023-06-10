#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "transform.h"
#include "rotateX.h"
#include "rotateY.h"
#include "rotateZ.h"
#include "scale.h"
#include "translate.h"
#include "light.h"
#include "ambientLight.h"
#include "parallelLight.h"
#include "spotLight.h"
#include "pointLight.h"
#include "camera.h"
#include "sceneBuilder.h"
#include "material.h"
#include "materialSolid.h"
#include "materialTextured.h"
#include <exception>
#include "surface.h"
#include "sphere.h"
#include "mesh.h"
#include "OBJLoader.h"
#include <filesystem>

class XmlParser{
    private:
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError result;
        tinyxml2::XMLElement* rootElement{nullptr};
        tinyxml2::XMLElement* backgroundColorElement{nullptr};

        // camera
        tinyxml2::XMLElement* cameraElement{nullptr};
        tinyxml2::XMLElement* cameraPositionElement{nullptr};
        tinyxml2::XMLElement* cameraLookAtElement{nullptr};
        tinyxml2::XMLElement* cameraUpElement{nullptr};
        tinyxml2::XMLElement* cameraHorizontalFovElement{nullptr};
        tinyxml2::XMLElement* cameraBouncesElement{nullptr};
        tinyxml2::XMLElement* cameraResolutionElement{nullptr};


        //light
        tinyxml2::XMLElement* lightElement{nullptr};
        tinyxml2::XMLElement* AmbientLightElement{nullptr};
        tinyxml2::XMLElement* PointLightElement{nullptr};
        tinyxml2::XMLElement* ParallelLightElement{nullptr};
        tinyxml2::XMLElement* SpotLightElement{nullptr};

        // surfaces
        tinyxml2::XMLElement* surfaceElement{nullptr};
        tinyxml2::XMLElement* sphereElement{nullptr};
        tinyxml2::XMLElement* meshElement{nullptr};


        // vector of transformations
        // std::vector <std::unique_ptr> transformations;
        std::vector<std::unique_ptr<Transform>> transformations;

        // ONLY ONE FOR ENTIRE SCENE
         std::vector<std::unique_ptr<Light>> LightVector;

        // std::unique_ptr<Light> ambientLight;
        // std::vector<std::unique_ptr<parallelLight>> parallelLightVector;
        // std::vector<std::unique_ptr<spotLight>> spotLightVector;
        // std::vector<std::unique_ptr<pointLight>> pointLightVector;

        std::vector<std::unique_ptr<Surface>> Meshes;
        std::vector<std::unique_ptr<Surface>> Spheres;
        // std::vector<std::unique_ptr<Transform>> transformations;

    public:
        SceneBuilder Builder;
        OBJLoader Loader;
        XmlParser(std::filesystem::path fileName);
        // ~XmlParser();
        // root node
        void getbackgroundColorElement(double &x, double&y, double&z);
        const char* getFileName();

        // camera node
        std::unique_ptr<Camera> parseCamera();
        void initCamera();
        void getCameraElement(double &x, double&y, double &z);
        void getCameraLookAtElement(double &x, double&y, double &z);
        void getUpCameraElement(double &x, double&y, double &z);
        void getAngleCameraElement(double &angle);
        void getResolutionCameraElement(double &vertical, double &horizontal);
        void getMaxBouncesCameraElement(int &maxBounces);

        // light Node

        void initLight();
        void getAmbientLightElement();
        void getParallelLightElement();
        void getPointLightElement();
        void getSpotLightElement();

        // 
        void initSurface();
        void getSpheres();
        void getMeshes();

        void translateFunc(tinyxml2::XMLElement* translateElement, std::vector<std::unique_ptr<Transform>> &transformVector);
        void scaleFunc(tinyxml2::XMLElement* translateElement, std::vector<std::unique_ptr<Transform>> &transformVector);
        void rotateXFunc(tinyxml2::XMLElement* translateElement, std::vector<std::unique_ptr<Transform>> &transformVector);
        void rotateYFunc(tinyxml2::XMLElement* translateElement, std::vector<std::unique_ptr<Transform>> &transformVectors);
        void rotateZFunc(tinyxml2::XMLElement* translateElement, std::vector<std::unique_ptr<Transform>> &transformVector);

        using transformation = std::vector<std::unique_ptr<Transform>> ;

        std::map<std::string, std::function<void (tinyxml2::XMLElement* translateElements, transformation &transformVector)>> dispatcher{
            {"translate", [this]( tinyxml2::XMLElement* translateElement, transformation &transformVector) { translateFunc(translateElement, transformVector);}},
            {"scale",[this]( tinyxml2::XMLElement* translateElement, transformation &transformVector){ scaleFunc(translateElement, transformVector);}},
            {"rotateX",[this]( tinyxml2::XMLElement* translateElement, transformation &transformVector){ rotateXFunc(translateElement, transformVector);}},
            {"rotateY",[this]( tinyxml2::XMLElement* translateElement, transformation &transformVector){ rotateYFunc(translateElement, transformVector);}},
            {"rotateZ",[this]( tinyxml2::XMLElement* translateElement, transformation &transformVector){ rotateZFunc(translateElement, transformVector);}},
        };


        
};