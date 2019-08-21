#include <string>
#include <iostream>
#include "Tree.hpp"

//TODO remove <iostream>
using namespace std;
//using string = std::string;


char Peek(string &str, int &index){
    if(index < str.size()) return str[index];
    return '\0';
}

Node* ParseRegex(string &regex, int &index)
{
    Node* tree = MATCH;
    char curr = Peek(regex, index);
    while(curr != '|' && curr != ')' && curr != '\0')
    {
        index++;
        //TODO remove debug stuff; cout << curr << endl;
        Node* node = new Terminal(curr);
        if(curr == '\\')
        {
            node = new Terminal(Peek(regex, index));
            index++;
        }
        else if(curr == '(')
        {
            node = ParseRegex(regex, index);
        } 
        curr = Peek(regex, index);
        while (curr == '+' || curr == '*')
        {
            Node* temp = node;
            if(curr == '*') node = new Star(temp);
            else node = new And(temp, new Star(temp));
            index++;
            curr = Peek(regex, index);
        }
        if(tree != MATCH) tree = new And(tree, node);
        else tree = node;
    }
    index++;
    if(curr == '|'){return new Or(tree, ParseRegex(regex, index));}
    return tree;
}

Node* CreateTree(string &regex)
{
    int index = 0;
    return ParseRegex(regex, index);
}