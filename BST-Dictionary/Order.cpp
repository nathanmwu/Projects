//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA7
// Order.cpp
// Client program that reads in a file of words and returns an output file
// consisting of the alphabetized list with each corresponding line number,
// along with the words in a pre order string.
//-----------------------------------------------------------------------------

#include "Dictionary.h"
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
    
    // read in lines, adding to Dictionary
    Dictionary D;
    std::string line; 
    int line_count = 1;
    while (getline(in, line)){
        D.setValue(line, line_count);
        line_count++;
    }

    out << D << endl;
    out << D.pre_string();

    // close files 
    in.close();
    out.close();

    return 0;
}