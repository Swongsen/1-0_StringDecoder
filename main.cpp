#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;


string trimS(string s, string signal, int &trimcounter){
  string newS;
  char first = signal.at(0);

  while(s.at(0) != first && s.length() > 1){
    trimcounter++;
    s.erase(0, 1);
  }
  newS = s;
  return newS;
}

// Created with x subsequences checked first then y subsequences checked in mind.
// However, it is arbitrary, and x now really just denotes first and y denotes second.
// Can pass either 'x' or 'y' string in that place for it to work in the algorithm.
bool interweaving(string s, string signal1, string signal2, ofstream &output, int &trimcounter, int &signal1counter, int& signal2counter){
  bool result;
  cout << "s length: " + to_string(s.length()) + "\n";
  // Checks first if s is at least longer than the two signals x and y.
  if(s.length() < signal1.length() && s.length() < signal2.length()){
    //cout << "Signal not long enough. Not interweaving.";
    //output << "Signal not long enough. Not interweaving.";
    result = false;
    return result;
  }

  int signal1spot = 0;
  int signal2spot = 0;
  bool signal1found = false;
  string newstring;    // Used for figuring out the leftover symbols needed for y to determine if interweaving
  string whole_string; // Used for holding the entire sequence of symbols
  string diff_string;  // Used for holding only the differing sequence of symbols between x and s or y and the remaining symbols
  string finalstring;  // Not necessarily needed. Just used for debugging purposes. If len > 0, result has to be false

  //cout << "Untrimmed S: " + s + "\n";
  s = trimS(s, signal1, trimcounter);
  cout << "Trim operations: " + to_string(trimcounter) + "\n";
  output << "Trim operations: " + to_string(trimcounter) + "\n";
  trimcounter = 0;
  //cout << "Trimmed S: " + s + "\n";

  // Comparing x string to s string
  for(int i = 0; i < s.length(); i++){
    signal1counter++;
    // Add every element in s to the temporary whole string.
    whole_string += s.at(i);
    if(signal1.at(signal1spot) == s.at(i)){
      signal1spot++;
      // If a full x sequence is found, add all of the differing elements found to newstring,
      // reset the xspot, mark xfound as true, and reset both the temp string to restart the process for rest of elements in s.
      if(signal1spot == signal1.length()){
        newstring += diff_string;
        signal1spot = 0;
        signal1found = true;
        diff_string.clear();
        whole_string.clear();
      }
    }
    else if(signal1.at(signal1spot) != s.at(i) ){
      diff_string += s.at(i);
    }
    // If it reaches the last element in s, add the remaining string to the newstring.
    // If the last element is a final piece of x in s, then whole_string should be reset
    // earlier so this wouldn't add anything.
    if(i == s.length()-1){
      newstring += whole_string;
    }
  }

  cout << "Signal1 operations: " + to_string(signal1counter) + "\n";
  output << "Signal1 operations: " + to_string(signal1counter) + "\n";
  signal1counter = 0;
  //cout << "Newstring: " + newstring + "\n";
  diff_string.clear();
  whole_string.clear();

  // Uses newstring string built from x and s to compare for y. Exact same logic
  for(int i = 0; i < newstring.length(); i++){
    signal2counter++;
    whole_string += newstring.at(i);
    if(signal2.at(signal2spot) == newstring.at(i)){
      signal2spot++;
      if(signal2spot == signal2.length()){
        finalstring += diff_string;
        diff_string.clear();
        whole_string.clear();
        signal2spot = 0;
      }
    }
    else if(signal2.at(signal2spot) != newstring.at(i)){
      diff_string += newstring.at(i);
    }

    if(i == newstring.length() - 1){
      finalstring += whole_string;
    }
  }
  cout << "Signal2 operations: " + to_string(signal2counter) + "\n";
  output << "Signal2 operations: " + to_string(signal2counter) + "\n";
  signal2counter = 0;

  // Different cases to consider when not interweaving
  // First case is if there is a finalstring with length larger than 0. That is leftover symbols that mean not interweaving
  // Second case is maybe there is no finalstring but x has not been found to interweave. So also not interweaving.
  // Third case is where x is interweaving but not y, so also not interweaving.
  // Any other cases will result in having an interweaving result.
  if(finalstring.length() != 0 || signal1found == false || newstring.length() == 0){
    result = false;
    //cout << "\nFinalstring: " + finalstring + "\n";
  }
  else{
    result = true;
  }
  return result;
}

