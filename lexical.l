%{
#include <stdio.h>
#include "SymbolTable.h"
#include "parser.tab.h"

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
DATA    {printf("MC_DATA\n"); rechercher(yytext, "MC_DATA", "Mot clé", 0, 1); return mc_data;}
END     {printf("MC_END\n"); rechercher(yytext, "MC_END", "Mot clé", 0, 1); return mc_end;}
CODE    {printf("MC_CODE\n"); rechercher(yytext, "MC_CODE", "Mot clé", 0, 1); return mc_code;}

VECTOR  {printf("MC_VECTOR\n"); rechercher(yytext, "MC_VECTOR", "Mot clé", 0, 1); return MC_VECTOR;}
CONST   {printf("MC_CONST\n"); rechercher(yytext, "MC_CONST", "Mot clé", 0, 1); return mc_const;}
INTEGER {printf("MC_INTEGER\n"); rechercher(yytext, "MC_INTEGER", "Mot clé", 0, 1); return mc_integer;}
FLOAT   {printf("MC_FLOAT\n"); rechercher(yytext, "MC_FLOAT", "Mot clé", 0, 1); return mc_float;}
CHAR    {printf("MC_CHAR\n"); rechercher(yytext, "MC_CHAR", "Mot clé", 0, 1); return mc_char;}
STRING  {printf("MC_STRING\n"); rechercher(yytext, "MC_STRING", "Mot clé", 0, 1); return mc_string;}

IF      {printf("MC_IF\n"); rechercher(yytext, "MC_IF", "Mot clé", 0, 1); return mc_if;}
ELSE    {printf("MC_ELSE\n"); rechercher(yytext, "MC_ELSE", "Mot clé", 0, 1); return mc_else;}
FOR     {printf("MC_FOR\n"); rechercher(yytext, "MC_FOR", "Mot clé", 0, 1); return mc_for;}

AND     {printf("MC_AND\n"); rechercher(yytext, "MC_IF", "Mot clé", 0, 1); return mc_if;}
OR      {printf("MC_OR\n"); rechercher(yytext, "MC_OR", "Mot clé", 0, 1); return mc_or;}
NOT     {printf("MC_NOT\n"); rechercher(yytext, "MC_NOT", "Mot clé", 0, 1); return mc_not;}

GE      {printf("mc_GE\n"); rechercher(yytext, "MC_GE", "Mot clé", 0, 1); return mc_ge;}
L       {printf("mc_L\n"); rechercher(yytext, "MC_L", "Mot clé", 0, 1); return mc_l;}

LE      {printf("mc_LE\n"); rechercher(yytext, "MC_LE", "Mot clé", 0, 1); return mc_le;}
DI      {printf("mc_DI\n"); rechercher(yytext, "MC_DI", "Mot clé", 0, 1); return mc_di;}

";"     {printf("PVGR\n"); rechercher(yytext, "PVG", "Séparateur", 0, 1); return pvg;}
"+"     {printf("PLUS\n"); rechercher(yytext, "SUM", "Séparateur", 0, 1); return sum;}
"*"     {printf("MULT\n"); rechercher(yytext, "MUL", "Séparateur", 0, 1); return mul;}
"-"     {printf("MINUS\n"); rechercher(yytext, "MINUS", "Séparateur", 0, 1); return minus;}
"/"     {printf("DIV\n"); rechercher(yytext, "DIV", "Séparateur", 0, 1); return DIV;}
"="     {printf("EQ\n"); rechercher(yytext, "EQ", "Séparateur", 0, 1); return eq;} 
"("     {printf("PARAO\n"); rechercher(yytext, "PARAO", "Séparateur", 0, 1); return PARAO;}
")"     {printf("PARAF\n"); rechercher(yytext, "PARAF", "Séparateur", 0, 1); return PARAF;}
":"     {printf("COLON\n"); rechercher(yytext, "COLON", "Séparateur", 0, 1); return colon;}
"."     {printf("DOT\n"); rechercher(yytext, "DOT", "Séparateur", 0, 1); return dot;}
","     {printf("VIRGULE\n"); rechercher(yytext, "VIRGULE", "Séparateur", 0, 1); return virgule;}
"["     {printf("OPENED\n"); rechercher(yytext, "VIRGULE", "Séparateur", 0, 1); return batata;}
"]"     {printf("CLOSED\n"); rechercher(yytext, "VIRGULE", "Séparateur", 0, 1); return bata;}

{IDF} {
    yylval.string = strdup(yytext); 
    rechercher(yytext, "IDF", "Identifiant", 0, 0);
    return idf;
}

{INTEGER} {
    yylval.entier=atoi(yytext); rechercher(yytext, "INTEGER", "INTEGER", atof(yytext), 0); return INTEGER;
}

{FLOAT} {
    yylval.entier=atof(yytext); rechercher(yytext, "FLOAT", "FLOAT", atof(yytext), 0); return FLOAT;
}

{char} { 
    yylval.caracter = yytext[1]; 
    rechercher(yytext, "CHAR", "CHAR", 0, 0); 
    return CHAR; 
}

{commentaire} 

{string} { 
    yylval.string=strdup(yytext); rechercher(yytext, "STRING", "STRING", 0, 0); return STRING; 
}


