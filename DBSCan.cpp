/**
 *  @file   DBSCan.cpp
 *  @author Mingcheng Wu 2/19/2021
 *  @version 1.0
 * 
 *  Describe:   Implemented the core algorithm of DBSCan, but not optimized for modern computer
 *              architecture yet. It is sucessful to cluster the nodes by an arbitrary variable
 *              epsilon, which denotes the max radius from an arbitrary node, and all nodes falls
 *              in this radius will be grouped into a single cluster.
**/

#include <fstream>
#include <iostream>
#include "Point.cpp"
#include <vector>
#include <stdlib.h>
#include <algorithm>

//this function is used for testing vector point
void print_point_vector(std::vector<Point> &a) {
   std::cout << "This is a new point: \n";

   for(int i=0; i < a.size(); i++){
   std::cout << "i is:";
   std::cout << i;
   std::cout << "__\n";
   std::cout << "the x is";
   std::cout << a.at(i).get_x() << ' ';
   std::cout << "||\n";
   std::cout << "the y is";
   std::cout << a.at(i).get_y() << ' ';
   std::cout << "||\n";
   std::cout << "it belongs to cluster:";
   std::cout << a.at(i).get_cluster() << ' ';
   std::cout << "||\n";
   }
}

void Clusterjoin(std::vector<int> &Neighbor1,std::vector<int> &Neighbor,std::vector<Point> &Dataset,int clusterNo){
    //it is used to find the points'old cluster
    std::vector<int> oldcluster;

    //set all neighbor points in the cluster 
    for(int j=0;j<Neighbor.size();j++){
        int m=Neighbor.at(j);
        
        //record if the point have some old cluster
        if(Dataset.at(m).get_cluster()!=0){
            oldcluster.push_back(Dataset.at(m).get_cluster());
        }
        
    }
    
    for(int j=0;j<Neighbor1.size();j++){
        int m=Neighbor1.at(j);
        
        //record if the point have some old cluster
        if(Dataset.at(m).get_cluster()!=0){
            oldcluster.push_back(Dataset.at(m).get_cluster());
        }
        
    }
     
    //set all points in neighbor in the cluster
    for(int k=0;k<Neighbor.size();k++){
        int n=Neighbor.at(k);
        Dataset.at(n).set_cluster(clusterNo);
    }
    
    //set all neighbor1 point in the cluster 
    for(int k=0;k<Neighbor1.size();k++){
        int n=Neighbor1.at(k);
        Dataset.at(n).set_cluster(clusterNo);
    }
    
    //set all old members in the new cluster
    int temp=0;
    for(int i=0;i<oldcluster.size();i++){
        temp=oldcluster.at(i);
        for(int j=0;j<Dataset.size();j++){
            if(Dataset.at(j).get_cluster()==temp){
                Dataset.at(j).set_cluster(clusterNo);
            } 
        }
    }

}

std::vector<int> regionQuery(std::vector<Point> &Dataset, int j, double eps){
    std::vector<int> Neighbor;

    for(int i=0; i < Dataset.size(); i++){
        if(Dataset.at(j).get_distance(Dataset.at(i).get_x(), Dataset.at(i).get_y()) < eps){
            Neighbor.push_back(i);
        }
    } 
    
    return Neighbor;
}

void expendCluster(std::vector<Point>& Dataset, std::vector<int>& Neighbor, double eps, int Minpts, int clusterNo){    
    //check the neighbour if it is in other cluster
    for(int j=0; j<Neighbor.size(); j++){
        //get the index of its neighbor
        int m = Neighbor.at(j);
        
        //check the corresponding index
        //mark neighbor as visited
        Dataset.at(m).mark_visited();

        //check neighbor's neighbor
        std::vector<int> Neighbor1=regionQuery(Dataset,m,eps);
            
        //if neighbour point is a cluster point then combine them together via Clusterjoin()
        //if(Neighbor1.size()>Minpts){
        Clusterjoin(Neighbor1,Neighbor,Dataset,clusterNo);
            
            
        //if the point is not in any cluster then mark it in this cluster
        //if(Dataset.at(m).get_cluster()==0){
        Dataset.at(m).set_cluster(clusterNo);
    }
}

void DSBscan (std::vector<Point> &Dataset, double eps, int Minpts){
    //std::Vector<Point> Clusters;
    //initialize the class No.
    int clusterNo = 0;

    //pick the first point and check its neighbor
    for(int i=0; i < Dataset.size(); i++) {
        if(Dataset.at(i).is_visited() == 0) {
            
            Dataset.at(i).mark_visited();
            
            //check all of its neighbour
            std::vector<int> Neighbor = regionQuery(Dataset,i,eps);

            //if the num of neighbor < Minpts then it is a noise point
            if(Neighbor.size() < Minpts) {
                Dataset.at(i).mark_noise();
            }

            //else it is a cluster point and check its neighbor
            else{
                //increase No.
                clusterNo++;
                
                //set this point in the cluster
                Dataset.at(i).set_cluster(clusterNo);
                
                //expend and check the point's neighbor
                expendCluster(Dataset,Neighbor,eps,Minpts,clusterNo);
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