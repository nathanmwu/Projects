# pa6

This repository contains source files for performing arithmetic on arbitrarily large integers, supporting operations for addition, subtraction, and multiplication.

## Files

+ List.h: The interface for the List ADT.
+ List.cpp: Implementation of the List ADT.
+ ListTest.cpp: Student made test client for the List ADT.
+ BigInteger.h: The interface for the BigInteger ADT.
+ BigInteger.cpp: Implementation of the BigInteger ADT.
+ BigIntegerTest.cpp: Student made test client for the BigInteger ADT.
+ Makefile: The Makefile which derives the executable and object files for and Arithmetic.
+ README.md: Lists all necessary files and provides notes and usage for the Arithmetic program.

## Usage

To build the Arithmetic program, derive the necessary object and executable files by running the Makefile using   

`$ make`   

To use Arithmetic, run the executable with two command line arguments representing input and output files.   

`$ ./Arithmetic <input file> <output file>`

## Notes

BigInteger.cpp uses several private helper functions for its arithmetic operations. isZero() determines whether or not a BigInteger's digits are 0, which helps simplify the result of addition or subtraction if the digits become a list of zeroes. stripLeadingZeroes() removes any leading zeros in a list of digits, and is used by the from string constructor. isNum() determines whether a base b digit from a string contains any non-numeric characters. The functions vectorAdd(), vectorDiff(), scalarMult(), and normalize() are used by the arithemtic operation functions to make operating on base b digits easier. 