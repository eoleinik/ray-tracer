//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H


#include "ray.h"
#include "hitable.h"

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};


#endif //RAY_TRACER_MATERIAL_H
