%{
#include <stdio.h>
#include "SymbolTable.h"
#include "parser.tab.h"
extern int nb_ligne;
extern int nb_colonne;
%}


lettre         [a-zA-Z]
NATUREL        {chiffre}+
INTEGER        [\-]?{NATUREL}
FLOAT          [\-]?{NATUREL}\.{NATUREL}
chiffre        [0-9]
char           \'.\'
string         \".+\"   
commentaire %.*;
IDF {lettre}({lettre}|{chiffre}|\_){0,9}


%%
DATA    {nb_colonne = nb_colonne + yyleng; printf("MC_DATA\n"); rechercher(yytext, "MC_DATA", "Mot clé", 0, 1); return mc_data;}
END     {nb_colonne = nb_colonne + yyleng; printf("MC_END\n"); rechercher(yytext, "MC_END", "Mot clé", 0, 1); return mc_end;}
CODE    {nb_colonne = nb_colonne + yyleng; printf("MC_CODE\n"); rechercher(yytext, "MC_CODE", "Mot clé", 0, 1); return mc_code;}

VECTOR  {nb_colonne = nb_colonne + yyleng; printf("MC_VECTOR\n"); rechercher(yytext, "MC_VECTOR", "Mot clé", 0, 1); return MC_VECTOR;}
CONST   {nb_colonne = nb_colonne + yyleng; printf("MC_CONST\n"); rechercher(yytext, "MC_CONST", "Mot clé", 0, 1); return mc_const;}
INTEGER {nb_colonne = nb_colonne + yyleng; printf("MC_INTEGER\n"); rechercher(yytext, "MC_INTEGER", "Mot clé", 0, 1); return mc_integer;}
FLOAT   {nb_colonne = nb_colonne + yyleng; printf("MC_FLOAT\n"); rechercher(yytext, "MC_FLOAT", "Mot clé", 0, 1); return mc_float;}
CHAR    {nb_colonne = nb_colonne + yyleng; printf("MC_CHAR\n"); rechercher(yytext, "MC_CHAR", "Mot clé", 0, 1); return mc_char;}
STRING  {nb_colonne = nb_colonne + yyleng; printf("MC_STRING\n"); rechercher(yytext, "MC_STRING", "Mot clé", 0, 1); return mc_string;}

READ    {nb_colonne = nb_colonne + yyleng; printf("MC_READ\n"); rechercher(yytext, "MC_READ", "Mot clé", 0, 1); return mc_read;}
DISPLAY {nb_colonne = nb_colonne + yyleng; printf("MC_DISPLAY\n"); rechercher(yytext, "MC_DISPLAY", "Mot clé", 0, 1); return mc_display;}

IF      {nb_colonne = nb_colonne + yyleng; printf("MC_IF\n"); rechercher(yytext, "MC_IF", "Mot clé", 0, 1); return mc_if;}
ELSE    {nb_colonne = nb_colonne + yyleng; printf("MC_ELSE\n"); rechercher(yytext, "MC_ELSE", "Mot clé", 0, 1); return mc_else;}
FOR     {nb_colonne = nb_colonne + yyleng; printf("MC_FOR\n"); rechercher(yytext, "MC_FOR", "Mot clé", 0, 1); return mc_for;}

AND     {nb_colonne = nb_colonne + yyleng; printf("MC_AND\n"); rechercher(yytext, "MC_IF", "Mot clé", 0, 1); return mc_if;}
OR      {nb_colonne = nb_colonne + yyleng; printf("MC_OR\n"); rechercher(yytext, "MC_OR", "Mot clé", 0, 1); return mc_or;}
NOT     {nb_colonne = nb_colonne + yyleng; printf("MC_NOT\n"); rechercher(yytext, "MC_NOT", "Mot clé", 0, 1); return mc_not;}

GE      {nb_colonne = nb_colonne + yyleng; printf("mc_GE\n"); rechercher(yytext, "MC_GE", "Mot clé", 0, 1); return mc_ge;}
L       {nb_colonne = nb_colonne + yyleng; printf("mc_L\n"); rechercher(yytext, "MC_L", "Mot clé", 0, 1); return mc_l;}

