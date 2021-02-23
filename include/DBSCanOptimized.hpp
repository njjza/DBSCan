#ifndef DBS_CAN_H
#define DBS_CAN_H

#include <vector>
#include "PointOptimized.hpp"

std::vector<Point> rangeQuery(std::vector<Point> &Dataset, Point& p, double eps);
void DBSCan (std::vector<Point> &Dataset, double eps, unsigned int Minpts);
bool comparator(Point a, Point b);

#endif
