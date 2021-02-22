//main function TODO:better revise it in another file
int main(int argc, char *argv[]) {
  std::cout << argv[1];
  
  std::string filename=argv[1];
  double eps=atof(argv[2]);
  int MinPts=atof(argv[3]);
  std::cout << filename;
  
  std::ifstream input(filename);
  std::vector<Point> Dataset;
  //int i=0;// used for testing
  std::string line;
  while(input)
  {
    getline(input, line);
    double x, y;
    input >> x >> y;
    Point point(x,y);
    
    //the last line will not be push twice because of the getline() problem in c++
    if(input.fail()){
        break;
    
    }
    
    //add new data to the Vector
    Dataset.push_back(point);
  }

  DSBscan (Dataset,eps,MinPts);

  std::sort(Dataset.begin(),Dataset.end(), &sortMe);
  
  print_point_vector(Dataset);//testing
  return 0;
} 