/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA4 
* Matrix.c 
* Functions for Matrix ADT 
*********************************************************************************/

#include "Matrix.h"

// Types ---------------------------------------------------------------------
// Entry struct definition
typedef struct EntryObj* Entry;
typedef struct EntryObj {
	int col;
	double val;
} EntryObj;

// Matrix struct definition
typedef struct MatrixObj {
	List* row;
    int size;
    int nnz;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------
// Entry constructor
Entry newEntry(int c, double x){
    // Returns reference to new Entry object. Initializes column and data fields
    Entry e = malloc(sizeof(EntryObj));
    e->col = c;
    e->val = x;
    return e;
}

// Entry destructor
void deleteEntry(Entry* pE){
    // Frees heap memory pointed to by *pE, sets *pE to NULL.
    if( pE!=NULL && *pE!=NULL ){
        free(*pE);
		*pE = NULL;
    }
}

// Matrix constructor
Matrix newMatrix(int n){
    // Returns a reference to a new nXn Matrix object in the zero state.
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nnz = 0;
    M->row = calloc(n+1, sizeof(List)); // 0th row / column are left empty for easy indexing
    for(int i = 1; i < n+1; i++){
        M->row[i] = newList();
    }
    return M;
}

void freeMatrix(Matrix* pM){
    // Frees heap memory associated with *pM, sets *pM to NULL.
    if( pM!=NULL && *pM!=NULL ){
        for(int i = 1; i <= (*pM)->size; i++){
            List row = (*pM)->row[i];
            moveFront(row);
            for(int i = 0; i < length(row); i++){
                Entry e = get(row);
                deleteEntry(&e);
                moveNext(row);
            }
            freeList(&row);
        }
        free((*pM)->row);
        free(*pM);
        *pM = NULL;
    }
}

// Access Functions -----------------------------------------------------------

int size(Matrix M){
    // Return the size of square Matrix M.
    if(M){
        return M->size;
    } else {
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

int NNZ(Matrix M){
    // Return the number of non-zero elements in M.
    if(M){
        return M->nnz;
    } else {
        fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A && B){
        if(A == B){ // trivial equality
            return 1;
        }
        if (NNZ(A) == NNZ(B) && size(A) == size(B)){    // check easy conditions
            for(int i = 1; i <= size(A); i++){
                if (length(A->row[i]) == length(B->row[i])){    // each row must be same length
                    moveFront(A->row[i]);
                    moveFront(B->row[i]);
                    while(index(A->row[i])>-1){
                        Entry a = get(A->row[i]);
                        Entry b = get(B->row[i]);
                        if(a->col == b->col && a->val == b->val){   // compare columns and values
                            moveNext(A->row[i]);
                            moveNext(B->row[i]);
                        } else {
                            return 0;
                        }
                    }
                } else {
                    return 0;
                }
            }
        } else {
            return 0;
        }
        return 1;
    } else {
        fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

// Manipulation Procedures -----------------------------------------------------------

void makeZero(Matrix M){
    // Re-sets M to the zero Matrix state.
    if(M){
        for(int i = 1; i <= size(M); i++){  // clears all rows of M
            for(moveFront(M->row[i]); index(M->row[i])>-1; moveNext(M->row[i])){
                Entry e = get(M->row[i]);
                deleteEntry(&e);
            }
            clear(M->row[i]);
        }
        M->nnz = 0;
    } else {
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

void changeEntry(Matrix M, int i, int j, double x){
    // Changes the ith row, jth column of M to the value x.
    // Pre: 1<=i<=size(M), 1<=j<=size(M)
    if(M){
        // check preconditions
        if(1>i || i>size(M)){
            fprintf(stderr, "Matrix Error: calling changeEntry() with invalid row index\n");
            exit(EXIT_FAILURE);
        } else if(1>j || j>size(M)){
            fprintf(stderr, "Matrix Error: calling changeEntry() with invalid column index\n");
            exit(EXIT_FAILURE);
        }
        List r = M->row[i];
        if(length(r) == 0){ // row is empty
            if(x!=0){   // x = 0, Mij = 0
                Entry new = newEntry(j, x);
                append(r, new);
                M->nnz++;
                return;
            }
        } else {    // row has elements
            if(x==0){
                for(moveFront(r); index(r)>-1; moveNext(r)){
                    Entry e = get(r);
                    if(e->col > j){ // x = 0, Mij = 0
                        return;
                    }
                    if(e->col==j){  // x = 0, Mij != 0
                        deleteEntry(&e);
                        delete(r);
                        M->nnz--;
                        return;
                    }
                }
            } else {
                for(moveFront(r); index(r)>-1; moveNext(r)){
                    Entry e = get(r);
                    if(e->col > j){ // x != 0, Mij = 0
                        Entry new = newEntry(j, x);
                        insertBefore(r, new);
                        M->nnz++;
                        return;
                    }
                    if(e->col == j){    // x != 0, Mij != 0
                        Entry new = newEntry(j, x);
                        insertBefore(r, new);
                        deleteEntry(&e);
                        delete(r);
                        return;
                    }
                }
                // x != 0, Mij = 0
                Entry new = newEntry(j, x);
                append(r, new);
                M->nnz++;
                return;
            }
        }
    } else {
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

Matrix copy(Matrix A){
    // Returns a reference to a new Matrix object having the same entries as A.
    if(A){
        Matrix B = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
            List r = A->row[i];
            if(length(r) > 0){
                for(moveFront(r); index(r)>-1; moveNext(r)){
                    Entry curr = get(r);
                    changeEntry(B, i, curr->col, curr->val);    // for every nnz, create copy in new matrix
                }
            }
        }
        return B;
    } else {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

Matrix transpose(Matrix A){
    // Returns a reference to a new Matrix object representing the transpose
    // of A.
    if(A){
        Matrix T = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
            List r = A->row[i];
            if(length(r) > 0){
                for(moveFront(r); index(r)>-1; moveNext(r)){
                    Entry curr = get(r);
                    changeEntry(T, curr->col, i, curr->val);    // for every nnz, create inverse in new matrix
                }
            }
        }
        return T;
    } else {
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

Matrix scalarMult(double x, Matrix A){
    // Returns a reference to a new Matrix object representing xA.
    if(A){
        Matrix xA = newMatrix(size(A));
        for(int i = 1; i <= size(A); i++){
            List r = A->row[i];
            if(length(r) > 0){
                for(moveFront(r); index(r)>-1; moveNext(r)){
                    Entry curr = get(r);
                    changeEntry(xA, i, curr->col, x * curr->val);    // for every nnz, create inverse in new matrix
                }
            }
        }
        return xA;
    } else {
        fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

Matrix sum(Matrix A, Matrix B){
    // Returns a reference to a new Matrix object representing A+B.
    // pre: size(A)==size(B)
    if(A && B){
        // check preconditions
        if (size(A) == size(B)){
            if (equals(A, B)){
                return scalarMult(2, A);
            }
            Matrix s = newMatrix(size(A));
            for(int i = 1; i <= size(A); i++){
                List rowA = A->row[i];
                List rowB = B->row[i];
                if (length(rowA) == 0 && length(rowB) == 0){    // 2 zero rows
                    continue;
                } else if (length(rowB) == 0){  // only rowB is zero
                    // add all of A
                    for(moveFront(rowA); index(rowA)>-1; moveNext(rowA)){
                        Entry e = get(rowA);
                        changeEntry(s, i, e->col, e->val);
                    }
                } else if(length(rowA) == 0){   // only rowA is zero
                    // add all of B
                    for(moveFront(rowB); index(rowB)>-1; moveNext(rowB)){
                        Entry e = get(rowB);
                        changeEntry(s, i, e->col, e->val);
                    }
                } else {    // 2 nonzero rows
                    // add however much before exhausting rowA or rowB
                    moveFront(rowA);
                    moveFront(rowB);
                    while( index(rowA)>=0 && index(rowB)>=0 ){
                        Entry a = get(rowA);
                        Entry b = get(rowB);
                        if(a->col > b->col){
                            changeEntry(s, i, b->col, b->val);
                            moveNext(rowB);
                        } else if(a->col < b->col){
                            changeEntry(s, i, a->col, a->val);
                            moveNext(rowA);
                        } else if (a->col == b->col){
                            changeEntry(s, i, a->col, b->val + a->val);
                            moveNext(rowA);
                            moveNext(rowB);
                        }
                    }
                    // flush remaining entries
                    while( index(rowA)>=0 ){
                        Entry a = get(rowA);
                        changeEntry(s, i, a->col, a->val);
                        moveNext(rowA);
                    }
                    while( index(rowB)>=0 ){
                        Entry b = get(rowB);
                        changeEntry(s, i, b->col, b->val);
                        moveNext(rowB);
                    }
                }
            }
            return s;
        } else {
            fprintf(stderr, "Matrix Error: calling sum() on differently sized matrices\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

Matrix diff(Matrix A, Matrix B){
    // Returns a reference to a new Matrix object representing A-B.
    // pre: size(A)==size(B)
    if(A && B){
        if(equals(A, B)){
            Matrix d = newMatrix(size(A));  // zero matrix
            return d;
        }
        if (size(A) == size(B)){
            Matrix subtract = scalarMult(-1, B);
            Matrix d = sum(A, subtract);    // A-B = A + (-1*B)
            freeMatrix(&subtract);
            return d;
        } else {
            fprintf(stderr, "Matrix Error: calling diff() on differently sized matrices\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

double vectorDot(List P, List Q){
    // helper function which returns the dot product of two matrix rows
    if(length(P) == 0 || length(Q) == 0){   // dot with zero vector results in 0
        return 0;
    }
    double sum = 0; // running total
    moveFront(P);
    moveFront(Q);
    while(index(P)>-1 && index(Q)>-1){
        Entry p = get(P);
        Entry q = get(Q);
        if(p->col > q->col){
            moveNext(Q);
        } else if(p->col < q->col){
            moveNext(P);
        } else if (p->col == q->col){   // sum is increased when P and Q share a column
            sum += (p->val * q->val);
            moveNext(Q);
            moveNext(P);
        }
    }   // if either P or Q is exhausted, the rest of the dot product will sum to 0
    return sum;
}

Matrix product(Matrix A, Matrix B){
    // Returns a reference to a new Matrix object representing AB
    // pre: size(A)==size(B)
    if(A && B){
        if (size(A) == size(B)){
            Matrix P = newMatrix(size(A));
            Matrix T = transpose(B);
            for(int i = 1; i<=size(A); i++){    // iterate through rows of A
                if(length(A->row[i])>0){     // row and column are both nonzero
                    for(int j = 1; j<=size(A); j++){    // iterate through columns of B (rows of T)
                        if(length(T->row[j])>0){
                            double dot = vectorDot(A->row[i], T->row[j]);
                            if(dot!=0){
                                changeEntry(P, i, j, dot);
                            }
                        }
                    }
                }
            }
            freeMatrix(&T);     // free heap memory
            return P;
        } else {
            fprintf(stderr, "Matrix Error: calling product() on differently sized matrices\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}

// Matrix Arithmetic operations ---------------------------------------------------

void printMatrix(FILE* out, Matrix M){
    // Prints a string representation of Matrix M to filestream out. Zero rows
    // are not printed. Each non-zero row is represented as one line consisting
    // of the row number, followed by a colon, a space, then a space separated
    // list of pairs "(col, val)" giving the column numbers and non-zero values
    // in that row. The double val will be rounded to 1 decimal point.
    if(M){
        for(int i = 1; i <= M->size; i++){
            List r = M->row[i];
            if(length(r) > 0){
                fprintf(out, "%i: ", i);
                for(moveFront(r); index(r) > -1; moveNext(r)){
                    Entry e = get(r);
                    fprintf(out, "(%i, %.1f) ", e->col, e->val);
                }
                if(i<size(M)){
                    fprintf(out, "\n");
                }
            }
        }
    } else {
        fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
}