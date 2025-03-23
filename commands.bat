flex lexical.l && bison parser.y && gcc -o compilateur SymbolTable.c lex.yy.c parser.tab.c -lfl