LE      {nb_colonne = nb_colonne + yyleng; printf("mc_LE\n"); rechercher(yytext, "MC_LE", "Mot clé", 0, 1); return mc_le;}
DI      {nb_colonne = nb_colonne + yyleng; printf("mc_DI\n"); rechercher(yytext, "MC_DI", "Mot clé", 0, 1); return mc_di;}

";"     {nb_colonne = nb_colonne + yyleng; printf("PVGR\n"); rechercher(yytext, "PVG", "Séparateur", 0, 2); return pvg;}
"+"     {nb_colonne = nb_colonne + yyleng; printf("PLUS\n"); rechercher(yytext, "SUM", "Séparateur", 0, 2); return sum;}
"*"     {nb_colonne = nb_colonne + yyleng; printf("MULT\n"); rechercher(yytext, "MUL", "Séparateur", 0, 2); return mul;}
"-"     {nb_colonne = nb_colonne + yyleng; printf("MINUS\n"); rechercher(yytext, "MINUS", "Séparateur", 0, 2); return minus;}
"/"     {nb_colonne = nb_colonne + yyleng; printf("DIV\n"); rechercher(yytext, "DIV", "Séparateur", 0, 2); return DIV;}
"="     {nb_colonne = nb_colonne + yyleng; printf("EQ\n"); rechercher(yytext, "EQ", "Séparateur", 0, 2); return eq;} 
"("     {nb_colonne = nb_colonne + yyleng; printf("PARAO\n"); rechercher(yytext, "PARAO", "Séparateur", 0, 2); return PARAO;}
")"     {nb_colonne = nb_colonne + yyleng; printf("PARAF\n"); rechercher(yytext, "PARAF", "Séparateur", 0, 2); return PARAF;}
"@"     {nb_colonne = nb_colonne + yyleng; printf("Arobase\n"); rechercher(yytext, "Arobase", "Séparateur", 0, 2); return arobase;}
":"     {nb_colonne = nb_colonne + yyleng; printf("COLON\n"); rechercher(yytext, "COLON", "Séparateur", 0, 2); return colon;}
"."     {nb_colonne = nb_colonne + yyleng; printf("DOT\n"); rechercher(yytext, "DOT", "Séparateur", 0, 2); return dot;}
","     {nb_colonne = nb_colonne + yyleng; printf("VIRGULE\n"); rechercher(yytext, "VIRGULE", "Séparateur", 0, 2); return virgule;}
"["     {nb_colonne = nb_colonne + yyleng; printf("OPENED\n"); rechercher(yytext, "VIRGULE", "Séparateur", 0, 2); return batata;}
"]"     {nb_colonne = nb_colonne + yyleng; printf("CLOSED\n"); rechercher(yytext, "VIRGULE", "Séparateur", 0, 2); return bata;}

{IDF} {
    if (yyleng > 8)
    {
        printf("ERREUR LEXICALE a la ligne %d, et la colonne %d sur l'entite %s (IDF trop long)\n",nb_ligne,nb_colonne,yytext);
    }
    yylval.string = strdup(yytext); 
    rechercher(yytext, "IDF", "", 0, 0);
    return idf;
}

{INTEGER} {
    if (atoi(yytext) < -32768 || atoi(yytext) > 32767) {
        printf("ERREUR LEXICALE a la ligne %d, et la colonne %d sur l'entite %s (INTEGER non valide)\n",nb_ligne,nb_colonne,yytext);
    }
    
    yylval.entier=atoi(yytext); rechercher(yytext, "INTEGER", "", atof(yytext), 0); return INTEGER;
}

{FLOAT} {
    yylval.real=atof(yytext); rechercher(yytext, "FLOAT", "", atof(yytext), 0); return FLOAT;
    if (yylval.real < -3.4e38 || yylval.real > 3.4e38) {
        printf("ERREUR LEXICALE à la ligne %d, colonne %d sur l'entité %s (real non valide)\n", nb_ligne, nb_colonne, yytext);
    }
}

{char} { 
    yylval.caracter = yytext[1]; 
    rechercher(yytext, "CHAR", "", 0, 0); 
    return CHAR; 
}

{commentaire} 

{string} { 
    yylval.string=strdup(yytext); rechercher(yytext, "STRING", "", 0, 0); return STRING; 
}

[ \t] nb_colonne = nb_colonne + yyleng;

\n {nb_colonne=1; nb_ligne++;}


