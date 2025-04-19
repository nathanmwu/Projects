/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA4 
* List.c 
* Functions for modified List ADT
*********************************************************************************/

#include "List.h"

// types---------------------------------------------------------------------
// Node struct definition
typedef struct NodeObj* Node;
typedef struct NodeObj {
	void* data;
	Node prev;
	Node next;
} NodeObj;

// List struct definition
typedef struct ListObj {
	int length;
	int cursorIndex;
	Node cursorElement;
	Node front;
	Node back;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
// Node constructor
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* x){
    Node n = malloc(sizeof(NodeObj));
    n->data = x;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

// Node destructor
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
		*pN = NULL;
    }
}

// List constructor
// Creates and returns a new empty List.
List newList(void){
    List L = malloc(sizeof(ListObj));
    L->length = 0;
    L->cursorIndex = -1;    // cursor is initially undefined
	L->cursorElement = NULL;
	L->front = NULL;
	L->back = NULL;
	return L;
}

// List destructor
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL){
    if( pL!=NULL && *pL!=NULL ){
        while((*pL)->length > 0){
            deleteBack(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions---------------------------------------------------------------------
int length(List L){
    // Returns the number of elements in L.
    if(L){
        return L->length;
    } else {
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

int index(List L){
    // Returns index of cursor element if defined, -1 otherwise.
    if(L){
        return L->cursorIndex;
    } else {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void* front(List L){
    // Returns front element of L. Pre: length()>0
    if(L){
        if(length(L)>0){
            return L->front->data;
        } else {
            fprintf(stderr, "List Error: calling front() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void* back(List L){
    // Returns back element of L. Pre: length()>0
    if(L){
        if(length(L)>0){
            return L->back->data;
        } else {
            fprintf(stderr, "List Error: calling back() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void* get(List L){
    // Returns cursor element of L. Pre: length()>0, index()>=0
    if(L){
        if (length(L)>0 && index(L)>=0){
            return L->cursorElement->data;
        } else if(length(L)<1){
        fprintf(stderr, "List Error: calling get() on an empty list\n");
        exit(EXIT_FAILURE);
        } else {
            fprintf(stderr, "List Error: calling get() on undefined cursor\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

// Manipulation procedures---------------------------------------------------------------------
void clear(List L){
    // Resets L to its original empty state.
    while(L->length > 0){
        deleteBack(L);
    }
    L->cursorElement = NULL;
    L->cursorIndex = -1;
}

void set(List L, void* x){
    // Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr, "List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)>0 && index(L)>=0){
        L->cursorElement->data = x;     // sets data field of cursor Node to x
    } else if(length(L)<1){
        fprintf(stderr, "List Error: calling set() on an empty list\n");
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "List Error: calling set() on undefined cursor\n");
        exit(EXIT_FAILURE);
    }
}

void moveFront(List L){
    // If L is non-empty, sets cursor under the front element, otherwise does nothing.
    if( L==NULL ){
      fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L)>0){
        L->cursorIndex = 0;
        L->cursorElement = L->front;    // cursor now is under front element
    }
} 

void moveBack(List L){
    // If L is non-empty, sets cursor under the back element, otherwise does nothing.
    if( L==NULL ){
      fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L)>0){
        L->cursorIndex = length(L) - 1; // index of back element
        L->cursorElement = L->back;    // cursor now is under back element
    }
} 

void movePrev(List L){
    // If cursor is defined and not at front, move cursor one
    // step toward the front of L; if cursor is defined and at
    // front, cursor becomes undefined; if cursor is undefined
    // do nothing
    if( L==NULL ){
      fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (L->cursorIndex>0){  // cursor is defined and not at front
        L->cursorIndex--;
        L->cursorElement = L->cursorElement->prev;
    } else if (L->cursorIndex==0){  // cursor is defined and at front
        L->cursorIndex = -1;
        L->cursorElement = NULL;
    }   // else (cursor undefined) do nothing
}

void moveNext(List L){
    // If cursor is defined and not at back, move cursor one
    // step toward the back of L; if cursor is defined and at
    // back, cursor becomes undefined; if cursor is undefined
    // do nothing
    if( L==NULL ){
      fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (L->cursorIndex==length(L)-1){  // cursor is defined and at back
        L->cursorIndex = -1;
        L->cursorElement = NULL;
    } else if (L->cursorIndex<length(L)-1 && L->cursorIndex>=0){  // cursor is defined and not at back
        L->cursorIndex++;
        L->cursorElement = L->cursorElement->next;        
    }   // else (cursor undefined) do nothing
}

void append(List L, void* x){
    // Insert new element into L. If L is non-empty, insertion takes place after back element.
    Node n = newNode(x);
    if( L==NULL ){
      fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)==0){
        L->front = n;       // inserts into empty list, so x is front and back
        L->back = n;
    } else {
        L->back->next = n;	// former back points to new back
        n->prev = L->back;	// new back points to former back		
        L->back = n;		// new back becomes List back
    }
    L->length +=1;
}

void prepend(List L, void* x){
    // Insert new element into L. If L is non-empty, insertion takes place before front element.
    Node n = newNode(x);
    if( L==NULL ){
      fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)==0){
        L->front = n;       // inserts into empty list, so x is front and back
        L->back = n;
    } else {
        L->front->prev = n;	// former front points to new front
        n->next = L->front;	// new fron points to former front		
        L->front = n;		// new front becomes List front
    }
    L->length ++;
    if(index(L)>=0){    // if cursor is defined, increment by 1 to reflect new position
        L->cursorIndex++;
    }
}

void insertBefore(List L, void* x){
    // Insert new element before cursor. Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)>0 && index(L)>=0){
        Node n = newNode(x);
        if (L->cursorIndex==0){ // insert at front
            prepend(L, x);
            freeNode(&n);   // prepend allocates memory for a node, so n is not needed
        } else {
            Node before = L->cursorElement->prev;   // this node comes before n
            Node after = L->cursorElement;  // this node comes after n
            n->prev = before;
            n->next = after;
            after->prev = n;
            before->next = n;
            L->length++;
            L->cursorIndex++;
        }
    } else if(length(L)<1){
        fprintf(stderr, "List Error: calling insertBefore() on an empty list\n");
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "List Error: calling insertBefore() on undefined cursor\n");
        exit(EXIT_FAILURE);
    }
}

void insertAfter(List L, void* x){
    // Insert new element after cursor. Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)>0 && index(L)>=0){
        Node n = newNode(x);
        if (L->cursorIndex==length(L)-1){ // insert at back
            append(L, x);
            freeNode(&n);   // append allocates memory for a node, so n is not needed
        } else {
            Node before = L->cursorElement;   // this node comes before n
            Node after = L->cursorElement->next;  // this node comes after n
            n->prev = before;
            n->next = after;
            after->prev = n;
            before->next = n;
            L->length++;
        }
    } else if(length(L)<1){
        fprintf(stderr, "List Error: calling insertAfter() on an empty list\n");
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "List Error: calling insertAfter() on undefined cursor\n");
        exit(EXIT_FAILURE);
    }
} 

void deleteBack(List L){
    // Delete the back element. Pre: length()>0
    if( L==NULL ){
      fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)>0){
        if (L->cursorIndex == length(L)-1){    // in case cursor is under back element
            L->cursorIndex = -1;    // cursor is undefined after deleting
            L->cursorElement = NULL;
        }
        Node n = L->back;   
        if(length(L)==1){       // one element left to delete
            L->front = NULL;    // empty list will have front and back NULL
            L->back = NULL;
        } else {    // length > 1
            L->back = n->prev;  // new back is second to last element
            L->back->next = NULL;   // points to NULL
        }
        freeNode(&n);
        L->length--;
    } else if(length(L)<1){
        fprintf(stderr, "List Error: calling deleteBack() on empty list\n");
        exit(EXIT_FAILURE);
    }
} 

void deleteFront(List L){
    // Delete the front element. Pre: length()>0
    if( L==NULL ){
      fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)>0){
        if (L->cursorIndex == 0){    // in case cursor is under front element
            L->cursorIndex = -1;    // cursor is undefined after deleting
            L->cursorElement = NULL;
        } else {L->cursorIndex--;}
        Node n = L->front;   
        if(length(L)==1){       // one element left to delete
            L->front = NULL;    // empty list will have front and back NULL
            L->back = NULL;
        } else {    // length > 1
            L->front = n->next;  // new front is second to front element
            L->front->prev = NULL;   // points to NULL
        }
        freeNode(&n);
        L->length--;
    } else if(length(L)<1){
        fprintf(stderr, "List Error: calling deleteFront() on an empty list\n");
        exit(EXIT_FAILURE);
    } 
} 

void delete(List L){
    // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L)>0 && index(L)>=0){
        if(index(L)==0){    // if cursor is at front, delete front
            deleteFront(L);
        } else if (index(L)== length(L)-1){ // if cursor is at back, delete back
            deleteBack(L);
        } else {
            Node before = L->cursorElement->prev;
            Node after = L->cursorElement->next;
            before->next = after;     // link outer two nodes
            after->prev = before;    // link outer two nodes
            freeNode(&(L->cursorElement));
            L->length--;
            L->cursorElement = NULL;    // cursor becomes undefined
            L->cursorIndex = -1;
        }        
    } else if(length(L)<1){
        fprintf(stderr, "List Error: calling delete() on an empty list\n");
        exit(EXIT_FAILURE);
    } else {
        fprintf(stderr, "List Error: calling delete() on undefined cursor\n");
        exit(EXIT_FAILURE);
    }
} 

void printList(FILE* out, List L){
    // Prints to the file pointed to by out, a string representation of L consisting
    // of a space separated sequence of integers, with front on left.
    if (L){
        Node n = L->front;
        int first = 1;
        while(n!=NULL){
            if(first){
                first = 0;
            } else {fprintf(out, " ");}
            fprintf(out, "%p", n->data);
            n = n->next;
        }
    } else {
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

//
