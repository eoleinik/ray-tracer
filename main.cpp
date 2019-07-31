#include <iostream>
#include <fstream>
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

using namespace std;

int main() {


//    stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);


    int nx = 400;
    int ny = 200;

//    ofstream myfile;
//    myfile.open("helloworld.ppm");
//    myfile << "P3\n" << nx << " " << ny << "\n255\n";
//    for (int j = ny-1; j >= 0; j--) {
//        for (int i = 0; i<nx; i++) {
//            vec3 color = vec3(float(i) / float(nx), float(j) / float(ny), 0.2);
//            int ir = int(255.99 * color.r());
//            int ig = int(255.99 * color.g());
//            int ib = int(255.99 * color.b());
//            myfile << ir << " " << ig << " " << ib << "\n";
//        }
//    }
//    myfile.close();

    char *data=(char*)malloc(nx*ny*3);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i<nx; i++) {
            vec3 color = vec3(float(i) / float(nx), float(j) / float(ny), 0.2);
            int serial_coord = j*nx + i;
            data[serial_coord*3] = char(255.99 * color.r());
            data[serial_coord*3+1] = char(255.99 * color.g());
            data[serial_coord*3+2] = char(255.99 * color.b());
        }
    }

    stbi_write_jpg("helloworld.jpg", nx, ny, 3, data, 100);

    return 0;
}