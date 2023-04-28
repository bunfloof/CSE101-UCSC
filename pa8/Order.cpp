/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA8
* Order.cpp
* Order entry file for Dictionary ADT
*********************************************************************************/ 

#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
  // check command line for correct number of arguments
  ifstream in;
  ofstream out;
  
  if( argc != 3 ){
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return(EXIT_FAILURE);
  }
  
  // open files for reading and writing 
  in.open(argv[1]);
  if( !in.is_open() ){
    cerr << "Unable to open file " << argv[1] << " for reading" << endl;
    return(EXIT_FAILURE);
  }
  
  out.open(argv[2]);
  if( !out.is_open() ){
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return(EXIT_FAILURE);
  }
  
  // read each line of input file, then count and print tokens 
  Dictionary D;
  string s;
  for (int i = 1; getline(in, s); i++) {
    D.setValue(s, i);
  }

  out << D << '\n'
      << D.pre_string() << '\n';

  
  /* 
    9436ms, 9679ms, 9871ms
  */
  
  return(EXIT_SUCCESS);
}
