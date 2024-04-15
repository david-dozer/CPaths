
#include <iostream>
// #include "Graph.h"
// #include "pqueue.h"


int main(int argc, char *argv[]){
    int n = 10;


  // g.display();

    if(argc == 2)
      sscanf(argv[1], "%d", &n);

    int u, v, d;

    for(u = 0; u<n; u++) {
        v = (u+1) % n;
        printf("a%d a%d 1\n", u, v);
    }
    for(u = 0; u<n; u++) {
        d = 2;
        v = u+d;
        while(v < n) {
           printf("a%d a%d %d\n", u, v, (u+v)/2);

           d *= 2;
           v = u+d;
        }
        v = u-1;
        while(v > 0) {
           printf("a%d a%d %d\n", u, v, (u+v)/2);
           v = v/2;
        }
    }




  return 0;
}

