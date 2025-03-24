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

%token mc_end
%token mc_data mc_code MC_VECTOR mc_const mc_integer mc_float mc_char mc_string mc_if mc_else mc_for mc_or mc_not mc_ge mc_l mc_di mc_le
%token <string> idf <entier> INTEGER <real> FLOAT <string> CHAR <string> STRING
%token <string> pvg sum mul minus PARAO paraf colon dot DIV eq

%%

instruction_Do_While : 
    idf mc_data declartion mc_end mc_code instructions mc_end mc_end { printf("Program executed successfully.\n"); YYACCEPT; }
;

declartion : type colon pvg
;

type : mc_integer
       | mc_float
       | mc_char
       | mc_string

;
instructions : mc_if
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