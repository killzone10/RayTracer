#include "tinyxml2.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "XmlParser.h"
#include "vec3.h"
#include "camera.h"
#include "light.h"
#include "parallelLight.h"
#include "spotLight.h"
#include "scale.h"
#include "rotateX.h"
#include "materialTextured.h"
#include "rayTracer.h"
#include "sceneBuilder.h"
#include "scene.h"
#include <filesystem>

int main(int argc, char *argv[]){    
    if (argc > 2){
        throw std::length_error{ "Passed more than 2 arguments!" };
    }
    // std::string filePath = argv[1];
    // std::filesystem::path p2 = argv[1];
     // concat 2 filenames

    try{
        std::filesystem::path p1 = "/scenes/";
        std::filesystem::path filePath = p1 / argv[1]; // get filePath !


        /// T1 render black output ! UNCOMMENT LINES BELOW SO IT WORKS !! //

        /* SceneBuilder blackSceneBuilder;
            blackSceneBuilder.addSceneName("black_image.png");
            blackSceneBuilder.addBackgroundColor(math::vec3 <double>(0,0,0));
            // get position
            double positionZ{-1}, positionY{0}, positionX{0};
            math::vec3<double> position{positionX, positionY, positionZ};
            double lookAtX{0}, lookAtY{1}, lookAtZ{0};
            math::vec3<double> lookat{lookAtX, lookAtY, lookAtZ};
            double upX{0}, upY{0}, upZ{0};
            math::vec3<double> up{upX, upY, upZ};
            double angle {45};
            double vertical {800}, horizontal {800};
            int maxBounces {2};
            std::unique_ptr<Camera> camera = std::make_unique<Camera>(position,lookat,up,angle, vertical , horizontal, maxBounces);
            blackSceneBuilder.addCamera(std::move(camera));

            auto blackscene = blackSceneBuilder.getScene();

            RayTracer blackRay{blackscene.get()};
            blackRay.render();
        */

        /// T2 UNCOMMENT LINES BELOW SO IT WORKS //  ALTHOUGH I ADDED 1 SPHERE
         /* SceneBuilder sphereBuilder;
            sphereBuilder.addSceneName("sphere_image.png");
            sphereBuilder.addBackgroundColor(math::vec3 <double>(0,0,0));
            // get position
            // double positionZ{-1}, positionY{0}, positionX{0};
            // math::vec3<double> position{positionX, positionY, positionZ};
            // double lookAtX{0}, lookAtY{1}, lookAtZ{0};
            // math::vec3<double> lookat{lookAtX, lookAtY, lookAtZ};
            // double upX{0}, upY{0}, upZ{0};
            // math::vec3<double> up{upX, upY, upZ};
            // double angle {45};
            // double vertical {800}, horizontal {800};
            // int maxBounces {2};
            std::unique_ptr<Camera> camera1 = std::make_unique<Camera>(position,lookat,up,angle, vertical , horizontal, maxBounces);
            sphereBuilder.addCamera(std::move(camera1));
            // CREATING THE SPHERE 
            math::vec3<double> positionS(-0.1,0.0,-3);
            double ka,kd,ks;
            double exponent = 1; 
            double reflectance = 0;
            double transmitance = 0;
            double refraction = 2.3;
            math::vec3<double> color(0.25,0.18,0.50);
            double radius = 1;
            ka = 0.3;
            ks =1.0;
            kd =  0.9;
            std::unique_ptr <Transform> transformation = std::make_unique<RotateY>(0);
            std::vector <std::unique_ptr<Transform>>transformations;
            transformations.push_back(std::move(transformation));
            std::unique_ptr<materialSolid> material = std::make_unique<materialSolid>(ka, kd, ks, exponent, reflectance, transmitance, refraction, color);
            std::unique_ptr <Sphere> sphere = std::make_unique<Sphere>(std::move(transformations), std::move(material), radius, positionS);
            std::unique_ptr<ambientLight> ambient = std::make_unique<ambientLight>(color);
            sphereBuilder.addLight(std::move(ambient)); // one light has to be there

            sphereBuilder.addMeshes(std::move(sphere));
            auto sphereScene = sphereBuilder.getScene();

            RayTracer sphereRay{sphereScene.get()};
            sphereRay.render();
        */
        

        // NORMAL PROGRAM //

        
        // filePath = "scenes/example3.xml";
        std::cout<<filePath<<std::endl;
        // xml parser class
        XmlParser xmlParser{filePath};
        // filename
        const char* output_file = xmlParser.getFileName();
        //r,g,b
        double r{0},g{0},b {0};
        xmlParser.getbackgroundColorElement(r,g,b); // camera przez refenrencje
    
        // final object !
        auto scene = xmlParser.Builder.getScene();

        RayTracer RayTracer{scene.get()};
        RayTracer.render();

        
    }
    catch(const std::runtime_error& e){
        std::cout << e.what();
    }

    return 0;

}







