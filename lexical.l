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
END     {printf("MC_END\n");}
CODE    {printf("MC_CODE\n");}

VECTOR  {printf("MC_VECTOR\n");}
CONST   {printf("MC_CONST\n");}
INTEGER {printf("MC_INTEGER\n");}
FLOAT   {printf("MC_FLOAT\n");}
CHAR    {printf("MC_CHAR\n");}
STRING  {printf("MC_STRING\n");}

IF      {printf("MC_IF\n");}
ELSE    {printf("MC_ELSE\n");}
FOR     {printf("MC_FOR\n");}

AND     {printf("MC_AND\n");}
OR      {printf("MC_OR\n");}
NOT     {printf("MC_NOT\n");}

GE      {printf("mc_GE\n");}
L       {printf("mc_L\n");}

LE      {printf("mc_LE\n");}
DI      {printf("mc_DI\n");}

";"     {printf("PVGR\n");}
"+"     {printf("PLUS\n");}
"*"     {printf("MULT\n");}
"-"     {printf("MINUS\n");}
"/"     {printf("DIV\n");}
"="     {printf("EQ\n");}
"("     {printf("PARAO\n");}
")"     {printf("PARAF\n");}
":"     {printf("COLON\n");}
"."     {printf("DOT\n");}



