#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace math{

template <typename T> 
class vec3 {
    public:
        //base constructor

        vec3():vec{0.0, 0.0 ,0.0}{};    
        // argument constructor
        vec3(T x, T y, T z) : vec{x, y, z} { };  
        // copy concstructor
        vec3(const vec3& v): vec{v.vec[0], v.vec[1], v.vec[2]}{};

        // r value // 
        vec3(vec3&& v) : vec{v.vec[0], v.vec[1], v.vec[2]} { };

        T operator [](int i) const {return vec[i];};
        T& operator [] (int i){return vec[i];};
        // getters 
        T& x() { return vec[0]; }
        T& y() { return vec[1]; }
        T& z() { return vec[2]; }
        // rgb too
        T& r() { return vec[0]; }
        T& g() { return vec[1]; }
        T& b() { return vec[2]; }

        const T& x() const { return vec[0]; }
        const T& y() const { return vec[1]; }
        const T& z() const { return vec[2]; }

        const T& r() const { return vec[0]; }
        const T& g() const { return vec[1]; }
        const T& b() const { return vec[2]; }  

        // simple operations +, -, 
        // point – point = vector
        // • point + vector = point
        // • vector operations:
        // – vector + vector = vector
      
         // point - point = vector
        // vectoir - vector = vector
        vec3 operator-() const { // negate
            return vec3{-vec[0], -vec[1], -vec[2]};
        }
        // vector + vector output vector
        vec3 operator+(const vec3& a) const {
            return vec3{vec[0] + a.vec[0], vec[1] + a.vec[1], vec[2] + a.vec[2]};
        }

        // vector + vector
        vec3& operator+=(const vec3& a) {
            vec[0] += a.vec[0]; vec[1] += a.vec[1]; vec[2] += a.vec[2];
            return *this;
        }

        // point - point = vector 
         vec3 operator-(const vec3& a) const {
            return vec3{vec[0] - a.vec[0], vec[1] - a.vec[1], vec[2] - a.vec[2]};
        }
        // nothing changes
        vec3 operator+() const {
                return *this;
        }
        
        // vector - vector
        vec3& operator-=(const vec3& a) {
            vec[0] -= a.vec[0]; vec[1] -= a.vec[1]; vec[2] -= a.vec[2];
            return *this;
        }

        // multiplication
        // – scalar * vector = vector
        // – vector ⋅ vector = scalar, dot product
        // – vector × vector =  vector, the cross product
        //scalar ones 

        vec3& operator*=(T a) {
            vec[0] = vec[0] * a; vec[1] = vec[1] *a; vec[2] = vec[2] *a;
            return *this;
        }

        vec3& operator/=(T a) {
            vec[0] = vec[0] / a; vec[1] = vec[1] /a; vec[2] = vec[2] /a;
            return *this;
        }

        vec3 operator*(T n) const {
            return vec3{vec[0] * n, vec[1] * n, vec[2] * n};
        }

        vec3 operator/(T n) const {
            return vec3{vec[0] / n, vec[1] / n, vec[2] / n};
        }


        // vector ones
        vec3 operator*(const vec3& a) const {
            return vec3{vec[0] * a.vec[0], vec[1] * a.vec[1], vec[2] * a.vec[2]};
        }

        vec3& operator*=(const vec3& a) {
            vec[0] *= a.vec[0]; vec[1] *= a.vec[1]; vec[2] *= a.vec[2];
            return *this;
        }

        vec3 operator/(const vec3& a) const {
            return vec3{vec[0] / a.vec[0], vec[1] / a.vec[1], vec[2] / a.vec[2]};
        }


        vec3& operator/=(const vec3& a) {
            vec[0] = a.vec[0] / vec[0]; vec[1] = a.vec[1] / vec[1]; vec[2] = a.vec[2] / vec[2];
            return *this;
        }

        vec3& operator=(const vec3& a) {
            vec[0] = a.vec[0]; vec[1] = a.vec[1] ; vec[2] = a.vec[2];
            return *this;
        }
        vec3& operator=(T  n) {
            vec[0] = n; vec[1] = n ; vec[2] = n;
            return *this;
        }
      
        T SqrLenght() const{
            return pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2);
        }

        T Lenght() const {
            return sqrt(SqrLenght());
        }

        T dotProduct(const vec3& a) const {
            return vec[0] * a.vec[0] +
                   vec[1] * a.vec[1] +
                   vec[2] * a.vec[2]; 
        }
        
        // i j k
        // ax ay az
        // bx by bz  i(aybz -azby) + j (azbx - axbz) +k(axby - aybx)
        vec3 crossProduct (const vec3&a) const {
            return vec3(vec[1] * a.vec[2] - vec[2] *a.vec[1],
                        vec[2] * a.vec[0] - vec[0] * a.vec[2],
                        vec[0] * a.vec[1] - vec[1] * a.vec[0]);
        }


        void normalize (){
            auto lenght = Lenght();
            vec[0] /= lenght; vec[1]/=lenght; vec[2] /= lenght;
        }

        void nullIt(){
            vec[0] = 0; vec[1] = 0; vec[2] = 0;

        }
    template <typename F> 
    friend std::ostream& operator<<(std::ostream &os, const vec3<F>& a);

    T vec[3]{};

    vec3 save_color(){
        return vec3(static_cast<int>(255.999 * vec[0]), static_cast<int>(255.999 * vec[1]),static_cast<int>(255.999 * vec[2]));
    }
};
    template <typename T>
    std::ostream& operator<<(std::ostream &os, const vec3<T>& a) {
        os << std::fixed << std::setprecision(5) 
        << a.vec[0] << ", " << a.vec[1] << ", " << a.vec[2];
        return os;
}


};