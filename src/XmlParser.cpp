#include "XmlParser.h"



XmlParser::XmlParser(std::filesystem::path fileName){

    result = doc.LoadFile(fileName.string().c_str());    
     if (result == tinyxml2::XML_SUCCESS) {
        std::cout<<"success" << std::endl;
        // initialize root element:
        rootElement = doc.RootElement();
        // std::cout <<rootElement->Name()<<std::endl;
        initCamera();
        initLight();
        initSurface();
        // name of the Scene !
        const char* output_file = getFileName();
        // r,g,b of the scene
        double r{0},g{0},b {0};
        getbackgroundColorElement(r,g,b); // camera przez refenrencje
        math::vec3<double>c {r,g,b};

        Builder.addSceneName(output_file);
        Builder.addBackgroundColor(c);

        auto camera = parseCamera();
        Builder.addCamera(std::move(camera));


        getAmbientLightElement(); // add ambiennts light
        getParallelLightElement();
        getPointLightElement();
        getSpotLightElement();
        getSpheres();
        getMeshes();

     }
     else {
        throw std::runtime_error("Cant load a file") ;    
    }
}
const char* XmlParser ::getFileName(){
    if (result == tinyxml2::XML_SUCCESS) {

    const char* output_file = rootElement->Attribute("output_file");
    return output_file;
    }
    else {
        return nullptr;
    }
}

void XmlParser::getbackgroundColorElement(double &r, double&g, double&b){
    if (result == tinyxml2::XML_SUCCESS) {
        backgroundColorElement = rootElement->FirstChildElement("background_color");
        backgroundColorElement->QueryDoubleAttribute("r", &r);
        backgroundColorElement->QueryDoubleAttribute("g", &g);
        backgroundColorElement->QueryDoubleAttribute("b", &b);

    }
    else {
        std::invalid_argument("XML Sucess failed");
    }
}
void XmlParser::initCamera(){
    if (result == tinyxml2::XML_SUCCESS) {
        cameraElement = rootElement->FirstChildElement("camera");
    }
    else{
        std::invalid_argument("XML Sucess failed");
    }

}


void XmlParser:: getCameraElement(double &positionX, double &positionY, double &positionZ){
     if (result == tinyxml2::XML_SUCCESS && cameraElement != nullptr) {
        cameraPositionElement = cameraElement->FirstChildElement("position");
        cameraPositionElement->QueryDoubleAttribute("z", &positionZ);
        cameraPositionElement->QueryDoubleAttribute("y", &positionY);
        cameraPositionElement->QueryDoubleAttribute("x", &positionX);
        std::cout << "Camera Position: x=" << positionX << ", y=" << positionY << ", z=" << positionZ << ")" << std::endl;

    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }
}

    // //     tinyxml2::XMLElement* cameraLookAtElement = cameraElement->FirstChildElement("lookat");

void XmlParser:: getCameraLookAtElement(double &X, double &Y, double &Z){
     if (result == tinyxml2::XML_SUCCESS && cameraElement != nullptr) {
        cameraLookAtElement = cameraElement->FirstChildElement("lookat");
        cameraLookAtElement->QueryDoubleAttribute("z", &Z);
        cameraLookAtElement->QueryDoubleAttribute("y", &Y);
        cameraLookAtElement->QueryDoubleAttribute("x", &X);
        std::cout << "Camera : x=" << X << ", y=" << Y << ", z=" << Z << ")" << std::endl;

    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }
}


void XmlParser:: getUpCameraElement(double &X, double &Y, double &Z){
     if (result == tinyxml2::XML_SUCCESS && cameraElement != nullptr) {
        cameraUpElement = cameraElement->FirstChildElement("up");
        cameraUpElement->QueryDoubleAttribute("z", &Z);
        cameraUpElement->QueryDoubleAttribute("y", &Y);
        cameraUpElement->QueryDoubleAttribute("x", &X);
        std::cout << "Camera Up : x=" << X << ", y=" << Y << ", z=" << Z << ")" << std::endl;

    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }
}


