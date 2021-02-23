#ifndef Point_H
#define Point_H

#include <iostream>
#include <vector>
class Points {
     std::vector<std::vector<double>> pos; //attributes denotes the position on x, and y axis.
     std::vector<int> clusters; //attributes denotes which cluster it belongs to.
     std::vector<bool> visited; //0 is not visited 1=visited

    public:
     Points();
     void add_point(double x, double y);

     std::vector<double> get_pos(unsigned int i);

     void set_cluster(unsigned int pos, unsigned int group_id);
     void mark_visisted(unsigned int pos);
     void undo_visited(unsigned int pos);
     bool is_visited(unsigned int pos);

     int get_cluster(unsigned int pos1, unsigned int pos2);
     double get_distance(unsigned int pos1, unsigned int pos2);
     double get_distance(unsigned int pos, double x, double y);
     
};

#endif