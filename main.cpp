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
  string newstring;
  string finalstring;
  // Goes through s and checks if x string is in it. If an x string is fully found, reset spot to 0
  // and keep checking to see if there are more. Rebuild string without the found x string(s).
  for(int i = 0; i < s.length(); i++){
    if(x.at(xspot) == s.at(i)){
      xspot++;
      if(xspot == x.length()){
        xspot = 0;
      }
    }
    // If in the initial string, the subsequence element is not found at a spot, add it to the new string.
    // The || condition is making sure that the remaining unchecked string is still longer than x.
    else if(x.at(xspot) != s.at(i) || ((s.length() - i) < x.length()) ){
      newstring += s.at(i);
    }
  }
  cout << newstring;

  for(int i = 0; i < newstring.length(); i++){
    if(y.at(yspot) == newstring.at(i)){
      yspot++;
      if(yspot == y.length()){
        yspot = 0;
      }
    }
    else if(y.at(yspot) != newstring.at(i)){
      finalstring += newstring.at(i);
    }
  }

  if(finalstring.length() != 0){
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
