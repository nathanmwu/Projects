//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA6 
// BigIntegerTest.cpp
// A test client for BigInteger ADT
//-----------------------------------------------------------------------------

#include"BigInteger.h"
using namespace std;

int main(){
    // constructor and comparison tests
    // A < B returns -1
    BigInteger A("1234567890123456788");
    BigInteger B("1234567890123456789");
    BigInteger C("+1234567890123456787");
    BigInteger D;
    BigInteger E("-1234567890123456787");
    cout << A.compare(B) << endl;   // positive / positive
    cout << D.compare(C) << endl;   // 0 / positive
    cout << C.compare(A) << endl;   // + / positive
    cout << C.compare(B) << endl;   // positive / +
    B.negate();
    C.negate();
    cout << C.compare(A) << endl;   // negative / positive
    cout << B.compare(C) << endl;   // negative / negative
    cout << B.compare(E) << endl;   // negative / -
    cout << B.compare(D) << endl;   // negative / 0
    cout << B.sign() << endl;
    // A > B returns 1
    B.negate();
    cout << B.compare(A) << endl;   // positive / positive
    cout << B.compare(D) << endl;   // positive / 0
    cout << D.compare(E) << endl;   // 0 / negative
    A.negate();
    cout << E.compare(A) << endl;   // negative / negative
    cout << B.sign() << endl;
    // A == B returns 0
    cout << C.compare(E) << endl;    // negative / negative
    C.negate();
    E.negate();
    cout << C.compare(E) << endl;    // positive / positive
    E.makeZero();
    cout << D.compare(E) << endl;    // 0 / 0
    cout << D.sign() << endl;
    // test copy constructor
    cout << A << endl;  // to_string / stream operator
    BigInteger F = A;
    cout << F << endl;

    cout << endl << A << endl << B << endl << C << endl << D << endl << E << endl << F << endl;
    // test overloaded operator==
    cout << (F==A) << endl; // 1
    cout << (D==A) << endl; // 0
    // test overloaded operator>
    cout << (B>A) << endl; // 1
    cout << (F>A) << endl; // 0
    cout << (A>D) << endl; // 0
    // test overloaded operator>=
    cout << (B>=A) << endl; // 1
    cout << (F>=A) << endl; // 1
    cout << (A>=D) << endl; // 0
    // test overloaded operator<
    cout << (A<D) << endl; // 1
    cout << (D<E) << endl; // 0
    cout << (D<A) << endl; // 0
    // test overloaded operator<=
    cout << (A<=D) << endl; // 1
    cout << (D<=E) << endl; // 1
    cout << (D<=A) << endl; // 0

    // tests for add
    BigInteger X("4068");
    BigInteger Y("762908");

    cout << X << " + " << Y << " = " << endl;
    cout << X+Y << endl;

    X.negate();
    cout << X << " + " << Y << " = " << endl;
    cout << X+Y << endl;

    Y.negate();
    cout << X << " + " << Y << " = " << endl;
    cout << X+Y << endl;

    X.negate();
    cout << X << " + " << Y << " = " << endl;
    cout << X+Y << endl;

    X+=X;   // test += operator
    cout << X << endl;
    
    // tests for sub
    Y.negate();

    cout << X << " - " << Y << " = " << endl;
    cout << X-Y << endl;

    X.negate();
    cout << X << " - " << Y << " = " << endl;
    cout << X-Y << endl;

    Y.negate();
    cout << X << " - " << Y << " = " << endl;
    cout << X-Y << endl;

    X.negate();
    cout << X << " - " << Y << " = " << endl;
    cout << X-Y << endl;
    
    // tests for mult
    BigInteger a("9128734667000004389234563456345619187236478");
    BigInteger b("9876545439000000000000000200000000000006543654365346534");
    cout << a << " * " << b << " = " << endl;
    cout << a*b << endl;
    a.negate();
    cout << a << " * " << b << " = " << endl;
    cout << a*b << endl;
    b.negate();
    cout << a << " * " << b << " = " << endl;
    cout << a*b << endl;
    a.negate();
    cout << a << " * " << b << " = " << endl;
    cout << a*b << endl;

    //a*=b;   // test *= operator
    //cout << a << endl;

    // test errors
    try{
        BigInteger J = BigInteger("");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        BigInteger J = BigInteger("+");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        BigInteger J = BigInteger("1232923874928#487293");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        BigInteger J = BigInteger("5298374902-273409374902872928734");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    return 0;
}