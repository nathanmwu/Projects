/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA2 
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
    int* distance;
    int order;
    int size;
    int source;
} GraphObj;

/*** Constructors-Destructors ***/

// returns a Graph pointing to a newly created GraphObj representing a 
// graph having n vertices and no edges. 

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
    for(int i=0; i<n+1; i++){
        G->neighbors[i] = newList();
    }
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

// frees all heap memory associated with the Graph *pG, then sets the 
// handle *pG to NULL

void freeGraph(Graph* pG){
	if (pG!=NULL && (*pG)!=NULL){
        for(int i=0; i<getOrder(*pG)+1; i++){   // free adjacency lists
            freeList((*pG)->neighbors+i);
        }
		free((*pG)->neighbors);
		free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
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

int getSource(Graph G){
    // getSource() returns the source vertex most recently used in function BFS(),
    // or NIL if BFS() has not yet been called.
    if(G){
        return G->source;
    } else {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getParent(Graph G, int u){
    // Function getParent() will return the parent of vertex u in the BFS tree
    // created by BFS(), or NIL if BFS() has not yet been called.
    // Pre: 1<=u<=getOrder(G)
    if(G){
        if(1>u || u>getOrder(G)){
            fprintf(stderr, "Graph Error: calling getParent() with invalid vertex\n");
            exit(EXIT_FAILURE);
        }
        if(G->source == NIL){
            return NIL;
        } else {
            return G->parent[u];
        }
    } else {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

int getDist(Graph G, int u){
    // Function getDist() returns the distance from
    // the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
    // Pre: 1<=u<=getOrder(G)
    if(G){
        if(1>u || u>getOrder(G)){
            fprintf(stderr, "Graph Error: calling getDist() with invalid vertex\n");
            exit(EXIT_FAILURE);
        }
        if(G->source == NIL){   // BFS() has not been called yet
            return INF;
        } else {
            return G->distance[u];
        }
    } else {
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

void getPath(List L, Graph G, int u){
    // Function getPath() appends to the List L the vertices of a shortest path in G 
    // from source to u, or appends to L the value NIL if no such path exists. 
    // Pre: getSource(G)!=NIL, 1<=u<=getOrder(G)
    if(G){
        // check preconditions
        if(1>u || u>getOrder(G)){
            fprintf(stderr, "Graph Error: calling getPath() with invalid vertex\n");
            exit(EXIT_FAILURE);
        } else if (getSource(G) == NIL){
            fprintf(stderr, "Graph Error: calling getPath() with undefined source\n");
            exit(EXIT_FAILURE);
        }
        // append to path
        if (u == getSource(G)){
            append(L, getSource(G));
        } else if (G->parent[u] == NIL){
            append(L, NIL);
        } else {
            getPath(L, G, G->parent[u]);
            append(L, u);
        }
    } else {
        fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

/*** Manipulation procedures ***/

void makeNull(Graph G){
    // deletes all edges of G, restoring it to its original (no edge) state. 
    if(G){
        for(int i = 0; i<=getOrder(G); i++){clear(G->neighbors[i]);};    // frees adjacency Lists
        memset(G->color, 0, sizeof(*(G->color)));   // zeroes color, parent, and distance arrays
        memset(G->parent, 0, sizeof(*(G->parent)));
        memset(G->distance, 0, sizeof(*(G->distance)));
        G->size = 0;    // G now has zero edges
    } else {
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

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

void BFS(Graph G, int s){
    // runs the BFS algorithm on the Graph G with source s,
    // setting the color, distance, parent, and source fields of G accordingly
    if(G){
        if(1>s || s>getOrder(G)){
            fprintf(stderr, "Graph Error: calling BFS() with invalid source\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 1; i<=getOrder(G); i++){
            G->color[i] = 0;
            G->distance[i] = INF;
            G->parent[i] = NIL;
        }
        G->color[s] = 1;    // discover the source s
        G->distance[s] = 0;
        G->parent[s] = NIL;
        List Q = newList();
        append(Q, s);
        while(length(Q) > 0){
            int x = front(Q);
            deleteFront(Q);
            List adj = G->neighbors[x];
            moveFront(adj);
            while(index(adj)>=0){   // iterates through every adjacent vertex
                if (G->color[get(adj)] == 0){    // vertex is undiscovered
                    G->color[get(adj)] = 1;      // discover vertex
                    G->distance[get(adj)] = G->distance[x] + 1;
                    G->parent[get(adj)] = x;
                    append(Q, get(adj));
                }
                moveNext(adj);
            }
            G->color[x] = 2;    // finish x
        }
        freeList(&Q);
        G->source = s;
    } else {
        fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
}

/*** Other operations ***/

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
