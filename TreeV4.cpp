//в данной версии работают многочисленные скобки, а также несколько оперций над одной скобкой.
//нужно сделать умножение, сложение, деление, разность чисел без пределов в размере
//работает все норм в принципе, но нет унарного знака
#include <iostream>
#include <iomanip>
#include <string>
#include <QList>
#include <vector>
#include <QString>
#include "mainwindow.h"



using namespace std;

struct Node {
    string data;
    Node* left, * right;
};
typedef Node* PNode;
bool Is_Letter(char x);

string Print_Width(PNode tree)
{
    if (tree){
        vector <PNode> nv;
        string res="";
        nv.push_back(tree);
        while (!nv.empty())
        {
            PNode q = nv[0];
            res+=q->data;
            auto iter = nv.begin();
            nv.erase(iter);
            if (q->left)
            {
                nv.push_back(q->left);
            }
            if (q->right)
            {
                nv.push_back(q->right);
            }
        }
        return res;
    }

}

int calctree(PNode tree) {
    if (tree){
        int num1, num2;
        if (!tree->left && !tree->right)
            return stoi(tree->data);
        num1 = calctree(tree->left);
        num2 = calctree(tree->right);
        switch (tree->data[0]) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/':
                if (num2!=0) return num1 / num2;
                else return 0;//ошибка
        }
        return 0;//ошибка.
    }

}
string Print_Deep(PNode tree, int n) {
    string res;
    if (tree) {
        res+=Print_Deep(tree->right, n + 5);
        for (int i = 0; i < n; i++) {
            res += " ";
        }
        res+= tree->data + "\n";
        res+=Print_Deep(tree->left, n + 5);
    }
    return res;
}
string printLKP(PNode tree) {
    string res;
    if (!tree) return "";
    res+=printLKP(tree->left);
    res+= tree->data;
    res+=printLKP(tree->right);
    return res;
}
string printLPK(PNode tree) {
    string res;
    if (!tree) return "";
    res+=printLKP(tree->left);
    res+=printLKP(tree->right);
    res+=tree->data;
    return res;
}
string printKLP(PNode tree) {
    string res;
    if (!tree) return "";
    res+= tree->data;
    res+=printLKP(tree->left);
    res+=printLKP(tree->right);
    return res;
}
int priority(char c) {
    switch (c) {
    case '+': case'-': return 1;
    case '*': case'/': return 2;
    }
    return 100;
}
int chardigtointdigit(char k) {
    switch (k) {
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case '5': return 5; break;
    case '6': return 6; break;
    case '7': return 7; break;
    case '8': return 8; break;
    case '9': return 9; break;
    default: return 0;
    }
}

