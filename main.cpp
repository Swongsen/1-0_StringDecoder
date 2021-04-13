#include <string>
#include <iostream>

using namespace std;

string interleaving(string s, string x, string y){
  string result;
  // Checks first if s is at least longer than the two signals x and y.
  if(s.length() < x.length() && s.length() < y.length()){
    result = "Signal not long enough. Not interleaving.";
    return result;
  }

  int xspot = 0;
  int yspot = 0;
  bool xfound = false;
  string newstring;    // Used for figuring out the leftover symbols needed for y to determine if interweaving
  string whole_string; // Used for holding the entire sequence of symbols
  string diff_string;  // Used for holding only the differing sequence of symbols between x and s or y and the remaining symbols
  string finalstring;  // Not necessarily needed. Just used for debugging purposes. If len > 0, result has to be false

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

  // If there is nothing in the final string, then it is interweaving. If there is something, then it is not interweaving.
  if(finalstring.length() != 0 || xfound == false){
    result = "\false";
    cout << "Finalstring: " + finalstring + "\n";
  }
  else
    result = "\ntrue";

  return result;
}

int main(){
  // Initial variables as described in the project document
  string s;
  string x;
  string y;
  string answer;

  // Takes user input and stores into s, x, and y respectively
  cout << "Input s: ";
  cin >> s;

  cout << "Input x: ";
  cin >> x;

  cout << "Input y: ";
  cin >> y;

  // Passes variables to function and prints whether s is interleaving of x and y or not
  answer = interleaving(s, x, y);
  cout << answer;

  return 0;
}
