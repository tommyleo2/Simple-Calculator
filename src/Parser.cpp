#include "Parser.h"

Parser::Parser(const string &exp) : lex(exp) {}

void Parser::setExpression(const string &exp) {
    lex.setExpression(exp);
}

float Parse::parse() throw(exception) {
    return production_1();
}

float Parse::production_1() throw(exception) {
    /**
       Production 1:
         E -> TE_
     */
    float token = 0;
    Type type = lex.getToken(&token);
    if (type == CHAR) {
        return production_2();
    }
}
