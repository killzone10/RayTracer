#pragma once
#include "transform.h"
#include "vec3.h"

class Scale : public Transform {
    private:
        math::vec3<double> scale{};
    public:
        Scale(math::vec3<double> scale);
};