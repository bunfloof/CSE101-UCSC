/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA5
* Shuffle.cpp
* Shuffle entry file for List ADT
*********************************************************************************/ 

#include<string>
#include"List.h"

using namespace std;

void shuffle(List& D);

void shuffle(List& D) {
  List a;
  int d_half = D.length() / 2;
  D.moveFront();
  for (int i = 0; i < d_half; i++) {
    a.insertBefore(D.moveNext());
    D.eraseBefore();
  }
  a.moveFront();
  for (int i = 0; i < a.length(); i++) {
    D.moveNext();
    D.insertBefore(a.moveNext());
  }
}

int main(int argc, char* argv[]) {
   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <deck size>" << endl;
      return(EXIT_FAILURE);
   }

  // open files for reading and writing 
  int deck_size = atoi(argv[1]);
  if (deck_size <= 0) {
    cerr << "Deck size must be a positive integer" << endl;
    return(EXIT_FAILURE);
  }

  cout << "deck size\t\tshuffle count\n------------------------------" << endl;

  for (int i = 1; i <= deck_size; i++) {
    List deck;
    for (int j = 1; j <= i; j++) {
      deck.insertBefore(j);
    }
    
    List deck_copy = deck;
    int count = 0;
    while (true) {
      shuffle(deck);
      count++;
      if (deck.equals(deck_copy)) {
        break;
      }
    }
    cout << i << "\t\t\t\t" << count << endl;
  }
  return(EXIT_SUCCESS);
}
