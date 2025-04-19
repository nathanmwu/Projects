# pa4

This repository contains source files for performing Matrix operations on a Matrix ADT.

## Files

+ List.h: The interface for the List ADT.
+ List.c: Implementation of the List ADT.
+ ListTest.c: Student made test client for the List ADT.
+ Matrix.h: The interface for the Matrix ADT.
+ Matrix.c: Implementation of the Matrix ADT.
+ MatrixTest.c: Student made test client for the Matrix ADT.
+ Sparse.c: The program which lists the outputs of various Matrix opertions on two given matrices. 
+ Makefile: The Makefile which derives the executable and object files for and Sparse.
+ README.md: Lists all necessary files and provides notes and usage for the Sparse program.

## Usage

To build the Sparse program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use Sparse, run the executable with two command line arguments for the input and output files.   

`$ ./Sparse <input file> <output file>`

## Notes

List.c and List.h are slightly modified versions of the List ADT from pa1, but instead of accepting ints as arguments for List elements, they accept void pointers to allow for the sparse Matrix representation of Matrix entries. 

The underlying ADT for a Matrix entry is an EntryObj, defined in Matrix.c.