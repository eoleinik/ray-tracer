//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "hitable.h"

class sphere: public hitable {
public:
    sphere() {}
    sphere(vec3 cen, float r, material* mat_pointer) {center = cen; radius = r; material = mat_pointer;}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 center;
    float radius;
    material* material;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        float root = (-b - sqrt(discriminant)) / (2.0*a);
        if (t_min < root && root < t_max) {
            rec.t = root;
            rec.p = r.point_at_parameter(root);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
        root = (-b + sqrt(discriminant)) / (2.0*a);
        if (t_min < root && root < t_max) {
            rec.t = root;
            rec.p = r.point_at_parameter(root);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }
    return false;
}

#endif //RAY_TRACER_SPHERE_H
