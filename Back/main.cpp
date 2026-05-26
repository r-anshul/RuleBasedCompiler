#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include "parser.h"
#include "token.h"
#include "tac.h"
#include "ast_export.h"
#include "evaluator.h"

using namespace std;

extern vector<Token> tokens;
extern int yylex();

string tokenToString(Token t)
{
    switch (t.type)
    {
        case IF: return "IF";
        case THEN: return "THEN";
        case AND: return "AND";
        case OR: return "OR";

        case IDENTIFIER:
            return "IDENTIFIER(" + t.value + ")";

        case NUMBER:
            return "NUMBER(" + t.value + ")";

        case GT: return "GT";
        case LT: return "LT";
        case EQ: return "EQ";
        case END: return "END";
    }

    return "";
}

int main()
{
    yylex();

    tokens.push_back({END, ""});

    Parser parser(tokens);

    Node* root = parser.parseRule();

    generateTAC(root);

    // Dynamic variable evaluation
    map<string, int> variables;

    ifstream variableFile("variables.json");

    string jsonContent(
        (istreambuf_iterator<char>(variableFile)),
        istreambuf_iterator<char>()
    );

    variableFile.close();

    size_t pos = 0;

    while ((pos = jsonContent.find("\"", pos))
            != string::npos)
    {
        size_t endKey =
            jsonContent.find("\"", pos + 1);

        string key =
            jsonContent.substr(
                pos + 1,
                endKey - pos - 1
            );

        size_t colon =
            jsonContent.find(":", endKey);

        size_t comma =
            jsonContent.find(",", colon);

        if (comma == string::npos)
        {
            comma =
                jsonContent.find("}", colon);
        }

        string valueStr =
            jsonContent.substr(
                colon + 1,
                comma - colon - 1
            );

        variables[key] = stoi(valueStr);

        pos = comma;
    }

    bool result = evaluate(root->right, variables);

    ofstream resultFile("../output/result.txt");

    if (result)
    {
        resultFile << "ACTION TRIGGERED: "
                   << root->left->value;
    }
    else
    {
        resultFile << "RULE CONDITION FAILED";
    }

    resultFile.close();

    // TOKENS FILE
    ofstream tokenFile("../output/tokens.txt");

    for (const auto& t : tokens)
    {
        tokenFile << tokenToString(t) << endl;
    }

    tokenFile.close();

    // TAC FILE
    ofstream tacFile("../output/tac.txt");

    for (const auto& line : tacLines)
    {
        tacFile << line << endl;
    }

    tacFile.close();

    // AST JSON
    ofstream astFile("../output/ast.json");

    exportAST(root, astFile);

    astFile.close();

    cout << "Compilation Successful\n";

    return 0;
}