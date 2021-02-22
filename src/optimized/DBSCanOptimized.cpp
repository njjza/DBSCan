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

void Clusterjoin(std::vector<int> &Neighbor1,std::vector<int> &Neighbor,std::vector<Point> &Dataset, int clusterNo){
    //it is used to find the points'old cluster
    std::vector<int> oldcluster;

    //set all neighbor points in the cluster 
    for(unsigned int j = 0; j < Neighbor.size(); j++){
        int m = Neighbor.at(j);
        
        //record if the point have some old cluster
        if(Dataset.at(m).get_cluster()!=0){
            oldcluster.push_back(Dataset.at(m).get_cluster());
        }
        
    }
    
    for(unsigned int j=0;j < Neighbor1.size();j++){
        int m=Neighbor1.at(j);
        
        //record if the point have some old cluster
        if(Dataset.at(m).get_cluster()!=0){
            oldcluster.push_back(Dataset.at(m).get_cluster());
        }
        
    }
     
    //set all points in neighbor in the cluster
    for(unsigned int k = 0; k < Neighbor.size(); k++){
        int n=Neighbor.at(k);
        Dataset.at(n).set_cluster(clusterNo);
    }
    
    //set all neighbor1 point in the cluster 
    for(unsigned int k=0; k < Neighbor1.size(); k++){
        int n=Neighbor1.at(k);
        Dataset.at(n).set_cluster(clusterNo);
    }
    
    //set all old members in the new cluster
    int temp=0;
    for(unsigned int i=0; i < oldcluster.size(); i++){
        temp=oldcluster.at(i);
        for(unsigned int j=0; j < Dataset.size(); j++){
            if(Dataset.at(j).get_cluster()==temp){
                Dataset.at(j).set_cluster(clusterNo);
            } 
        }
    }

}

std::vector<Point> rangeQuery(std::vector<Point> &Dataset, Point p, double eps){
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

void expendCluster(std::vector<Point>& Dataset, std::vector<Point>& Neighbor, double eps, int Minpts, int clusterNo){    
    //check the neighbour if it is in other cluster
    for(unsigned int i = 0; i < Neighbor.size(); i++){
        //get the index of its neighbor
        Point p = Neighbor.at(j);
        p.mark_visited();

        //check neighbor's neighbor
        std::vector<Point> Neighbor1=rangeQuery(Dataset,p,eps);
            
        //if neighbour point is a cluster point then combine them together via Clusterjoin()
        //if(Neighbor1.size()>Minpts){
        Clusterjoin(Neighbor1,Neighbor,Dataset,clusterNo);

        //if the point is not in any cluster then mark it in this cluster
        //if(Dataset.at(m).get_cluster()==0){
        Dataset.at(m).set_cluster(clusterNo);
    }
}

void DBSCan (std::vector<Point> &Dataset, double eps, unsigned int Minpts){
    int clusterId = 1;
    unsigned int len = Dataset.size();
    Point p;

    //pick the first point and check its neighbor
    for (unsigned int i = 0; i < len; i++) {
        p = Dataset.at(i);
        if (p.is_visited()) {
            
            p.mark_visited();
            
            //check all of its neighbour
            std::vector<Point> Neighbor = rangeQuery(Dataset, p, eps);
            unsigned int len = Neighbor.size();
            if (len < Minpts) {
                continue;
            }

            p.set_cluster(clusterId);
            for (unsigned int j = 0; j < len; j++)
                
                expendCluster(Dataset,Neighbor,eps,Minpts,clusterId);
            }
        }
    }
}

//c++ comparator
bool sortMe(Point & a, Point & b){
    if (a.get_cluster() < b.get_cluster()){
        return true;
    } else {
        return false;
    }
}