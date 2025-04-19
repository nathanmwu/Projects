//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA8
// WordFrequency.cpp
// Client program that reads in a file of words and returns an output file
// consisting of the alphabetized list with each corresponding word frequency,
// along with the words in a pre order string according to the underlying RBT.
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include"Dictionary.h"

using namespace std;

std::string str_to_lower(std::string token){
    std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ return std::tolower(c); });
    return token;
}

int main(int argc, char * argv[]){

    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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

    // create RBT
    Dictionary D;
    // read each line of input file, then count and print tokens 
    while( getline(in, line) )  {
        len = line.length();

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        token = str_to_lower(token);
        // add to dictionary
        if(token != "\0"){  // not null terminating "word"
            if(D.contains(token)){
                D.setValue(token, D.getValue(token) + 1);
            } else {
                D.setValue(token, 1);
            }
        }
        while( token!="" ){  // we have a token
            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
            token = str_to_lower(token);
            // add to dictionary
            if(token != "\0"){
                if(D.contains(token)){
                    D.setValue(token, D.getValue(token) + 1);
                } else {
                    D.setValue(token, 1);
                }
            }
        }
    }
    out << D;
    // close files 
    in.close();
    out.close();
 
    return(EXIT_SUCCESS);
}
