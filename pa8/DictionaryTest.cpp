/********************************************************************************* 
 * Bun Ma, jma363
 * 2022 Winter CSE101 PA8
 * DictionaryTest.cpp
 * Dictionary for Dictionary ADT
 *********************************************************************************/
//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   Dictionary A;

   // insert some pairs into A
   A.setValue("apple", 1);
   A.setValue("banana", 2);
   A.setValue("cherry", 3);
   A.setValue("date", 4);
   A.setValue("elderberry", 5);
   A.setValue("fig", 6);
   A.setValue("grape", 7);
   A.setValue("honeydew", 8);
   A.setValue("kiwi", 9);
   A.setValue("lemon", 10);

   // test size()
   cout << "A.size() = " << A.size() << endl;

   // test contains()
   cout << "A.contains(\"kiwi\") = " << (A.contains("kiwi") ? "true" : "false") << endl;

   try {
      cout << "A.contains(\"pear\") = " << (A.contains("pear") ? "true" : "false") << endl;
   } catch(logic_error& e) {
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   // test getValue()
   cout << "A.getValue(\"fig\") = " << A.getValue("fig") << endl;

   // test hasCurrent()
   cout << "A.hasCurrent() = " << (A.hasCurrent() ? "true" : "false") << endl;

   // test currentKey()
   A.begin();
   cout << "A.currentKey() = " << A.currentKey() << endl;

   // test currentVal()
   cout << "A.currentVal() = " << A.currentVal() << endl;

   // test setValue()
   A.setValue("lemon", 20);
   A.setValue("mango", 30);

   // test remove()
   A.remove("cherry");
   try {
      A.remove("pear");
   } catch(logic_error& e) {
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   // test begin() and end()
   A.begin();
   cout << "A.currentKey() (begin) = " << A.currentKey() << endl;
   A.end();
   cout << "A.currentKey() (end) = " << A.currentKey() << endl;

   // test next() and prev()
   A.begin();
   A.next();
   cout << "A.currentKey() (next) = " << A.currentKey() << endl;
   A.prev();
   cout << "A.currentKey() (prev) = " << A.currentKey() << endl;

   // test to_string()
   cout << "A.to_string() = " << endl << A.to_string() << endl;

   // test pre_string()
   cout << "A.pre_string() = " << endl << A.pre_string() << endl;

   // test equals()
   Dictionary B;
   B.setValue("apple", 1);
   B.setValue("banana", 2);
   B.setValue("cherry", 3);
   B.setValue("date", 4);
   B.setValue("elderberry", 5);
   B.setValue("fig", 6);
   B.setValue("grape", 7);
   B.setValue("honeydew", 8);
   B.setValue("kiwi", 9);
   B.setValue("lemon", 20);
   B.setValue("mango", 30);
   cout << "A.equals(B) = " << (A.equals(B) ? "true" : "false") << endl;

   // test copy constructor and operator=()
   Dictionary D(A);
   cout << "D: " << D << endl;
   
   Dictionary E = B;
   cout << "E: " << E << endl;
   
   // test equals()
   cout << "A==B: " << (A==B) << endl;
   cout << "B==D: " << (B==D) << endl;
   
   // test setValue() and getValue()
   A.setValue("mango", 7);
   cout << "A: " << A << endl;
   int val = A.getValue("mango");
   cout << "Value of 'mango' in A: " << val << endl;
   
   // test remove()
   A.remove("mango");
   cout << "A: " << A << endl;
   
   // test begin(), end(), hasCurrent(), currentKey(), currentVal(), next(), prev()
   A.begin();
   cout << "A begin(): " << A.currentKey() << " " << A.currentVal() << endl;
   A.end();
   cout << "A end(): " << A.currentKey() << " " << A.currentVal() << endl;
   A.begin();
   cout << "A hasCurrent(): " << A.hasCurrent() << endl;
   cout << "A current(): " << A.currentKey() << " " << A.currentVal() << endl;
   A.next();
   cout << "A next(): " << A.currentKey() << " " << A.currentVal() << endl;
   A.prev();
   cout << "A prev(): " << A.currentKey() << " " << A.currentVal() << endl;
   
   // test clear()
   A.clear();
   cout << "A: " << A << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;  

   return( EXIT_SUCCESS );
}

/* Output after running ./DictionaryTest */
/*
A.size() = 10
A.contains("kiwi") = true
A.contains("pear") = false
A.getValue("fig") = 6
A.hasCurrent() = false
A.currentKey() = apple
A.currentVal() = 1
Dictionary: remove(): key "pear" does not exist
   continuing without interruption
A.currentKey() (begin) = apple
A.currentKey() (end) = mango
A.currentKey() (next) = banana
A.currentKey() (prev) = apple
A.to_string() = 
apple : 1
banana : 2
date : 4
elderberry : 5
fig : 6
grape : 7
honeydew : 8
kiwi : 9
lemon : 20
mango : 30

A.pre_string() = 
fig
date
banana
apple
elderberry
honeydew
grape
lemon
kiwi
mango

A.equals(B) = false
D: apple : 1
banana : 2
date : 4
elderberry : 5
fig : 6
grape : 7
honeydew : 8
kiwi : 9
lemon : 20
mango : 30

E: apple : 1
banana : 2
cherry : 3
date : 4
elderberry : 5
fig : 6
grape : 7
honeydew : 8
kiwi : 9
lemon : 20
mango : 30

A==B: 0
B==D: 0
A: apple : 1
banana : 2
date : 4
elderberry : 5
fig : 6
grape : 7
honeydew : 8
kiwi : 9
lemon : 20
mango : 7

Value of 'mango' in A: 7
A: apple : 1
banana : 2
date : 4
elderberry : 5
fig : 6
grape : 7
honeydew : 8
kiwi : 9
lemon : 20

A begin(): apple 1
A end(): lemon 20
A hasCurrent(): 1
A current(): apple 1
A next(): banana 2
A prev(): apple 1
A: 
test pre-condition errors:
Dictionary: getValue(): key "blah" does not exist
   continuing without interruption
Dictionary: remove(): key "blah" does not exist
   continuing without interruption
Dictionary: currentKey(): current undefined
   continuing without interruption
Dictionary: currentVal(): current undefined
   continuing without interruption
Dictionary: next(): current undefined
   continuing without interruption
Dictionary: prev(): current undefined
   continuing without interruption

*/