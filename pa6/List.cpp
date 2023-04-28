/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA6
* List.cpp
* List for List ADT originally from PA2 reused in PA4, rev for PA6
*********************************************************************************/ 

#include "List.h"

/* Class Constructors & Destructors */


// --- Private constructors ---
List::Node::Node(ListElement x) {
  data = x;
  next = nullptr;
  prev = nullptr;
}

// --- Public constructors ---
// List() creates new List in the empty state.
List::List() {
  frontDummy = new Node(-420);
  backDummy = new Node(420);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// List(const List &L) copy constructor.
List::List(const List& L) {
  frontDummy = new Node(-420);
  backDummy = new Node(420);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;

  Node *N = L.frontDummy->next;
  while (N != L.backDummy) {
    this->insertBefore(N->data);
    N = N->next;
  }
}

// ~List() Destructor
List::~List() {
  this->clear();
  delete frontDummy;
  delete backDummy;
}

// Access functions --------------------------------------------------------

// length() returns the length of this List.
int List::length() const {
  return num_elements;
}

// front() returns the front element in this List. pre: length() > 0
ListElement List::front() const {
  if (length() <= 0) throw std::length_error("List: front(): empty list");
  return frontDummy->next->data;
}

// back() returns the back element in this list. pre: length() > 0
ListElement List::back() const {
  if (length() <= 0) throw std::length_error("List: back(): empty list");
  return backDummy->prev->data;
}

// position() returns the position of the cursor in this List. 0 <= position() <= length()
int List::position() const {
  return pos_cursor;
}

// peekNext() returns the element after the cursor. pre: position() < length()
ListElement List::peekNext() const {
  //if (position() >= length()) throw std::range_error("List: peekNext(): position is out of range or at range");
  if (position() == length()) throw std::range_error("List: peekNext(): cursor at back");
  if (position() > length()) throw std::range_error("List: peekNext(): cursor at front");
  return afterCursor->data;
}

// peekPrev() returns the element before the cursor. pre: position() > 0
ListElement List::peekPrev() const {
  //if (position() <= 0) throw std::range_error("List: peekPrev(): position is out of range or at range");
  if (position() == 0) throw std::range_error("List: peekPrev(): cursor at front");
  if (position() < 0) throw std::range_error("List: peekPrev(): cursor at back");
  return beforeCursor->data;
}

// Manipulation procedures ----------------------------------------------------

// clear deletes all elements in this List, setting it to the empty state.
void List::clear() {
  moveFront();
  while(length() > 0) eraseAfter();
}

// moveFront() moves cursor to position 0 in this List.
void List::moveFront() {
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
}

// moveBack() moves cursor to position length() in this List.
void List::moveBack() {
  beforeCursor = backDummy->prev;
  afterCursor = backDummy;
  pos_cursor = length(); // num_elements
}

// Note to myself: new error messages may pose inaccuracies about pos_cursor but matches output regardless
// moveNext() advances cursor to next higher position. Returns the List element that was passed over. pre: position() < length()
ListElement List::moveNext() {
  //if (position() >= length()) throw std::range_error("List: moveNext(): position is out of range or at range");
  if (position() == length()) throw std::range_error("List: moveNext(): cursor at back");
  if (position() > length()) throw std::range_error("List: moveNext(): cursor at front");
  beforeCursor = afterCursor;
  afterCursor = afterCursor->next;
  pos_cursor++;
  return beforeCursor->data;
}

// movePrev() advances cursor to next lower position. Returns the List element that was passed over. pre: position() > 0
ListElement List::movePrev() {
  //if (position() <= 0) throw std::range_error("List: movePrev(): position is out of range or at range");
  if (position() == 0) throw std::range_error("List: movePrev(): cursor at front");
  if (position() < 0) throw std::range_error("List: movePrev(): cursor at back");
  afterCursor = beforeCursor;
  beforeCursor = beforeCursor->prev;
  pos_cursor--;
  return afterCursor->data;
}

// insertAfter() inserts x after cursor.
void List::insertAfter(ListElement x) {
  Node *N = new Node(x);
  N->prev = beforeCursor;
  N->next = afterCursor;
  beforeCursor->next = N;
  afterCursor->prev = N;
  
  afterCursor = N;
  num_elements++;
}

// insertBefore() inserts x before cursor.
void List::insertBefore(ListElement x) {
  Node *N = new Node(x);
  N->prev = beforeCursor;
  N->next = afterCursor;
  beforeCursor->next = N;
  afterCursor->prev = N;
  
  beforeCursor = N;
  pos_cursor++;

  num_elements++;
}

// setAfter() overwrites the List element after the cursor with x. pre: position() < length()
void List::setAfter(ListElement x) {
  //if (position() >= length()) throw std::range_error("List: setAfter(): position is out of range or at range");
  if (position() == length()) throw std::range_error("List: setAfter(): cursor at back");
  if (position() > length()) throw std::range_error("List: setAfter(): cursor at front");
  afterCursor->data = x;
}

// setBefore() overwrites the List element before the cursor with x. pre: position() > 0
void List::setBefore(ListElement x) {
  //if (position() <= 0) throw std::range_error("List: setBefore(): position is out of range or at range");
  if (position() == 0) throw std::range_error("List: setBefore(): cursor at front");
  if (position() < 0) throw std::range_error("List: setBefore(): cursor at back");
  beforeCursor->data = x;
}

// eraseAfter() deletes element after cursor. pre: position() < length()
void List::eraseAfter() {
  //if (position() >= length()) throw std::range_error("List: eraseAfter() position is out of range or at range");
  if (position() == length()) throw std::range_error("List: eraseAfter(): cursor at back");
  if (position() > length()) throw std::range_error("List: eraseAfter(): cursor at front");
  Node *N = afterCursor;
  beforeCursor->next = N->next;
  afterCursor->next->prev = beforeCursor;
  afterCursor = N->next;
  delete N;
  num_elements--;
}

// eraseBefore() deletes element before cursor. pre: position() > 0
void List::eraseBefore() {
  //if (position() <= 0) throw std::range_error("List: eraseBefore() position is out of range or at range");
  if (position() == 0) throw std::range_error("List: eraseBefore(): cursor at front");
  if (position() < 0) throw std::range_error("List: eraseBefore(): cursor at back");
  Node *N = beforeCursor;
  afterCursor->prev = N->prev;
  afterCursor->prev->next = afterCursor;
  beforeCursor = N->prev;
  delete N;
  num_elements--;
  pos_cursor--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
	while (position() < length()) { // position() = pos_cursor
		if (peekNext() == x) {       // peekNext() = afterCursor->data
			moveNext();
			return position();
		}
		moveNext();
	}
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
  while (position() > 0) {          // position() = pos_cursor
    if (peekPrev() == x) {          // peekNext() = afterCursor->data
      movePrev();
      return position();
    }
    movePrev();
  }
  return -1;
}

/* 
Notes for myself:
First while loop iterate through all nodes in the list.
Second while loop compares each node to all subsequent nodes in the list.
If-statements starting from the second if statement:
2. If the node is before the cursor, erase it and update compare_node to its previous node.
3. If the node is after the cursor, erase it and update compare_node to its previous node.
4. If the node is not before or after the cursor, delete the node and update compare_node to its previous node.
5. If the position of the deleted node is before the cursor, decrement the cursor position.
*/
// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
  int current_pos = 0;
  Node *current_node = frontDummy->next;
  while (current_node != backDummy) {
    int compare_pos = current_pos + 1;
    Node *compare_node = current_node->next;
    while (compare_node != backDummy) {
      Node *prev_node = compare_node->prev;
      if (compare_node->data == current_node->data) {
        if (compare_node == beforeCursor) {
          eraseBefore();
          compare_node = prev_node;
        } else if (compare_node == afterCursor) {
          eraseAfter();
          compare_node = prev_node;
        } else {
          Node *temp = compare_node;
          compare_node = compare_node->prev;
          temp->prev->next = temp->next;
          temp->next->prev = temp->prev;
          delete temp;
          num_elements--;
          if (compare_pos <= position()) pos_cursor--;
        }
      }
      compare_node = compare_node->next;
      compare_pos++;
    }
    current_node = current_node->next;
    current_pos++;
  }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
  List M = List();
  for (Node *n1 = frontDummy->next; n1 != backDummy; n1 = n1->next) M.insertBefore(n1->data);
  for (Node *n2 = L.frontDummy->next; n2 != L.backDummy; n2 = n2->next) M.insertBefore(n2->data);
  M.moveFront();
  return M;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
  std::string s = "(";
  for (Node *N = frontDummy->next; N != backDummy; N = N->next) {
    s += std::to_string(N->data) + (N != backDummy->prev ? ", " : ")");
  }
  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
  if (length() != R.length()) return false;
  for (Node *N = frontDummy->next, *M = R.frontDummy->next; N != backDummy; N = N->next, M = M->next) {
    if (N->data != M->data) return false;
  }
  return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
  return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
  return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
	if (this != &L) {
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;
}
