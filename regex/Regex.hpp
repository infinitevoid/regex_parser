#include "Parser.hpp"

//TODO return amount of matched characters
bool Match(string test, Node* tree)
{
    Node* step = tree;
    for(int i = 0; i < test.size(); i++)
    {
        step = step->Derive(test[i]);
        cout << i << ": ";
        channel s;
        step->Debug(s);
        cout << s.str();
        cout << endl;
    }
    return step->Nullable;
}

bool Match(string test, string regex)
{
    int index = 0;
    Node* tree = ParseRegex(regex, index);
    return Match(test, tree);
}
