//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_HITABLE_H
#define RAY_TRACER_HITABLE_H

#include "ray.h"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //RAY_TRACER_HITABLE_H