void XmlParser:: getAngleCameraElement(double &angle){
     if (result == tinyxml2::XML_SUCCESS && cameraElement != nullptr) {
        cameraHorizontalFovElement = cameraElement->FirstChildElement("horizontal_fov");
        cameraHorizontalFovElement->QueryDoubleAttribute("angle", &angle);

        std::cout << "Angle: " <<angle << std::endl;

    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }
}



void XmlParser:: getResolutionCameraElement(double &vertical, double&horizontal){
     if (result == tinyxml2::XML_SUCCESS && cameraElement != nullptr) {
        cameraResolutionElement = cameraElement->FirstChildElement("resolution");
        cameraResolutionElement->QueryDoubleAttribute("vertical", &vertical);
        cameraResolutionElement->QueryDoubleAttribute("horizontal", &horizontal);

        std::cout << "Vertical: " <<vertical<< "Horizontal:" << horizontal<< std::endl;

    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }
}


void XmlParser::getMaxBouncesCameraElement( int &maxBounces){
     if (result == tinyxml2::XML_SUCCESS && cameraElement != nullptr) {
        cameraBouncesElement = cameraElement->FirstChildElement("max_bounces");
        cameraBouncesElement->QueryIntAttribute("n", &maxBounces);

        std::cout << "Max Bounces: " <<maxBounces << std::endl;

    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }
}


void XmlParser::initLight(){
    if (result == tinyxml2::XML_SUCCESS) {
        lightElement = rootElement->FirstChildElement("lights");
    }
    else{
        std::invalid_argument("XML Sucess failed");
    }
}

void XmlParser::getAmbientLightElement(){
    double r {0}, g {0}, b {0};
     if (result == tinyxml2::XML_SUCCESS && lightElement != nullptr) {
        AmbientLightElement = lightElement->FirstChildElement("ambient_light");
        tinyxml2::XMLElement* colorElement{nullptr};
        // std::cout <<AmbientLightElement->FirstChild()->Value() <<std::endl;
        // std::cout <<AmbientLightElement->FirstChild()->ToText() <<std::endl;

        colorElement = AmbientLightElement->FirstChildElement("color");
        colorElement->QueryDoubleAttribute("r", &r);
        colorElement->QueryDoubleAttribute("g", &g);
        colorElement->QueryDoubleAttribute("b", &b);
        math::vec3 <double> color{r,g,b};
        std::unique_ptr<ambientLight> ambient = std::make_unique<ambientLight>(color);

        // LightVector.push_back(std::move(ambient));
        Builder.addLight(std::move(ambient));

        std::cout << "Ambient Light b=" << b << ", g=" << g << ", r=" << r << ")" << std::endl;
        
    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }

}


void XmlParser::getParallelLightElement(){
    double r{0},g{0},b{0},x{0},y{0},z{0};
     if (result == tinyxml2::XML_SUCCESS && lightElement != nullptr) {
        ParallelLightElement = lightElement->FirstChildElement("parallel_light");
        // std::cout << ParallelLightElement << std::endl;
        // std::cout << ParallelLightElement->Value() << std::endl;

        if (ParallelLightElement != nullptr){
        // std::cout <<AmbientLightElement->FirstChild()->Value() <<std::endl;
        // std::cout <<AmbientLightElement->FirstChild()->ToText() <<std::endl;
            tinyxml2::XMLElement* colorElement{nullptr};
            tinyxml2::XMLElement* directionElement{nullptr};
            colorElement = ParallelLightElement->FirstChildElement("color");
            directionElement = ParallelLightElement->FirstChildElement("direction");

            colorElement->QueryDoubleAttribute("r", &r);
            colorElement->QueryDoubleAttribute("g", &g);
            colorElement->QueryDoubleAttribute("b", &b);
            math::vec3 <double> color{r,g,b};

            directionElement ->QueryDoubleAttribute("x",&x);
            directionElement ->QueryDoubleAttribute("y",&y);
            directionElement ->QueryDoubleAttribute("z",&z);
            math::vec3 <double> direction{x,y,z};

            std::unique_ptr<parallelLight> parallel = std::make_unique<parallelLight>(color, direction);
            // LightVector.push_back(std::move(parallel));
            Builder.addLight(std::move(parallel));
            std::cout << "Parallel Light b=" << b << ", g=" << g << ", r=" << r << ")" << std::endl;
            std::cout << "Parallel pos x=" << x << ", y=" << y << ", z=" << z << ")" << std::endl;

        }
   
    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }

}

