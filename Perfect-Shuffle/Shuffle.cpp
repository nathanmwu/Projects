//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA5 
// Shuffle.cpp
// Main program which performs a perfect shuffle repeatedly on a List until
// it returns to its original state.
//-----------------------------------------------------------------------------

#include <iomanip>
#include<stdexcept>
#include <cmath>
#include"List.h"

using namespace std;

void shuffle(List& D){
    // merges the right half of D with the left in alternating order,
    // with the first element being from the right side. If the length
    // of D is odd, the right side has one more card than the left. 
    List L, R;
    int n = D.length();     
    int l = floor(n/2);     // length of L
    // fill L with left half
    D.moveFront();
    while(D.position()<l){
        L.insertBefore(D.moveNext());
    }
    // fill R with right half
    while(D.position()<n){
        R.insertBefore(D.moveNext());
    }
    D.moveFront();
    L.moveFront();
    R.moveFront();
    // shuffle D
    while(R.position()<R.length() || L.position()<L.length()){  // there is still something to be added
        if(R.position()<R.length()){
            D.setAfter(R.peekNext());   // change next element of D to next element of R
            R.moveNext();
            D.moveNext();
        }
        if(L.position()<L.length()){
            D.setAfter(L.peekNext());   // change next element of D to next element of L
            L.moveNext();
            D.moveNext();
        }
    }
}

int main(int argc, char * argv[]){
    // check command line for correct number of arguments
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << " <deck size>" << endl;
        return(EXIT_FAILURE);
    }
    // create list, store n
    List A;
    int n = stoi(argv[1]);
    // print header
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    // shuffle for each deck size up to n
    for(int i = 1; i <= n; i++){
        // add one more element to list each time
        A.insertBefore(i-1);
        // create copy of A
        List temp = A;  
        //cout << A << endl;
        List& r = A;    // reference to A
        int count = 0;
        do{
            shuffle(r);
            count++;
        } while(!(A == temp));
        printf(" %-16i%i", i, count); 
        if(i < n){  // if not the last one, print newline character
            printf("\n");  
        }
    }
    return 0;
}