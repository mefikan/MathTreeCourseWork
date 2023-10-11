#ifndef TREEV4_H
#define TREEV4_H

#endif // TREEV4_H

#include <iostream>
#include <QString>
using namespace std;
struct Node {
    string data;
    Node* left, * right;
};
typedef Node* PNode;

PNode maketree(string Data, int first, int last);//string на qstring
int calctree(PNode tree);
string deletewhitespaces(string s);
string Print_Deep(PNode tree, int n);
string printLKP(PNode tree);
string printLPK(PNode tree);
string printKLP(PNode tree);
int chardigtointdigit(char k);
int priority(char c);

bool Check_on_Brackets(string expr);
bool Is_Letter(char x);
bool Check_on_Letters(string expr);
bool Znak_Repeat_Test(string expr);
bool Allowed_Signs(string expr);
bool Is_Sign(char x);

string Print_Width(PNode tree);
