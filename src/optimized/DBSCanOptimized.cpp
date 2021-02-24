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
#include "../../include/DBSCanOptimized.hpp"

std::vector<unsigned int> rangeQuery(std::vector<Point> pVec, Point p, double eps){
    Point tmp1, tmp2, tmp3, tmp4;
    std::vector<unsigned int> Neighbor;
    Neighbor.reserve(3);
    unsigned int len = pVec.size();
    unsigned int m = len%4;

    for(unsigned int i = 0; i < m; i++){
        if(get_distance(p, pVec[i]) < eps){
            Neighbor.push_back(i);
        }
    }

    for(unsigned int i = m; i < len; i++){
        tmp1 = pVec[i++];
        if(get_distance(p, tmp1) < eps){
            Neighbor.push_back(i);
        }
        tmp2 = pVec[i++];
        if(get_distance(p, tmp2) < eps){
            Neighbor.push_back(i);
        }
        tmp3 = pVec[i++];
        if(get_distance(p, tmp3) < eps){
            Neighbor.push_back(i);
        }
        tmp4 = pVec[i++];
        if(get_distance(p, tmp4) < eps){
            Neighbor.push_back(i);
        }
    }

    return Neighbor;
}

bool comparator(Point a, Point b) {
    return get_distance(a, b) < 2.0;
}

std::vector<unsigned int> DBSCan (std::vector<Point> pVec, double eps, unsigned short int Minpts){
    unsigned int len, len2, grp_id = 0;
    Point p, p2;
    std::vector<unsigned int> neighbor, neighbor_neighbor;
    
    std::sort(pVec.begin(), pVec.end(), comparator);

    len = pVec.size();
    //pick the first point and check its neighbor
    for (unsigned int i = 0; i < len; i++) {
        p = pVec[i];
        if (p.grp_id != POINT_UNDEFINED) {
            continue;
        }

        //check all of its neighbour
        neighbor = rangeQuery(pVec, p, eps);
        len2 = neighbor.size();
        if (len2 < Minpts) {
            p.grp_id = 0;
            continue;
        }

        p.grp_id = ++grp_id;
        for (unsigned int j = 0; j < len2; j++) {
            p2 = pVec[j];
            if (p2.grp_id == POINT_UNDEFINED) {
                continue;
            }

            p2.grp_id = grp_id;
            neighbor_neighbor = rangeQuery(pVec, p2, eps);
            if (neighbor_neighbor.size() > Minpts) {
                std::vector<unsigned int> tmp;
                tmp.reserve(neighbor.size() + neighbor_neighbor.size());

                std::set_union(neighbor.begin(), neighbor.end(),
                                neighbor_neighbor.begin(), neighbor_neighbor.end(),
                                tmp.begin());
                neighbor = tmp;
            }
        }
    }

    return neighbor;
}