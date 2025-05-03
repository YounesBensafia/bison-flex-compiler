bison -d -v parser.y
flex lexical.l
gcc -c SymbolTable.c -o SymbolTable.o
gcc -c parser.tab.c -o parser.o
gcc -c lex.yy.c -o lexical.o
gcc -o compilateur SymbolTable.o lexical.o parser.o -lfl

./compilateur