void XmlParser::getPointLightElement(){
    double r{0}, g{0}, b{0},  x{0},  y{0},  z{0};
     if (result == tinyxml2::XML_SUCCESS && lightElement != nullptr) {
        PointLightElement = lightElement->FirstChildElement("point_light");
        // std::cout<<PointLightElement <<std::endl;
        tinyxml2::XMLElement* colorElement{nullptr};
        tinyxml2::XMLElement* positionElement{nullptr};
        // std::cout<<PointLightElement->Value()<<std::endl;
        // std::cout<<PointLightElement->NextSiblingElement()->Value()<<std::endl;
        // std::cout<<PointLightElement->NextSiblingElement()->NextSiblingElement()<<std::endl;

        // if (PointLightElement != nullptr){
        while (PointLightElement){
       
            colorElement = PointLightElement->FirstChildElement("color");
            positionElement = PointLightElement->FirstChildElement("position");

            colorElement->QueryDoubleAttribute("r", &r);
            colorElement->QueryDoubleAttribute("g", &g);
            colorElement->QueryDoubleAttribute("b", &b);
            math::vec3 <double> color{r,g,b};

            positionElement ->QueryDoubleAttribute("x",&x);
            positionElement ->QueryDoubleAttribute("y",&y);
            positionElement ->QueryDoubleAttribute("z",&z);
            math::vec3 <double> position{x,y,z};

            std::unique_ptr<pointLight> point = std::make_unique<pointLight>(color, position);
            // LightVector.push_back(std::move(parallel));
            Builder.addLight(std::move(point));
            // create lights

            PointLightElement = PointLightElement->NextSiblingElement("point_light");


        }

    }

    else {
        std::logic_error("tinyxml not initialized properly");
    }

}


void XmlParser::getSpotLightElement(){
     if (result == tinyxml2::XML_SUCCESS && lightElement != nullptr) {
        SpotLightElement = lightElement->FirstChildElement("spot_light");
        tinyxml2::XMLElement* colorElement{nullptr};
        tinyxml2::XMLElement* positionElement{nullptr};
        tinyxml2::XMLElement* directionElement{nullptr};
        tinyxml2::XMLElement* falloffEement{nullptr};
        double r{0},  g{0},  b{0};
        double posX{0}, posY{0}, posZ{0};
        double dirX{0}, dirY{0}, dirZ{0};
        int alpha1{0}, alpha2{0};

        

        // std::cout<<PointLightElement->Value()<<std::endl;
        // std::cout<<PointLightElement->NextSiblingElement()->Value()<<std::endl;
        // std::cout<<PointLightElement->NextSiblingElement()->NextSiblingElement()<<std::endl;

        // if (PointLightElement != nullptr){
        while (SpotLightElement){
       
            colorElement = SpotLightElement->FirstChildElement("color");
            positionElement = SpotLightElement->FirstChildElement("position");
            directionElement = SpotLightElement->FirstChildElement("direction");
            falloffEement = SpotLightElement->FirstChildElement("falloff");


            colorElement->QueryDoubleAttribute("r", &r);
            colorElement->QueryDoubleAttribute("g", &g);
            colorElement->QueryDoubleAttribute("b", &b);
            math::vec3 <double> color{r,g,b};

            positionElement ->QueryDoubleAttribute("x",&posX);
            positionElement ->QueryDoubleAttribute("y",&posY);
            positionElement ->QueryDoubleAttribute("z",&posZ);
            math::vec3 <double> position{posX,posY,posZ};

            directionElement ->QueryDoubleAttribute("x",&dirX);
            directionElement ->QueryDoubleAttribute("y",&dirY);
            directionElement ->QueryDoubleAttribute("z",&dirZ);
            math::vec3 <double> direction{dirX,dirY,dirZ};

            
            falloffEement ->QueryIntAttribute("alpha1",&alpha1);
            falloffEement ->QueryIntAttribute("alpha2",&alpha2);
            // create lights
            std::cout << "Point Light b=" << b << ", g=" << g << ", r=" << r << ")" << std::endl;
            std::cout << "Point pos x=" << posX << ", y=" << posY << ", z=" << posZ << ")" << std::endl;
            std::cout << "Direction pos x=" << dirX << ", y=" << dirY << ", z=" << dirZ << ")" << std::endl;
            std::cout << "Faloff =" << alpha1 << ",alpha 2" << alpha2 << std::endl;



            std::unique_ptr<spotLight> spot = std::make_unique<spotLight>(color, position, direction, alpha1, alpha2);
            // LightVector.push_back(std::move(parallel));
            Builder.addLight(std::move(spot));

            SpotLightElement = SpotLightElement->NextSiblingElement("spot_light");

        }

    }

    else {
        std::logic_error("tinyxml not initialized properly");
    }

}



