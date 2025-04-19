//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA7
// DictionaryTest.cpp
// Student made test client for Dictionary ADT
//-----------------------------------------------------------------------------

#include<stdexcept>
#include "Dictionary.h"

using namespace std;

int main(){
    Dictionary D;
    D.setValue("crabcake", 2);
    D.setValue("aardvark", 0);
    D.setValue("birthday", 5);
    D.setValue("dillweed", 3);
    D.setValue("energize", 4);
    D.setValue("birthday", 1);

    cout << "size D: " << D.size() << endl;
    cout << D << endl;
    cout <<  D.pre_string() << endl;

    D.remove("aardvark");

    cout << "size D: " << D.size() << endl;
    cout << D << endl;
    cout <<  D.pre_string() << endl;

    Dictionary E = Dictionary(D);   // copy constructor
    cout << "size E: " << E.size() << endl;
    cout << E << endl;
    cout <<  E.pre_string() << endl;

    E.remove("crabcake");
    E.setValue("facepalm", 5);

    cout << E << endl;
    cout <<  E.pre_string() << endl;

    cout << (D == E) << endl;   // test for equality

    D = E;  // assignment operator

    cout << "size D: " << D.size() << endl;
    cout << D << endl;
    cout <<  D.pre_string() << endl;

    cout << (D == E) << endl;   // test for equality

    cout << D.contains("birthday") << endl;         // true
    cout << D.contains("aardvark") << endl; // false

    cout << D.getValue("facepalm") << endl;

    // iterate through dictionary from beginning to end
    cout << D.hasCurrent() << endl << endl;
    for(D.begin(); D.hasCurrent(); D.next()){
        cout << D.currentKey() << " : " << D.currentVal() << endl;
    }
    cout << endl;
    // iterate through dictionary from end to beginning
    for(D.end(); D.hasCurrent(); D.prev()){
        cout << D.currentKey() << " : " << D.currentVal() << endl;
    }

    D.clear();
    Dictionary F;
    cout << D << endl;
    cout << (F==D) << endl << endl;

    // check exceptions
    try{
        D.getValue("hydroplane");
    }catch(logic_error& e){
        cout << e.what() << endl;
    }
    try{
        D.remove("hydroplane");
    }catch(logic_error& e){
        cout << e.what() << endl;
    }
    try{
        D.currentKey();
    }catch(logic_error& e){
        cout << e.what() << endl;
    }
    try{
        D.currentVal();
    }catch(logic_error& e){
        cout << e.what() << endl;
    }  
    try{
        D.next();
    }catch(logic_error& e){
        cout << e.what() << endl;
    }
    try{
        D.prev();
    }catch(logic_error& e){
        cout << e.what() << endl;
    }

    
    return 0;
}
