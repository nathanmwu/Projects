//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA6 
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include "BigInteger.h"
#include <iostream> 
#include<fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }
 
    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
 
    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }


    // scan first line of input file, put into string
    // scan third line of input file, put into string
    // create BigInteger objects using strings
    string a;
    string b;
    getline(in, a);
    getline(in, b); // skip newline
    getline(in, b);
    BigInteger A = BigInteger(a);
    BigInteger B = BigInteger(b);   
    out << A << endl << endl; 
    out << B << endl << endl; 
    out << A+B << endl << endl;    
    out << A-B << endl << endl;
    out << A-A << endl << endl;
    out << (A+A+A) - (B+B) << endl << endl;    // 3A - 2B
    out << A*B << endl << endl;                // A * B
    out << A*A << endl << endl;                // A^2                
    out << B*B << endl << endl;                // B^2

    A = A*A*A*A;    // A = A^4
    B = B*B*B*B*B;  // B = B^5
    
    BigInteger polyA;
    BigInteger polyB;
    for(int i = 0; i < 9; i++){
        polyA += A; // polyA = 9A^4
    }
    for(int i = 0; i < 16; i++){
        polyB += B; // polyB = 16A^5
    }
    out << polyA + polyB << endl;   

    // close files 
    in.close();
    out.close();

    return 0;
}