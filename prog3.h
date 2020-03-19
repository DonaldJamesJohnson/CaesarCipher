/*
  prog3.h
  Donald Johnson
  9-24-18
  
  Header file for prog3 
*/
#ifndef __PROG3_H__
#define __PROG3_H__

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const string FILE1 = "/home/cs501/progs/18f/p3/prog3.d1";
const string FILE2 = "/home/cs501/progs/18f/p3/prog3.d2";

void process_infile (const int& shift, const string& key);
string encodeCaesarCipher (string str, const int& shift, const string& key);
int new_position (const char& c, const int& shift, const string& key);

#endif
