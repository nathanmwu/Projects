/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA2 
* FindPath.c 
* Takes an input file representing a graph and returns the adjacency List 
* representation along with the shortest path between given vertices. 
*********************************************************************************/

#include "Graph.h"

#define MAX_LEN 15;

int main(int argc, char* argv[]){
    FILE *in, *out;

    // check command line for correct number of arguments
    if (argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // read first line of infile, indicating number the order of G
    int n;
    fscanf(in, "%i\n", &n);
    Graph G = newGraph(n);
    // add edges to G
    int a = 1; int b = 1;   // initially nonzero
    while(a>0 && b>0){      // stops at dummy line "0 0"
        fscanf(in, "%i %i\n", &a, &b);
        if(a>0 && b>0){
            addEdge(G, a, b);
        }
    }
    printGraph(out, G);
    // perform BFS() on each source-destination pair
    a = 1; b = 1;
    List path = newList();
    while(a>0 && b>0){      // stops at dummy line "0 0"
        clear(path);
        fscanf(in, "%i %i\n", &a, &b);
        if(a>0 && b>0){
            fprintf(out, "\n\n");
            BFS(G, a);
            if(getDist(G, b) == -1){
                fprintf(out, "The distance from %i to %i is infinity\n", a, b);
                fprintf(out, "No %i-%i path exists", a, b);
            } else {
                fprintf(out, "The distance from %i to %i is %i\n", a, b, getDist(G, b));
                fprintf(out, "A shortest %i-%i path is: ", a, b);
                getPath(path, G, b);
                printList(out, path);
            }
        }
    }

    // free heap memory
    freeGraph(&G);
    freeList(&path);

    // close files
    fclose(in);
    fclose(out);
    return 0;
}