/**
 * @file    Point.cpp
 * @author  Henry Jiang 2/19/2021
 * @author  Mingcheng Wur 2/19/2021
 * @version 1.0        
 * 
 * Describe:    Implemented a point class, which contains value x, y, and integer value cluster. 
 *              It also contains function get_pos(), andget_distance().
 * 
 *              The parameters denotes a point at a 2-d euclidean space, and the cluster denots
 *              which group it falls into. If no extension is been defined, the default should
 *              be 0.
**/

#include <math.h>
#include "../include/Point.hpp"

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->cluster = 0;
    this->visited = 0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
    this->cluster = 0;
    this->visited = 0;
}

void Point::set_cluster(int group_id) {
    this->cluster = group_id;
}

//mark as visited
void Point::mark_visited() {
    this->visited = 1;
}

//mark as noise
void Point::mark_noise() {
    this->visited = 2;
}

//undo visited
void Point::undo_visited() {
    this->visited = 0;
}

int Point::is_visited() {
    return this->visited;
}

double Point::get_x() {
    return this->x;
}

double Point::get_y() {
    return this->y;
}


double Point::get_cluster() {
    return this->cluster;
}

std::vector<double> Point::get_pos() {
    return {this->x, this->y};
}

double Point::get_distance(Point* p) {
    double delta_x = this->x - p->get_x();
    double delta_y = this->y - p->get_y();

    double result = sqrt( pow(delta_x, 2) + pow(delta_y, 2) );
    return result;
}

double Point::get_distance(double x, double y) {
    double delta_x = this->x - x;
    double delta_y = this->y - y;

    double result = sqrt(pow(delta_x, 2) + pow(delta_y, 2) );
    return result;
}