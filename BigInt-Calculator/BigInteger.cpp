//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA6 
// BigInteger.cpp
// Implementation file for the BigInteger ADT
//-----------------------------------------------------------------------------

#include"BigInteger.h"
#include"List.h"
#include<cctype>
#include<cmath>
#include<string>
#include<stdexcept>

const int p = 9;
const ListElement b = pow(10, p);

// Class Constructors & Destructors ----------------------------------------

bool isZero(List& L){
    // helper function which tells if a list is composed of all zeroes
    for(L.moveFront(); L.position()<L.length(); L.moveNext()){
        if(L.peekNext() != 0){
            return false;
        }
    }
    return true;
}

bool isNum(const std::string s){
    // helper function to parse string
    int len = s.length();
    for(int i = 0; i < len; i++){
        if(!isdigit(s.at(i))){
            return false;
        }
    }
    return true;
}

void stripLeadingZeroes(List& L){
    // helper function which removes leading zeroes from a list of digits
    if(L.length() > 0){
        for(L.moveBack(); L.peekPrev() == 0; L.eraseBefore());
    }
}

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if(s.compare("")==0){   // empty string
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    // create BigInteger in zero state
    signum = 0;
    digits = List();
    int sign_char = 0;  // there is no sign character
    double num_dig = s.length();   // initialized to length of string, represents length in b10
    if(num_dig == 0){
        return;
    }
    signum = 1; // default positive if not 0 if no sign is given
    // parse first character
    if(s.substr(0, 1).compare("-") == 0){
        signum = -1;
        sign_char = 1;
        num_dig--;  // decrement since first character is not a digit
    } else if (s.substr(0, 1).compare("+") == 0){
        sign_char = 1;
        num_dig--;  // decrement since first character is not a digit
    } 
    // else first character must be an integer
    if(num_dig>0){
        int num_elements = floor(num_dig / p);  // number of digits without leading 0s
        ListElement element;
        for(int i = 1; i <= num_elements; i++){
            std::string base_b_dig = s.substr(s.length() - (i*p), p);
            try{
                if(!isNum(base_b_dig)){
                    throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
                }
                element = std::stol(base_b_dig, nullptr, 10);
                
            } catch( std::invalid_argument& e ) {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            digits.insertBefore(element);
        }
        if(num_elements != (num_dig / p)){  // there are still digits to be processsed
            std::string base_b_dig = s.substr(sign_char, num_dig - (num_elements * p));
            try{
                element = std::stol(base_b_dig, nullptr, 10);
            } catch( std::invalid_argument& e ) {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }  
            digits.insertBefore(element);
        }
        // check to see if zero
        if(isZero(digits)){
            makeZero();
        }
        // strip off any leading zeroes
        stripLeadingZeroes(digits);
    } else {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    // front on left, is lsd
    // back on right, is msd
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.sign();
    digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if (signum > N.sign()){ // this > N
        return 1;
    }
    if(signum < N.sign()){  // this < N
        return -1;  
    }
    // this and N have same sign
    if(signum == 0){    // this == N == 0
        return 0;
    }
    // this and N nonzero, same sign
    if(digits.length() > N.digits.length()){    // this has greater magnitude
        return signum;  // 1 if positive, -1 if negative
    }
    // N has greater or equal magnitude
    if(digits.length() < N.digits.length()){    // N has greater magnitude
        return (-1)*signum;     // -1 if positive, 1 if negative
    }
    // this and N have same length
    List A = digits;
    List B = N.digits;
    A.moveBack(); B.moveBack();
    while(A.position() > 0){
        if(A.peekPrev() > B.peekPrev()){    // msd of A > msd of B, |A| > |B|
            return signum;
        }
        if(A.peekPrev() < B.peekPrev()){    // msd of A < msd of B, |B| < |A|
            return (-1)*signum;
        }
        A.movePrev(); B.movePrev(); // msd A == msd B, look at next msd
    }
    return 0;   // A and B are equal
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(signum != 0){    // this is nonzero
        signum *= -1;   // flip sign
    }
}

// BigInteger Arithmetic operations ----------------------------------------

// vectorSum()
// Helper function which returns the vector sum of two lists of base b digits
List vectorSum(List& A, List&B){
    // fill shorter operand with leading zeroes
    while(A.length() != B.length()){
        if(A.length()>B.length()){
            B.moveBack();
            B.insertAfter(0);
        }
        if(A.length()<B.length()){
            A.moveBack();
            A.insertAfter(0);
        }
    }
    List sum;
    A.moveFront();
    B.moveFront();
    while(A.position() < A.length()){
        sum.insertBefore(A.peekNext() + B.peekNext()); // add elements
        A.moveNext();
        B.moveNext();
    }
    return sum;
}

// vectorDiff()
// Helper function which returns the vector difference of two lists of base b digits
List vectorDiff(List& A, List& B){
    // fill shorter operand with leading zeroes
    while(A.length() != B.length()){
        if(A.length()>B.length()){
            B.moveBack();
            B.insertAfter(0);
        }
        if(A.length()<B.length()){
            A.moveBack();
            A.insertAfter(0);
        }
    }
    List diff;
    A.moveFront();
    B.moveFront();
    while(A.position() < A.length()){
        diff.insertBefore(A.peekNext() - B.peekNext()); // add elements
        A.moveNext();
        B.moveNext();
    }
    return diff;
}

// normalize()
// Helper function which normalizes a List into base b digits
void normalize(List& L){
    L.moveFront();   // start at lsd
    while(L.position() < L.length()){
        L.moveNext();
        ListElement e = L.peekPrev();
        if(e>=b){
            long carry = e/b;  // represents the amount needed to carry
            L.setBefore(e%b);
            if(L.position() == L.length()){
                L.insertAfter(carry);
            } else {
                L.setAfter(L.peekNext()+carry);
            }
        }
        if(e<0){
            long carry = (e/b) -1;  // represents the amount needed to carry
            L.setBefore(L.peekPrev()-(b*(carry)));
            if(L.position() == L.length()){
                L.insertAfter(carry);
            } else {
                L.setAfter(L.peekNext()+carry);
            }
        }
    }
}

// scalarMult()
// Helper function which performs scalar multiplication on a vector List
List scalarMult(List& L, long c){
    List S = L;
    if(c == 0){
        S.clear();
        return S;
    }
    for(S.moveFront(); S.position()<S.length(); S.moveNext()){
        S.setAfter(S.peekNext() * c);
    }
    return S;
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    // if one of the operands is zero, return the other
    if(signum == 0){
        BigInteger I = N;
        return I;
    }
    if(N.sign() == 0){
        BigInteger I = *this;
        return I;
    }
    BigInteger S;   // sum to return
    if((signum==1 && N.sign()==1) || (signum==-1 && N.sign()==-1)){
        // this and N have the same sign
        List A = digits;
        List B = N.digits;
        List C = vectorSum(A, B);
        normalize(C);
        S.signum = signum;
        S.digits = C;
        return S;
    }
    // if something has not been returned by this point, the operands have opposite signs
    // ignore signs, make both positive to compare magnitudes
    BigInteger a = *this;
    BigInteger b = N;
    a.signum = 1;   
    b.signum = 1;
    // this is negative, N is positive || this is positive, N is negative
    if(a.compare(b) == 1){
        // a has larger magnitude than b
        List C = vectorDiff(a.digits, b.digits);
        normalize(C);
        S.digits = C;
        S.signum = signum;  // sign will be this.sign()
    } else {
        // b has larger magnitude than a
        List C = vectorDiff(b.digits, a.digits);
        normalize(C);
        S.digits = C;
        S.signum = N.sign();    // sign will be N.sign()
    }
    // check to see if zero
    if(isZero(S.digits)){
        S.makeZero();
    }
    stripLeadingZeroes(S.digits);
    return S;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    // one of the operands is zero
    if(signum == 0){
        BigInteger I = N;
        I.signum = N.sign() * (-1);
        return I;
    }
    if(N.sign() == 0){
        BigInteger I = *this;
        return I;
    }
    BigInteger D;   // difference to return
    if((signum==1 && N.sign()==-1) || (signum==-1 && N.sign()==1)){
        // this and N have opposite signs
        List A = digits;
        List B = N.digits;
        List C = vectorSum(A, B);
        normalize(C);
        D.signum = signum;
        D.digits = C;
        return D;
    }
    // if something has not been returned by this point, the operands have the same signs
    // ignore signs, make both positive to compare magnitudes
    BigInteger a = *this;
    BigInteger b = N;
    a.signum = 1;   
    b.signum = 1;
    // this is positive, N is positive || this is negative, N is negative
    if(a.compare(b) == 1){
        // a has larger magnitude than b
        List C = vectorDiff(a.digits, b.digits);
        normalize(C);
        D.digits = C;
        D.signum = signum;  // sign will be this.sign()
    } else {
        // b has larger magnitude than a
        List C = vectorDiff(b.digits, a.digits);
        normalize(C);
        D.digits = C;
        D.signum = signum * (-1);    // sign will be opposite of this.sign()
    }
    // check to see if zero
    if(isZero(D.digits)){
        D.makeZero();
    }
    stripLeadingZeroes(D.digits);
    return D;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger P;   // product to be returned
    List sum;   // running sum which is represented as a vector
    if(signum == 0 || N.sign() == 0){
        return P;   // zero product
    }
    // calculate product of positives
    BigInteger A;
    BigInteger B;
    if(digits.length() > N.digits.length()){    // set A to the longer of the two operands
        A = *this;
        B = N;
    } else {
        B = *this;
        A = N;
    }
    A.signum = 1;
    B.signum = 1;
    // multiply
    for(B.digits.moveFront(); B.digits.position()<B.digits.length(); B.digits.moveNext()){
        ListElement b_dig = B.digits.peekNext();
        if(b_dig != 0){     // skip if digit is 0
            List a = scalarMult(A.digits, b_dig);   // scalarMult
            // add zeroes (shift)
            a.moveFront();
            for(int i = 0; i < B.digits.position(); i++){
                a.insertAfter(0);
            }
            sum = vectorSum(sum, a);            // add
            normalize(sum);                     // normalize
        }
    }
    P.digits = sum;
    // compute product sign
    if(signum == N.sign()){ // this and N have same sign, so product is positive
        P.signum = 1;
    } else {    // this and N have opposite signs, so product is negative
        P.signum = -1;
    }
    stripLeadingZeroes(P.digits);
    return P;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    if(signum == 0){    // zero state
        return "0";
    }
    std::string s = "";
    if(signum == -1){
        s += "-";   // prefix with negative sign
    }
    //s += digits.to_string();
    digits.moveBack();
    // do first digit outside of loop to avoid adding leading zeroes
    s += std::to_string(digits.peekPrev()); // concatenates to the string each subsequent base b digit
    digits.movePrev();
    while(digits.position()>0){
        // add leading zeroes to each base b digit
        int num_zeroes = p - std::to_string(digits.peekPrev()).length();
        for(int i = 0; i < num_zeroes; i++){
            s += '0';   
        }
        s += std::to_string(digits.peekPrev()); // concatenates to the string each subsequent base b digit
        digits.movePrev();
    }
    return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)==0){    // strictly equal
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)==-1){    // A strictly less than B
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)<1){    // A less than or equal to B
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)==1){    // A strictly greater than B
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)>-1){    // A greater than or equal to B
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    return (A = A.add(B));
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    return (A = A.sub(B));
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    return (A = A.mult(B));
}
