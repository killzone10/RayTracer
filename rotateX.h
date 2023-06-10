#pragma once
#include "transform.h"
#include "vec3.h"

class RotateX : public Transform {
    private:
        int theta{0};
    public:
        RotateX(int theta);
};