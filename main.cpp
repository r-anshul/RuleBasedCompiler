#include <iostream>
#include <vector>
#include "parser.h"
#include "token.h"
using namespace std;
extern vector<Token> tokens;
extern int yylex();
int main() {
    cout << "Enter rule - \n";
    yylex();
    tokens.push_back({END, ""});
    cout << "\nTokens -\n";
    for (const auto &t : tokens) //ony for debugging
    {
        switch (t.type) {
            case IF: cout << "IF\n"; break;
            case THEN: cout << "THEN\n"; break;
            case AND: cout << "AND\n"; break;
            case OR: cout << "OR\n"; break;
            case IDENTIFIER: cout << "IDENTIFIER(" << t.value << ")\n"; break;
            case NUMBER: cout << "NUMBER(" << t.value << ")\n"; break;
            case GT: cout << "GT\n"; break;
            case LT: cout << "LT\n"; break;
            case EQ: cout << "EQ\n"; break;
            case END: cout << "END\n"; break;
        }
    }
    cout << endl;
    Parser parser(tokens);
    parser.parseRule();
    return 0;
}