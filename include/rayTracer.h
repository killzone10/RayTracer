#pragma once
#include "scene.h"
#include "camera.h"
#include "lodepng.h"
#include "intersection.h"

class RayTracer{
    private:
        Scene *scene;
        Camera* c;

    public:

        RayTracer(Scene *scene);
        void render();
        void renderBlackObject();
        Scene * getScene();
        void print();
        
        void push_back_once(std::vector<unsigned char> &colors, math::vec3<double> color );
        void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
        math::vec3<double> trace(Ray *r, int bounces);



};