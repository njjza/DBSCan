//main function TODO:better revise it in another file
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

#include "include/DataGenerator.hpp"
#include "include/PointsOptimized.hpp"
#include "include/DBSCanOptimized.hpp"

void read_file(Points p);

int main() {

  double eps=2.0;
  unsigned int MinPts=3;

  Points p;
  read_file(p);
  DBSCan(p, eps, MinPts);

  //std::sort(Dataset.begin(),Dataset.end(), comparator);
  //print_point_vector(Dataset);//testing
  return 0;
}

void read_file(Points p) {
  std::string filePath = "Data/sample.dat";

  std::ifstream input(filePath);
  std::string line;

  while(input)
  {
    getline(input, line);
    double x, y;
    input >> x >> y;
    p.add_point(x, y);
    
    //the last line will not be push twice because of the getline() problem in c++
    if(input.fail()){
        break;
    }
  }
}
