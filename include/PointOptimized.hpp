#ifndef Point_H
#define Point_H

#ifndef POINT_UNDEFIEND
#define POINT_UNDEFINED 0xffffffff
#endif

#include <iostream>
#include <vector>
struct Point {
     double              x;
     double              y;
     unsigned int        grp_id;
};

double get_distance(Point p1, Point p2);
double get_distance(Point p, double x, double y);

#endif