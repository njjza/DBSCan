#include <fstream>
#include <iostream>
#include "Point.cpp"
#include <vector>
#include <stdlib.h>


//this function is used for testing vector point
void print_point_vector(std::vector<Point> &a) {
   std::cout << "The vector elements x y are : ";

   for(int i=0; i < a.size(); i++){
   std::cout << a.at(i).get_x() << ' ';
   std::cout << a.at(i).get_y() << ' ';
   
   }
}




int main(int argc, char *argv[]) {
  std::cout << argv[1];
  std::cout << "I am learning C++";
  std::string filename=argv[1];
  double eps=atof(argv[2]);
  std::cout << filename;
  
  std::ifstream input(filename);
  std::vector<Point> Dataset;
  for( std::string line; getline( input, line ); )
  {
    double x, y;
    input >> x >> y;
    Point point(x,y);
    
    
    //testing
    std::cout << point.get_x();//testing
    std::cout << "|";//testing
    std::cout << point.get_y();//testing
    std::cout << eps;//testing
    std::cout << "//";//testing
    
    Dataset.push_back(point);
    
    
    print_point_vector(Dataset);//testing
    
    
    
    
    
    
    
    
    
    
    
    
    
  }
  
  
  
  
  
  
  return 0;
} 
