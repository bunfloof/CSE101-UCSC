/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA6
* BigInteger.cpp
* BigInteger for BigInteger ADT
*********************************************************************************/

#include "BigInteger.h"
#include "List.h"

// When you submit your project however, be sure to set power = 9 and base = 1000000000 (1 billion), for proper grading.
int power = 9;
long base = 1000000000;

// Class Constructors & Destructors ----------------------------------------

// BigInteger() constructor that creates a new BigInteger in the zero state: signum=0, digits=().
BigInteger::BigInteger() {
  signum = 0;
  digits = List();
}

// BigInteger() constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
  if (s.length() == 0) throw std::invalid_argument("BigInteger: Constructor: empty string");
  signum = (s[0] == '-') ? -1 : 1;
  if (s[0] == '+' || s[0] == '-') s = s.substr(1);
  //digits = List();
  for (char c : s) { // needs to be placed here, not above in precondition checks
    if (!isdigit(c)) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
  }
  int pos = s.length() % power;
  if (pos) digits.insertBefore(stol(s.substr(0, pos)));
  for (pos = s.length() % power; pos < (int)s.length(); pos += power) { // (int) cast in condition loop to suppress warning
    digits.insertBefore(stol(s.substr(pos, power)));
  }

}

// BigInteger() constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
  this->signum = N.signum;
  this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Access functions --------------------------------------------------------

// sign() returns -1, 1 or 0 according to whether this BigInteger is negative, positive or 0, respectively.
int BigInteger::sign() const {
    return this->signum;
}

// compare() returns -1, 1 or 0 according to whether this BigInteger is less than N, greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (this->signum != N.signum) return this->signum > N.signum ? 1 : -1;
    else if (this->signum == 0) return 0;

    List tempdigits = this->digits;
    List tempn = N.digits;

    int cmp = 0;
    if (tempdigits.length() != tempn.length()) {
      cmp = tempdigits.length() > tempn.length() ? 1 : -1;
    }
    else {
      tempdigits.moveFront();
      tempn.moveFront();
      while (tempdigits.position() < tempdigits.length() && cmp == 0) {
        cmp = tempdigits.peekNext() > tempn.peekNext() ? 1 : (tempdigits.peekNext() < tempn.peekNext() ? -1 : 0);
        tempdigits.moveNext();
        tempn.moveNext();
      }
    }
    return this->signum == 1 ? cmp : -cmp;
}




// Manipulation procedures -------------------------------------------------

/* Private helper functions --------------- */

// negateList() changes the sign of each integer in List L. Used by sub().
void negateList(List& L);

void negateList(List& L) {
  for (L.moveFront(); L.position() < L.length(); L.moveNext()) {
    L.setAfter(L.peekNext() * -1);
  }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn);

void sumList(List& S, List A, List B, int sgn) {
  S.clear();
  for (B.moveFront(); B.position() < B.length(); B.moveNext()) {
    B.setAfter(sgn * B.peekNext());
  }
  A.moveBack();
  B.moveBack();
  while (A.position() > 0 || B.position() > 0) {
    S.insertAfter((A.position() > 0 ? A.peekPrev() : 0) + (B.position() > 0 ? B.peekPrev() : 0));
    if (A.position() > 0) A.movePrev();
    if (B.position() > 0) B.movePrev();
  }
  
  S.moveFront();
  while (S.front() == 0 && S.length() > 1) { // remove leading zeros from S
    S.eraseAfter();
  }
  
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L);

int normalizeList(List& L) {
  if (L.front() == 0) return 0;
  int i = 1;
  if (L.front() < 0) {
    i = -1;
    negateList(L);
  }
  L.moveBack();
  int car = 0;
  ListElement a = 0; //int a;
  
  while (L.position() > 0) {
    a = L.peekPrev() + car;
    car = 0;
    if (a < 0) {
      car = -1;
      a += base;
    }
    L.setBefore(a % base);
    car += a / base;
    L.movePrev();
  }
  if (car > 0) {
    L.moveFront();
    L.insertAfter(car);
  }
  return i;
}

// shiftList() prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
  L.moveBack();
  for (int i = 0; i < p; i++) {
    L.insertAfter(0);
  }
}