int main(){
  // Initial variables as described in the project document
  string s;
  string x;
  string y;
  bool answer;
  bool xinterweave = false;
  bool yinterweave = false;
  int trimcounter = 0;
  int signal1counter = 0;
  int signal2counter = 0;

  // Variables for menu / output
  int option;
  int n;
  ofstream output("output.txt");
  srand(time(0));

  cout << "Please select option. \n1. Generate N different s's, x's, and y's. \n2. Manually input s, x, and y.\n";
  cin >> option;

  while(1){
    if(option == 1){
      cout << "Enter N: ";
      cin >> n;
      for(int i = 0; i < n; i++){
        output << "Trial: " + to_string(i) + "\n";
        cout << "Trial: " + to_string(i) + "\n";

        // Randomly generate an 's' string with random length with at least size 1.
        for(int j = 0; j < rand()+1; j++){
          s += to_string(rand() % 2);
        }

        // Randomly generate an 'x' string with random length shorter than 's' length.
        for(int j = 0; j < rand() % s.length() + 1; j++){
          x += to_string(rand() % 2);
        }

        // Randomly generate an 'y' string with random length shorter than 's' length.
        for(int j = 0; j < rand() % s.length() + 1; j++){
          y += to_string(rand() % 2);
        }

        //cout << "S: " + s + "\n";
        //cout << "x: " + x + "\n";
        //cout << "y: " + y + "\n";

        // Runs the given strings into interweaving to check with x first then y.
        cout << "X first:\n";
        output << "X first:\n";
        answer = interweaving(s, x, y, output, trimcounter, signal1counter, signal2counter);
        if(answer == true){
          output << "Interweaving with signal X first\n";
          xinterweave = true;
        }
        else if(answer == false){
          output << "Not interweaving with signal X first\n";
        }

        // Runs the given strings into interweaving to check with y first then x.
        cout << "\nY first:\n";
        output << "\nY first:\n";
        answer = interweaving(s, y, x, output, trimcounter, signal1counter, signal2counter);
        if(answer == true){
          output << "Interweaving with signal Y first\n";
          yinterweave = true;
        }
        else if(answer == false){
          output << "Not interweaving with signal Y first\n";
        }

        // If both ways are interweaving, then it is interweaving both ways.
        if(xinterweave == true && yinterweave == true){
          output << "Interweaving with both X and Y\n";
          //output << "s: " + s;
          //output << "\nx: " + x;
          //output <<"\ny: " + y;
          xinterweave = false;
          yinterweave = false;
        }
        output << "\n";
        cout << "\n\n";

        // Clear and reset strings and values for next set.
        xinterweave = false;
        yinterweave = false;
        s.clear();
        x.clear();
        y.clear();
      }

      break;
    }
    else if(option == 2){
      // Takes user input and stores into s, x, and y respectively
      cout << "Input s: ";
      cin >> s;

      cout << "Input x: ";
      cin >> x;

      cout << "Input y: ";
      cin >> y;


      // Runs the given strings into interweaving to check with x first then y.
      cout << "X first:\n";
      output << "X first:\n";
      answer = interweaving(s, x, y, output, trimcounter, signal1counter, signal2counter);
      if(answer == true){
        cout << "Interweaving with signal X first\n";
        output << "Interweaving with signal X first\n";
        xinterweave = true;
      }
      else if(answer == false){
        cout << "Not Interweaving with signal X first\n";
        output << "Not Interweaving with signal X first\n";
      }

      // Runs the given strings into interweaving to check with y first then x.
      cout << "\nY first:\n";
      output << "\nY first:\n";
      answer = interweaving(s, y, x, output, trimcounter, signal1counter, signal2counter);
      if(answer == true){
        cout << "Interweaving with signal Y first\n";
        output << "Interweaving with signal Y first\n";
        yinterweave = true;
      }
      else if(answer == false){
        cout << "Not Interweaving with signal Y first\n";
        output << "Not Interweaving with signal Y first\n";
      }

      if(xinterweave == true && yinterweave == true){
        cout << "Interweaving with either signal first\n";
        output << "Interweaving with either signal first\n";
      }

      break;
    }
    else
      cout << "Please enter '1' or '2'";
  }


  return 0;
}
