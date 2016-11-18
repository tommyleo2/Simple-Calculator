#include "Calculator.h"

Calculator::Calculator() {}

float Calculator::calculate(const string &exp) throw(exception) {
    parser.setExpression(exp);
    return parser.parse();
}
