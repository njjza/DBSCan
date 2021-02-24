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
  std::vector<unsigned int> iVec = DBSCan(p, eps, MinPts);
  return 0;
}

void read_file(std::vector<Point> pVec) {
  std::string filePath = "../data/sample.dat";
  std::ifstream input(filePath);
  std::string line;
  double x, y;
  Point p1;

  for(;;)
  {
    getline(input, line);
    
    input >> x >> y;
    p1.x = x;
    p1.y = y;
    pVec.push_back(p1);

    if(input.fail()){
        break;
    }

    std::cout << "<" << p1.x << ", " << p1.y << ">" << "\n";
    //the last line will not be push twice because of the getline() problem in c++
  }
}
