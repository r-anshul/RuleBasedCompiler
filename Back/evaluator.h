#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <map>
#include <string>
#include "tac.h"

using namespace std;

bool evaluate(Node* root, map<string, int>& variables);

#endif