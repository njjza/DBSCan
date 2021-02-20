/**
 * @file    Point.cpp
 * @author  Henry Jiang 2/19/2021
 * @version 1.0        
 * 
 * Describe:    Implemented a point class, which contains value x, y, and integer value cluster. 
 *              It also contains function get_pos(), andget_distance().
 * 
 *              The parameters denotes a point at a 2-d euclidean space, and the cluster denots
 *              which group it falls into. If no extension is been defined, the default should
 *              be 0.
**/
#include <vector>
#include <math.h>

class Point {
    double x, y;
    int cluster;

    public:
     Point() {
         this->x = 0;
         this->y = 0;
         this->cluster = 0;
     }
     Point(double x, double y) {
         this->x = x;
         this->y = y;
     }

     void set_cluster(int x) {
         this->cluster = 0;
     }

     double get_x() {
         return this->x;
     }

     double get_y() {
         return this->y;
     }

     std::vector<double> get_pos() {
         std::vector<double> a = {this->x, this->y};
         return a;
     }

     double get_distance(Point* p) {
         double delta_x = this->x - p->get_x();
         double delta_y = this->y - p->get_y();

         double result = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
         return result;
     }
};