#pragma once
#include "transform.h"
#include "vec3.h"

class Translate : public Transform {
    private:
        math::vec3<double> translate{};
    public:
        Translate(math::vec3<double> translate);
};