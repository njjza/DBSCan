#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "../include/Random_Generator.hpp"

void generate_data(int range, unsigned int size, std::string& type) {
    std::ofstream fs;
    if(type == "new") {
        fs.open("Data/sample.dat", std::ios::out | std::ios::trunc);
    }
    else {
        fs.open("Data/sample.dat", std::ios::out | std::ios::app);
    }

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