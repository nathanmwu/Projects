# pa3

This repository contains source files for finding the strongly connected components of a graph using DFS.

## Files

+ List.h: The interface for the List ADT.
+ List.c: Implementation of the List ADT.
+ Graph.h: The interface for the Graph ADT.
+ Graph.c: Implementation of the Graph ADT.
+ GraphTest.c: Student made test client for the Graph ADT.
+ FindComponents.c: The program which finds the strongly connected components of a given Graph.
+ Makefile: The Makefile which derives the executable and object files for and FindPath.
+ README.md: Lists all necessary files and provides notes and usage for the FindComponents program.

## Usage

To build the FindComponents program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use FindComponents, run the executable with two command line arguments for the input and output files.   

`$ ./FindComponents <input file> <output file>`

## Notes

Much of the code for this repository was adapted from pa2, such as the List and Graph ADTS and the file input of FindPath. The extraneous functions like BFS() have been removed in lieu of DFS().

When implementing the visit() helper function to DFS, I chose to pass a local copy of the time variable to visit, and have it return the updated time. 

