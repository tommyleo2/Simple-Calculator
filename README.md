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

## Parsing table

Non-terminal | id | + | - | * | / | ( | ) | $ 
------------ | --- | --- | --- | --- | --- | --- | --- | --- 
E  | E -> TE_ |             | E -> TE_    |            |            | E -> TE_  |             |             | 
E_ |          | E_ -> +TE_  | E_ -> -TE_  |            |            |           | E_ -> empty | E_ -> empty | 
T  | T -> FT_ |             | T -> FT_    |            |            | T -> FT_  |             |             | 
T_ |          | T_ -> empty | T_ -> empty |            |            |           |             |             | 
F  | F -> N   |             | F -> -N     | T_ -> *FT_ | T_ -> /FT_ | F -> N    |             |             | 
N  | N -> id  |             |             |            |            | N -> (E)  |             |             | 

Note: blank means error

## Drawback(s) in the productions

1. The parser using these productions cannot handle expressions like `1+1)` correctly, where left parentheses are less than right parentheses.
   To overcome this drawback, the parser checks if the lexical analyzer has met the end when it is about to return the result.

## Install and run

Just make the project and execute the executable main in the bin/ directory.
