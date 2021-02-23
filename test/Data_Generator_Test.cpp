#include "../include/DataGenerator.hpp"
#include <math.h>

int main() {
    generate_data(100000, pow(2, 12), "new");
    return 0;
}