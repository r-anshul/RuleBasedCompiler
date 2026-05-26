#ifndef TAC_H
#define TAC_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val);
};

extern vector<string> tacLines;

string generateTAC(Node* root);

#endif