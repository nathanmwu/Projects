/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA4 
* MatrixTest.c 
* Test client for Matrix ADT 
*********************************************************************************/

#include "Matrix.h"
#define out stdout

int main(){
    Matrix M = newMatrix(5);
    printf("size: %i\n", size(M));

    printf("nnz: %i\n", NNZ(M));
    changeEntry(M, 1, 1, 4);
    changeEntry(M, 1, 3, 2);
    changeEntry(M, 1, 2, 3);
    changeEntry(M, 1, 4, 4);
    changeEntry(M, 1, 3, 0);
    changeEntry(M, 2, 1, 2);
    changeEntry(M, 3, 1, 0);
    changeEntry(M, 2, 2, 2);
    changeEntry(M, 3, 3, 0);

    Matrix N = newMatrix(5);
    changeEntry(N, 1, 1, 1);
    changeEntry(N, 1, 3, 1);
    changeEntry(N, 3, 1, 1);
    changeEntry(N, 3, 2, 1);
    changeEntry(N, 3, 3, 1);

    Matrix P = product(M, N);
    Matrix S = sum(M, M);
    Matrix D = diff(M, N);
    Matrix sm = scalarMult(3, M);
    Matrix C = copy(M);
    Matrix T = transpose(M);

    printf("Matrix M:\n");
    printMatrix(out, M);
    printf("\n");
    printf("nnz: %i\n", NNZ(M));

    printf("Matrix N:\n");
    printMatrix(out, N);
    printf("\n");
    printf("nnz: %i\n", NNZ(N));

    printf("Matrix M copy:\n");
    printMatrix(out, C);
    printf("\n");

    printf("Transpose M:\n");
    printMatrix(out, T);
    printf("\n");

    if(equals(M, C)){
        printf("M and M copy are equal\n");
    } else {
        exit(EXIT_FAILURE);
    }

    printf("M+M:\n");
    printMatrix(out, S);
    printf("\n");

    printf("M-N:\n");
    printMatrix(out, D);
    printf("\n");

    printf("3*N:\n");
    printMatrix(out, sm);
    printf("\n");

    printf("M*N:\n");
    printMatrix(out, P);
    printf("\n");

    // zeroed
    makeZero(M);
    printf("nnz: %i\n", NNZ(M));

    // free heap memory
    freeMatrix(&M);
    freeMatrix(&N);
    freeMatrix(&S);
    freeMatrix(&D);
    freeMatrix(&C);
    freeMatrix(&P);
    freeMatrix(&T);
    freeMatrix(&sm);

    return 0;
}
/* output of this program:
size: 5
nnz: 0
Matrix M:
1: (1, 4.0) (2, 3.0) (4, 4.0) 
2: (1, 2.0) (2, 2.0) 

nnz: 5
Matrix N:
1: (1, 1.0) (3, 1.0) 
3: (1, 1.0) (2, 1.0) (3, 1.0) 

nnz: 5
Matrix M copy:
1: (1, 4.0) (2, 3.0) (4, 4.0) 
2: (1, 2.0) (2, 2.0) 

Transpose M:
1: (1, 4.0) (2, 2.0) 
2: (1, 3.0) (2, 2.0) 
4: (1, 4.0) 

M and M copy are equal
M+M:
1: (1, 8.0) (2, 6.0) (4, 8.0) 
2: (1, 4.0) (2, 4.0) 

M-N:
1: (1, 3.0) (2, 3.0) (3, -1.0) (4, 4.0) 
2: (1, 2.0) (2, 2.0) 
3: (1, -1.0) (2, -1.0) (3, -1.0) 

3*N:
1: (1, 12.0) (2, 9.0) (4, 12.0) 
2: (1, 6.0) (2, 6.0) 

M*N:
1: (1, 4.0) (3, 4.0) 
2: (1, 2.0) (3, 2.0) 

nnz: 0
*/