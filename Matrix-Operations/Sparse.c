/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA4 
* Sparse.c 
* Performs various operations on given Matrices
*********************************************************************************/

#include "Matrix.h"

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

    // read first line of infile, indicating n, a and b
    int n, a, b;
    fscanf(in, "%i %i %i\n\n", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // read in Matrix entries
    int row, col;
    double val;
    for(int i = 0; i < a; i++){
        fscanf(in, "%i %i %lf\n", &row, &col, &val);
        changeEntry(A, row, col, val);
    }
    fscanf(in, "\n");
    for(int i = 0; i < b; i++){
        fscanf(in, "%i %i %lf\n", &row, &col, &val);
        changeEntry(B, row, col, val);
    }
    // print output
    // A
    fprintf(out, "A has %i non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");
    // A
    fprintf(out, "B has %i non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");
    // (1.5)A
    Matrix M = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, M);
    fprintf(out, "\n");
    // A+B
    Matrix S = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, S);
    fprintf(out, "\n");
    // A+A
    Matrix S2 = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, S2);
    fprintf(out, "\n");
    // B-A
    Matrix D = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, D);
    fprintf(out, "\n");
    // A-A
    Matrix D2 = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, D2);
    fprintf(out, "\n");
    // Transpose(A)
    Matrix T = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, T);
    fprintf(out, "\n");
    // A*B
    Matrix P = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, P);
    fprintf(out, "\n");
    // B*B
    Matrix P2 = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, P2);

    // free heap memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&M);
    freeMatrix(&S);
    freeMatrix(&S2);
    freeMatrix(&D);
    freeMatrix(&D2);
    freeMatrix(&T);
    freeMatrix(&P);
    freeMatrix(&P2);

    // close files
    fclose(in);
    fclose(out);

    return 0;
}