// scalarMultList() multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
  for (L.moveFront(); L.position() < L.length(); L.moveNext()) {
    L.setAfter(L.peekNext() * m);
  }
}

// makeZero() re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
  signum = 0;
  digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
  signum *= -1;
}

// BigInteger Arithmetic operations ----------------------------------------

/* Note to self: 
Runtime varying greatly on grubhub code-server for infile5.txt
Lowest: 17 seconds
Average: ~26 seconds
Highest: 38 seconds
*/
// add() returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
  BigInteger sum;
  BigInteger tempdigits = *this;
  BigInteger tempn = N;
  int sign = 1;
  if (this->signum ==  -1) negateList(tempdigits.digits);
  if (N.signum == -1) sign = -1;
  sumList(sum.digits, tempdigits.digits, tempn.digits, sign);

  sum.signum = normalizeList(sum.digits);
  if (normalizeList(sum.digits) == -1) negateList(sum.digits);
  
  return sum;
}

// sub() returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
  // Code below is broken
  // BigInteger B;
  // List T;
  // if (signum == N.signum) {
  //     // Both signs are the same, so subtract normally
  //     int sign = signum * (-1);
  //     sumList(B.digits, digits, N.digits, sign);
  // } else {
  //     // Signs are different, so negate one of the operands and add
  //     if (signum == -1) {
  //         T = digits;
  //         negateList(T);
  //         sumList(B.digits, N.digits, T, N.signum);
  //     } else {
  //         T = N.digits;
  //         negateList(T);
  //         sumList(B.digits, digits, T, signum);
  //     }
  // }
  // int s = normalizeList(B.digits);
  // B.signum = s;
  // return B;
  // End of Code below is broken

  // shortcut no need to rewrite sub
  BigInteger ntemp = N;
  negateList(ntemp.digits);
  BigInteger sum = add(ntemp);
  return sum;
}

// mult() returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
  BigInteger res;
  if (this->signum == 0 || N.signum == 0) return res;
  List sum;
  List Ntemp = N.digits; // to not tamper with original N
  List temp; // tutor suggest to move outside of loop to optimize runtime

  for (int shift = 0; Ntemp.position() > 0; ++shift, Ntemp.movePrev()) {
    temp = this->digits;
    scalarMultList(temp, Ntemp.peekPrev());
    shiftList(temp, shift);
    List sumtemp = sum;
    sumList(sum, sumtemp, temp, 1);
    normalizeList(sum);
  }

  res.digits = sum;
  res.signum = (this->signum == N.signum) ? 1 : -1;
  return res;
}

// Other Functions ---------------------------------------------------------

// to_string() returns a string representation of this BigInteger consisting of its base 10 digits. If this BigInteger is negative, the returned string will begin with a negative sign '-'. If this BigInteger is zero, the returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
  // Use this one pass all and test 1 which other
  if (this->signum == 0) return "0";
  std::string s = (this->signum == -1) ? "-" : "";
  digits.moveFront();
  
  for (;digits.front() == 0 && digits.length() > 1; digits.eraseAfter()) {}
  for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
    std::string d = std::to_string(digits.peekNext());
    std::string m = "";
    for (;(int)m.length() + (int)d.length() < power && digits.position() > 0; m += '0') {}
    s += m + d;
  }
  return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<() inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
  return stream << N.to_string();
}

// operator==() returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
  return A.compare(B) == 0;
}

// operator<() returns true if and only if A is less than B.  
bool operator<( const BigInteger& A, const BigInteger& B ){
  return A.compare(B) < 0;
}

// operator<=() returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
  return A.compare(B) <= 0;
}

// operator>() returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
  return A.compare(B) > 0;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
  return A.compare(B) >= 0;
}

// operator+() returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
  return A.add(B);
}

// operator+=() overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
  A = A.add(B);
  return A;
}

// operator-() returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
  return A.sub(B);
}

// operator-=() overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
  A = A.sub(B);
  return A;
}

// operator*() returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
  return A.mult(B);
}

// operator*=() overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
  A = A.mult(B);
  return A;
}