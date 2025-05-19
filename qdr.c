// Quad.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qdr.h"

// Matrice globale des quadruplets
char quad[MAX_QUAD][5][MAX_STR];
int qc = 0; // compteur de quadruplets
Pile branch;

void empiler_branch(int val)
{
    Cellule *nouv = malloc(sizeof(Cellule));
    nouv->val = val;
    nouv->next = branch.sommet;
    branch.sommet = nouv;
}

int depiler_branch()
{
    if (branch.sommet == NULL)
    {
        return -1;
    }
    else
    {
        int val = branch.sommet->val;
        Cellule *p = branch.sommet;
        branch.sommet = branch.sommet->next;
        free(p);
        return val;
    }
}

void init_qdr()
{
    for (int i = 0; i < MAX_QUAD; i++)
        for (int j = 0; j < 5; j++)
            quad[i][j][0] = '\0';

    branch.sommet = NULL;
    qc = 0;
}

void quadr(char label[], char oper[], char op1[], char op2[], char res[])
{
    if (qc >= MAX_QUAD)
    {
        printf("Erreur : dépassement du nombre maximum de quadruplets\n");
        return;
    }

    strcpy(quad[qc][0], label);
    strcpy(quad[qc][1], oper);
    strcpy(quad[qc][2], op1);
    strcpy(quad[qc][3], op2);
    strcpy(quad[qc][4], res);

    qc++;
}

void changer_quad(int ligne, int colonne, char val[])
{
    if (ligne >= MAX_QUAD || colonne < 0 || colonne > 4)
    {
        printf("Erreur : Indice invalide (ligne=%d, colonne=%d)\n", ligne, colonne);
        return;
    }

    if (quad[ligne][1][0] == '\0') // oper vide
    {
        printf("Erreur : Quad %d n'existe pas\n", ligne);
        return;
    }

    strcpy(quad[ligne][colonne], val);
}

void afficher_qdr()
{
    printf("\n\n********************* Les Quadruplets avec Label ***********************\n");

    for (int i = 0; i < MAX_QUAD; i++)
    {
        if (quad[i][1][0] == '\0') {
            break;
        }

        if (quad[i][0][0] != '\0')
        {
            printf("%s - ( %s , %s , %s , %s )\n", quad[i][0]
                   , quad[i][1], quad[i][2], quad[i][3], quad[i][4]);
            printf("---------------------------------------------------------------------\n");
        }
        else
        {
            printf("(%s , %s , %s , %s )\n"
                , quad[i][1], quad[i][2], quad[i][3], quad[i][4]);
            printf("---------------------------------------------------------------------\n");
        }
    }
}