void XmlParser::initSurface(){
    if (result == tinyxml2::XML_SUCCESS) {
        surfaceElement = rootElement->FirstChildElement("surfaces");
    }
    else{
        std::invalid_argument("XML Sucess failed");
    }

}





void XmlParser::getSpheres(){
     if (result == tinyxml2::XML_SUCCESS && surfaceElement != nullptr) {
        sphereElement = surfaceElement->FirstChildElement("sphere");
        double radius {0};
        tinyxml2::XMLElement* positionElement{nullptr};
        tinyxml2::XMLElement* materialSolidElement{nullptr};
        tinyxml2::XMLElement* materialTexturedElement{nullptr};

        tinyxml2::XMLElement* transformElement{nullptr};
        double posX{0}, posY{0}, posZ{0};

        double dirX{0}, dirY{0}, dirZ{0}, alpha1{0}, alpha2{0};

        // for material 
        double r{0},  g{0},  b{0};
        double ka{0}, kd{0}, ks{0}, exponent{0};
        double reflectance{0}, transmitance{0}, refraction{0};
        std::string name{};

        // for transform

        double translateX{0}, translateY{0}, translateZ{0},scaleX{0}, scaleY{0}, scaleZ{0};
        int rotateX{0}, rotateY{0}, rotateZ{0};
        // if (PointLightElement != nullptr){
        while (sphereElement){
            sphereElement->QueryDoubleAttribute("radius", &radius);
            positionElement = sphereElement->FirstChildElement("position");
            materialSolidElement = sphereElement->FirstChildElement("material_solid");
            materialTexturedElement = sphereElement->FirstChildElement("material_textured");
            transformElement = sphereElement->FirstChildElement("transform");

            positionElement ->QueryDoubleAttribute("x",&posX);
            positionElement ->QueryDoubleAttribute("y",&posY);
            positionElement ->QueryDoubleAttribute("z",&posZ);
            math::vec3 position{posX, posY, posZ};

            // transform created
            std::vector<std::unique_ptr<Transform>> transformations;
            if (transformElement != nullptr){
                tinyxml2::XMLElement* childElement = transformElement->FirstChildElement();

                while (childElement){
                    auto it = dispatcher.find(childElement->Name());
                    if (it != dispatcher.end()) {
                          it->second(childElement, transformations);
                    }
                    childElement = childElement->NextSiblingElement();
                }
            }

            if (materialSolidElement != nullptr){
                tinyxml2::XMLElement* colorElement = materialSolidElement->FirstChildElement("color");
                if (colorElement != nullptr){
                    colorElement->QueryDoubleAttribute("r", &r);
                    colorElement->QueryDoubleAttribute("g", &g);
                    colorElement->QueryDoubleAttribute("b", &b);
                }
                math::vec3 color{r, g, b};

                tinyxml2::XMLElement* phongElement = materialSolidElement->FirstChildElement("phong");
                    phongElement->QueryDoubleAttribute("ka", &ka);
                    phongElement->QueryDoubleAttribute("kd", &kd);
                    phongElement->QueryDoubleAttribute("ks", &ks);
                    phongElement->QueryDoubleAttribute("exponent", &exponent);


                tinyxml2::XMLElement* reflectanceElement = materialSolidElement->FirstChildElement("reflectance");
                    reflectanceElement->QueryDoubleAttribute("r", &reflectance);
                         
                tinyxml2::XMLElement* transmitanceElement = materialSolidElement->FirstChildElement("transmittance");
                    transmitanceElement->QueryDoubleAttribute("t", &transmitance);

                tinyxml2::XMLElement* refractionElement = materialSolidElement->FirstChildElement("refraction");
                    refractionElement->QueryDoubleAttribute("iof", &refraction);

                std::unique_ptr<materialSolid> material = std::make_unique<materialSolid>(ka, kd, ks, exponent, reflectance, transmitance, refraction, color);

                std::unique_ptr <Sphere> sphere = std::make_unique<Sphere>(std::move(transformations), std::move(material), radius, position);
                Builder.addMeshes(std::move(sphere));

            }
            if (materialTexturedElement != nullptr){ 

                tinyxml2::XMLElement* phongElement = materialTexturedElement->FirstChildElement("phong");
                    phongElement->QueryDoubleAttribute("ka", &ka);
                    phongElement->QueryDoubleAttribute("kd", &kd);
                    phongElement->QueryDoubleAttribute("ks", &ks);
                    phongElement->QueryDoubleAttribute("exponent", &exponent);

                tinyxml2::XMLElement* reflectanceElement = materialTexturedElement->FirstChildElement("reflectance");
                    reflectanceElement->QueryDoubleAttribute("r", &reflectance);
                         
                tinyxml2::XMLElement* transmitanceElement = materialTexturedElement->FirstChildElement("transmittance");
                    transmitanceElement->QueryDoubleAttribute("t", &transmitance);
                    
                tinyxml2::XMLElement* refractionElement = materialTexturedElement->FirstChildElement("refraction");
                    refractionElement->QueryDoubleAttribute("iof", &refraction);

                tinyxml2::XMLElement* textureElement = materialTexturedElement->FirstChildElement("texture");
                    name = textureElement->Attribute("name");

                std::cout << "OBJ Material" << "Name:"<< name <<std::endl; 
                
                std::unique_ptr<materialTextured> material = std::make_unique<materialTextured>(ka, kd, ks, exponent, reflectance, transmitance, refraction, name);
                //material->decodeTwoSteps(); // add texture !! 

                std::unique_ptr <Sphere> sphere = std::make_unique<Sphere>(std::move(transformations), std::move(material), radius, position);
                Builder.addMeshes(std::move(sphere));
            }
            sphereElement = sphereElement->NextSiblingElement("sphere");

        }
    }
    else {
        std::logic_error("tinyxml not initialized properly");
    }

}





