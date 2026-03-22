%{
#include "token.h"
#include <vector>
using namespace std;
vector<Token> tokens;
%}
%%
"IF"        { tokens.push_back({IF, ""}); }
"THEN"      { tokens.push_back({THEN, ""}); }
"AND"       { tokens.push_back({AND, ""}); }
"OR"        { tokens.push_back({OR, ""}); }
">"         { tokens.push_back({GT, ""}); }
"<"         { tokens.push_back({LT, ""}); }
"=="        { tokens.push_back({EQ, ""}); }
[0-9]+      { tokens.push_back({NUMBER, yytext}); }
[a-zA-Z_][a-zA-Z0-9_]*  { tokens.push_back({IDENTIFIER, yytext}); }
[ \t\n]+    ;   // ignore whitespace
.           ;   // ignore unknown characters
%%
int yywrap()
{
    return 1;
}