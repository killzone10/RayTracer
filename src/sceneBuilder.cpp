#include "sceneBuilder.h"




void SceneBuilder::addCamera(std::unique_ptr<Camera> camera){
    scene->setCamera(std::move(camera));
}

void SceneBuilder::addLight(std::unique_ptr<Light> light){
    scene->Light.push_back(std::move(light));
}

void SceneBuilder::addMeshes(std::unique_ptr<Surface> surface){
    scene->surface.push_back(std::move(surface));
}

std::unique_ptr<Scene> SceneBuilder::getScene(){
    return std::move(scene);
}

SceneBuilder::SceneBuilder(){
    this->scene = std::make_unique<Scene>();
}

void SceneBuilder::addSceneName(std::string s){
    scene->outputFile = s;
}

void SceneBuilder::addBackgroundColor(math::vec3<double> color){
    scene->backgroundColor = color;

}
