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


    //std::cout << "welcome to CJ functionCCCCCCCJJJJJJJCCJCJCJCJCJCJCJ!\n";//testing


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
    
    //std::cout << "leave to CJ functionCCCCCCCJJJJJJJCCJCJsssCJCJCJsssCJCJ!\n";//testing


}




std::vector<int> regionQuery(std::vector<Point> &Dataset,int j,double eps){


    /*comment,only for testing
    std::cout << "welcome to RQ function!RQRQRQRQRQRQ\n";//testing
    
    std::cout << "Now the eps is: ";//testing
    std::cout <<  eps;
    std::cout << "\n ";//testing
    
    std::cout << "this is index: ";//testing
    std::cout <<  j;
    std::cout << "\n ";//testing
    */
   
    
    std::vector<int> Neighbor;
    for(int i=0; i < Dataset.size(); i++){
        std::cout << "The result of distance is:";//testing
        std::cout <<  Dataset.at(j).get_distanceviaxy(Dataset.at(i).get_x(),Dataset.at(i).get_y());
        
        std::cout << "\n";//testing
        if(Dataset.at(j).get_distanceviaxy(Dataset.at(i).get_x(),Dataset.at(i).get_y()) < eps){
            
            std::cout << "calculate succeed!\n";
            std::cout <<  Dataset.at(j).get_distanceviaxy(Dataset.at(i).get_x(),Dataset.at(i).get_y());
            Neighbor.push_back(i);
        }
    } 
    
    
    /*comment only for testing
    std::cout << "The size of neighbor is:\n";
    
    std::cout << Neighbor.size();
    std::cout << "\n\n";
    std::cout << "welcome to leave RQ function!TTTTTTTTTRQRQRQRQRQRQ\n";//testing
    */
    
    
    
    return Neighbor;
}




void expendCluster(std::vector<Point> &Dataset,std::vector<int> &Neighbor,double eps,int Minpts, int clusterNo){




    std::cout << "welcome to EEEEXpend! function!-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-\n";//testing
    
    //check the neighbour if it is in other cluster
    for(int j=0;j<Neighbor.size();j++){
        //get the index of its neighbor
        int m=Neighbor.at(j);
        
        //check the corresponding index
            /*testing
            std::cout << "mark ";//testing
            std::cout << m;//testing
            std::cout << "as visited in expension\n";//testing
            */
            
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
                
                /*comment only for testing
                
                //testing setting
                std::cout << "set ";//testing
                std::cout << j;//testing
                std::cout << "as visited in expension\n";//testing
                std::cout << "mark ";//testing
                std::cout << m;//testing
                std::cout << "as visited in expension\n";//testing
                */
            //}
        //}
    }
    
    //std::cout << "leave EEEEXpend! function!iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii\n";//testing
}












void DSBscan (std::vector<Point> &Dataset,double eps,int Minpts){
    //std::Vector<Point> Clusters;
    //initialize the class No.
    int clusterNo=0;
    //pick the first point and check its neighbor
    for(int i=0; i < Dataset.size(); i++){
        if(Dataset.at(i).if_visited()==0){
            
            Dataset.at(i).mark_visited();
            
            //check all of its neighbour
            std::vector<int> Neighbor=regionQuery(Dataset,i,eps);
            
            
            //std::cout << Neighbor.size();//testing2
            
            
            //if the num of neighbor < Minpts then it is a noise point
            if(Neighbor.size()<Minpts){
                Dataset.at(i).mark_noise();
            }
            //else it is a cluster point and check its neighbor
            else{
                //increase No.
                /*comment only for testing    
                std::cout << "cluster num increased at: ";
                std::cout << i;
                std::cout << "-----------------------------------\n";
                //testing
                */
                clusterNo=clusterNo+1;
                
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



//main function TODO:better revise it in another file
int main(int argc, char *argv[]) {
  std::cout << argv[1];
  
  std::string filename=argv[1];
  double eps=atof(argv[2]);
  int MinPts=atof(argv[3]);
  std::cout << filename;
  
  /*comment used for testing eps/MinPts
  
  std::cout << "eps is:";
  std::cout << eps;//testing
  std::cout << "\n";
  std::cout << "MinPts is:";
  std::cout << MinPts;//testing
  std::cout << "\n";
  */
  
  
  
  std::ifstream input(filename);
  std::vector<Point> Dataset;
  //int i=0;// used for testing
  std::string line;
  while(input)
  {
    getline(input, line);
    //std::cout << "i is:";
    //std::cout << i;
    //std::cout << "__\n";
    double x, y;
    input >> x >> y;
    Point point(x,y);
    
    
    /*comment for testing 
    std::cout << point.get_x();//testing
    std::cout << "|";//testing
    std::cout << point.get_y();//testing
    //std::cout << eps;//testing
    //std::cout << MinPts;//testing
    std::cout << "//";//testing
    */
    
    //the last line will not be push twice because of the getline() problem in c++
    if(input.fail()){
        break;
    
    }
 
    
    //add new data to the Vector
    Dataset.push_back(point);
    
    /*comment used for testing the input vector dataset
    std::cout << "The size of data is:";
    std::cout << Dataset.size();
    std::cout << "\n";
    */
    //i++;//testing
  }
  
  
  //std::cout << Dataset.size();//testing
  
  
  //print_point_vector(Dataset);//testing
  
  DSBscan (Dataset,eps,MinPts);
  
  //std::cout << "after\n";//testing
  
  //print_point_vector(Dataset);//testing
  
  
  std::sort(Dataset.begin(),Dataset.end(), &sortMe);
  
  
  //std::cout << "after sort----------------------------->>>>>>>>>>.\n";//testing
  
  
  print_point_vector(Dataset);//testing
 
  
  return 0;
} 





