#ifndef DBS_CAN_H
#define DBS_CAN_H

#include <vector>
#include "PointOptimized.hpp"

void Clusterjoin(std::vector<int> &Neighbor1,std::vector<int> &Neighbor,std::vector<Point> &Dataset,int clusterNo);
std::vector<Point> rangeQuery(std::vector<Point> &Dataset, int j, double eps);
void expendCluster(std::vector<Point>& Dataset, std::vector<int>& Neighbor, double eps, int Minpts, int clusterNo);
void DBSCan (std::vector<Point> &Dataset, double eps, unsigned int Minpts);
bool sortMe(Point & a, Point & b);

#endif
