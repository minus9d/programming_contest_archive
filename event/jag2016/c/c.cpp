#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>


using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#define FOR(i,a,b) for(int i = (a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(v) ((int)v.size())

#define pb push_back
#define mp make_pair

struct Tree {
    int root;
    Tree* left;
    Tree* right;

    Tree() :
        root(-1),
        left(nullptr),
        right(nullptr)
        {};
};


std::string tostring(Tree* tree) {
    std::string ret = "";
    ret = "(" + (tree->left == nullptr ? "" : tostring(tree->left)) + ")"
        + "[" + to_string(tree->root) + "]"
        + "(" + (tree->right == nullptr ? "" : tostring(tree->right)) + ")";
    return ret;
}

void divide(const string s, string& left, int& root, string& right) {
    int paren = 0;

    int i = 0;
    for(; i < SIZE(s); ++i) {
        auto ch = s[i];
        if (ch == '(') {
            ++paren;
        }
        else if  (ch == ')') {
            --paren;
        }

        if (paren == 0 && i != 0) {
            left = s.substr(1, i - 1);
            break;
        }
    }
    
    paren = 0;
    int j = 0;
    for(j = i + 1; j < SIZE(s); ++j) {
        auto ch = s[j];
        if (ch == '[') {
            ++paren;
        }
        else if  (ch == ']') {
            --paren;
        }
        if (paren == 0) {
            auto r = s.substr(i + 2, j - i - 2);
            root = stoi(r);
            break;
        }
    }
    
    right = s.substr(j + 2);
    right = right.substr(0, SIZE(right) - 1);
}

Tree* parse(string s) {
    auto tree = new Tree();

    string left, right;
    int root;
    divide(s, left, root, right);
    
    Tree* leftTree = (left == "") ? nullptr : parse(left);
    Tree* rightTree = (right == "") ? nullptr : parse(right);
    
    tree->root = root;
    tree->left = leftTree;
    tree->right = rightTree;

    return tree;
}

Tree* add_tree(Tree* t1, Tree* t2) {
    Tree* ret = new Tree();
    ret->root = t1->root + t2->root;
    if (t1->left != nullptr && t2->left != nullptr) {
        ret->left = add_tree(t1->left, t2->left);
    }
    if (t1->right != nullptr && t2->right != nullptr) {
        ret->right = add_tree(t1->right, t2->right);
    }
    return ret;
}


int main(void)
{
    cin.sync_with_stdio(false);
    string s1, s2;
    cin >> s1 >> s2;

    Tree* t1 = parse(s1);
    Tree* t2 = parse(s2);
    Tree* t3 = add_tree(t1,t2);

    //cout << tostring(t1) << endl;
    //cout << tostring(t2) << endl;

    cout << tostring(t3) << endl;
    
    return 0;
}
