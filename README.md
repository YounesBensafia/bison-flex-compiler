## Execute the Commands Inside `exemple.txt`

The following steps compile and build the compiler:

```sh
bison -d parser.y
flex lexical.l
gcc -c SymbolTable.c -o SymbolTable.o
gcc -c parser.tab.c -o parser.o
gcc -c lex.yy.c -o lexical.o
gcc -o compilateur SymbolTable.o lexical.o parser.o -lfl


./compilateur < exemple.txt

