/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA5
* ListTest.cpp
* Test Client for List ADT
*********************************************************************************/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

    //creating a new List object
    List myList;

    //testing the length function, should return 0
    cout << "Length of List: " << myList.length() << endl;

    //testing insertAfter function
    myList.insertAfter(1);
    myList.insertAfter(2);
    myList.insertAfter(3);

    //testing the front and back function
    cout << "Front element: " << myList.front() << endl;
    cout << "Back element: " << myList.back() << endl;

    //testing the moveFront function
    myList.moveFront();
    cout << "Current element: " << myList.peekNext() << endl;

    //testing the moveNext function
    cout << "Next element: " << myList.moveNext() << endl;

    //testing the moveBack function
    myList.moveBack();
    cout << "Current element: " << myList.peekPrev() << endl;

    //testing the movePrev function
    cout << "Previous element: " << myList.movePrev() << endl;

    //testing the insertBefore function
    myList.insertBefore(0);

    //testing the setAfter and setBefore functions
    myList.setAfter(5);
    myList.setBefore(4);

    //testing the findNext and findPrev functions
    cout << "Index of 5: " << myList.findNext(5) << endl;
    cout << "Index of 4: " << myList.findPrev(4) << endl;

    //testing the eraseAfter and eraseBefore functions
    myList.eraseAfter();
    myList.eraseBefore();

    //testing the to_string function
    cout << "List: " << myList.to_string() << endl;

    //testing the equals function with an identical list
    List identicalList;
    identicalList.insertAfter(1);
    identicalList.insertAfter(2);
    identicalList.insertAfter(3);
    cout << "Lists equal? " << myList.equals(identicalList) << endl;

    //testing the equals function with a different list
    List differentList;
    differentList.insertAfter(3);
    differentList.insertAfter(2);
    differentList.insertAfter(1);
    cout << "Lists equal? " << myList.equals(differentList) << endl;

    //testing the assignment operator
    List copyList = myList;
    cout << "Copy of List: " << copyList.to_string() << endl;

    //testing the concat function
    List concatList = myList.concat(identicalList);
    cout << "Concatenated List: " << concatList.to_string() << endl;

    //testing the clear function
    myList.clear();
    cout << "Length of List after clearing: " << myList.length() << endl;

    return 0;
}

/* Output of ListTest */
/*
Length of List: 0
Front element: 3
Back element: 1
Current element: 3
Next element: 3
Current element: 1
Previous element: 1
Index of 5: 4
Index of 4: 2
List: (3, 5)
Lists equal? 0
Lists equal? 0
Copy of List: (3, 5)
Concatenated List: (3, 5, 3, 2, 1)
Length of List after clearing: 0
*/