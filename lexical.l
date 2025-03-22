%{
#include <stdio.h>
%}


lettre         [a-zA-Z]
NATUREL        {chiffre}+
chiffre        [0-9]
IDF {lettre}({lettre}|{chiffre}|\_){0,9}
REALNEGATIF    -{NATUREL}\.{NATUREL}
REALPOSITIF    \+{NATUREL}\.{NATUREL}
commentaire %.*;


%%
DATA    {printf("MC_DATA\n");}
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



