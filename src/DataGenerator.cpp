//#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "../include/DataGenerator.hpp"

void generate_data(double range, unsigned int size, std::string const& type) {
    std::fstream fs;
    if(type == "new") {
        fs.open("../Data/sample.dat", std::ios::out | std::ios::trunc);
        fs << "x y\n";
    }
    else {
        fs.open("../Data/sample.dat", std::ios::out | std::ios::app);
    }

    for(unsigned int i = 0; i < size; i++) {
        double a = rand_float(-range, range);
        double b = rand_float(-range, range);
        fs << a << " " << b;
        fs << "\n";
    }
}

void generate_data(double range, unsigned int size, double delta) {
    std::fstream fs;
    double range_p, range_n;

    fs.open("../Data/sample.dat", std::ios::out | std::ios::app);

    range_p = range + delta;
    range_n = range - delta;

    for (unsigned int i = 0; i < size; i++) {
        double a = rand_float(range_n, range_p);
        double b = rand_float(range_n, range_p);

        fs << a << " " << b;
        fs << "\n";
    }
}

double rand_float(double a, double b) {
	return ((double)rand() / RAND_MAX) * (b - a) + a;
}