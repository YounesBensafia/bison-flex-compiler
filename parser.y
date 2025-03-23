%{
#include <stdio.h>
int yylex(void);           
void yyerror(const char *s);
#include "SymbolTable.h"
%}

%union 
{ 
   int entier;
   float real; 
   char* string;
   char caracter;
}

%token <string> mc_do mc_if mc_else mc_while mc_data
%token <string> idf <real> REELN <real> REELP
%token pvg gt ls plus produit minus divi eq paraF paraO

%%

instruction_Do_While : 
    mc_do mc_if paraO condition paraF inst mc_else inst mc_while paraO condition paraF pvg { printf("Program executed successfully.\n"); YYACCEPT; }
;

oper_math : plus 
          | minus 
          | divi 
          | produit
;

oper : ls 
     | gt
;

inst: var eq instplus pvg
    | inst var eq instplus pvg
;

instplus : var oper_math var instplus 
         | var
;

condition : var oper var
;

var : REELN 
    | REELP 
    | idf
;

%%

int main() {
    initialisation();
    yyparse();
    afficher();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}