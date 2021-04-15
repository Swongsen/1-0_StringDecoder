#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;


string trimS(string s, string signal){
  string newS;
  char first = signal.at(0);

  while(s.at(0) != first && s.length() > 1){
    cout << s.length();
    s.erase(0, 1);
  }
  newS = s;
  return newS;
}

// Created with x subsequences checked first then y subsequences checked in mind.
// However, it is arbitrary, and x now really just denotes first and y denotes second. 
// Can pass either 'x' or 'y' string in that place for it to work in the algorithm.
bool interweaving(string s, string x, string y, ofstream &output){
  bool result;
  // Checks first if s is at least longer than the two signals x and y.
  if(s.length() < x.length() && s.length() < y.length()){
    result = "Signal not long enough. Not interweaving.";
    return result;
  }

  int xspot = 0;
  int yspot = 0;
  bool xfound = false;
  string newstring;    // Used for figuring out the leftover symbols needed for y to determine if interweaving
  string whole_string; // Used for holding the entire sequence of symbols
  string diff_string;  // Used for holding only the differing sequence of symbols between x and s or y and the remaining symbols
  string finalstring;  // Not necessarily needed. Just used for debugging purposes. If len > 0, result has to be false

  cout << "Untrimmed S: " + s + "\n";
  s = trimS(s, x);
  cout << "Trimmed S: " + s + "\n";

  // Comparing x string to s string
  for(int i = 0; i < s.length(); i++){
    // Add every element in s to the temporary whole string.
    whole_string += s.at(i);
    if(x.at(xspot) == s.at(i)){
      xspot++;
      // If a full x sequence is found, add all of the differing elements found to newstring,
      // reset the xspot, mark xfound as true, and reset both the temp string to restart the process for rest of elements in s.
      if(xspot == x.length()){
        newstring += diff_string;
        xspot = 0;
        xfound = true;
        diff_string.clear();
        whole_string.clear();
      }
    }
    else if(x.at(xspot) != s.at(i) ){
      diff_string += s.at(i);
    }
    // If it reaches the last element in s, add the remaining string to the newstring.
    // If the last element is a final piece of x in s, then whole_string should be reset
    // earlier so this wouldn't add anything.
    if(i == s.length()-1){
      newstring += whole_string;
    }
  }

  cout << "Newstring: " + newstring + "\n";
  diff_string.clear();
  whole_string.clear();

  // Uses newstring string built from x and s to compare for y. Exact same logic
  for(int i = 0; i < newstring.length(); i++){
    whole_string += newstring.at(i);
    if(y.at(yspot) == newstring.at(i)){
      yspot++;
      if(yspot == y.length()){
        finalstring += diff_string;
        diff_string.clear();
        whole_string.clear();
        yspot = 0;
      }
    }
    else if(y.at(yspot) != newstring.at(i)){
      diff_string += newstring.at(i);
    }

    if(i == newstring.length() - 1){
      finalstring += whole_string;
    }
  }

  // Different cases to consider when not interweaving
  // First case is if there is a finalstring with length larger than 0. That is leftover symbols that mean not interweaving
  // Second case is maybe there is no finalstring but x has not been found to interweave. So also not interweaving.
  // Third case is where x is interweaving but not y, so also not interweaving.
  // Any other cases will result in having an interweaving result.
  if(finalstring.length() != 0 || xfound == false || newstring.length() == 0){
    result = false;
    cout << "\nFinalstring: " + finalstring + "\n";
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
  bool xinterleave = false;
  bool yinterleave = false;

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

        cout << "S: " + s + "\n";
        cout << "x: " + x + "\n";
        cout << "y: " + y + "\n";

        // Runs the given strings into interweaving to check with x first then y.
        answer = interweaving(s, x, y, output);
        if(answer == true){
          output << "interweaving with signal X first\n";
          xinterleave = true;
        }
        else if(answer == false){
          output << "Not interweaving with signal X first\n";
        }

        // Runs the given strings into interweaving to check with y first then x.
        answer = interweaving(s, y, x, output);
        if(answer == true){
          output << "interweaving with signal Y first\n";
          yinterleave = true;
        }
        else if(answer == false){
          output << "Not interweaving with signal Y first\n";
        }

        // If both ways are interweaving, then it is interweaving both ways.
        if(xinterleave == true && yinterleave == true){
          output << "interweaving with both X and Y\n";
          output << "s: " + s;
          output << "\nx: " + x;
          output <<"\ny: " + y;
          xinterleave = false;
          yinterleave = false;
        }
        output << "\n";
        cout << "\n\n";

        // Clear the strings for the next randomly generated set.
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
      answer = interweaving(s, x, y, output);
      if(answer == true){
        cout << "Interweaving with signal X first\n";
        output << "Interweaving with signal X first\n";
        xinterleave = true;
      }
      else if(answer == false){
        cout << "Not Interweaving with signal X first\n";
        output << "Not Interweaving with signal X first\n";
      }

      // Runs the given strings into interweaving to check with y first then x.
      answer = interweaving(s, y, x, output);
      if(answer == true){
        cout << "Interweaving with signal Y first\n";
        output << "Interweaving with signal Y first\n";
        yinterleave = true;
      }
      else if(answer == false){
        cout << "Not Interweaving with signal Y first\n";
        output << "Not Interweaving with signal Y first\n";
      }

      if(xinterleave == true && yinterleave == true){
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
