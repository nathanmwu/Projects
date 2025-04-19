/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA2 
*  GraphTest.c
*  Test client for Graph ADT
*********************************************************************************/

#include"Graph.h"

#define out stdout

int main(int argc, char* argv[]){
   Graph G = newGraph(5); // Graph with 5 vertices
   Graph F = newGraph(3); // NULL Graph
   Graph H = NULL;   // NULL Graph Reference
   
   addArc(G, 5, 1);
   addArc(G, 5, 2);
   addArc(G, 5, 3);
   addArc(G, 1, 4);
   addArc(G, 4, 1);
   addEdge(G, 1, 4); // duplicate edge, should not affect getSize(G)

   printf("G order: %i\n", getOrder(G));
   printf("G size: %i\n",   getSize(G));
   printf("G source: %i\n", getSource(G));
   printGraph(out, G);

   printf("\n\n");

   printf("F order: %i\n", getOrder(F));
   printf("F size: %i\n",   getSize(F));
   printf("F source: %i\n", getSource(F));
   printGraph(out, F);

   printf("\n\n");

   // no operations should be possible on NULL Graph reference

   //printf("H order: %i\n", getOrder(H));  // call getOrder on NULL graph reference
   //printf("H size: %i\n",   getSize(H));  // call getSize on NULL graph reference
   //printf("H source: %i\n", getSource(H));   // call getSource on NULL graph reference
   //printGraph(out, H);  // correctly prints error

   // perform BFS on all Graphs
   BFS(G, 5);
   //BFS(F, 5);   // test on invalid source
   BFS(F, 3);     // valid source
   //BFS(H, 5);   // prints correct error message

   List L = newList();
   
   // print results
   getPath(L, G, 4);
   printList(out, L);
   printf("\n");

   clear(L);   // client clears List ADT

   // print results
   getPath(L, F, 1);
   printList(out, L);
   printf("\n");

   clear(L);

   //getPath(L, H, 4); // call getPath on NULL graph reference
   printList(out, L);
   printf("\n");

   makeNull(G);
   printGraph(out, G);  // test makeNull

   // free objects
   freeList(&L);
   freeGraph(&G);
   freeGraph(&F);
   freeGraph(&H);

   return(0);
}
