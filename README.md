# A simple calculator

This is a simple calculator in C++ implementing with LL(1) parser

---

## Structure

1. The `Lexical` traverses the input expression and returns tokens it extract.
2. The `Parser` receives the tokens and calculates according to the productions.

## Productions

The productions that the parser uses is as follows:

1. E -> TE_
2. E_ -> +TE_ | -TE_ | empty
3. T -> FT_
4. T_ -> *FT_ | /FT_ | empty
5. F -> -N|N
6. N -> (E) | id

## Install and run

Just make the project and execute the executable main in the bin/ directory.
