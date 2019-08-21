#include <iostream>
#include "regex/Regex.hpp"

using namespace std;

int main(){
    cout << "HELLO" << endl;
    string re = "a|(b*c)";
    int ind = 0;
    ostringstream s; 
    Node* tree = ParseRegex(re, ind);
    tree->Debug(s);
    cout << s.str() << endl;
    string test = "bbbbbbc";
    string test1 = "bbbbbb";
    string test2 = "a";
    string test3 = "ab";
    cout << Match(test3, tree) << endl;
    return 0;
}