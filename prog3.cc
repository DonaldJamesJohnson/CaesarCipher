/*
  prog3.cc
  Donald Johnson
  9-24-18
  
  Implementation file for prog3.h
  prog3.cc is a Caesar Cipher program that reads in text from a data file, 
  which is then altered by shifting the letters according to the shift and key values read in from another data file.
*/
#include "prog3.h"

int main(){  // the main function opens the first file, reads in values from that file into shift and key, and calls the process_infile function
    int shift = 0;
    string istring = "";
    ifstream infile (FILE1.c_str()); 
    
    if (!infile){
        cout << "Error: could not open file " << FILE1;
        return 1;
    }
    while (infile.good()){
        infile >> shift;
        infile >> istring;
        process_infile(shift, istring);
    }
    infile.close();

    return 0;
}
void process_infile (const int& shift, const string& key){ // the process_infile function prints out the shift and key values passed to it, opens the second file and reads the text from it, and then calls the encodeCaesarCipher function.
    string text = "";
    cout << "shift = " << shift << endl;
    cout << "key = " << "\""<< key << "\"" << endl;
    cout << endl;
    
    ifstream infile2 (FILE2.c_str());
    if (!infile2) {
        cout << "Error: could not open file" << FILE2;
    }
    while (infile2.good()){
        getline(infile2, text);
        encodeCaesarCipher (text, shift, key);  
    }
    infile2.close();      
    }
string encodeCaesarCipher (string str, const int& shift, const string& key){ // the encodeCaesarCipher function iterates through the string passed to it, determines if characters in the string are letters, and if so they are sent to the new_position function to be altered.
    string newString = "";
    for (unsigned i=0; i<str.size(); i++){
        char c = str.at(i);
        if (int(c) >= 65 && int(c) <=90 || int(c) >=97 && int(c) <=122){
            c = char(new_position (c, shift, key));
            newString += c;
        } else newString += c;
    }
    cout << newString << endl;
    cout << endl;
    return newString;
}
int new_position (const char& c, const int& shift, const string& key){  // the new_position function alters the character passed to it according to the passed in shift and key values.
    int value = 0;                                 // used to store the return value for the function
    value = int(c);                                // assigns value to the integer value of c     
    int shiftVal = shift;                          // declares and initializes a shift value equal to shift, but which, unlike the const shift value, can be modified 
    const string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // establishes a constant alphabet used to compare positions with the key value 
    int aPos = 0;                                  // declares an integer used to store the position of c in the alphabet
    int keyShift = 0;                              // declares an integer used to store the shift value from the key
    
    if (value >= 97 && value <= 122){              // if c is lower case, make it upper case
        value = toupper(c);
    }
    for (unsigned i=0; i<a.size(); i++){                // iterates through the alphabet
        if (value == int(a.at(i))){                // if the uppercase integer value of c is equal to the integer value of the character at pos i in the alphabet...
            aPos = int(a.at(i));                   // assign aPos to current position. We now know where c is located in the alphabet.     
            keyShift = aPos - int(key.at(i));      // assigns the keyShift value to the difference between aPos and the character at position i of the key
        }
    }
    shiftVal += keyShift;                          // assigns shiftVal to shiftVal + keyShift. We are now combining the original shift value with the shift from the key 
    if (shiftVal < 0){                             // if shiftVal is negative, make shiftVal positive
        shiftVal *= (-1);
    }
    int adjShift = shiftVal - 26;                  // declares and initializes adjShift equal to shiftVal-26. If adjShift is still greater than 26, then we start the following for-loop.
    for (unsigned i=1; adjShift > 26; i++){        // iterates through multiples of 26 and subtracts them from shiftVal and assigns that value to adjShift
        adjShift = shiftVal - (26 * i);
    }
    if (shift + keyShift < 0) adjShift *= (-1);    // if the original total shift value was less than 0, we need to convert back to a negative number 
      
    if ((value + adjShift) > 90){                  // if value + adjShift is greater than 90, we know we are past the ASCII value of Z, and must loop back around
       value = (((value + adjShift) - 90) + 64);
    } else if ((value + adjShift) < 65){           // else if value + adjShift is less than 65, we know we are below the ASCII value of A, and must loop back around
      value = (91 - (65 - (value + adjShift))); 
    } else {                                       // else value + adjShift is within the range of ASCII values from A-Z
      value = (value + adjShift);
    }
    if (c >= 97 && c <= 122) return value+32;      // if the original character passed to the function was lowercase, convert back to lowercase and return that value
    else return value;                             // else return as uppercase value
}
