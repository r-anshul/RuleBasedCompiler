#include "evaluator.h"

bool evaluate(Node* root, map<string, int>& variables)
{
    if (root == NULL)
        return false;

    // AND
    if (root->value == "AND")
    {
        return evaluate(root->left, variables)
            && evaluate(root->right, variables);
    }

    // OR
    if (root->value == "OR")
    {
        return evaluate(root->left, variables)
            || evaluate(root->right, variables);
    }

    // >
    if (root->value == ">")
    {
        string var = root->left->value;
        int value = stoi(root->right->value);

        return variables[var] > value;
    }

    // <
    if (root->value == "<")
    {
        string var = root->left->value;
        int value = stoi(root->right->value);

        return variables[var] < value;
    }

    // ==
    if (root->value == "==")
    {
        string var = root->left->value;
        int value = stoi(root->right->value);

        return variables[var] == value;
    }

    return false;
}