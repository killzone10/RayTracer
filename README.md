Ray Tracer part 1:
    T1:
        Its implemented, because example1-3 are implemented. If there is neccessity to check it you can uncomment the T1 Code in the main
        How the code works: the sceneBuilder is responsible for creating a scene, so by using Builder.addxxx() functions you can add things to the scene.
    T2:
        The same as T1 just uncomment the  code in main with T2 label
    T3:
        Done - used TinyXML. Entire reading is actually done. Surface is parent class of mesh and sphere. Vector of meshes and spheres is stored in the "scene" class. The same is with the Light(parent), rest of lights are children and are stored in vector in scenes class.
    T4:
        Its done in the rayTracer.cpp --> scene.cpp checkGlobalIntersections  --> surface.cpp checkIntersection. I implemented it with slides and 
        with https://raytracing.github.io/books/RayTracingInOneWeekend.html, I cited in the code where it was used.

    T5:
         done - added casting shadow ray in scene.cpp  checkGlobalIntersections 


I have used c ++ 17 its minimal requirment to run this program. My building environment was: 

Edition	Windows 10 Education N
Version	22H2
Installed on	‎02/‎09/‎2021
OS build	19045.2965
Experience	Windows Feature Experience Pack 1000.19041.1000.0

but it also worked on almigty.

How to build that:
    - be in the main directory,
    - mkdir build
    - cd build
    - cmake ..\CMakeLists.txt  windows   or cmake ../CMakeLists.txt  linux
    - cmake --build .  for windows   or cmake --build .. for Linux

on Windows the program is in build/Debug/ray_tracer.exe // on linux in the main directory

How to execute:
ray_tracer -filename e.g .\ray_tracer.exe example1.xml
If executed without arguments nothing will happen.
The outfiles are saved in the directory where executable file is.

If something does not work I can deliver my task.json file, so there is possibility to build it from the scratch.


How things work in this program:
    First of all the files which want to be  read should be in "scenes" file just because in the beggining of main I enforce that from the user (filesystem::path).
    XmlParser is main object which parse xml (used tinyxml2 library). Inside the parser I create sceneBuilder instantion.
    SceneBuilder insantion is responsible for creating a scene - so everything that is added to scene is added through the builder. It is possible through builder methods  to return a pointer to the scene.

    Scene consists of many objects  the most crucial ones are: lights, surfaces and camera.
    The surfaces are divided on meshes and spheres, both of them contains vector with transformations objects (Rotate, Translate, Scale), Material object and their own specific variables. Everything from xml was read properly and its inside the "scene" object.
    Lighs consist of 4 types of lights: ambient, spot, parallel and point. Everyone of them is different object which is child of Light Class.

    In the main I have created RayTracer instation, which needs a pointer to the scene. Inside this object raytracing happens render() fuction which is rensponsible of returning a color it launches a trace function which checks for intersections.

    Intersection check is implemented in sphere.cpp (checkIntersection).
    Summing of the lights is done in scene.cpp .

    



