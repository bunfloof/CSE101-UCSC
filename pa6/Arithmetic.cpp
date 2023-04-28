/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA6
* Arithmetic.cpp
* Arithmetic entry file for BigIntegerADT
*********************************************************************************/ 

#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"

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

  string As, Bs;
  in >> As >> Bs;

  BigInteger A(As), B(Bs);
  const BigInteger s3("3"), s2("2"), s9("9"), s16("16");

  out << A << '\n' << '\n'
      << B << '\n' << '\n'
      << A + B << '\n' << '\n'
      << A - B << '\n' << '\n'
      << A - A << '\n' << '\n'
      << A.mult(s3) - B.mult(s2) << '\n' << '\n'
      << A * B << '\n' << '\n'
      << A * A << '\n' << '\n'
      << B * B << '\n' << '\n'
      << s9 * A * A * A * A + s16 * B * B * B * B * B << '\n';

  // close files 
  in.close();
  out.close();
  
  // printf("Done Time"); // for the read console container overhead
  
  /* 
  Unfortunately won't be able to test on unix.ucsc.edu due to ban :'(

  Runtimes for $`./Arithmetic in5 out5` on an 8vCPU (pinned) AMD EPYC 7812 GrubHub code-server:
    27934ms, 27417ms, 27483ms, 28833ms, 32934ms
  */
  
  return(EXIT_SUCCESS);
}
