#include "Parser.h"

const vector<string> Parser::expectedTokens[6] {
    {"number", "-", "("},
    {"+", "-", ")", "EOF"},
    {"number", "-", "("},
    {"+", "-", "*", "/", ")", "EOF"},
    {"number", "-", "("},
    {"number", "-", "("}
};

Parser::Parser() {}

Parser::Parser(const string &exp) : lex(exp) {}

void Parser::setExpression(const string &exp) {
    lex.setExpression(exp);
}

char Parser::getChar() {
    return *(char *)&token;
}

float Parser::parse() throw(exception) {
    token = 0;
    type = lex.getToken(&token);
    if (type == FLOAT) {
        float result = production_1();
        if (type != END) {
            throw MismatchedParenthesis();
        }
        return result;
    }
    if (type == CHAR) {
        char op = getChar();
        if (op == '-' || op == '(') {
            float result = production_1();
            if (type != END) {
                throw MismatchedParenthesis();
            }
            return result;
        }
    }
    string s = lex.unexpectedToken(expectedTokens[0]);
    throw UnexpectedTokenException(s);
}

float Parser::production_1() throw(exception) {
    /**
       Production 1:
         E -> TE_
     */

    //  already in this production, just forward to production 3
    float T = production_3();


    //    type = lex.getToken(&token);
    if (type == CHAR) {
        char op = getChar();
        if (op == '+' || op == '-') {
            return production_2(T);
        }
        if (op == ')') {
            return T;
        }
    }
    else if (type == END) {
        return T;
    }
    throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[1]));
}

float Parser::production_2(float inherited) throw(exception) {
    /**
       Production 2:
       E_ -> +TE_ | -TE_ | empty
    */

    if (type == END ||
        (type == CHAR && getChar() == ')')) {
        return inherited;
    }

    char op = getChar();

    token = 0;
    type = lex.getToken(&token);


    float T = 0;

    if (type == CHAR) {
        char nextOp = getChar();
        if (nextOp == '-' || nextOp == '(') {
            T = production_3();
        } else {
            throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[2]));
        }
    }
    else if (type == FLOAT) {
        T = production_3();
    } else {
        throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[2]));
    }

    if (op == '+') {
        production_2(inherited + T);
    }
    if (op == '-') {
        production_2(inherited - T);
    }
}

float Parser::production_3() throw(exception) {
    /**
       Production 3:
       T -> FT_
    */

    //  already in this production, just forward to production 5
    float F = production_5();

    // type = lex.getToken(&token);
    if (type == CHAR) {
        char op = getChar();
        if (op == '*' || op == '/') {
            return production_4(F);
        }
        if (op == ')' || op == '-' || op == '+') {
            return F;
        }
    }
    else if (type == END) {
        return F;
    }
    throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[3]));
}

float Parser::production_4(float inherited) throw(exception) {
    /**
       Production 4:
       T_ -> *FT_ | /FT_ | empty
    */

    if (type == END ||
        (type == CHAR && getChar() == ')')) {
        return inherited;
    }

    char op = getChar();

    token = 0;
    type = lex.getToken(&token);

    float F = 0;

    if (type == CHAR) {
        char nextOp = getChar();
        if (nextOp == '-' || nextOp == '(') {
            F = production_5();
        } else {
            throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[2]));
        }
    }
    else if (type == FLOAT) {
        F = production_5();
    } else {
        throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[4]));
    }

    if (op == '*') {
        return production_4(inherited * F);
    }
    if (op == '/') {
        return production_4(inherited / F);
    }
}

float Parser::production_5() throw(exception) {
    /**
       Production 5:
       F -> -N|N
    */

    if (type == FLOAT) {
        return production_6();
    }
    if (type == CHAR) {
        char op = getChar();
        if (op == '-') {
            type = lex.getToken(&token);
            return 0 - production_6();
        }
        if (op == '(') {
            return production_6();
        }
    }
    throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[5]));
}

float Parser::production_6() throw(exception) {
    /**
       Production 6:
       N -> (E) | id
    */

    if (type == FLOAT) {
        float _token = token;
        type = lex.getToken(&token);
        return _token;
    }
    if (type == CHAR) {
        char op = getChar();
        if (op == '(') {
            type = lex.getToken(&token);
            float E = 0;
            if (type == FLOAT) {
                E = production_1();
            }
            else if (type == CHAR) {
                char op = getChar();
                if (op == '-' || op == '(') {
                    E = production_1();
                }
            } else {
                throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[0]));
            }
            if (type == CHAR && getChar() == ')') {
                type = lex.getToken(&token);
                return E;
            }
        }
    }
    throw UnexpectedTokenException(lex.unexpectedToken(expectedTokens[0]));
}
