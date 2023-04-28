/********************************************************************************* 
 * Bun Ma, jma363
 * 2022 Winter CSE101 PA7
 * Dictionary.cpp
 * Dictionary for Dictionary ADT
 *********************************************************************************/

#include "Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

// Dictionary() creates new Dictionary in the empty state. 
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
}

Dictionary::Dictionary() {
  nil = nullptr;
  current = nullptr;
  root = nullptr;
  num_pairs = 0;
}

// Dictionary copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
  nil = new Node(" ", -1);
  current = nil;
  root = nil;
  //num_pairs = D.num_pairs;
  num_pairs = 0;
  preOrderCopy(D.root, D.nil);
}
// Dictionary destructor
Dictionary::~Dictionary() {
  clear();
  delete nil; // remember to free memory
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString() appends a string representation of the tree rooted at R to string s. The string appended consists of: "key : value \n" for each key-value pair in tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
  if (R == nil) return;
  inOrderString(s, R->left);
  s += R->key + " : " + std::to_string(R->val) + '\n';
  inOrderString(s, R->right);
}

// preOrderString() appends a string representation of the tree rooted at R to s. The appended string consists of keys only, separated by "\n", with the order determined by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
  if (R == nil) return;
  s += R->key + '\n';
  preOrderString(s, R->left);
	preOrderString(s, R->right);
}
// preOrderCopy() recursively inserts a deep copy of the subtree rooted at R into this Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
  if (R == N) return;
  setValue(R->key, R->val);
  preOrderCopy(R->left, N);
  preOrderCopy(R->right, N);
}

// postOrderDelete() deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
  if (R == nil) return;
  postOrderDelete(R->left);
  postOrderDelete(R->right);
  delete(R);
}

// search() searches the subtree rooted at R for a Node with key==k. Returns the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
  if (R == nil) return R;
  if (R->key > k) {
    return search(R->left, k);
  } else if (R->key < k) return search(R->right, k);
  return R;
}

// findMin() if the subtree rooted at R is not empty, returns a pointer to the leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
  if (R == nil) return nil;
  Node *temp = R;
  while (temp->left != nil) {
    temp = temp->left;
  }
  return temp;
}

// findMax() if the subtree rooted at R is not empty, returns a pointer to the rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
  if (R == nil) return nil;
  Node *temp = R;
  while (temp->right != nil) {
    temp = temp->right;
  }
  return temp;
}

// findNext() if N does not point to the rightmost Node, returns a pointer to the Node after N in an in-order tree walk. If N points to the rightmost Node, or is nil, returns nil. Node* findNext(Node* N);
Dictionary::Node* Dictionary::findNext(Node* N) {
  //if (N == nil) return nil;
  if (N->right != nil) return findMin(N->right);
  Node *temp = N->parent;
  while (temp != nil && N == temp->right) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

// findPrev() if N does not point to the leftmost Node, returns a pointer to the Node before N in an in-order tree walk.  If N points to the leftmost Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
  if (N == nil) return nil;
  if (N->left != nil) return findMax(N->left);
  Node *temp = N->parent;
  while (temp != nil && N == temp->left) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

// Access functions --------------------------------------------------------

// size() returns the size of this Dictionary.
int Dictionary::size() const {
  return num_pairs;
}

// contains() returns true if there exists a pair such that key==k, and returns false otherwise.
bool Dictionary::contains(keyType k) const {
  return this->search(root, k) != nil;
}

// getValue() returns a reference to the value corresponding to key k. Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
  Node *temp = this->search(root, k);
  if (temp == nil) throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
  return temp->val;
}

// hasCurrent() returns true if the current iterator is defined, and returns false otherwise.
bool Dictionary::hasCurrent() const {
  return current != nil;
}

// currentKey() returns the current key. Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
  if (current == nil) throw std::logic_error("Dictionary: currentKey(): current undefined");
  return current->key;
}

// currentVal() returns a reference to the current value. Pre: hasCurrent()
valType& Dictionary::currentVal() const {
  if (current == nil) throw std::logic_error("Dictionary: currentVal(): current undefined");
  return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear() resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
  postOrderDelete(root);
  root = nil;
  current = nil;
  num_pairs = 0;
}

