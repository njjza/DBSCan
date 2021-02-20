#include <iostream>
#include <fstream>
#include <stdlib.h>

double rand_float(double, double);

int main() {
    std::fstream fs;
    fs.open("Data/sample.dat", std::fstream::in | std::fstream::app);
    fs << "x, y\n";

    for(int i = 0; i < 100; i++) {
        double a = rand_float(-5.0, 5.0);
        double b = rand_float(-5.0, 5.0);
        fs << a << ", " << b;
        fs << "\n";
    }
    
    return 0;
}

double rand_float(double a, double b) {
	return ((double)rand() / RAND_MAX) * (b - a) + a;
}