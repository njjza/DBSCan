//main function TODO:better revise it in another file
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

#include "include/DBSCanOptimized.hpp"

void read_file(std::vector<Point> p);

int main() {
  double eps=2.0;
  unsigned int MinPts=3;
  
  std::vector<Point> p;
  p.reserve(10);

  read_file(p);
  DBSCan(p, eps, MinPts);

  //std::sort(Dataset.begin(),Dataset.end(), comparator);
  //print_point_vector(Dataset);//testing
  return 0;
}

void read_file(std::vector<Point> pVec) {
  std::string filePath = "Data/sample.dat";
  std::ifstream input(filePath);
  std::string line;

  while(input)
  {
    getline(input, line);
    double x, y;
    input >> x >> y;
    
    Point p;
    p.x = x;
    p.y = y;
    pVec.push_back(p);
    
    //the last line will not be push twice because of the getline() problem in c++
    if(input.fail()){
        break;
    }
  }
}
