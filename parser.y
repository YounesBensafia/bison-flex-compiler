%{
#include <stdio.h>
#include <string.h>
int yylex(void);           
void yyerror(const char *s);
#include "SymbolTable.h"
#include "qdr.h"
char type[30];
char* typeIdf;
int nb_ligne=1, nb_colonne=1;
char* string;
int tempCount = 0;
int nbQdr = -1;
int tempQdr = 0; 

char* newtemp() {
    char* tempName = malloc(10);       // alloue de l'espace pour le nom (ex: "t123")
    sprintf(tempName, "t%d", tempCount++); // génère "t0", "t1", "t2", ...
    return tempName;
}
%}

%start program

%union 
{ 
   int entier;
   float real; 
   char *string;
   char caracter;
}

%token <string> mc_end double_quote 
%token <string> mc_data <string> mc_code MC_VECTOR mc_const
%token mc_if mc_else mc_for mc_or mc_not mc_ge mc_l mc_di mc_le mc_read mc_display
%token <string> idf <entier> INTEGER <real> FLOAT <caracter> CHAR <string> STRING
%token <string> pvg sum mul minus PARAO PARAF colon dot DIV eq virgule bar arobase
%token left_bracket right_bracket
%token <string> mc_integer mc_float mc_char mc_string
%token <string> percent hash dollar ampersand
%type <string> type
%type <string> factor term expression
 
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
        char buf1[20], buf2[20];
        sprintf(buf1, "%d", $5);
        sprintf(buf2, "%d", $7);
        nbQdr = nbQdr + 1;
        quadr(nbQdr, "BOUNDS", strdup(buf1), strdup(buf2), "");
        nbQdr = nbQdr + 1;
        quadr(nbQdr,"ADEC",$3,"","");
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
} eq expression {
    pop_type(); 
    nbQdr = nbQdr + 1;
    quadr(nbQdr, "=", string, "", $1);
} pvg 
;

expression : term { 
                string = $1;
                $$ = $1; 
            }
           | expression sum term {
                $$ = $1; 
                nbQdr = nbQdr + 1;
                char* temp = newtemp();
                string = temp;
                quadr(nbQdr,"+",strdup($1),strdup($3),temp); 
            }
           | expression minus term
           {
                $$ = $1; 
                nbQdr = nbQdr + 1;
                char* temp = newtemp();
                string = temp;
                quadr(nbQdr,"-",strdup($1),strdup($3),temp); 
            }
;

read_display : mc_read PARAO CHAR colon arobase idf PARAF pvg
{
        nbQdr = nbQdr + 1;
        char format[4];
        if ($3 == '$') strcpy(format, "%d");
        else if ($3 == '%') strcpy(format, "%f");
        else if ($3 == '#') strcpy(format, "%s");
        else if ($3 == '&') strcpy(format, "%c");
        else strcpy(format, "");
        quadr(nbQdr, "READ", $6, format, "");
        if (double_declaration($6, "") == 1) {
            printf("ERREUR SEMANTIQUE: %s non declare, a la ligne %d\n", $6, nb_ligne);
            exit(1);
        }
        char* expected = getType($6);
        if (($3 == '$' && strcmp(expected, "INTEGER") != 0) ||
            ($3 == '%' && strcmp(expected, "FLOAT") != 0)   ||
            ($3 == '#' && strcmp(expected, "STRING") != 0)  ||
            ($3 == '&' && strcmp(expected, "CHAR") != 0))
        {
            printf("ERREUR SEMANTIQUE: Type incompatible pour %s, a la ligne %d\n", $6, nb_ligne);
            exit(1);
        
        }
}
| mc_display PARAO STRING colon idf PARAF pvg
        {
            nbQdr = nbQdr + 1;
            quadr(nbQdr, "DISPLAY", strdup($3), strdup($5), "");
            if (double_declaration($5, "") == 1) {
                printf("ERREUR SEMANTIQUE: %s non declare, a la ligne %d\n", $5, nb_ligne);
                exit(1);
            }

            char* expected = getType($5);
            char* str = $3;
            int len = strlen(str);
            char last_char = '\0';

            for (int i = len - 2; i >= 0; i--) {
                if (str[i] != ' ' && str[i] != '"') {
                    last_char = str[i];
                    break;
                }
            }
            if ((last_char == '%' && strcmp(expected, "FLOAT") != 0) ||
                (last_char == '$' && strcmp(expected, "INTEGER") != 0) ||
                (last_char == '#' && strcmp(expected, "STRING") != 0) ||
                (last_char == '&' && strcmp(expected, "CHAR") != 0)) {
                printf("ERREUR SEMANTIQUE: Type incompatible pour %s, a la ligne %d\n", $5, nb_ligne);
                exit(1);
            }
        }
