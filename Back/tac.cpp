#include "tac.h"

vector<string> tacLines;

Node::Node(string val)
{
    value = val;
    left = right = NULL;
}

int tempCount = 1;

string newTemp()
{
    return "t" + to_string(tempCount++);
}

string generateTAC(Node* root)
{
    if (root == NULL)
        return "";

    if (root->left == NULL && root->right == NULL)
        return root->value;

    if (root->value == "=")
    {
        string right = generateTAC(root->right);

        string line = root->left->value + " = " + right;

        tacLines.push_back(line);

        return root->left->value;
    }

    string left = generateTAC(root->left);
    string right = generateTAC(root->right);

    string temp = newTemp();

    string line = temp + " = " + left + " " + root->value + " " + right;

    tacLines.push_back(line);

    return temp;
}