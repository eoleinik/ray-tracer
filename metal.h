//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_METAL_H
#define RAY_TRACER_METAL_H


#include "material.h"

class metal: public material {
public:
    metal(const vec3& a): albedo(a) {};
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }
    vec3 albedo;
};

#endif //RAY_TRACER_METAL_H
