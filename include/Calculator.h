#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "Parser.h"

class Calculator {
public:
    Calculator();
    float calculate(const string &exp) throw(exception);

private:
    Parser parser;
};


#endif /* CALCULATOR_H */
