//
// Created by Evgeniy Oleinik on 2019-08-02.
//

#ifndef RAY_TRACER_DIELECTRIC_H
#define RAY_TRACER_DIELECTRIC_H


#include "material.h"

class dielectric: public material {
public:
    dielectric(float ri): ref_idx(ri) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 outward_normal;
        float ni_over_nt;
        attenuation = vec3(1.0, 1.0, 1.0);
        vec3 refracted;
        float reflect_prob;
        float cosine;

        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0/ref_idx;
            cosine = - dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0;
        }
        if (drand48() < reflect_prob) {
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }
        return true;
    }

    float ref_idx;
};


#endif //RAY_TRACER_DIELECTRIC_H
