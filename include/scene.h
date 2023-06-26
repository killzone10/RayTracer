#pragma once
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
#include "surface.h"
#include "vec3.h"
#include <typeinfo>
#include <optional>
#include <limits>
#include  <cmath>
#include <algorithm>
#include "intersection.h"
class Scene{
    private:
        std::string outputFile{};
        math::vec3 <double> backgroundColor{};
        std::vector<std::unique_ptr<Surface>> surface;
        std::vector<std::unique_ptr<Light>> light;

        std::unique_ptr<Camera> c;
        int k{2};
    

    public:
        void render();
        void renderBlack();
        void printSurface();
        void setCamera(std::unique_ptr<Camera> c);

        Camera * getCamera();
        
        friend class SceneBuilder;
        std::string getOutputFile();
        math::vec3 <double> getbackgroudColor();    
        std::optional<std::shared_ptr<Intersection>> checkGlobalIntersections(Ray *ray, double t_min, double t_max, std::vector<std::shared_ptr<Intersection>> &intersection);
        math::vec3 <double>illuminate(Ray *ray, std::shared_ptr<Intersection> &intersection);
        std::shared_ptr<Intersection> chooseMinIntersection(std::vector<std::shared_ptr<Intersection>> &intersections);
};