#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

using namespace std;

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

vec3 color(const ray& r, hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {  // slightly >0 to remove shadow-acne
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color(ray(rec.p, target-rec.p), world);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float w = 0.5*(unit_direction.y() + 1.0);
    return (1.0-w)*vec3(1.0, 1.0, 1.0) + w*vec3(0.5, 0.7, 1.0);
}

void draw_ppm(int nx, int ny) {
    ofstream myfile;
    myfile.open("helloworld.ppm");
    myfile << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i<nx; i++) {
            vec3 color = vec3(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * color.r());
            int ig = int(255.99 * color.g());
            int ib = int(255.99 * color.b());
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    myfile.close();
}


int main() {

    int nx = 800;
    int ny = 400;
    int ns = 100;

    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    camera cam;

    char *data=(char*)malloc(nx*ny*3);

    for (int j = ny-1; j >=0; j--) {
        for (int i = 0; i<nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s<ns; s++) {
                float u = float(i+drand48()) / float(nx);
                float v = float(j+drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); // gamma-correction
            int serial_coord = j*nx + i;
            data[serial_coord*3] = char(255.99 * col.r());
            data[serial_coord*3+1] = char(255.99 * col.g());
            data[serial_coord*3+2] = char(255.99 * col.b());
        }
    }

    stbi_write_jpg("helloworld.jpg", nx, ny, 3, data, 100);
    free(data);
    return 0;
}