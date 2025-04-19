//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA6 
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor
List::List(const List& L){
    // make this an empty List
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    if(L.length() > 0){     // if L is not empty
        // load elements of L into this List
        Node* M = L.frontDummy->next;
        for(Node* N = M; N != L.backDummy; N = M){
            insertBefore(N->data);
            M = M->next;
        }
    }
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(num_elements == 0){
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(num_elements == 0){
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(pos_cursor == length()){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(pos_cursor == 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while(length()>0){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(pos_cursor == length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return peekPrev();
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(pos_cursor == 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return peekNext();
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* n = new Node(x);
    // link node before cursor to new node
    beforeCursor->next = n;
    n->prev = beforeCursor;
    // link node after cursor to new node
    afterCursor->prev = n;
    n->next = afterCursor;
    // update after cursor
    afterCursor = n;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* n = new Node(x);
    // link node before cursor to new node
    beforeCursor->next = n;
    n->prev = beforeCursor;
    // link node after cursor to new node
    afterCursor->prev = n;
    n->next = afterCursor;
    // update before cursor
    beforeCursor = n;
    // update cursor position
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(pos_cursor == length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(pos_cursor == 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(pos_cursor == length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    // link outer nodes
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    // erase afterCursor
    delete afterCursor;
    // update afterCursor
    afterCursor = beforeCursor->next;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(pos_cursor == 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    // link outer nodes
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    // erase afterCursor
    delete beforeCursor;
    // update beforeCursor and cursor position
    beforeCursor = afterCursor->prev;
    pos_cursor--;
    num_elements--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(pos_cursor<length()){
        if(moveNext() == x){
            return pos_cursor;
        }
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while(pos_cursor>0){
        if(movePrev() == x){
            return pos_cursor;
        }
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    // keep track of where cursor started
    int cursor = pos_cursor;
    for(int i=1; i<length(); i++){
        moveFront();
        int e;
        for(int j=0; j<i; j++){ // start at next new element
            e = moveNext();
        }
        // loop until all duplicates are removed
        int pos = findNext(e);  // cursor position after next duplicate element
        while(pos != -1){
            eraseBefore();
            if(pos <= cursor){  // if an element before the cursor is removed, 
                cursor--;       // lower position of cursor
                //beforeCursor = afterCursor->prev;
            }
            pos = findNext(e);
        }
    }
    // set cursor to new position
    while(pos_cursor > cursor){
        movePrev(); // using movePrev and moveNext updates A.beforeCursor and A.afterCursor
    }
    while(pos_cursor < cursor){
        moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List cat = *this;
    Node* N = nullptr;
    for(N=L.frontDummy->next; N!=L.backDummy; N=N->next){
        cat.insertBefore(N->data);
    }
    cat.moveFront();
    return cat;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    if(length() == 0){
        return "()";
    }
    std::string s = "(";
    for(N=frontDummy->next; N!=backDummy; N=N->next){
        if(N->next != backDummy){   
            s += std::to_string(N->data)+", ";
        } else {    // last element is reached
            s += std::to_string(N->data)+")";
        }
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
    eq = ( this->num_elements == R.num_elements );
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while(eq && N!=this->backDummy){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.

List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
        // make a copy of S
        List temp = L;
        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    // return this with the new data installed
    return *this;
    // the copy, if there is one, is deleted upon return   
}