vector <vector <int>> separating(string Data, int first, int last) {
    vector <vector <int>> sep;
    int begint, endint, prior, p = -1, pr2flag, pr1flag;//
    for (int i = first; i < last; i++) {
        pr2flag = 0; pr1flag = 0;
        if (i > p) {
            if (i > 0 && Data[i - 1] == ')' && (priority(Data[i]) == 1 || priority(Data[i]) == 2)) {
                if (priority(Data[i]) == 1) sep.push_back({ -11,i });
                else if (priority(Data[i]) == 2) sep.push_back({ -2,i });
            }

            if (Data[i] == '(') {
                int BeginOfFirstBracket = i, AnotherBracket = 0, Passedanother = 0;
                for (int j = i + 1; j < last+1; j++) {
                    if (Data[j] == '(') {
                        AnotherBracket++;
                    }
                    if (Data[j] == ')') {
                        if (AnotherBracket == Passedanother) {
                            int border = -123;
                            for (int k = j - 1; k > 0; k--) {
                                if (Data[k] != ')') {
                                    border = k; break;
                                }
                            }
                            sep.push_back({ 999,BeginOfFirstBracket + 1, border });
                            p = j - 1;
                            break;
                        }
                        else {
                            Passedanother++;
                        }
                    }
                }
            }

            if (isdigit(Data[i])||Is_Letter(Data[i])) {
                begint = i; endint = i;
                for (p = i + 1; p < last; p++) {
                    if (isdigit(Data[p]) || Is_Letter(Data[p]))
                        endint = p;
                    else {
                        prior = priority(Data[p]);
                        if (prior == 2) pr2flag = 1;
                        else if (prior == 1) pr1flag = 1;
                        break;
                    }
                }
                sep.push_back({ begint,endint });
                if (pr1flag == 1) sep.push_back({ -11,p });
                else if (pr2flag == 1) sep.push_back({ -2,p });
            }
        }

    }
    return sep;
}
int priorcounter(vector<vector<int>> sep) {
    int prt, minprt = 100, ind = -1;
    for (int i = 0; i < int(sep.size()); i++) {
        if (sep[i][0] == -11 || sep[i][0] == -2)
            prt = sep[i][0];
        else prt = 100;
        if (prt <= minprt) {
            minprt = prt;
            ind = i;
        }
    }
    return ind;
}
string deletewhitespaces(string s) {
    string res;
    for (int i=0;i<int(s.length());i++){
        if (s[i]!=' '){
            res+=s[i];
        }
    }
    return res;

}
PNode maketree(string Data, int first, int last) {
    PNode tree = new Node;
    vector <vector <int>> sep = separating(Data, first, last);


    if (first == last) {
        tree->data = Data[first];
        tree->left = NULL;
        tree->right = NULL;
        return tree;
    }

    int ind;
    ind = priorcounter(sep);
    if (sep[ind][0] == -11 || sep[ind][0] == -2) {
        tree->data = Data[sep[ind][1]];
        tree->left = maketree(Data, first, sep[ind][1]);
        tree->right = maketree(Data, sep[ind][1] + 1, last);
    }
    else if (sep[ind][0] == 999) {
        string tempsum;
        int mbc = 0, umbc = 0;
        for (int g = sep[ind][1]; g <= sep[ind][2] + 1; g++) {
            if (Data[g] == '(') mbc++;
            if (Data[g] == ')' && umbc < mbc) {
                tempsum.push_back(Data[g]);
                umbc++;
                continue;
            }
            else if (Data[g] == ')' && umbc >= mbc)
                continue;
            tempsum.push_back(Data[g]);
        }
        vector <vector <int>> sep1 = separating(tempsum, 0, tempsum.length());
        int ind1 = priorcounter(sep1);
        if (sep1[ind1][0] == -11 || sep1[ind1][0] == -2){
            tree->data = tempsum[sep1[ind1][1]];
            tree->left = maketree(tempsum, 0, sep1[ind1][1] - 1);
            tree->right = maketree(tempsum, sep1[ind1][1] + 1, tempsum.length());
        }
        else
        {
            tree->data=tempsum;
            tree->left=NULL;
            tree->right=NULL;
        }
    }
    else {
        string tempsum;
        for (int g = sep[ind][0]; g <= sep[ind][1] + 1; g++) {
            if (Data[g] != '+' && Data[g] != '-' && Data[g] != '*' && Data[g] != '/' && Data[g] != '(' && Data[g] != ')')
                tempsum.push_back(Data[g]);
        }
        tree->data = tempsum;
        tree->left = NULL;
        tree->right = NULL;
    }
    return tree;
}
bool Check_on_Brackets(string expr){
    int a = expr.length(), BrOpencount = 0, BrClosecount=0;
    for (int i=0;i<a;i++){
        if (expr[i]=='(')
            BrOpencount++;
        else if (expr[i]==')')
            BrClosecount++;
    }
    if (BrOpencount==BrClosecount)
        return true;
    else return false;
}

bool Is_Letter(char x){
    x=tolower(x);
    int a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for (int i=0;i<26;i++){
        if (x==a[i])
            return true;
    }
    return false;
}
bool Allowed_Signs(string expr){
    int a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
             'o','p','q','r','s','t','u','v','w','x','y','z','1','2',
             '3','4','5','6','7','8','9','0','-','+','/','*','(',')'};
    int f=0;
    for (int i=0;i<int(expr.length());i++){
        f=0;
        for (int j=0;j<43;j++){
            if (tolower(expr[i])==a[j])
                f=1;
        }
        if (f==0) {
            return false;

        }
    }
    return true;
}
bool Check_on_Letters(string expr){
    for (int i=0;i<int(expr.length());i++){
        if (Is_Letter(expr[i])) return false;
    }
    return true;
}
bool Is_Sign(char x){
    if (x=='-' || x=='+' || x=='*' || x=='/')
        return true;
    else return false;
}
bool Znak_Repeat_Test(string expr){
    for (int i=0;i<int(expr.length())-1;i++){
        if (Is_Sign(expr[i]) && Is_Sign(expr[i+1])){
            return false;
        }
    }
    return true;
}





