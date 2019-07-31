#include <iostream>
#include <fstream>
#include "vec3.h"

using namespace std;

int main() {
    ofstream myfile;
    myfile.open("helloworld.ppm");


    int nx = 400;
    int ny = 200;
    myfile << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i<nx; i++) {
            vec3 color = vec3(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99)*color.r();
            int ig = int(255.99)*color.g();
            int ib = int(255.99)*color.b();
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    myfile.close();
    return 0;
}