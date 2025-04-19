# pa2

This repository contains source files for finding the shortest path in a graph using BFS.

## Files

+ List.h: The interface for the List ADT.
+ List.c: Implementation of the List ADT.
+ Graph.h: The interface for the Graph ADT.
+ Graph.c: Implementation of the Graph ADT.
+ GraphTest.c: Student made test client for the Graph ADT.
+ FindPath.c: The program which finds the shortest path between two vertices of a given Graph.
+ Makefile: The Makefile which derives the executable and object files for and FindPath.

## Usage

To build the FindPath program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use FindPath, run the executable with two command line arguments for the input and output files.   

`$ ./FindPath <input file> <output file>`