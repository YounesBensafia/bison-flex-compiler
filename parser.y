%{
#include <stdio.h>
int yylex(void);           
void yyerror(const char *s);
#include "SymbolTable.h"
char type[20];
int nb_ligne=1, nb_colonne=1;
%}

%start program

%union 
{ 
   int entier;
   float real; 
   char *string;
   char caracter;
}

%token <string> mc_end
%token <string> mc_data <string> mc_code MC_VECTOR mc_const
%token mc_if mc_else mc_for mc_or mc_not mc_ge mc_l mc_di mc_le mc_read mc_display
%token <string> idf <entier> INTEGER <real> FLOAT <string> CHAR <string> STRING
%token <string> pvg sum mul minus PARAO PARAF colon dot DIV eq virgule arobase
%token left_bracket right_bracket
%token <string> mc_integer mc_float mc_char mc_string
%type <string> type

%%

// GITHUB ISSUE: #5 PROGRAM EXECUTED SUCCESSFULLY printed despite semantic errors

program : 
    idf {
            update_type($1, "STRING");
        } mc_data declartions_list mc_end mc_code instruction_list mc_end mc_end { printf("Program executed successfully.\n"); YYACCEPT; }
;

declartions_list : type colon idf {
                if (double_declaration($3, $1) == 0) {
                    printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne);
                } else {
                    if (double_declaration($3, $1) == 2)
                    {
                        printf("ERREUR SEMANTIQUE: %s TYPE ERROR, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne);
                    }
                    else
                    {
                        strcpy(type, $1);
                        update_type($3, $1);
                    }
                }
                }
            liste_vars declartions_list
           | vector declartions_list | constante pvg declartions_list
           | /* empty */
;

liste_vars : virgule idf liste_vars {
                if (double_declaration($2, type) == 0) {
                    printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $2, nb_ligne, nb_colonne);
                } else {
                    update_type($2, type);
                }
}
            | pvg
;


vector :MC_VECTOR colon idf left_bracket INTEGER virgule INTEGER colon type 
    {
        if (double_declaration($3, $9) == 0) {
            printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne);
        } else {
            if (double_declaration($3, $9) == 2)
            {
                printf("ERREUR SEMANTIQUE: %s TYPE ERROR, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne);
            }
            else
            {
                strcpy(type, $9);
                update_type($3, $9);
            }
        }
    }
right_bracket pvg
;

// vector_list : virgule idf left_bracket INTEGER virgule INTEGER colon type right_bracket vector_list | pvg
// ;

constante: mc_const colon idf eq factor_constante {
    if (double_declaration($3, type) == 0) {
        printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne);
    } 
    else
    {
        if (double_declaration($3, type) == 2)
        {
            printf("ERREUR SEMANTIQUE: %s TYPE ERROR, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne);
        }
        else
        {
            update_type($3,type);
        }
    }
    
    }

factor_constante : INTEGER {strcpy(type, "INTEGER");}
                 | FLOAT {strcpy(type, "FLOAT");}
                 | STRING {strcpy(type, "STRING");}
                 | CHAR {strcpy(type, "CHAR");}

type : mc_integer {$$ = strdup($1); }
    | mc_float {$$ = strdup($1); }
    | mc_char {$$ = strdup($1); }
    | mc_string {$$ = strdup($1); }
;

// GITHUB ISSUE: #3 There is an issue with generating the `mc_read` instruction after an `if-else` block. The parser does not handle this sequence correctly, leading to unexpected behavior or errors.
instruction_list : instruction instruction_list | 
;

instruction : assignment 
            | read_display
            | if_condition 
            | loop
;

assignment : idf eq expression pvg
;

read_display : mc_read PARAO STRING colon arobase idf PARAF pvg
             | mc_display PARAO STRING colon idf PARAF pvg
;

if_condition : mc_if PARAO condition PARAF colon instruction_list else_condition
;

else_condition: mc_else colon instruction_list mc_end 
                | mc_end
;

loop : mc_for PARAO idf colon INTEGER colon INTEGER PARAF instruction_list mc_end
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
       | PARAO expression PARAF
;

condition : expression dot mc_ge dot expression
          | expression dot mc_le dot expression
          | expression dot mc_l dot expression
          | expression dot mc_di dot expression
          | expression dot mc_not dot expression
          | expression dot mc_or dot expression
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