;


if_condition : mc_if PARAO condition {empiler_quad(nbQdr);} PARAF colon instruction_list {tempQdr = depiler_quad(); nbQdr = nbQdr + 1; ajour_quad(tempQdr,3,nbQdr+1); quadr(nbQdr,"BR","","",""); empiler_quad(nbQdr);} else_condition
;

else_condition: mc_else colon instruction_list {tempQdr = depiler_quad();  ajour_quad(tempQdr,3,nbQdr+1);} mc_end  
                | mc_end 
;

loop : mc_for PARAO idf colon INTEGER {pop_type();} colon expression 
{
    char* qdrRet = get_colonne_qdr(nbQdr,4);
    nbQdr = nbQdr + 1; 
    char* temp = newtemp();
    quadr(nbQdr,"-",strdup($3),qdrRet,temp); 
    nbQdr = nbQdr + 1; 
    quadr(nbQdr,"BG",temp,"","");
    empiler_quad(nbQdr);
}  
PARAF instruction_list mc_end {tempQdr = depiler_quad(); ajour_quad(tempQdr,3,nbQdr+1);}
;


term : factor { $$ = $1;}
     | term mul factor {                
                nbQdr = nbQdr + 1;
                char* temp = newtemp();
                quadr(nbQdr,"*",strdup($1),strdup($3),temp); 
            }
     | term DIV factor {                
                nbQdr = nbQdr + 1;
                char* temp = newtemp();
                quadr(nbQdr,"/",strdup($1),strdup($3),temp); 
            }
;

factor : INTEGER {
            char buffer[32];
            sprintf(buffer, "%d", $1);
            $$ = strdup(buffer);

            push_type("INTEGER");
            char* expected_type = peek_type();
                if(expected_type == NULL) return 0;

                if(strcmp(expected_type, "INTEGER") != 0 && !isCTyped(expected_type)) {
                    printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                    exit(1);
                }
            }
       | FLOAT {
        char buffer[64];
        sprintf(buffer, "%f", $1);
        $$ = strdup(buffer);

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
            char buffer[4];
            sprintf(buffer, "'%c'", $1);
            $$ = strdup(buffer);
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
            $$ = $1;
            push_type("STRING");
            char* expected_type = peek_type();
            if(expected_type == NULL) return 0;

            if(strcmp(expected_type, "STRING") != 0 && !isCTyped(expected_type)) {
                printf("ERREUR SEMANTIQUE: Incompatibilité de type a la ligne %d\n", nb_ligne);
                exit(1);
            }
        }
       | idf {
            // $$ = strdup($1);
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

condition : expression dot mc_ge dot expression {char* temp = newtemp(); nbQdr = nbQdr + 1; quadr(nbQdr,"-",$1,$5,temp); nbQdr = nbQdr + 1; quadr(nbQdr,"BL",temp,"","");}
          | expression dot mc_le dot expression {char* temp = newtemp(); nbQdr = nbQdr + 1; quadr(nbQdr,"-",$1,$5,temp); nbQdr = nbQdr + 1; quadr(nbQdr,"BG",temp,"","");}
          | expression dot mc_l dot expression  {char* temp = newtemp(); nbQdr = nbQdr + 1; quadr(nbQdr,"-",$1,$5,temp); nbQdr = nbQdr + 1; quadr(nbQdr,"BGE",temp,"","");}
          | expression dot mc_di dot expression  {char* temp = newtemp(); nbQdr = nbQdr + 1; quadr(nbQdr,"-",$1,$5,temp); nbQdr = nbQdr + 1; quadr(nbQdr,"BZ",temp,"","");}
          | expression dot mc_not dot expression  {char* temp = newtemp(); nbQdr = nbQdr + 1; quadr(nbQdr,"-",$1,$5,temp); nbQdr = nbQdr + 1; quadr(nbQdr,"BG",temp,"","");}
          | expression dot "EQ" dot expression  {char* temp = newtemp(); nbQdr = nbQdr + 1; quadr(nbQdr,"-",$1,$5,temp); nbQdr = nbQdr + 1; quadr(nbQdr,"BNZ",temp,"","");}
;
;


%%

int main() {
    init_qdr();
    initialisation();
    yyparse();
    afficher_qdr();
    // afficher();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}