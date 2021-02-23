#ifndef Point_H
#define Point_H

#include <iostream>
#include <vector>
class Points {
     std::vector<std::vector<double>> pos; //attributes denotes the position on x, and y axis.
     std::vector<unsigned int> clusters; //attributes denotes which cluster it belongs to.
     std::vector<bool> visited; //0 is not visited 1=visited

    public:
     void add_point(double x, double y);

     std::vector<double> get_pos(unsigned int i);
     size_t size();

     void set_cluster(unsigned int i, unsigned int group_id);
     void mark_visited(unsigned int i);
     void undo_visited(unsigned int i);
     bool is_visited(unsigned int i);

     int get_cluster(unsigned int i);
     double get_distance(unsigned int i1, unsigned int i2);
     double get_distance(unsigned int i, double x, double y);
     
};

#endif