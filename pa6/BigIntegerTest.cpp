/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA6
* BigIntegerTest.cpp
* BigIntegerTest for BigInteger ADT
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

  // Test default constructor
  BigInteger defaultConstructed;
  cout << "defaultConstructed: " << defaultConstructed << endl;

  // Test string constructor
  BigInteger fromString1("123456789");
  cout << "fromString1: " << fromString1 << endl;
  BigInteger fromString2("-987654321");
  cout << "fromString2: " << fromString2 << endl;

  // Test copy constructor
  BigInteger copyConstructed(fromString1);
  cout << "copyConstructed: " << copyConstructed << endl;

  // Test sign function
  cout << "fromString1 sign: " << fromString1.sign() << endl;
  cout << "fromString2 sign: " << fromString2.sign() << endl;

  // Test comparison functions
  cout << "fromString1 == copyConstructed: " << (fromString1 == copyConstructed) << endl;
  cout << "fromString1 < fromString2: " << (fromString1 < fromString2) << endl;
  cout << "fromString1 <= fromString2: " << (fromString1 <= fromString2) << endl;
  cout << "fromString1 > fromString2: " << (fromString1 > fromString2) << endl;
  cout << "fromString1 >= fromString2: " << (fromString1 >= fromString2) << endl;

  // Test makeZero function
  fromString1.makeZero();
  cout << "fromString1 after makeZero: " << fromString1 << endl;

  // Test negate function
  fromString2.negate();
  cout << "fromString2 after negate: " << fromString2 << endl;
  fromString2.negate();
  cout << "fromString2 after second negate: " << fromString2 << endl;

  // Test addition
  BigInteger addResult = fromString2 + copyConstructed;
  cout << "addResult: " << addResult << endl;

  // Test subtraction
  BigInteger subResult = fromString2 - copyConstructed;
  cout << "subResult: " << subResult << endl;

  // Test multiplication
  BigInteger multResult = fromString2 * copyConstructed;
  cout << "multResult: " << multResult << endl;

  // Test to_string function
  cout << "fromString2 to_string: " << fromString2.to_string() << endl;

  return EXIT_SUCCESS;
}

/* Output from running ./BigIntegerTest */
/* 
defaultConstructed: 0
fromString1: 123456789
fromString2: -987654321
copyConstructed: 123456789
fromString1 sign: 1
fromString2 sign: -1
fromString1 == copyConstructed: 1
fromString1 < fromString2: 0
fromString1 <= fromString2: 0
fromString1 > fromString2: 1
fromString1 >= fromString2: 1
fromString1 after makeZero: 0
fromString2 after negate: 987654321
fromString2 after second negate: -987654321
addResult: -864197532
subResult: -1111111110
multResult: -121932631112635269
fromString2 to_string: -987654321
*/