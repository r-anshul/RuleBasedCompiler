#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "token.h"
class Parser {
    std::vector<Token> tokens;
    int current;
public:
    Parser(std::vector<Token> t);
    void parseRule();
private:
    void parseCondition();
    void parseExpr();
    void parseAction();
    Token peek();
    Token advance();
    bool match(TokenType type);
    void error();
};
#endif