// setValue() if a pair with key==k exists, overwrites the corresponding value with v, otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType value) {
  Node* N = new Node(k, value);
  N->left = nil;
  N->right = nil;

  Node* parent = this->nil;
  Node** currentptr = &this->root;

  while (*currentptr != this->nil) {
    parent = *currentptr;

    if (k < (*currentptr)->key) {
      currentptr = &((*currentptr)->left);
    } else if (k > (*currentptr)->key) {
      currentptr = &((*currentptr)->right);
    } else {
      (*currentptr)->val = value;
      delete N;
      return;
    }
  }

  N->parent = parent;
  *currentptr = N;

  num_pairs++;
}

// remove() deletes the pair for which key==k. If that pair is current, then current becomes undefined. Pre: contains(k).
void Dictionary::remove(keyType k) {
  if (!contains(k)) throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");

  Node *deltemp = search(root, k);
  if (deltemp->left == nil || deltemp->right == nil) {
    Node *child = deltemp->left == nil ? deltemp->right : deltemp->left;
    if (deltemp->parent == nil) {
      root = child;
    } else if (deltemp == deltemp->parent->left) {
      deltemp->parent->left = child;
    } else {
      deltemp->parent->right = child;
    }
    if (child != nil) child->parent = deltemp->parent;
  } else {
    Node *successor = findMin(deltemp->right);
    if (successor->parent != deltemp) {
      if (successor->right != nil) successor->right->parent = successor->parent;
      successor->parent->left = successor->right;
      successor->right = deltemp->right;
      successor->right->parent = successor;
    }
    (deltemp == root ? root : deltemp->parent->left == deltemp ? deltemp->parent->left : deltemp->parent->right) = successor;
    successor->parent = deltemp->parent;
    successor->left = deltemp->left;
    successor->left->parent = successor;
  }

  if (current == deltemp) current = nil;
  delete deltemp;

  this->num_pairs--;
}

// begin() if non-empty, places current iterator at the first (key, value) pair (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
  if (num_pairs <= 0) throw std::length_error("Dictionary: begin(): Dictionary is empty");
  current = findMin(root);
}

// end() if non-empty, places current iterator at the last (key, value) pair (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
  if (num_pairs <= 0) throw std::length_error("Dictionary: end(): Dictionary is empty");
  current = findMax(root);
}

// next() if the current iterator is not at the last pair, advances current to the next pair (as defined by the order operator < on keys). If the current iterator is at the last pair, makes current undefined. Pre: hasCurrent()
void Dictionary::next() {
  if (current == nil) throw std::logic_error("Dictionary: next(): current undefined");
  current = findNext(current);
}

// prev() if the current iterator is not at the first pair, moves current to the previous pair (as defined by the order operator < on keys). If the current iterator is at the first pair, makes current undefined. Pre: hasCurrent()
void Dictionary::prev() {
  if (current == nil) throw std::logic_error("Dictionary: prev(): current undefined");
  current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string() returns a string representation of this Dictionary. Consecutive (key, value) pairs are separated by a newline "\n" character, and the items key and value are separated by the sequence space-colon-space " : ". The pairs are arranged in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
  std::string s = "";
  inOrderString(s, root);
  return s;
}

// pre_string() returns a string consisting of all keys in this Dictionary. Consecutive keys are separated by newline "\n" characters. The key order is given by a pre-order tree walk.
std::string Dictionary::pre_string() const {
  std::string s = "";
  preOrderString(s, root);
  return s;
}

// equals() returns true if and only if this Dictionary contains the same (key, value) pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
  return (num_pairs == D.num_pairs) && (to_string() == D.to_string());
}

// Overloaded Operators ----------------------------------------------------

// operator<<() inserts string representation of Dictionary D into stream, as defined by member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
  return stream << D.to_string();
}

// operator==() returns true if and only if Dictionary A equals Dictionary B, as defined by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
  return A.equals(B);
}

// operator=() overwrites the state of this Dictionary with state of D, and returns a reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
  if (this != &D) {
    Dictionary temp = D;
    std::swap(nil, temp.nil);
    std::swap(root, temp.root);
    std::swap(current, temp.current);
    std::swap(num_pairs, temp.num_pairs);
  }
  return *this;
}