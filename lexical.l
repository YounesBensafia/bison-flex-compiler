%{
#include <stdio.h>
#include "compiler.tab.h"
#include "ts.h"
%}


lettre         [a-zA-Z]
NATUREL        {chiffre}+
chiffre        [0-9]
IDF {lettre}({lettre}|{chiffre}|\_){0,9}
REALNEGATIF    \-{NATUREL}\.{NATUREL}
REALPOSITIF    \+{NATUREL}\.{NATUREL}
commantaire %.*;


%%
DATA    {rechercher(yytext, "MC_DATA", "Mot clé", 0, 1); return mc_data;}
END     {rechercher(yytext, "MC_END", "Mot clé", 0, 1); return mc_end;}
CODE    {rechercher(yytext, "MC_CODE", "Mot clé", 0, 1); return mc_code;}
INTEGER {rechercher(yytext, "MC_INTEGER", "Mot clé", 0, 1); return mc_integer;}
FLOAT   {rechercher(yytext, "MC_FLOAT", "Mot clé", 0, 1); return mc_float;}
CHAR    {rechercher(yytext, "MC_CHAR", "Mot clé", 0, 1); return mc_char;}
STRING  {rechercher(yytext, "MC_STRING", "Mot clé", 0, 1); return mc_string;}
do      {rechercher(yytext, "MC_DO", "Mot clé", 0, 1); return mc_do;}
if      {rechercher(yytext, "MC_IF", "Mot clé", 0, 1); return mc_if;}
else    {rechercher(yytext, "MC_ELSE", "Mot clé", 0, 1); return mc_else;}
while   {rechercher(yytext, "MC_WHILE", "Mot clé", 0, 1); return mc_while;}
";"     {rechercher(yytext, "PVGR", "Séparateur", 0, 2); return pvg;}
GT      {rechercher(yytext, "GT", "Séparateur", 0, 2); return gt;}
LT      {rechercher(yytext, "LT", "Séparateur", 0, 2); return ls;}
"+"     {rechercher(yytext, "PLUS", "Séparateur", 0, 2); return plus;}
"*"     {rechercher(yytext, "MULT", "Séparateur", 0, 2); return produit;}
"-"     {rechercher(yytext, "MINUS", "Séparateur", 0, 2); return minus;}
"/"     {rechercher(yytext, "DIV", "Séparateur", 0, 2); return divi;}
"="     {rechercher(yytext, "EQ", "Séparateur", 0, 2); return eq;}
"("     {rechercher(yytext, "PARAO", "Séparateur", 0, 2); return paraO;}
")"     {rechercher(yytext, "PARAF", "Séparateur", 0, 2); return paraF;}


{commantaire} 

{IDF}         {
    yylval.string = strdup(yytext); 
    rechercher(yytext, "IDF", "Identifiant", 0, 0);
    return idf;
} 

{REALNEGATIF}  {
    yylval.real = atof(yytext); 
    rechercher(yytext, "CONST", "Réel négatif", atof(yytext), 0);
    return REELN;
}

{REALPOSITIF}  {
    yylval.real = atof(yytext); 
    rechercher(yytext, "CONST", "Réel positif", atof(yytext), 0);
    return REELP;
}

%%

