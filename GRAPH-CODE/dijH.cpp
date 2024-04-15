
#include <iostream>
#include "Graph.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<graph::vertex_label> bfs_rpt;
  std::vector<graph::vertex_label> dij_rpt;

  if(argc != 3) {
    std::cout << "usage:  ./dij <filename> <source-vertex>\n";
    return 0;
  }
  else {
    if(!g.read_file(argv[1])){
      std::cout << "could not open file '" << argv[1] << "'\n";
      return 0;
    }
  }

  /*
  std::cout << "\nADJACENCY-LIST REPRESENTATION:\n\n";
  g.display();
  std::cout << "\nEND ADJACENCY LIST:\n\n";
  */

  if(!g.dijkstraHEAP(argv[2], dij_rpt)) {
    std::cout << "dij failed -- bad source vertex name '" <<
      argv[2] << "'\n";
    return 0;
  }
  /*
  else {
    std::cout << "\nDIJ REPORT:\n\n";
    g.disp_report(dij_rpt, true);
    std::cout << "\nEND DIJ REPORT\n\n";
  }
  */

  return 0;
}

