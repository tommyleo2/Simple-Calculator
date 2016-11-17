#ifndef PARSER_H
#define PARSER_H

/**
   Parser for a simple calculator using LL(1) method

   Productions:
   1. E -> TE_
   2. E_ -> +TE_ | -TE_ | empty
   3. T -> FT_
   4. T_ -> *FT_ | /FT_ | empty
   5. F -> -N|N
   6. N -> (E) | id

 */
#include <string>
#include "lexical_analyzer.h"

using namespace std;

class Parser {
public:
    Parser(const string &exp);

    void setExpression(const string &exp);

    float parse() throw(exception);

private:
    Lexical lex;

    float production_1() throw(exception);
    float production_2() throw(exception);
    float production_3() throw(exception);
    float production_4() throw(exception);
    float production_5() throw(exception);
    float production_6() throw(exception);
};


#endif /* PARSER_H */
