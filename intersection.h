#pragma once
#include "vec3.h"
#include "ray.h"
// https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/anabstractionforhittableobjects
class Intersection{
    private:
        math::vec3 <double> point;
        math::vec3 <double> normal;
        // material solid
        math::vec3 <double> color;
        // materia ltextured
        std::string name{};
        /// material
        double t;
        double ka {0};
        double ks{0};
        double kd{0};
        double exponent {0};
        double reflectance{0};
        double transmitance {0};
        double refraction {0};
        bool isFront{};

    public:
        Intersection();
        Intersection(math::vec3 <double> point, math::vec3 <double> normal, double t);
        void setPoint(math::vec3<double>point);
        void setNormal(math::vec3<double>normal);
        void setRoot(double root);
        void setMaterialCoefficients(double ka, double kd, double ks, double exponent);
        void setReflectanceTransmitanceRefraction(double reflectance, double transmitance, double refraction);


        void setT(double t);

        void setColors(math::vec3<double> colors);
        void setName(std::string name);

        math::vec3<double> getPosition();
        math::vec3<double> getColor();
        math::vec3<double> getNormal();
        double getRoot();
        double getKa();
        double getKs();
        double getKd();
        double getExponent();
        double getReflectance();
        double getTransmitance();
        double getRefraction();
        void setFront(Ray *r, math::vec3 <double> & outward_normal);

};