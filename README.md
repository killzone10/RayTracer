
# Ray Tracer

This is RayTracer project done at University Vienna course "Foundation of Computer Graphics".
The main idea was to parse XML, which contained the information about the picture and then cast rays to detect objects and save it to PNG file.

What was done:
- camera
- triangle intersection
- sphere intersection
- sphere textures
- triangle textures
- camera movement
- object movement (transforming the rays, because its less expensive)

# Build
How to build:

    - be in the main directory,
    - mkdir build
    - cd build
    - cmake ..\CMakeLists.txt  
    - cmake --build . --target ALL_BUILD  --config Release
    
on Windows the program is in build/Debug/ray_tracer.exe // on linux in the main directory
Paths should work if not check the /scenes file.

# Execution
How to execute:

- ray_tracer -filename e.g .\ray_tracer.exe example1.xml
- If executed without arguments nothing will happen.
- The outfiles are saved in the directory where executable file is.



# Requirments
C ++ 17 is  required to run this program. My building environment was: 

Edition	Windows 10 Education N
Version	22H2
Installed on	‎02/‎09/‎2021
OS build	19045.2965
Experience	Windows Feature Experience Pack 1000.19041.1000.0


# Samples

![Spheres](example3.png)
![OBJ with refraction](example5.png)
![Textures](example6.png)
![Moving camera](example7.png)
![Spheres with textures](example8.png)
![Transforming Objects (implemented as translating rays)](example91.jpg)
# TO DO
Optimization + parallelization
