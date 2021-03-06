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
#include "PointOptimized.hpp"
#include <nmmintrin.h>
#include <immintrin.h>


float get_distance(Point p1, Point p2) {
    __m128 const vector2=_mm_load_ps(&(p1.x));
    __m128 const vector21=_mm_load_ps(&(p2.x));
    __m128 const sub=_mm_sub_ps(vector2,vector21);
    __m128 const squared=_mm_mul_ps(sub,sub);
    auto const vec = reinterpret_cast<float const *>(&squared);
 
    
 
    return sqrt(vec[0]+ vec[1]);
}

float get_distance(Point p, float x, float y) {
    Point p1;
    p1.x=x;
    p1.y=y;
    
    __m128 const vector2=_mm_load_ps(&(p.x));
    __m128 const vector21=_mm_load_ps(&(p1.x));
    __m128 const sub=_mm_sub_ps(vector2,vector21);
    __m128 const squared=_mm_mul_ps(sub,sub);
    auto const vec = reinterpret_cast<float const *>(&squared);
 
    return sqrt(vec[0]+ vec[1]);
}
