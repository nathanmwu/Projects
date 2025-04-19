# pa7

This repository contains source files for performing lexicographically sorting a file of words using a Dictionary ADT. The underlying data structure is a Binary Search Tree.

## Files

+ Dictionary.h: The interface for the Dictionary ADT.
+ Dictionary.cpp: Implementation of the Dictionary ADT.
+ ListTest.cpp: Student made test client for the List ADT.
+ DictionaryTest.cpp: Student made test client for the Dictionary ADT.
+ Makefile: The Makefile which derives the executable and object files for and Order.
+ README.md: Lists all necessary files and provides notes and usage for the Order program.

## Usage

To build the Order program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use Order, run the executable with two command line arguments representing input and output files.   

`$ ./Order <input file> <output file>`

## Notes

The provided Dictionary.h file has been slightly modified to support a private helper function  transplant(), which is used by the client function remove(). 

The pseudocode for the setValue() function has also been adapted to not call search(), which reduces runtime for large inputs by eliminating one walk of the tree to find the new key's position. 
