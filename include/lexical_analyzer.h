#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <vector>
#include <exception>

using namespace std;

class UnrecognizedTokenException : public exception {
public:
    string msg;

    UnrecognizedTokenException(const string &msg) {
        this->msg = move(msg);
    }

    virtual const char *what() const noexcept {
        return msg.c_str();
    }
};

typedef enum Type {
    CHAR, FLOAT, END
} Type;

class Lexical {
private:
    static const string errorMsg;

public:
    Lexical();
    Lexical(const string &exp);

    void setExpression(const string &exp);

    Type getToken(float *token) throw (exception);
    string unexpectedToken(const vector<string>& candidate);

private:
    string exp;

    int currentTokenPosition;
    int currentTokenSize;

    string unrecognizedToken();

    int parenthesis;
};

#endif /* LEXICAL_ANALYZER_H */
