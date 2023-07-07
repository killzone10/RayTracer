#pragma once
#include "transform.h"
#include "vec3.h"

class RotateY : public Transform {
    private:
        int theta{0};
    public:
        RotateY(int theta);
        void transform(math::mat4<double> &transformationMatrix, bool inverse);

};