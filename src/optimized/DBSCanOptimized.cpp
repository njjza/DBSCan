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
#include <omp.h>
#include "DBSCanOptimized.hpp"

std::vector<unsigned int> rangeQuery(std::vector<Point> pVec, Point p, double eps){
    //Point tmp1, tmp2, tmp3, tmp4;
    std::vector<unsigned int> Neighbor;
    std::vector<std::vector<unsigned int>> Neighbor1;
    Neighbor1.reserve(omp_get_max_threads());
    Neighbor.reserve(3);
    eps=10000;
    
    //initialize the neighbor1
    for(int test=0;test<omp_get_max_threads();test++){
        std::vector<unsigned int> newvec={};
        Neighbor1.push_back(newvec);
    }
    
    
    
    
    unsigned int len = pVec.size();
    
    
    
    //Error:I think loop A should not use m, instead, use len
    unsigned int m = len%4;
    
    
    //std::cout << "Hi";

    //LOOP A: check all the point to find if the point is in eps range
    //error2: large sample may cause seg fault here.
    //The problem might be 
    #pragma omp parallel for
    for(unsigned int i = 0; i < len; i++){
        if(get_distance(p, pVec[i]) < eps){
            auto const threadnum=omp_get_thread_num();
            //std::cout << threadnum;
            Neighbor1[threadnum].push_back(i);
        }
    }
    
    
    
    for(int k=0;k<omp_get_max_threads();k++){
        Neighbor.insert(Neighbor.end(),Neighbor1[k].begin(),Neighbor1[k].end());
    
    
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //loop unrolling to reduce the cache miss rate
    //find neighbor's neighbor.
    //Error:sometimes cause seg fault here, the problem might be Neighbor2 initialize in a wrong way. 
    
    
    
    std::vector<std::vector<unsigned int>> Neighbor2;
    Neighbor2.reserve(omp_get_max_threads());
    
    
    for(int test=0;test<omp_get_max_threads();test++){
        std::vector<unsigned int> newvec={};
        Neighbor2.push_back(newvec);
    }
    
    
    
    
    
    std::vector<Point> tp1,tp2,tp3,tp4;
    #pragma omp parallel for
    for(unsigned int i = m - 1; i < len; i=i+4){
        auto const threadnum=omp_get_thread_num();
        if ((i+1)<len)    {
            tp1[threadnum] = pVec[i+1];
        if(get_distance(p, tp1[threadnum]) < eps){
            Neighbor2[threadnum].push_back(i+1);
        }
        }
        if ((i+2)<len) {

            tp2[threadnum] = pVec[i+2];
        if(get_distance(p, tp2[threadnum]) < eps){
            Neighbor2[threadnum].push_back(i+2);
        }
        }
        if ((i+3)<len) {
        
            tp3[threadnum] = pVec[i+3];
        if(get_distance(p, tp3[threadnum]) < eps){
            Neighbor2[threadnum].push_back(i+3);
        }
        }
        if ((i+4)<len) {
            tp4[threadnum] = pVec[i+4];
        if(get_distance(p, tp4[threadnum]) < eps){
            Neighbor2[threadnum].push_back(i+4);
        }
        }
    }
    
    
    for(int k=0;k<omp_get_max_threads();k++){
        Neighbor.insert(Neighbor.end(),Neighbor2[k].begin(),Neighbor2[k].end());

    }
    //std::cout << "\n--------------\n";
    //std::cout << Neighbor.size();
    return Neighbor;
}

bool comparator(Point a, Point b) {
    return get_distance(a, b) < 2.0;
}

std::vector<unsigned int> DBSCan (std::vector<Point> pVec, double eps, unsigned short int Minpts){
    unsigned int len, len2, grp_id = 0;
    Point p, p2;
    std::vector<unsigned int> neighbor, neighbor_neighbor;
    //std::cout << "Hi";
    
    std::sort(pVec.begin(), pVec.end(), comparator);

    len = pVec.size();
    //std::cout << "hi\n";
    //std::cout << len;
    //pick the first point and check its neighbor
    
    
    
    
    //travel through the points' cluster list and do union(put all connected cluster together)
    for (unsigned int i = 0; i < len; i++) {
        p = pVec[i];
        //std::cout << "Hi";--for loop test pass
        if (p.grp_id != POINT_UNDEFINED) {
            continue;
        }
        //std::cout << "Hi";
        
        neighbor = rangeQuery(pVec, p, eps);
        len2 = neighbor.size();
        //std::cout << "\n--------------\n";
        //std::cout<<len2;
        
        
        if (len2 < Minpts) {
        
            //std::cout << "hello\n";
            
            p.grp_id = 0;
            continue;
        }
        
        
        
        //std::cout << "\n--------------\n";
        //std::cout << grp_id;
        
        //it is a new cluster head point
        p.grp_id = ++grp_id;
        
        
        for (unsigned int j = 0; j < len2; j++) {
            int numb=neighbor[j];
            p2 = pVec[numb];
            
            
            /*
            if (p2.grp_id == POINT_UNDEFINED) {
                std::cout << "\nwuwuwuwuwuwuwuwu\n";//test 
                continue;
            }
            */
            
            
            //std::cout << "\nyiyiyiyiyiyiyiyiyiyi\n";//test
            pVec[numb].grp_id = grp_id;
            neighbor_neighbor = rangeQuery(pVec, p2, eps);
            if (neighbor_neighbor.size() > Minpts) {
            
                //std::cout << "\nXXXXXXX\n";//test   
                std::vector<unsigned int> tmp;
                tmp.reserve(neighbor.size() + neighbor_neighbor.size());

                std::set_union(neighbor.begin(), neighbor.end(),
                                neighbor_neighbor.begin(), neighbor_neighbor.end(),
                                tmp.begin());
                neighbor = tmp;
            }
        }
        
        
        
    }
    
    
    /*this is used for testing the out put
    for(int i=0;i<pVec.size();i++){
        std::cout<<"\n";
        std::cout<<pVec[i].grp_id;
        std::cout<<"\n";
    }
    
    */
    
    
    
    //neibor is not needed infact, it is just used to test the code.
    return neighbor;
}
