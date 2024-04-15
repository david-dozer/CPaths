#include <iostream>
#include "Graph.h"


int main(int argc, char *argv[]){
  graph g;
  std::vector<graph::vertex_label> dij_rptS;
  std::vector<graph::vertex_label> dij_rptH;

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

  /**
  std::cout << "\nADJACENCY-LIST REPRESENTATION:\n\n";
  g.display();
  std::cout << "\nEND ADJACENCY LIST:\n\n";
  **/

  if(!g.dijkstraHEAP(argv[2], dij_rptH)) {
    std::cout << "dij failed -- bad source vertex name '" <<
      argv[2] << "'\n";
  }
  printf("...just finished heap run\n");
  printf("...starting scanning run \n");


  if(!g.dijkstraSCAN(argv[2], dij_rptS)) {
    std::cout << "dij failed -- bad source vertex name '" <<
      argv[2] << "'\n";
  }
  printf("...just finished scanning run\n");

  int u;
  int errors  = 0;

  for(u=0; u<g.num_nodes(); u++) {
      if(dij_rptH[u].dist != dij_rptS[u].dist)
          errors++;
  }
  printf("# errors:  %d\n", errors);


  /**
  else {
    std::cout << "\nDIJ REPORT:\n\n";
    g.disp_report(dij_rpt, true);
    std::cout << "\nEND DIJ REPORT\n\n";
  }
  **/

  return 0;
}

