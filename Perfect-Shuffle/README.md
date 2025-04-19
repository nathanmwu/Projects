# pa5

This repository contains source files for repeatedly performing a perfect shuffle on different sized decks of cards until the deck returns to its original state.

## Files

+ List.h: The interface for the List ADT.
+ List.cpp: Implementation of the List ADT.
+ ListTest.cpp: Student made test client for the List ADT.
+ Shuffle.c: The program which lists number of shuffles required to bring a deck back to its original state.
+ Makefile: The Makefile which derives the executable and object files for and Shuffle.
+ README.md: Lists all necessary files and provides notes and usage for the Shuffle program.

## Usage

To build the Shuffle program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use Shuffle, run the executable with one command line argument representing the largest deck size to perform perfect shuffles on.   

`$ ./Shuffle <deck size>`

## Notes

List.cpp and List.h are a different List ADT than in previous assignments. There is no longer an undefined cursor state, and the cursor lies between elements rather than underneath a particular element. With this change comes different List ADT operations. 
