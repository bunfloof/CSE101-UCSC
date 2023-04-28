/********************************************************************************* 
 * Bun Ma, jma363
 * 2022 Winter CSE101 PA7
 * Dictionary.cpp
 * Dictionary for Dictionary ADT
 *********************************************************************************/

#include "Dictionary.h"

#define BLACK 0
#define RED 1

// Class Constructors & Destructors ----------------------------------------

// Dictionary() creates new Dictionary in the empty state. 
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = BLACK; // for PA8
}

Dictionary::Dictionary() {
  nil = new Node(" ", -1); // previously nil = nullptr; in PA7
  current = nil;
  root = nil;
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
void Dictionary::setValue(keyType k, valType v) {
  Node* N = new Node(k, v);
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
      (*currentptr)->val = v;
      delete N;
      return;
    }
  }

  N->parent = parent;
  N->color = RED;
  *currentptr = N;
  
  RB_InsertFixUp(N); // edited for PA8
  num_pairs++;
}

// remove() deletes the pair for which key==k. If that pair is current, then current becomes undefined. Pre: contains(k).
void Dictionary::remove(keyType k) {
  if (!contains(k)) throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
  if (current->key == k) current = nil;

  RB_Delete(search(root, k)); // edited for PA8
  num_pairs--;
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

// Below are PA8 functions
// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
  Node* rightChild = N->right;
  Node* leftGrandchild = rightChild->left;
  rightChild->left = N;
  N->right = leftGrandchild;
  rightChild->parent = N->parent;
  if (N->parent == nil) {
    root = rightChild;
  } else if (N == N->parent->left) {
    N->parent->left = rightChild;
  } else {
    N->parent->right = rightChild;
  }
  N->parent = rightChild;

  if (leftGrandchild != nil) leftGrandchild->parent = N;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
  Node* leftChild = N->left;
  Node* rightGrandchild = leftChild->right;
  leftChild->right = N;
  N->left = rightGrandchild;
  leftChild->parent = N->parent;
  if (N->parent == nil) {
    root = leftChild;
  } else if (N == N->parent->right) {
    N->parent->right = leftChild;
  } else {
    N->parent->left = leftChild;
  }
  N->parent = leftChild;

  if (rightGrandchild != nil) rightGrandchild->parent = N;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
  while (N->parent->color == RED) {
    Node* grandparent = N->parent->parent;
    if (N->parent == grandparent->left) {
      Node* uncle = grandparent->right;
      if (uncle->color == RED) {
        N->parent->color = uncle->color = BLACK;
        grandparent->color = RED;
        N = grandparent;
      } else if (N == N->parent->right) {
        N = N->parent;
        LeftRotate(N);
      } else {
        N->parent->color = BLACK;
        grandparent->color = RED;
        RightRotate(grandparent);
      }
    } else {
      Node* uncle = grandparent->left;
      if (uncle->color == RED) {
        N->parent->color = uncle->color = BLACK;
        grandparent->color = RED;
        N = grandparent;
      } else if (N == N->parent->left) {
        N = N->parent;
        RightRotate(N);
      } else {
        N->parent->color = BLACK;
        grandparent->color = RED;
        LeftRotate(grandparent);
      }
    }
  }
  root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
  if (u->parent == nil) {
    root = v;
  } else {
    if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
  }
  v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
  while (N != root && N->color == BLACK) {
    Node* sibling = (N == N->parent->left) ? N->parent->right : N->parent->left;
    if (sibling->color == RED) {
      sibling->color = BLACK;
      N->parent->color = RED;
      if (N == N->parent->left) {
        LeftRotate(N->parent);
        sibling = N->parent->right;
      } else {
        RightRotate(N->parent);
        sibling = N->parent->left;
      }
    }
    if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
      sibling->color = RED;
      N = N->parent;
    } else {
      if (N == N->parent->left && sibling->right->color == BLACK) {
        sibling->left->color = BLACK;
        sibling->color = RED;
        RightRotate(sibling);
        sibling = N->parent->right;
      } else if (N == N->parent->right && sibling->left->color == BLACK) {
        sibling->right->color = BLACK;
        sibling->color = RED;
        LeftRotate(sibling);
        sibling = N->parent->left;
      }
      sibling->color = N->parent->color;
      N->parent->color = BLACK;
      if (N == N->parent->left) {
        sibling->right->color = BLACK;
        LeftRotate(N->parent);
      } else {
        sibling->left->color = BLACK;
        RightRotate(N->parent);
      }
      N = root;
    }
  }
  N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
  Node* node = N;
  Node* temp;
  int node_color = node->color;
  if (node->left == nil) {
    temp = node->right;
    RB_Transplant(node, node->right);
  } else if (node->right == nil) {
    temp = node->left;
    RB_Transplant(node, node->left);
  } else {
    node = findMin(node->right);
    node_color = node->color;
    temp = node->right;
    RB_Transplant(node, node->right);
    node->right = N->right;
    node->right->parent = node;
    RB_Transplant(N, node);
    node->left = N->left;
    node->left->parent = node;
    node->color = N->color;
  }
  if (node_color == BLACK) RB_DeleteFixUp(temp);
  delete N;
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