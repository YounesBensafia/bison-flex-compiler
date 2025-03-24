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
%token mc_data mc_code MC_VECTOR mc_const mc_integer mc_float
%token mc_char mc_string mc_if mc_else mc_for mc_or mc_not mc_ge mc_l mc_di mc_le mc_read mc_display
%token <string> idf <entier> INTEGER <real> FLOAT <string> CHAR <string> STRING
%token <string> pvg sum mul minus PARAO paraf colon dot DIV eq virgule

%%

Program : 
    idf mc_data declartions_list mc_end mc_code instruction_list mc_end mc_end { printf("Program executed successfully.\n"); YYACCEPT; }
;

declartions_list : type colon liste_vars pvg 
           | idf '[' INTEGER virgule INTEGER ']' colon type pvg
;

liste_vars : idf
           | virgule idf
;


type : mc_integer
       | mc_float
       | mc_char
       | mc_string
;

instruction_list :  instruction
                | instruction_list instruction
;

instruction : assignment
            | read_display
            | if_condition
            | loop
;

assignment : idf eq expression pvg
;

read_display : mc_read PARAO idf paraf pvg
             | mc_display PARAO idf paraf pvg
;

if_condition : mc_if PARAO condition paraf mc_code instruction_list mc_end
             | mc_if PARAO condition paraf mc_code instruction_list mc_end mc_else mc_code instruction_list mc_end
;

loop : mc_for PARAO assignment condition pvg assignment paraf mc_code instruction_list mc_end
;

expression : term
           | expression sum term
           | expression minus term
;

term : factor
     | term mul factor
     | term DIV factor
;

factor : INTEGER
       | FLOAT
       | CHAR
       | STRING
       | idf
       | PARAO expression paraf
;

condition : expression mc_ge expression
          | expression mc_le expression
          | expression mc_l expression
          | expression mc_di expression
          | expression mc_not expression
          | expression mc_or expression
;
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