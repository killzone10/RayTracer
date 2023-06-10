#pragma once
#include"scene.h"
#include <memory>
#include "vec3.h"
class SceneBuilder{
    private:
        std::unique_ptr<Scene> scene;

    public:
        //addLights
        void addLight(std::unique_ptr<Light> light);
        //addMeshes
        void addMeshes(std::unique_ptr<Surface> surface);
        void addCamera(std::unique_ptr<Camera> Camera);
        //addCamera to Scene obj all from parser
        std::unique_ptr<Scene> getScene();

        SceneBuilder();
        void addSceneName(std::string s);
        void addBackgroundColor(math::vec3<double> color);

};