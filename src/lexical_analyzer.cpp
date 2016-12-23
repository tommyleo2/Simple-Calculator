#include "lexical_analyzer.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

const string Lexical::errorMsg("ERROR: ");

Lexical::Lexical() {}

Lexical::Lexical(const string &exp) :
    currentTokenPosition(0), currentTokenSize(0) {
    this->exp = exp;
}

void Lexical::setExpression(const string &exp) {
    parenthesis = currentTokenSize = currentTokenPosition = 0;
    this->exp = exp;
}

Type Lexical::getToken(float *token) throw(exception) {
    *(int *)token = 0;
    while ((exp[currentTokenPosition] == ' ' ||
            exp[currentTokenPosition] == '\t') &&
           currentTokenPosition < exp.size()) {
        currentTokenPosition++;
    }
    if (currentTokenPosition == exp.size()) {
        currentTokenPosition++;
        return END;
    }
    char first = exp[currentTokenPosition];
    if (first < '0' || first > '9') {
        if (!(first == '(' || first == ')' || first == '+' || first == '-' ||
              first == '*' || first == '/')) {
            throw UnrecognizedTokenException(unrecognizedToken());
        }

        *(char *)token = first;
        currentTokenPosition++;
        return CHAR;
    }
    /*
      Todo: support dedcimal tokens
    */

    bool decimalPoint = false;
    int tmpPostion = currentTokenPosition;
    while (exp[tmpPostion] >= '0' &&
           exp[tmpPostion] <= '9' || exp[tmpPostion] == '.') {
        tmpPostion++;
        if (exp[tmpPostion] == '.') {
            if (!decimalPoint) {
                decimalPoint = true;
            } else {
                currentTokenPosition = tmpPostion;
                throw UnrecognizedTokenException(unrecognizedToken());
            }
        }
    }

    *token = atof(exp.c_str() + currentTokenPosition);

    currentTokenPosition = tmpPostion;
    return FLOAT;
}

string Lexical::unexpectedToken(const vector<string> &candidate) {
    stringstream ss;
    ss << errorMsg << exp << endl;
    for (int i = 0; i < errorMsg.size() + currentTokenPosition; i++) {
        if (exp[i - errorMsg.size()] == '\t') {
            ss << '\t';
        } else {
            ss << " ";
        }
    }
    ss << "\b";
    ss << "^";
    ss << "  Unexpected Token" << endl;
    // Todo

    // ss << "Note: Acceptable tokens are: ";
    // for (int i = 0; i < candidate.size() - 1; i++) {
    //     ss << "\"" << candidate[i] << "\", ";
    // }
    // ss << "\"" << candidate.back() <<  "\"" << endl;

    return ss.str();
}

string Lexical::unrecognizedToken() {
    stringstream ss;
    ss << errorMsg << exp << endl;
    for (int i = 0; i < errorMsg.size() + currentTokenPosition; i++) {
        if (exp[i - errorMsg.size()] == '\t') {
            ss << '\t';
        } else {
            ss << " ";
        }
    }
    ss << "^";
    ss << "  Unrecognized Token" << endl;
    ss << "Note: Acceptable tokens are: "
       << "numbers, `+`, `-`, '*', '/', '(' and ')'" << endl;
    return ss.str();
}
