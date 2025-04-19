# pa8

This repository contains source files for performing lexicographically sorting a file of words using a Dictionary ADT. The underlying data structure is a Red Black Tree. There is an additional main function which analyzes the frequency of words in a given text file. 

## Files

+ Dictionary.h: The interface for the Dictionary ADT.
+ Dictionary.cpp: Implementation of the Dictionary ADT.
+ ListTest.cpp: Student made test client for the List ADT.
+ DictionaryTest.cpp: Student made test client for the Dictionary ADT.
+ Makefile: The Makefile which derives the executable and object files for and Order and WordFrequncy.
+ Order.cpp: The main program which lexicographically sorts a file of words, and prints the corresponding line number and pre-order walk of the underlying RBT.
+ WordFrequency.cpp: The main program which lexicographically sorts a file of words, and prints the corresponding frequency.
+ README.md: Lists all necessary files and provides notes and usage for the Order and WordFrequency programs.

## Usage

To build the WordFrequency program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use Order, run the executable with two command line arguments representing input and output files.   

`$ ./WordFrequency <input file> <output file>`

To build the Order program, derive the necessary object and executable files by running the Makefile using   

`$ make Order`   

To use Order, run the executable with two command line arguments representing input and output files.   

`$ ./Order <input file> <output file>`

## Notes

The provided Dictionary.h file has been slightly modified to support a private helper function  transplant(), which is used by the client function remove(). 

The pseudocode for the setValue() function has also been adapted to not call search(), which reduces runtime for large inputs by eliminating one walk of the tree to find the new key's position. 

An additional helper function reg_remove() has been added to the header file, which is the same implementation as remove() from pa7. This is to avoid using RB_DeleteFixUp() in postOrderDelete, which interferes with the order in which nodes are recursively removed. 
