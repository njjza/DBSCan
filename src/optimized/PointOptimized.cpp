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
#include "../../include/PointOptimized.hpp"

double get_distance(Point p1, Point p2) {
    double delta_x = p1.x - p2.x;
    double delta_y = p1.y - p2.y;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double get_distance(Point p, double x, double y) {
    double delta_x = p.x - x;
    double delta_y = p.y - y;

    return sqrt(delta_x * delta_x + delta_y * delta_y);
}