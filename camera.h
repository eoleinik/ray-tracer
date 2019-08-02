//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "ray.h"

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vecup, float vfov, float aspect) {
        vec3 u, v, w;
        float theta = vfov*M_PI/180.0;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        w = unit_vector(lookfrom-lookat);
        u = unit_vector(cross(vecup, w));
        v = cross(w, u);

        origin = lookfrom;
        upper_left_corner = origin - half_width*u + half_height*v - w;
        horizontal = 2*half_width*u;
        vertical = 2*half_height*v;
    }

    ray get_ray(float s, float t) {return ray(origin, upper_left_corner + s*horizontal - t*vertical - origin);};

    vec3 upper_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;

};


#endif //RAY_TRACER_CAMERA_H