void XmlParser::getMeshes(){
     if (result == tinyxml2::XML_SUCCESS && surfaceElement != nullptr) {
        meshElement = surfaceElement->FirstChildElement("mesh");
        // tinyxml2::XMLElement* positionElement{nullptr};
        tinyxml2::XMLElement* materialSolidElement{nullptr};
        tinyxml2::XMLElement* materialTexturedElement{nullptr};

        tinyxml2::XMLElement* transformElement{nullptr};
        // int posX{0}, posY{0}, posZ{0};

        int dirX{0}, dirY{0}, dirZ{0}, alpha1{0}, alpha2{0};

        // for material 
        double r{0},  g{0},  b{0};
        double ka{0}, kd{0}, ks{0}, exponent{0};
        double reflectance{0}, transmitance{0}, refraction{0};
        std::string name{}, meshName{};

        // for transform

        double translateX{0}, translateY{0}, translateZ{0},scaleX{0}, scaleY{0}, scaleZ{0};
        int rotateX{0}, rotateY{0}, rotateZ{0};

        // if (PointLightElement != nullptr){
        while (meshElement){
            meshName = meshElement->Attribute("name");
            Loader.readFile(meshName);


            materialSolidElement = meshElement->FirstChildElement("material_solid");
            materialTexturedElement = meshElement->FirstChildElement("material_textured");
            transformElement = meshElement->FirstChildElement("transform");

            // transformation vector !
            std::vector<std::unique_ptr<Transform>> transformations;
            if (transformElement != nullptr){
                tinyxml2::XMLElement* childElement = transformElement->FirstChildElement();

                while (childElement){
                    auto it = dispatcher.find(childElement->Name());
                    if (it != dispatcher.end()) {
                        it->second(childElement, transformations);

                    }
                    childElement = childElement->NextSiblingElement();

                }

        
            }
            

            if (materialSolidElement != nullptr){
                tinyxml2::XMLElement* colorElement = materialSolidElement->FirstChildElement("color");
                if (colorElement != nullptr){
                    colorElement->QueryDoubleAttribute("r", &r);
                    colorElement->QueryDoubleAttribute("g", &g);
                    colorElement->QueryDoubleAttribute("b", &b);
                }
                math::vec3 color{r, g, b};

                tinyxml2::XMLElement* phongElement = materialSolidElement->FirstChildElement("phong");
                    phongElement->QueryDoubleAttribute("ka", &ka);
                    phongElement->QueryDoubleAttribute("kd", &kd);
                    phongElement->QueryDoubleAttribute("ks", &ks);
                    phongElement->QueryDoubleAttribute("exponent", &exponent);


                tinyxml2::XMLElement* reflectanceElement = materialSolidElement->FirstChildElement("reflectance");
                    reflectanceElement->QueryDoubleAttribute("r", &reflectance);
                         
                tinyxml2::XMLElement* transmitanceElement = materialSolidElement->FirstChildElement("transmittance");
                    transmitanceElement->QueryDoubleAttribute("t", &transmitance);

                tinyxml2::XMLElement* refractionElement = materialSolidElement->FirstChildElement("refraction");
                    refractionElement->QueryDoubleAttribute("iof", &refraction);

                std::unique_ptr<materialSolid> material = std::make_unique<materialSolid>(ka, kd, ks, exponent, reflectance, transmitance, refraction, color);

                std::unique_ptr <Mesh> mesh = std::make_unique<Mesh>(std::move(transformations), std::move(material), meshName);
                mesh->setTextures(Loader.getTextures());
                mesh->setNormals(Loader.getNormals());
                mesh->setVertices(Loader.getVertices());
                mesh->setIndices(Loader.getIndicesVertices(), Loader.getIndicesTextures(), Loader.getIndicesNormals());
                Builder.addMeshes(std::move(mesh));


            }
            if (materialTexturedElement != nullptr){ 

                tinyxml2::XMLElement* phongElement = materialTexturedElement->FirstChildElement("phong");
                    phongElement->QueryDoubleAttribute("ka", &ka);
                    phongElement->QueryDoubleAttribute("kd", &kd);
                    phongElement->QueryDoubleAttribute("ks", &ks);
                    phongElement->QueryDoubleAttribute("exponent", &exponent);

                tinyxml2::XMLElement* reflectanceElement = materialTexturedElement->FirstChildElement("reflectance");
                    reflectanceElement->QueryDoubleAttribute("r", &reflectance);
                         
                tinyxml2::XMLElement* transmitanceElement = materialTexturedElement->FirstChildElement("transmittance");
                    transmitanceElement->QueryDoubleAttribute("t", &transmitance);
                    
                tinyxml2::XMLElement* refractionElement = materialTexturedElement->FirstChildElement("refraction");
                    refractionElement->QueryDoubleAttribute("iof", &refraction);

                tinyxml2::XMLElement* textureElement = materialTexturedElement->FirstChildElement("texture");
                    name = textureElement->Attribute("name");


                std::unique_ptr<materialTextured> material = std::make_unique<materialTextured>(ka, kd, ks, exponent, reflectance, transmitance, refraction, name);
                //material->decodeTwoSteps(); // add texture !! 

                std::unique_ptr <Mesh> mesh = std::make_unique<Mesh>(std::move(transformations), std::move(material), meshName);

                mesh->setTextures(Loader.getTextures());
                mesh->setNormals(Loader.getNormals());
                mesh->setVertices(Loader.getVertices());
                mesh->setIndices(Loader.getIndicesVertices(), Loader.getIndicesTextures(), Loader.getIndicesNormals());
                Builder.addMeshes(std::move(mesh));

            }


            meshElement = meshElement->NextSiblingElement("mesh");


        }

    }

    else {
        std::logic_error("tinyxml not initialized properly");
    }

}




 void XmlParser:: translateFunc(tinyxml2::XMLElement* translateElement, std::vector<std::unique_ptr<Transform>> &transformVector){
    double translateX{0}, translateY{0}, translateZ{0};
    translateElement->QueryDoubleAttribute("x", &translateX);
    translateElement->QueryDoubleAttribute("y", &translateY);
    translateElement->QueryDoubleAttribute("z", &translateZ);
    math::vec3 vec{translateX, translateY, translateY};
    std::unique_ptr<Translate> translate = std::make_unique<Translate>(vec);
    transformVector.push_back(std::move(translate));
    


};
 void XmlParser:: scaleFunc(tinyxml2::XMLElement* scaleElement, std::vector<std::unique_ptr<Transform>> &transformVector){
    double scaleX{0}, scaleY{0}, scaleZ{0};
    scaleElement->QueryDoubleAttribute("x", &scaleX);
    scaleElement->QueryDoubleAttribute("y", &scaleY);
    scaleElement->QueryDoubleAttribute("z", &scaleZ);
    math::vec3 vec{scaleX, scaleY, scaleY};
    std::unique_ptr<Scale> scale = std::make_unique<Scale>(vec);
    transformVector.push_back(std::move(scale));
    

};
 void XmlParser:: rotateXFunc(tinyxml2::XMLElement* rotateElement, std::vector<std::unique_ptr<Transform>>& transformVector){
    int angle{0};
    rotateElement->QueryIntAttribute("theta", &angle);
    std::unique_ptr<RotateX> rotate = std::make_unique<RotateX>(angle);
    transformVector.push_back(std::move(rotate));
    

};

 void XmlParser:: rotateYFunc(tinyxml2::XMLElement* rotateElement, std::vector<std::unique_ptr<Transform>> &transformVector){
    int angle{0};
    rotateElement->QueryIntAttribute("theta", &angle);
    std::unique_ptr<RotateY> rotate = std::make_unique<RotateY>(angle);
    transformVector.push_back(std::move(rotate));
    

};

 void XmlParser:: rotateZFunc(tinyxml2::XMLElement* rotateElement, std::vector<std::unique_ptr<Transform>> &transformVector){
    int angle{0};
    rotateElement->QueryIntAttribute("theta", &angle);
    std::unique_ptr<RotateZ> rotate = std::make_unique<RotateZ>(angle);
    transformVector.push_back(std::move(rotate));
    


};


std::unique_ptr<Camera> XmlParser::parseCamera(){
    // get position
        double positionZ{0}, positionY{0}, positionX{0};
        getCameraElement(positionX,positionY,positionZ);  
        math::vec3<double> position{positionX, positionY, positionZ};
    // get lookAt 
        double lookAtX{0}, lookAtY{0}, lookAtZ{0};
        getCameraLookAtElement(lookAtX,lookAtY,lookAtZ);
        math::vec3<double> lookat{lookAtX, lookAtY, lookAtZ};
    // get up
        double upX{0}, upY{0}, upZ{0};
        getUpCameraElement(upX, upY, upZ);
        math::vec3<double> up{upX, upY, upZ};
    // angle
        double angle {0};
        // camera resoluton
        double vertical {0}, horizontal {0};
        int maxBounces {0};
        getAngleCameraElement(angle);
        getResolutionCameraElement(vertical, horizontal);
        getMaxBouncesCameraElement(maxBounces);
        std::unique_ptr<Camera> camera = std::make_unique<Camera>(position,lookat,up,angle, vertical , horizontal, maxBounces);
        return  std::move(camera);

}

