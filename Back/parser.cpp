#include <iostream>
#include <cstdlib>
#include "parser.h"
#include "tac.h"

using namespace std;

Parser::Parser(vector<Token> t)
{
    tokens = t;
    current = 0;
}

Token Parser::peek()
{
    return tokens[current];
}

Token Parser::advance()
{
    if (current < tokens.size())
        current++;
    return tokens[current - 1];
}

bool Parser::match(TokenType type)
{
    if (peek().type == type)
    {
        advance();
        return true;
    }
    return false;
}

void Parser::error()
{
    cout << "Syntax Error\n";
    exit(1);
}

Node* Parser::parseRule()
{
    if (!match(IF)) error();

    Node* condition = parseCondition();

    if (!match(THEN)) error();

    Node* action = parseAction();

    if (!match(END)) error();

    cout << "Parsing Successful\n";

    Node* root = new Node("=");   // assignment node
    root->left = action;
    root->right = condition;

    return root;
}

Node* Parser::parseCondition()
{
    Node* left = parseExpr();

    while (peek().type == AND || peek().type == OR)
    {
        Token op = advance();
        Node* right = parseExpr();

        Node* opNode;

        if (op.type == AND)
            opNode = new Node("AND");
        else
            opNode = new Node("OR");

        opNode->left = left;
        opNode->right = right;

        left = opNode;
    }

    return left;
}

Node* Parser::parseExpr()
{
    if (peek().type != IDENTIFIER) error();
    string id = advance().value;

    string op;

    if (match(GT)) op = ">";
    else if (match(LT)) op = "<";
    else if (match(EQ)) op = "==";
    else error();

    if (peek().type != NUMBER) error();
    string num = advance().value;

    Node* opNode = new Node(op);
    opNode->left = new Node(id);
    opNode->right = new Node(num);

    return opNode;
}

Node* Parser::parseAction()
{
    if (peek().type != IDENTIFIER) error();

    string action = advance().value;

    return new Node(action);
}