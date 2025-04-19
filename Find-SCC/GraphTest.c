/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA3 
* GraphTest.c
* Test client for Graph ADT
*********************************************************************************/

#include "Graph.h"
#define out stdout

int main(){
    Graph G = newGraph(8);
    Graph N = NULL;

    printf("G order: %i\n",    getOrder(G));        // initially 8
    printf("G size: %i\n",     getSize(G));         // initially 0
    printf("G parent: %i\n",   getParent(G, 1));    // initially NIL
    printf("G discover: %i\n", getDiscover(G, 1));  // initially UNDEF
    printf("G finish: %i\n",   getFinish(G, 1));    // initially UNDEF
    printf("G adjacency list:\n");
    printGraph(out, G);                             // initially empty
    printf("\n");

    // example graph from assignment document
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);

    // output matches example
    printf("G order: %i\n",    getOrder(G));    
    printf("G size: %i\n",     getSize(G));     
    printf("G parent: %i\n",   getParent(G, 1));  
    printf("G discover: %i\n", getDiscover(G, 1));  
    printf("G finish: %i\n",   getFinish(G, 1));    
    printf("G adjacency list:\n");
    printGraph(out, G);                           
    printf("\n");

    // output matches previous output
    printf("Copy of G:\n");
    Graph F = copyGraph(G);
    printf("F order: %i\n",    getOrder(F));    
    printf("F size: %i\n",     getSize(F));     
    printf("F parent: %i\n",   getParent(F, 1));  
    printf("F discover: %i\n", getDiscover(F, 1));  
    printf("F finish: %i\n",   getFinish(F, 1));    
    printf("F adjacency list:\n");
    printGraph(out, F);                             
    printf("\n");

    // output transposes previous output
    printf("Transpose of G:\n");
    Graph H = transpose(G);
    printf("H order: %i\n",    getOrder(H));    
    printf("H size: %i\n",     getSize(H));     
    printf("H parent: %i\n",   getParent(H, 1));  
    printf("H discover: %i\n", getDiscover(H, 1));  
    printf("H finish: %i\n",   getFinish(H, 1));    
    printf("H adjacency list:\n");
    printGraph(out, H);                             
    printf("\n");

    List S = newList();
    
    for(int i = 1; i <= getOrder(G); i++){
        append(S, i);
    }

    printf("before DFS: ");
    printList(out, S);
    printf("\n");

    DFS(G, S);

    printf("after DFS: ");
    printList(out, S);
    printf("\n");

    DFS(H, S);

    printf("after DFS(Gt): ");
    printList(out, S);
    printf("\n");

    freeList(&S);
    freeGraph(&F);
    freeGraph(&N);
    freeGraph(&H);
    freeGraph(&G);
    return 0;
}