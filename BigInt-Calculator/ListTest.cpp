//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA6 
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------

#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    List A, B;

    //cout << "A = " << A << endl;
    // length = 0, position = 0
    cout << "Empty List:\nA.length(): " << A.length() << endl;
    cout << "A.position(): " << A.position() << endl;
    cout << "A = " << A << endl;

    // catch errors on empty list
    try{
        A.front();  // no front on empty list
    }catch( std::length_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.back();  // no back on empty list
    }catch( std::length_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }


    // populate list
    int i, n = 10;
    for(i=1; i<=n; i++){
        A.insertBefore(i);
    }

    cout << "\nNon-empty List:" << endl;
    cout << "A = " << A << endl;
    cout << "A.length(): " << A.length() << endl;   // length 10
    cout << "A.front(): " << A.front() << endl;     // 1
    cout << "A.back(): " << A.back() << endl;       // 10

    A.movePrev();
    cout << "\nmovePrev()" << endl;
    cout << "A.position(): " << A.position() << endl;   // position 9
    cout << "A.peekNext(): " << A.peekNext() << endl;   // 10
    cout << "A.peekPrev(): " << A.peekPrev() << endl;   // 9

    A.moveBack();
    cout << "\nmoveBack()" << endl;
    cout << "A.position(): " << A.position() << endl << endl;   // position 10

    // catch errors at back
    try{
        A.peekNext();   // cannot peakNext at back
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.moveNext();   // cannot moveNext at back
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.setAfter(5);   // cannot setAfter at back
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.eraseAfter();   // cannot eraseAfter at back
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    A.moveFront();
    cout << "moveFront()\nA.position(): " << A.position() << endl << endl;  // position 0

    // catch errors at front
    try{
        A.peekPrev();   // cannot peakPrev at front
    }catch( std::range_error& e ){
            cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.movePrev();   // cannot movePrev at front
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.setBefore(5);   // cannot setBefore at front
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.eraseBefore();   // cannot eraseBefore at front
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    cout << "\nfindNext(0): " << A.findNext(0) << endl;  // -1
    cout << "findPrev(0): " << A.findPrev(0) << endl;    // -1
    cout << "findNext(5): " << A.findNext(5) << endl;  // 5
    

    cout << endl << "A==B is " << (A==B?"true":"false") << endl;    // true
    // make B equal to A
    for(i=1; i<=n; i++){
        B.insertBefore(i);
    }
    cout << "A==B is " << (A==B?"true":"false") << endl;    // true

    B.clear();
    // concat with empty List
    List C = A.concat(B);
    cout << endl << "C = " << C << endl;
    B.insertAfter(6);
    B.insertAfter(5);
    // concat with non-empty List
    cout << "B = " << B << endl;
    C = A.concat(B);
    cout << "C = " << C << endl;

    A.clear();
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(4);

    for(int i=0; i<3; i++){
        A.movePrev();   
    }
    // setup example from Ed
    cout << endl << "A = " << A << endl;
    cout << A.position() << endl;   // 6
    cout << "A.peekPrev(): " << A.peekPrev() << endl;   // 2
    cout << "A.peekNext(): " << A.peekNext() << endl;   // 2
    
    A.cleanup();
    cout << "A = " << A << endl;    // (1, 2, 3, 4)
    cout << A.position() << endl;
    cout << "A.peekPrev(): " << A.peekPrev() << endl;   // 3
    cout << "A.peekNext(): " << A.peekNext() << endl;   // 4
    
    A.setAfter(1);
    A.setBefore(2);
    cout << endl << "A = " << A << endl;    // (1, 2, 2, 1)
    A.cleanup();   
    cout << "A = " << A << endl;    // (1, 2)
    cout << A.position() << endl;   // 2
    A.cleanup();    // no duplicates, should remain the same
    cout << "A = " << A << endl;    // (1, 2)
    cout << A.position() << endl;   // 2



    return 0;
}

/*
Output of this program:
Empty List:
A.length(): 0
A.position(): 0
A = 
List: front(): empty list
   continuing without interruption
List: back(): empty list
   continuing without interruption

Non-empty List:
A = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
A.length(): 10
A.front(): 1
A.back(): 10

movePrev()
A.position(): 9
A.peekNext(): 10
A.peekPrev(): 9

moveBack()
A.position(): 10

List: peekNext(): cursor at back
   continuing without interruption
List: moveNext(): cursor at back
   continuing without interruption
List: setAfter(): cursor at back
   continuing without interruption
List: eraseAfter(): cursor at back
   continuing without interruption
moveFront()
A.position(): 0

List: peekPrev(): cursor at front
   continuing without interruption
List: movePrev(): cursor at front
   continuing without interruption
List: setBefore(): cursor at front
   continuing without interruption
List: eraseBefore(): cursor at front
   continuing without interruption

findNext(0): -1
findPrev(0): -1
findNext(5): 5

A==B is false
A==B is true

C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
B = (5, 6)
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 5, 6)

A = (1, 2, 2, 3, 1, 2, 2, 1, 4)
6
A.peekPrev(): 2
A.peekNext(): 2
A = (1, 2, 3, 4)
3
A.peekPrev(): 3
A.peekNext(): 4

A = (1, 2, 2, 1)
A = (1, 2)
2
A = (1, 2)
2
*/
