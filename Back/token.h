#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
    IF, THEN, AND, OR,
    IDENTIFIER, NUMBER,
    GT, LT, EQ,
    END
};

struct Token {
    TokenType type;
    std::string value;
};

#endif
