/********************************************************************************* 
 * Bun Ma, jma363
 * 2022 Winter CSE101 PA7
 * DictionaryClient.cpp
 * DictionaryTest for Dictionary ADT
 *********************************************************************************/
//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {

    // Create a new dictionary
    Dictionary dict;

    // Insert some key-value pairs into the dictionary
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    dict.setValue("cherry", 3);

    // Test the size() function
    cout << "Dictionary size: " << dict.size() << endl;

    // Test the contains() function
    cout << "Contains 'apple': " << dict.contains("apple") << endl;
    cout << "Contains 'durian': " << dict.contains("durian") << endl;

    // Test the getValue() function
    cout << "Value for 'banana': " << dict.getValue("banana") << endl;

    // Test the hasCurrent() function
    cout << "Has current: " << dict.hasCurrent() << endl;

    // Test the currentKey() and currentVal() functions
    dict.begin();
    cout << "Current key: " << dict.currentKey() << endl;
    cout << "Current value: " << dict.currentVal() << endl;

    // Test the setValue() function
    dict.setValue("apple", 4);
    cout << "New value for 'apple': " << dict.getValue("apple") << endl;

    // Test the remove() function
    dict.remove("banana");
    cout << "Dictionary size after removal: " << dict.size() << endl;

    // Test the clear() function
    dict.clear();
    cout << "Dictionary size after clear: " << dict.size() << endl;

    // Test the pre_string() function
    dict.setValue("dog", 1);
    dict.setValue("cat", 2);
    dict.setValue("bird", 3);
    cout << "Pre-order traversal: " << dict.pre_string() << endl;

    // Test the overloaded operator<<
    cout << "Dictionary contents: " << endl;
    cout << dict << endl;

    // Test the overloaded operator== and the copy constructor
    Dictionary dict2 = dict;
    cout << "Dict and dict2 are equal: " << (dict == dict2) << endl;

    // Test the overloaded operator=
    Dictionary dict3;
    dict3 = dict;
    cout << "Dict and dict3 are equal: " << (dict == dict3) << endl;

    // Test the iterator functions
    dict.begin();
    while (dict.hasCurrent()) {
        cout << dict.currentKey() << " -> " << dict.currentVal() << endl;
        dict.next();
    }

    /* Unable to test current() function due to it being a private function */
    // // Test the findNext() and findPrev() functions
    // dict.begin();
    // cout << "Next after " << dict.currentKey() << ": " << dict.findNext(dict.current())->key << endl;
    // dict.end();
    // cout << "Prev before " << dict.currentKey() << ": " << dict.findPrev(dict.current())->key << endl;
   
   // check exceptions
   try{
      dict.getValue("foo");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      dict.remove("foo");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      dict.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      dict.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      dict.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      dict.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;  

   return( EXIT_SUCCESS );
}

/* Output after running ./DictionaryClient */
/*
Dictionary size: 3
Contains 'apple': 1
Contains 'durian': 0
Value for 'banana': 2
Has current: 0
Current key: apple
Current value: 1
New value for 'apple': 4
Dictionary size after removal: 2
Dictionary size after clear: 0
Pre-order traversal: dog
cat
bird

Dictionary contents: 
bird : 3
cat : 2
dog : 1

Dict and dict2 are equal: 1
Dict and dict3 are equal: 1
bird -> 3
cat -> 2
dog -> 1
Dictionary: getValue(): key "foo" does not exist
   continuing without interruption
Dictionary: remove(): key "foo" does not exist
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