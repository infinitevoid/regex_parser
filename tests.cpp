#include <iostream>
#include "regex/Regex.hpp"

using namespace std;

int main(){

    string r1 = "a|(b*c)";
    string test1[4] = {"bbbbbbc", "bbbbbb", "a", "ab"};
    for(int i = 0; i < 4; i++)
        cout << i << ": " << Match(test1[i], r1) << endl;

    string r2 = "c\\((a|(b*c))";
    Node* tree = CreateTree(r2);
    //channel is just an alias for ostringstream...
    channel s;
    //print tree
    tree->Debug(s); cout << s.str() << endl;
    string test2[4] = {"c(a", "c", "c(bbbbc", "cd"};
    for(int i = 0; i < 4; i++)
        cout << i << ": " << Match(test2[i], tree) << endl;


    return 0;
}