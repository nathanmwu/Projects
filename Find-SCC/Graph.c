/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA3
* Graph.c 
* Functions for Graph ADT
*********************************************************************************/

#include "Graph.h"

/*** Types ***/

// Graph struct definition
typedef struct GraphObj {
	List* neighbors;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int order;
    int size;
} GraphObj;

/*** Constructors-Destructors ***/

Graph newGraph(int n){
    // Function newGraph() will return a reference to a new graph object containing 
    // n vertices and no edges.
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    for(int i=0; i<n+1; i++){
        G->neighbors[i] = newList();    // adjacency lists are all initially empty
        G->finish[i] = UNDEF;           // discover times are initially undefined
        G->discover[i] = UNDEF;         // finish times are initially undefined
    }
	G->order = n;
	G->size = 0;
	return G;
}

void freeGraph(Graph* pG){
    // freeGraph() frees all heap memory associated with a graph and sets its Graph 
    // argument to NULL. 
	if (pG!=NULL && (*pG)!=NULL){
        for(int i=0; i<getOrder(*pG)+1; i++){   // free adjacency lists
            freeList((*pG)->neighbors+i);
        }
		free((*pG)->neighbors);
		free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

int getOrder(Graph G){
    // getOrder() returns the number of vertices in the Graph G
    if(G){
        return G->order;
    } else {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getSize(Graph G){
    // getSize() returns the number of edges in the Graph G
    if(G){
        return G->size;
    } else {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getParent(Graph G, int u){
    // Function getParent() will return the parent of vertex u in the DFS forest
    // Pre: 1<=u<=getOrder(G)
    if(G){
        if(1>u || u>getOrder(G)){
            fprintf(stderr, "Graph Error: calling getParent() with invalid vertex\n");
            exit(EXIT_FAILURE);
        } else {
            return G->parent[u];
        }
    } else {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getDiscover(Graph G, int u){
    // Function getDiscover() will return the discover time of vertex u
    // Returns UNDEF if DFS() has not yet been called
    // Pre: 1<=u<=getOrder(G)
    if(G){
        if(1>u || u>getOrder(G)){
            fprintf(stderr, "Graph Error: calling getDiscover() with invalid vertex\n");
            exit(EXIT_FAILURE);
        } else {
            return G->discover[u];
        }
    } else {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getFinish(Graph G, int u){
    // Function getFinish() will return the finish time of vertex u
    // Returns UNDEF if DFS() has not yet been called
    // Pre: 1<=u<=getOrder(G)
    if(G){
        if(1>u || u>getOrder(G)){
            fprintf(stderr, "Graph Error: calling getFinish() with invalid vertex\n");
            exit(EXIT_FAILURE);
        } else {
            return G->finish[u];
        }
    } else {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

/*** Manipulation procedures ***/

bool insertOrdered(List L, int x){
    // helper function to insert a vertice into an adjacency List at the correct position
    // returns true upon successful insertion of x into List L, false otherwise
    if(length(L) > 0){  // List is non empty
        moveFront(L);   // start at front
        for(int i=0; i<length(L); i++){
            if(x==get(L)){
                return false;   // x is already in L, np need to add again
            } else if(x<get(L)){   // x comes before cursor element
                insertBefore(L, x);
                return true;
            } else {
                moveNext(L);    
            }
        }
        if(index(L) == -1){
            append(L, x);   // x is greater than every element in L
            return true;
        }
    } else {
        append(L, x);   // list is empty
        return true;
    }
    return false;
}

void addEdge(Graph G, int u, int v){
    // inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, 
    // and v to the adjacency List of u. 
    // Pre: 1<=u<=getOrder(G), 1<=v<=getOrder(G)
    if(G){
        if (1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G)){  // u and v are in range
            List uList = G->neighbors[u];
            List vList = G->neighbors[v];
            // add u to adjacency List of v
            // add v to adjacency List of u
            if(insertOrdered(vList, u) && insertOrdered(uList, v)){
                G->size++;  // increment number of edges
            }
        } else {
            fprintf(stderr, "Graph Error: calling addEdge() with invalid vertices\n");
        exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void addArc(Graph G, int u, int v){
    // inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u 
    // but not u to the adjacency List of v
    // Pre: 1<=u<=getOrder(G), 1<=v<=getOrder(G)
    if(G){
        if (1<=u && u<=getOrder(G) && 1<=v && v<=getOrder(G)){  // u and v are in range
            List uList = G->neighbors[u];
            if(insertOrdered(uList, v)){    // add v to adjacency List of u
                G->size++;  // increment number of edges 
            }
        } else {
            fprintf(stderr, "Graph Error: calling addEdge() with invalid vertices\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int visit(Graph G, int u, int time, List* pS){
    // helper function which visits a node in DFS
    // returns the new time
    G->discover[u] = (++time);
    G->color[u] = 1;
    List adj = G->neighbors[u];
    moveFront(adj);
    while(index(adj) >= 0){
        if(G->color[get(adj)] == 0){
            G->parent[get(adj)] = u;
            time = visit(G, get(adj), time, pS);
        }
        moveNext(adj);
    }
    G->color[u] = 2;
    G->finish[u] = (++time);
    prepend(*pS, u); // add to stack after finishing, prepend for decreasing finish times
    return time;
}

void DFS(Graph G, List S){
    // DFS() will perform the depth first search algorithm on 𝐺.
    /* Pre: length(S)==getOrder(G) */
    if(G){
        if (length(S) != getOrder(G)){
            fprintf(stderr, "Graph Error: calling DFS() with invalid List argument\n");
            exit(EXIT_FAILURE);
        }
        for(int i=1; i<=getOrder(G); i++){  // initialize fields for DFS
            G->color[i] = 0;
            G->parent[i] = NIL;
        }
        int time = 0;
        // main loop of DFS
        List SPrime = newList();    // stack representing decreasing finish times of vertices
        moveFront(S);   // processes vertices in order of S
        while(index(S)>=0){
            if(G->color[get(S)] == 0){
                time = visit(G, get(S), time, &SPrime);
            }
            moveNext(S);
        }
        // concatenate SPrime to S, remove original S elements
        moveFront(SPrime);
        for(int i=1; i<=length(S); i++){
            deleteFront(S);
            append(S, get(SPrime));
            moveNext(SPrime);    
        }
        freeList(&SPrime);
    } else {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
} 

/*** Other operations ***/

Graph transpose(Graph G){
    // transpose() returns a reference to a new graph that the transpose of G
    if(G){
        Graph H = newGraph(getOrder(G));
        for(int i=1; i<getOrder(G)+1; i++){   // populate H's fields with G's data
            // matches edges of H to edges of G
            List L = G->neighbors[i];
            moveFront(L);
            while(index(L)>=0){
                addArc(H, get(L), i);   // adds edges in reversed direction
                moveNext(L);
            }
        }
	    return H;
    } else {
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

Graph copyGraph(Graph G){
    // copyGraph() returns a reference to a new graph that is a copy of G
    if(G){
        Graph H = newGraph(getOrder(G));
        for(int i=1; i<getOrder(G)+1; i++){   // populate H's fields with G's data
            H->color[i] = G->color[i];
            H->parent[i] = G->parent[i];
            H->finish[i] = G->finish[i];
            H->discover[i] = G->discover[i];
            // matches edges of H to edges of G
            List L = G->neighbors[i];
            moveFront(L);
            while(index(L)>=0){
                addArc(H, i, get(L));   
                moveNext(L);
            }
        }
	    return H;
    } else {
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void printGraph(FILE* out, Graph G){
    // prints the adjacency list representation of G to the file pointed to by out
    if (G){
        for(int i=1; i<=getOrder(G); i++){
            if (i>1){fprintf(out, "\n");}
            fprintf(out, "%i: ", i);
            printList(out, G->neighbors[i]);
        }
    } else {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}
