/**
 * @file    Point.cpp
 * @author  Henry Jiang 2/19/2021
 * @author  Mingcheng Wur 2/19/2021
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
    int is_visited;//0 is not visited 1=visited

    public:
     Point() {
         this->x = 0;
         this->y = 0;
         this->cluster = 0;
         this->is_visited=0;
     }
     Point(double x, double y) {
         this->x = x;
         this->y = y;
         this->cluster = 0;
         this->is_visited=0;
     }

     void set_cluster(int x) {
         this->cluster = x;
     }
     
     //mark as visited
     void mark_visited() {
         this->is_visited = 1;
     }
     
     //mark as noise
     void mark_noise() {
         this->is_visited = 2;
     }
     
     
     
     //undo visited
     void undo_visited() {
         this->is_visited = 0;
     }
     
     int if_visited() {
         return this->is_visited;
     }
     
     double get_x() {
         return this->x;
     }

     double get_y() {
         return this->y;
     }
     
     
     double get_cluster() {
         return this->cluster;
     }
     
     std::vector<double> get_pos() {
         return {this->x, this->y};
     }

     double get_distance(Point* p) {
         double delta_x = this->x - p->get_x();
         double delta_y = this->y - p->get_y();

         double result = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
         return result;
     }
     
     double get_distanceviaxy(int x1,int y1) {
         double delta_x = x - x1;
         double delta_y = y - y1;

         double result = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
         return result;
     }
};
