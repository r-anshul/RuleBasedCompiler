#include "ast_export.h"

void exportAST(Node* root, ofstream& file)
{
    if (root == NULL)
    {
        file << "null";
        return;
    }

    file << "{";
    file << "\"name\":\"" << root->value << "\",";

    file << "\"children\":[";

    bool hasLeft = (root->left != NULL);
    bool hasRight = (root->right != NULL);

    if (hasLeft)
    {
        exportAST(root->left, file);

        if (hasRight)
            file << ",";
    }

    if (hasRight)
    {
        exportAST(root->right, file);
    }

    file << "]";

    file << "}";
}