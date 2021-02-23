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

std::vector<unsigned int> rangeQuery(Points &p, unsigned int pos, double eps){
    std::vector<unsigned int> Neighbor;
    Neighbor.reserve(20);
    unsigned int len = p.size();

    for(unsigned int i = 0; i < len; i++){
        if(p.get_distance(pos, i) < eps){
            Neighbor.push_back(i);
        }
    }
    
    return Neighbor;
}

void DBSCan (Points &p, double eps, unsigned int Minpts){
    int grp_id = 1;
    unsigned int len;
    std::vector<unsigned int> neighbor, neighbor_neighbor;
    
    len = p.size();
    //pick the first point and check its neighbor
    for (unsigned int i = 0; i < len; i++) {
        if (!p.is_visited(i)) {
            
            p.mark_visited(i);
            
            //check all of its neighbour
            neighbor = rangeQuery(p, i, eps);
            if (neighbor.size() < Minpts) {
                continue;
            }

            p.set_cluster(i, grp_id);
            for (unsigned int j : neighbor) {
                p.set_cluster(j, grp_id);

                if(p.get_cluster(j) > 0) {
                    continue;
                }

                neighbor_neighbor = rangeQuery(p, j, eps);
                if (neighbor_neighbor.size() > Minpts) {
                    std::sort(neighbor_neighbor.begin(), neighbor_neighbor.end());
                    std::sort(neighbor.begin(), neighbor.end());
                    std::vector<unsigned int> tmp;
                    tmp.reserve(neighbor.size() + neighbor_neighbor.size());

                    std::set_union(neighbor.begin(), neighbor.end(),
                                    neighbor_neighbor.begin(), neighbor_neighbor.end(),
                                    tmp.begin());
                    neighbor = tmp;
                }
            }
        }
    }
}