#include <iostream>
#include <cstdlib>
#include "parser.h"
using namespace std;
Parser::Parser(vector<Token> t) {
    tokens = t;
    current = 0;
}
Token Parser::peek() {
    return tokens[current];
}
Token Parser::advance() {
    if (current < tokens.size())
        current++;
    return tokens[current - 1];
}
bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}
void Parser::error() {
    cout << "Syntax Error\n";
    exit(1);
}
void Parser::parseRule() {
    if (!match(IF)) error();
    parseCondition();
    if (!match(THEN)) error();
    parseAction();
    if (!match(END)) error();
    cout << "Parsing Successful\n";
}
void Parser::parseCondition() {
    parseExpr();

    while (peek().type == AND || peek().type == OR) {
        advance();
        parseExpr();
    }
}
void Parser::parseExpr() {
    if (!match(IDENTIFIER)) error();

    if (!(match(GT) || match(LT) || match(EQ)))
        error();

    if (!match(NUMBER)) error();
}
void Parser::parseAction() {
    if (!match(IDENTIFIER)) error();
}