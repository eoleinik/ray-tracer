//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "ray.h"

class camera {
public:
    camera(float vfov, float aspect) {
        float theta = vfov*M_PI/180;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        upper_left_corner = vec3(-half_width, half_height, -1.0);
        horizontal = vec3(2*half_width, 0.0, 0.0);
        vertical = vec3(0.0, -2*half_height, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    ray get_ray(float u, float v) {return ray(origin, upper_left_corner + u*horizontal + v*vertical);};

    vec3 upper_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;

};


#endif //RAY_TRACER_CAMERA_H
