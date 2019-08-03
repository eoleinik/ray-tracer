#include <iostream>
#include <fstream>
#include <vector>
#include "vec3.h"
#include "ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb/stb_image_write.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

using namespace std;

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {  // slightly >0 to remove shadow-acne
        ray scattered;
        vec3 attenuation;
        if (depth < 10 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        }
        return vec3(0, 0, 0);
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

hitable *random_scene() {
    int n = 500;
    auto list = new hitable*[n + 1];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
            if ((center-vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) { // matte
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                } else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                            new metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48()));
                } else { //glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(-4, 1, 0), 1, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(0, 1, 0), 1, new dielectric( 1.5));
    list[i++] = new sphere(vec3(4, 1, 0), 1, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    return new hitable_list(list, i);
}


int main() {

    int nx = 800;
    int ny = 400;
    int ns = 100;

    auto world = random_scene();

    vec3 lookfrom(10, 2, 4);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = (lookfrom-lookat).length();
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 30, float(nx)/float(ny), aperture, dist_to_focus);

    vector<char> data(nx*ny*3);
    int prev_percentage = 0;

    for (int j = ny-1; j >=0; j--) {
        for (int i = 0; i<nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s<ns; s++) {
                float u = float(i+drand48()) / float(nx);
                float v = float(j+drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); // gamma-correction
            int serial_coord = j*nx + i;
            data[serial_coord*3] = char(255.99 * col.r());
            data[serial_coord*3+1] = char(255.99 * col.g());
            data[serial_coord*3+2] = char(255.99 * col.b());
        }
        float percentage = (ny-j)/float(ny)*100.0;
        if (prev_percentage < int(percentage)) {
            prev_percentage = int(percentage);
            cout<<prev_percentage<<"%\n";
        }
    }

    stbi_write_jpg("helloworld.jpg", nx, ny, 3, data.data(), 100);
    return 0;
}
