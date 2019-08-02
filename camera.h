//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "ray.h"

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while(p.squared_length() > 1.0);
    return p;
}

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vecup, float vfov, float aspect, float aperture, float focus_dist) {
        lens_radius = aperture/2;
        float theta = vfov*M_PI/180.0;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        w = unit_vector(lookfrom-lookat);
        u = unit_vector(cross(vecup, w));
        v = cross(w, u);

        origin = lookfrom;
        upper_left_corner = origin + focus_dist*(-half_width*u + half_height*v - w);
        horizontal = 2*half_width*focus_dist*u;
        vertical = 2*half_height*focus_dist*v;
    }

    ray get_ray(float s, float t) {
        vec3 rd = lens_radius*random_in_unit_disk();
        vec3 offset = u*rd.x() + v*rd.y();
        return ray(origin + offset, upper_left_corner + s*horizontal - t*vertical - origin - offset);
    };

    vec3 upper_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
    vec3 u, v, w;
    float lens_radius;

};


#endif //RAY_TRACER_CAMERA_H
