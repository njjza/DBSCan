/**
 *  @file   DBSCanOptimized.cpp
 *  @author Henry Jiang 2/22/2021
 *  @version 1.0
 * 
 *  Describe:   Implemented the core algorithm of DBSCan, but optimized for modern computer
 *              architecture in single core, single thread situation. It is to 
 *              cluster the nodes by an arbitrary variable epsilon, which denotes the max 
 *              radius from an arbitrary node, and all nodes falls in this radius will be 
 *              grouped into a single cluster.
**/

#include <stdlib.h>
#include <algorithm>
#include <set>
#include "../../include/DBSCanOptimized.hpp"

std::vector<Point> rangeQuery(std::vector<Point> &Dataset, Point& p, double eps){
    std::vector<Point> Neighbor;
    Point tmp;

    for(unsigned int i = 0; i < Dataset.size(); i++){
        tmp = Dataset.at(i);
        
        if(p.get_distance(tmp) < eps){
            Neighbor.push_back(tmp);
        }
    }
    
    return Neighbor;
}

bool comparator(Point rhs, Point lhs) {
    return rhs.get_distance(0, 0) < lhs.get_distance(0, 0);
}

void union_point_vector(std::vector<Point>& rhs, std::vector<Point>&lhs, std::vector<Point>& newVec) {
    unsigned int i1 = 0, i2 = 0, l1 = rhs.size(), l2 = lhs.size();
    Point p1, p2;

    while (i1 < l1 || i2 < l2) {
        p1 = rhs[i1];
        p2 = lhs[i2];

        if (p1.get_x() == p2.get_x() && p1.get_y() == p2.get_y()) {
            i1++;
            i2++;
        }
        else if (comparator(p1, p2)) {
            newVec.push_back(p1);
            i1++;
        }
        else {
            newVec.push_back(p2);
            i2++;
        }
    }
}

void DBSCan (std::vector<Point> &Dataset, double eps, unsigned int Minpts){
    int grp_id = 1;
    unsigned int len;
    std::vector<Point> neighbor, neighbor_neighbor;
    Point p;
    
    len = Dataset.size();
    //pick the first point and check its neighbor
    for (unsigned int i = 0; i < len; i++) {
        p = Dataset.at(i);
        if (!p.is_visited()) {
            
            p.mark_visited();
            
            //check all of its neighbour
            neighbor = rangeQuery(Dataset, p, eps);
            if (neighbor.size() < Minpts) {
                continue;
            }

            p.set_cluster(grp_id);
            for (unsigned int j = 0; j < neighbor.size(); j++) {
                p = neighbor.at(j);
                p.set_cluster(grp_id);

                if(p.get_cluster() > 0) {
                    continue;
                }

                neighbor_neighbor = rangeQuery(neighbor, p, eps);
                if (neighbor_neighbor.size() > Minpts) {
                    std::sort(neighbor_neighbor.begin(), neighbor_neighbor.end(), comparator);
                    std::sort(neighbor.begin(), neighbor.end(), comparator);
                    std::vector<Point> tmp;
                    tmp.reserve(neighbor.size() + neighbor_neighbor.size());

                    union_point_vector(neighbor, neighbor_neighbor, tmp);
                    neighbor = tmp;
                }
            }
        }
    }
}