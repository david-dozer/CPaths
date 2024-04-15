
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main(int argc, char *argv[]){
    int n = 10;

    srand(time(0));
    // g.display();

    if(argc == 2)
        sscanf(argv[1], "%d", &n);

    int u, v, d;

    for(u = 0; u<n; u++) {
        v = (u+1) % n;
        printf("a%d a%d 1\n", u, v);
    }

    int max_deg=15;

    if(n < 50)
        max_deg = (n < 10)? 2 : 5;

    for(u = 0; u<n; u++) {

        int nedges = rand() % max_deg;
        v = u+1;
        for(int i=0; i<nedges; i++) {
            v = (v + 1 + rand()%(n/max_deg) ) % n;
            int w = 1 + rand() % (n/4);
            printf("a%d a%d %d\n", u, v, w);
        }
    }

    return 0;
}

