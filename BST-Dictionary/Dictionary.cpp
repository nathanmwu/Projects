//-----------------------------------------------------------------------------
// Nathan Wu, nmwu 
// 2023 Winter CSE101 PA7
// Dictionary.cpp
// Implememtation of Dictionary ADT
//-----------------------------------------------------------------------------

#include "Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    // Initialize Node fields
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        remove(R->key);
        R = nil;
        //num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    int walk = R->key.compare(k);
    if(walk == 0 || R == nil){  
        return R;
    } else if(walk > 0) {
        return search(R->left, k);
    } else {  // R->key.compare(k) < 0
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if(R!=nil){
        while(R->left != nil){
            R = R->left;
        }
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R!=nil){
        while(R->right != nil){
            R = R->right;
        }
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N->right != nil){    // case 1
        return findMin(N->right);
    }
    Node* y = N->parent;    // case 2
    while(y != nil && N == y->right){
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N->left != nil){    // case 1
        return findMax(N->left);
    }
    Node* y = N->parent;    // case 2
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}

// Class Constructors & Destructors ----------------------------------------
   
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node("nil", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("nil", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    //postOrderDelete(root);
    clear();
    delete(nil);
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    Node* N = search(root, k);
    return (N != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node* N = search(root, k);
    if(N != nil){
        return N->val;
    } else {
        std::string error_msg = "Dictionary: getValue(): key \"" + k + "\" does not exist";
        throw std::logic_error(error_msg);
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(current == nil){
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent()){
        return current->key;
    } else {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        valType& v = current->val;
        return v;
    } else {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    num_pairs = 0;
    current = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* z = new Node(k, v);
    z->parent = nil;
    z->left = nil;
    z->right = nil;
    Node* y = nil;
    Node* x = root;
    int walk;
    while(x != nil){
        y = x;
        walk = (z->key).compare(x->key);
        if(walk == 0){  // key==k exists
            x->val = v;
            delete(z);
            return;     // terminate
        } else if(walk < 0){ // z.key < x.key  
            x = x->left;
        } else {    // z.key > x.key
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nil){
        root = z;   // tree is empty
    } else if(walk < 0){//(z->key).compare(y->key) < 0){
        y->left = z;
    } else {
        y->right = z;
    }
    num_pairs++;
}

// transplant()
// reconnects pointers of u and v depending on the number of children in
// in u
void Dictionary::transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    } else if(u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    Node* z = search(root, k);
    if(z != nil){   
        if(z == current){   // current becomes undefined
            current = nil;
        }
        if(z->left == nil){             // case 1 or case 2.1 (right only)
            transplant(z, z->right);
        } else if (z->right == nil){    // case 2.2 (left only)
            transplant(z, z->left);
        } else {                        // case 3
            Node* y = findMin(z->right);
            if(y->parent != z){
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;           
        }
        delete(z);
        num_pairs--;
    } else {
        std::string error_msg = "Dictionary: remove(): key \"" + k + "\" does not exist";
        throw std::logic_error(error_msg);
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(root != nil){
        // leftmost node is the first key alphabetically
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(root != nil){
        // rightmost node is the last key alphabetically
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(hasCurrent()){
        // sets current to nil if current is at last pair
        current = findNext(current);    
    } else {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(hasCurrent()){
        // sets current to nil if current is at first pair
        current = findPrev(current);    
    } else {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s;
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    bool eq = ( this->num_pairs == D.num_pairs );
    std::string s;
    std::string d;
    s = to_string();
    d = D.to_string();
    if(s.compare(d) != 0){
        return false;
    }
    return eq;
}

// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if( this != &D ){ // not self assignment
        // make a copy of D
        Dictionary temp = D;
        // then swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    // return this with the new data installed
    return *this;
}