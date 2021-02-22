#ifndef Point_H
#define Point_H

#include <vector>
class Point {
     double x, y; //attributes denotes the position on x, and y axis.
     int cluster; //attributes denotes which cluster it belongs to.
     bool visited; //0 is not visited 1=visited

    public:
     Point();
     Point(double x, double y);
     
     void set_cluster(int group_id);
     
     bool is_visited();
     void undo_visited();
     void mark_visited();

     int get_cluster();
     double get_x();
     double get_y();
     double get_distance(Point p);
     double get_distance(double x, double y);
     std::vector<double> get_pos();
};

#endif