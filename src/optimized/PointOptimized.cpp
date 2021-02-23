/**
 * @file    Points.cpp
 * @author  Henry Jiang 2/19/2021
 * @author  Mingcheng Wur 2/19/2021
 * @version 1.0        
 * 
 * Describe:    Implemented a Points class, which contains value x, y, and integer value cluster. 
 *              It also contains function get_pos(), andget_distance().
 * 
 *              The parameters denotes a Points at a 2-d euclidean space, and the cluster denots
 *              which group it falls into. If no extension is been defined, the default should
 *              be 0.
**/

#include <math.h>
#include "../../include/PointsOptimized.hpp"

void Points::add_point(double x, double y) {
    std::vector<double> tmp = {x, y};
    pos.push_back(tmp);
}

std::vector<double> Points::get_pos(unsigned int i) {
    return pos[i];
}

void Points::set_cluster(unsigned int i, unsigned int group_id) {
    clusters[i] = group_id;
}

//mark as visited
void Points::mark_visited(unsigned int i) {
    visited[i] = true;
}

//undo visited
void Points::undo_visited(unsigned int i) {
    visited[i] = false;
}

bool Points::is_visited(unsigned int i) {
    return visited[i];
}

int Points::get_cluster(unsigned int i) {
    return clusters[i];
}

double Points::get_distance(unsigned int i1, unsigned int i2) {
    std::vector<double> tmp = get_pos(i1);
    std::vector<double> tmp2 = get_pos(i2);

    double delta_x = tmp[0] - tmp2[0];
    double delta_y = tmp[1] - tmp2[1];

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double Points::get_distance(unsigned int i, double x, double y) {
    std::vector<double> tmp = get_pos(i);
    
    double delta_x = tmp[0] - x;
    double delta_y = tmp[1] - y;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

size_t Points::size() {
    return pos.size();
}