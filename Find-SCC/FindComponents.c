/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA3 
* FindPath.c 
* Takes an input file representing a graph and returns the adjacency List 
* representation along with its strongly connected components. 
*********************************************************************************/

#include "Graph.h"

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
            addArc(G, a, b);
        }
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n\n");
    // perform DFS() on G and transpose G
    List S = newList();
    for(int i = 1; i <= getOrder(G); i++){
        append(S, i);   // populate S with vertices of G
    }
    DFS(G, S);  // run DFS() on G
    Graph T = transpose(G); // get transpose of G
    DFS(T, S);  // run DFS() on T with G's output
    int components = 0; // count number of trees in DFS Forest of T
    for(int i=1; i <= getOrder(T); i++){
        if(getParent(T, i) == NIL){    // a vertice has no parents, so it is the root of a tree
            components++;
        }
    }
    fprintf(out, "G contains %i strongly connected components:\n", components);
    // print strongly connected components
    List C = newList(); // keeps track of each strongly connected components
    moveBack(S);
    for (int i=1; i<=components; i++){  // one print per component
        clear(C);
        while(getParent(T, get(S)) != NIL) {
            prepend(C, get(S));
            movePrev(S);
        }
        prepend(C, get(S)); // prepend root of tree
        movePrev(S);
        fprintf(out, "Component %i: ", i);
        printList(out, C);
        if (i<components){
            fprintf(out, "\n");
        }
    }

    // free heap memory
    freeList(&C);
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);

    // close files
    fclose(in);
    fclose(out);
    return 0;
}