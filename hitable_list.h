//
// Created by Evgeniy Oleinik on 2019-08-01.
//

#ifndef RAY_TRACER_HITABLE_LIST_H
#define RAY_TRACER_HITABLE_LIST_H

#include "hitable.h"

class hitable_list: public hitable {
public:
    hitable_list() {}
    hitable_list(hitable **l, int n) {list = l; list_size = n;}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    hitable **list;
    int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_hit = t_max;
    for (int i=0; i<list_size; i++) {
        if (list[i]->hit(r, t_min, closest_hit, temp_rec)) {
            hit_anything = true;
            closest_hit = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}


#endif //RAY_TRACER_HITABLE_LIST_H
