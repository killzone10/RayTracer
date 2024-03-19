  #pragma once

  #include <cmath>
  #include <iomanip>
  #include <iostream>
  #include <sstream>
constexpr double PI = 3.14159265358979323846;

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
  // https://github.com/gynvael/MythTracer
  // Angle conversion.
inline double Deg2Rad(double angle) {
  return (angle * PI) / 180.0;
}

  template <typename T>
  class mat4 {  
  public:
    typedef T basetype;

    mat4 operator*(const mat4& a) {
      mat4 res;
      for (size_t j = 0; j < 4; j++) {
        for (size_t i = 0; i < 4; i++) {
          res.m[j][i] = m[j][0] * a.m[0][i] + 
                        m[j][1] * a.m[1][i] + 
                        m[j][2] * a.m[2][i] + 
                        m[j][3] * a.m[3][i];
        }
      }

      return res;
    }
        // Argument constructor that takes three vec3 objects
    mat4(){
      m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
      m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
      m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
      m[3][0] = 0;     m[3][1] = 0;     m[3][2] = 0;     m[3][3] = 1;
    }
    mat4(const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3, const vec3<T>&v4) {
      m[0][0] = v1[0]; m[0][1] = v2[0]; m[0][2] = v2[0]; m[0][3] = v4[0];
      m[1][0] = v1[1]; m[1][1] = v2[1]; m[1][2] = v2[1]; m[1][3] = v4[1];
      m[2][0] = v1[2]; m[2][1] = v2[2]; m[2][2] = v3[2]; m[2][3] = v4[2];
      m[3][0] = 0;     m[3][1] = 0;     m[3][2] = 0;     m[3][3] = 1;
    }
    mat4& operator*=(const mat4& a) {
      mat4 res = *this * a;
      *this = res;
      return *this;
    } 

    // Note: The fourth element of the vector is always assumed to be 1.
  //   template<typename U>
  //   vec3<U> operator*(const vec3<U>& a) {
  //     return vec3<U>{
  //       m[0][0] * a.vec[0] + m[0][1] * a.vec[1] + m[0][2] * a.vec[2] + m[0][3],
  //       m[1][0] * a.vec[0] + m[1][1] * a.vec[1] + m[1][2] * a.vec[2] + m[0][3],
  //       m[2][0] * a.vec[0] + m[2][1] * a.vec[1] + m[2][2] * a.vec[2] + m[0][3]
  //     };
  //   }
    template<typename U>
      vec3<U> operator*(const vec3<U>& a)  {
        return vec3<U>{
          m[0][0] * a.vec[0] + m[0][1] * a.vec[1] + m[0][2] * a.vec[2] + m[0][3],
          m[1][0] * a.vec[0] + m[1][1] * a.vec[1] + m[1][2] * a.vec[2] + m[0][3],
          m[2][0] * a.vec[0] + m[2][1] * a.vec[1] + m[2][2] * a.vec[2] + m[0][3]
        };
      }


      void setFromVectors(const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3, const vec3<T>&v4) {
      m[0][0] = v1[0]; m[0][1] = v2[0]; m[0][2] = v3[0]; m[0][3] = v4[0];
      m[1][0] = v1[1]; m[1][1] = v2[1]; m[1][2] = v3[1]; m[1][3] = v4[1];
      m[2][0] = v1[2]; m[2][1] = v2[2]; m[2][2] = v3[2]; m[2][3] = v4[2];
      m[3][0] = 0;     m[3][1] = 0;     m[3][2] = 0;     m[3][3] = 1;
    }

    void ResetIdentity() {
      for (size_t j = 0; j < 4; j++) {
        for (size_t i = 0; i < 4; i++) {
          m[j][i] = (i == j) ? 1.0 : 0.0;
        }
      }
    }

    // void ResetRotationXRad(T angle) {
    //   *this = { 
    //     1.0, 0.0, 0.0, 0.0,
    //     0.0, cos(angle), -sin(angle), 0.0,
    //     0.0, sin(angle), cos(angle), 0.0,
    //     0.0, 0.0, 0.0, 1.0
    //   };
    // }
    void setRotationX(T angle) {
      m[0][0] = 1.0;
      m[0][1] = 0.0;
      m[0][2] = 0.0;
      m[0][3] = 0.0;
      m[1][0] = 0.0;
      m[1][1] = cos(angle);
      m[1][2] = -sin(angle);
      m[1][3] = 0.0;
      m[2][0] = 0.0;
      m[2][1] = sin(angle);
      m[2][2] = cos(angle);
      m[2][3] = 0.0;
      m[3][0] = 0.0;
      m[3][1] = 0.0;
      m[3][2] = 0.0;
      m[3][3] = 1.0;
  }
  void setRotationY(T angle) {
    m[0][0] = cos(angle);
    m[0][1] = 0.0;
    m[0][2] = sin(angle);
    m[0][3] = 0.0;
    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = 0.0;
    m[1][3] = 0.0;
    m[2][0] = -sin(angle);
    m[2][1] = 0.0;
    m[2][2] = cos(angle);
    m[2][3] = 0.0;
    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
  }

void setRotationZ(T angle) {
    m[0][0] = cos(angle);
    m[0][1] = -sin(angle);
    m[0][2] = 0.0;
    m[0][3] = 0.0;
    m[1][0] = sin(angle);
    m[1][1] = cos(angle);
    m[1][2] = 0.0;
    m[1][3] = 0.0;
    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;
    m[2][3] = 0.0;
    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
  }

    void ResetRotationYRad(T angle) {
      *this = { 
        cos(angle), 0.0, sin(angle), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(angle), 0.0, cos(angle), 0.0,
        0.0, 0.0, 0.0, 1.0
      };
    }

    void ResetRotationZRad(T angle) {
      *this = { 
        cos(angle), -sin(angle), 0.0, 0.0,
        sin(angle), cos(angle), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 
      };
    }

    static mat4<T> RotationXRad(T angle) {
      mat4<T> m;
      m.ResetRotationXRad(angle);
      return m;
    }

    static mat4<T> RotationYRad(T angle) {
      mat4<T> m;
      m.ResetRotationYRad(angle);
      return m;
    }

    static mat4<T> RotationZRad(T angle) {
      mat4<T> m;
      m.ResetRotationZRad(angle);
      return m;
    }

    static mat4<T> RotationXDeg(T angle) {
      mat4<T> m;
      m.ResetRotationXRad(Deg2Rad(angle));
      return m;
    }

    static mat4<T> RotationYDeg(T angle) {
      mat4<T> m;
      m.ResetRotationYRad(Deg2Rad(angle));
      return m;
    }

    static mat4<T> RotationZDeg(T angle) {
      mat4<T> m;
      m.ResetRotationZRad(Deg2Rad(angle));
      return m;
    }

    // static mat4 scale(T scaleX, T scaleY, T scaleZ) {
    //       return mat4(scaleX, 0, 0, 0,
    //                   0, scaleY, 0, 0,
    //                   0, 0, scaleZ, 0,
    //                   0, 0, 0, 1);
    //   } //its scale matrix

       void scale(T scaleX, T scaleY, T scaleZ) {
        m[0][0] = scaleX;
        m[1][1] = scaleY;
        m[2][2] = scaleZ;
        m[3][3] = 1.0;
    }


    void translate(const vec3<T>& translation) {
      m[0][3] += translation.x();
      m[1][3] += translation.y();
      m[2][3] += translation.z();
    }

    template <typename U> 
    friend std::ostream& operator<<(std::ostream &os, const mat4<U>& a);

    T m[4][4]{};
  };


  template <typename T>
  std::ostream& operator<<(std::ostream &os, const mat4<T>& a) {
    os << std::fixed << std::setprecision(5)
      << "[  " << a.m[0][0] << ", " << a.m[0][1] << ", "
                << a.m[0][2] << ", " << a.m[0][3] << "   \n"
      << "   " << a.m[1][0] << ", " << a.m[1][1] << ", "
                << a.m[1][2] << ", " << a.m[1][3] << "   \n"
      << "   " << a.m[2][0] << ", " << a.m[2][1] << ", "
                << a.m[2][2] << ", " << a.m[2][3] << "   \n"
      << "   " << a.m[3][0] << ", " << a.m[3][1] << ", "
                << a.m[3][2] << ", " << a.m[3][3] << "  ]\n";
    return os;
  }
  };


