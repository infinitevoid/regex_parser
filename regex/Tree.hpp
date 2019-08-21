#include <string>
#include <sstream>

using channel = std::ostringstream;

struct Node {
    public:
        bool Nullable;
        Node(bool nullable): Nullable(nullable){}
        Node(){}
        virtual Node* Derive(char next) {return nullptr;}
        virtual void Debug(channel &s){}
};

struct Empty: public Node {
    Empty(): Node(true){}
    Node* Derive(char next) {return this;}
    void Debug(channel &s){s << "_";}
};

struct Error: public Node {
    Error(): Node(false){}
    Node* Derive(char next) {return this;}
    void Debug(channel &s){s << "#";}
};

// constant
Empty* MATCH = new Empty();
Error* MISMATCH = new Error();

struct Terminal: public Node
{
    char Char;
    Terminal(char ch): Char(ch), Node(false){}
    Node* Derive(char next)
    {
        if(Char == next) return MATCH;
        return MISMATCH;
    }
    void Debug(channel &s){s << '\\' << Char;}
};

struct Or: public Node 
{
    Node* Left; Node* Right;
    Or(Node* left, Node* right): Left(left), Right(right), Node(left->Nullable || right->Nullable){};
    Node* Derive(char next)
    {
        Node* first = Left->Derive(next);
        Node* second = Right->Derive(next);
        //TODO optimize?
        //if(first == MISMATCH) return second;
        //else if(second == MISMATCH) return first;
        return new Or(first, second);
    }
    void Debug(channel &s){ s << "("; Left->Debug(s); s << "|"; Right->Debug(s); s << ")";}
};

struct And: public Node
{
    Node* Left; Node* Right;
    And(Node* left, Node* right): Left(left), Right(right), Node(left->Nullable && right->Nullable){}
    Node* Derive(char next)
    {
        Node* temp = new And(Left->Derive(next), Right);
        if(Left->Nullable) return new Or(temp, Right->Derive(next));
        return temp;
    }
    void Debug(channel &s){ s << "("; Left->Debug(s); s << " "; Right->Debug(s); s << ")";}
};

struct Star: public Node
{
    Node* Expr; 
    Star(Node* expr): Expr(expr), Node(true) {}
    Node* Derive(char next)
    {
        return new And(Expr->Derive(next), this);
    }
    void Debug(channel &s){ s << "("; Expr->Debug(s); s << ")*";}

};