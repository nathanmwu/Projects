# pa1

This repository contains source files for sorting lines of an input file lexicographically.

## Files

+ List.h: The interface for the List ADT.
+ List.c: Implementation of the List ADT.
+ ListTest.c: Student made test client for the List ADT.
+ Lex.c: The program which sorts lines of an input file using a List ADT.
+ Makefile: The Makefile which derives the executable and object files for mtrand and sorting.

## Usage

To build the Lex program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use Lex, run the executable with two command line arguments for the input and output files.   

`$ ./Lex <input file> <output file>`

