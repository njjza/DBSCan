#include <iostream>
#include <fstream>
#include <stdlib.h>

double rand_float(double, double);

void generate_data(int range, unsigned int size) {
    std::ofstream fs;
    fs.open("Data/sample.dat", std::fstream::out | std::ios::trunc);
    fs << "x y\n";

    for(unsigned int i = 0; i < size; i++) {
        double a = rand_float(-range, range);
        double b = rand_float(-range, range);
        fs << a << " " << b;
        fs << "\n";
    }
}

double rand_float(double a, double b) {
	return ((double)rand() / RAND_MAX) * (b - a) + a;
}