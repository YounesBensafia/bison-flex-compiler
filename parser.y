%{
#include <stdio.h>
#include <string.h>
int yylex(void);           
void yyerror(const char *s);
#include "SymbolTable.h"
char type[30];
char* typeIdf;
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
%token <string> pvg sum mul minus PARAO PARAF colon dot DIV eq virgule bar arobase
%token left_bracket right_bracket
%token <string> mc_integer mc_float mc_char mc_string
%type <string> type

%%


program : 
    idf {
            update_type($1, "STRING");
        } mc_data declartions_list mc_end mc_code instruction_list mc_end mc_end { printf("Program executed successfully.\n"); YYACCEPT; }
;

declartions_list : type colon idf {
                if (double_declaration($3, $1) == 0) {
                    printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne); exit(1);
                } else {
                    if (double_declaration($3, $1) == 2)
                    {
                        printf("ERREUR SEMANTIQUE: %s TYPE ERROR, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne); exit(1);
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

instruction_list : instruction instruction_list |
;

instruction : assignment 
            | read_display
            | if_condition 
            | loop
;
liste_vars : bar idf liste_vars {
                if (double_declaration($2, type) == 0) {
                    printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $2, nb_ligne, nb_colonne); exit(1);
                } else {
                    update_type($2, type);
                }
}
            | pvg
;


vector :MC_VECTOR colon idf left_bracket INTEGER virgule INTEGER colon type 
    {
        if (double_declaration($3, $9) == 0) {
            printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne); exit(1);
        } else {
            if (double_declaration($3, $9) == 2)
            {
                printf("ERREUR SEMANTIQUE: %s TYPE ERROR, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne); exit(1);
            }
            else
            {
                sprintf(type, "%s*", $9);
                update_type($3, type);
            }
        }
    }
right_bracket pvg
;


constante: mc_const colon idf eq factor_constante {
    if (double_declaration($3, type) == 0) {
        printf("ERREUR SEMANTIQUE: %s double_declaration, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne); exit(1);
    } 
    else
    {
        if (double_declaration($3, type) == 2)
        {
            printf("ERREUR SEMANTIQUE: %s TYPE ERROR, a la ligne %d, et la colonne %d\n", $3, nb_ligne, nb_colonne); exit(1);
        }
        else
        {
            update_type($3,type);
        }
    }
    
    }

factor_constante : INTEGER {strcpy(type, "C_INTEGER");}
                 | FLOAT {strcpy(type, "C_FLOAT");}
                 | STRING {strcpy(type, "C_STRING");}
                 | CHAR {strcpy(type, "C_CHAR");}

type : mc_integer {$$ = strdup($1); }
    | mc_float {$$ = strdup($1); }
    | mc_char {$$ = strdup($1); }
    | mc_string {$$ = strdup($1); }
;


assignment : idf {
    
    if(double_declaration($1, "") == 1) 
    {
        printf("ERREUR SEMANTIQUE: %s non declare, a la ligne %d, et la colonne %d\n", $1, nb_ligne, nb_colonne); exit(1);
    }
    else {
        if(isConstant($1))
        {
            printf("ERREUR SÉMANTIQUE : %s est une constante et ne peut pas être modifiée (ligne %d, colonne %d)\n", $1, nb_ligne, nb_colonne); exit(1);
        }
        else
        {
           push_type(getType($1));
            
        }
    }
} eq expression {pop_type();} pvg
;

read_display : mc_read PARAO signe colon arobase idf PARAF pvg
             | mc_display PARAO STRING colon idf PARAF pvg
;

signe: "$" 
    | "%" 
    | "#" 
    | "&"
;

if_condition : mc_if PARAO condition PARAF colon instruction_list else_condition
;

else_condition: mc_else colon instruction_list mc_end 
                | mc_end
;

loop : mc_for PARAO idf colon INTEGER {pop_type();} colon expression PARAF instruction_list mc_end
;

expression : term 
           | expression sum term 
           | expression minus term
;

term : factor 
     | term mul factor
     | term DIV factor
;

factor : INTEGER {
            push_type("INTEGER");
            char* expected_type = peek_type();
                if(expected_type == NULL) return 0;

                if(strcmp(expected_type, "INTEGER") != 0 && !isCTyped(expected_type)) {
                    printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                    exit(1);
                }
            }
       | FLOAT {
                push_type("FLOAT");
                char* expected_type = peek_type();
                if(expected_type == NULL) return 0;

                if(strcmp(expected_type, "FLOAT") != 0 && !isCTyped(expected_type)) {
                    printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                    exit(1);
                }
                        }
       | CHAR
       {
            push_type("CHAR");
            char* expected_type = peek_type();
            if(expected_type == NULL) return 0;

            if(strcmp(expected_type, "CHAR") != 0 && !isCTyped(expected_type)) {
                printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                exit(1);
            }
        }
       | STRING
        {
            push_type("STRING");
            char* expected_type = peek_type();
            if(expected_type == NULL) return 0;

            if(strcmp(expected_type, "CHAR") != 0 && !isCTyped(expected_type)) {
                printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                exit(1);
            }
        }
       | idf {
            char* expected_type = peek_type();
            if (expected_type == NULL) return 0;

            if (double_declaration($1,"") == 1) {
                printf("ERREUR SEMANTIQUE: %s non declare, a la ligne %d, et la colonne %d\n", $1, nb_ligne, nb_colonne);
                exit(1);
            }

            if (strcmp(expected_type, getType($1)) != 0 && !isCTyped(expected_type)) {
                printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                exit(1);
            }
        }
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