#pragma once
#include <iostream>
#include "vec3.h"
class Transform{
    public:
        void print();
        virtual void transform(math::mat4<double> &m,  bool inverse);
}
;