#pragma once
#include "transform.h"
#include "vec3.h"

class RotateZ : public Transform {
    private:
        int theta{0};
    public:
        RotateZ(int theta);
};