#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUAD 1000

typedef struct Qdr
{
  char oper[100];
  char op1[100];
  char op2[100];
  char res[100];
} Qdr;

typedef struct Cellule
{
  int val;
  struct Cellule *next;
} Cellule;

typedef struct
{
  Cellule *sommet;
} Pile;

Qdr *quad[MAX_QUAD];
Pile branch;
extern int qc;

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
  {
    quad[i] = NULL;
  }

  branch.sommet = NULL;
}

void quadr(char oper[], char op1[], char op2[], char res[])
{
  Qdr *nouv = malloc(sizeof(Qdr));
  strcpy(nouv->oper, oper);
  strcpy(nouv->op1, op1);
  strcpy(nouv->op2, op2);
  strcpy(nouv->res, res);

  quad[qc] = nouv;
  qc++;
}

void changer_quad(int ligne, int colone, char val[])
{
  if (ligne >= MAX_QUAD || quad[ligne] == NULL)
  {
    printf("Erreur: Quad %d n'existe pas\n", ligne);
    return;
  }

  Qdr *q = quad[ligne];

  switch (colone)
  {
  case 0:
    strcpy(q->oper, val);
    break;
  case 1:
    strcpy(q->op1, val);
    break;
  case 2:
    strcpy(q->op2, val);
    break;
  case 3:
    strcpy(q->res, val);
    break;
  default:
    printf("Erreur: Colonne %d n'existe pas\n", colone);
    break;
  }
}

void afficher_qdr()
{
  printf("\n\n********************* Les Quadruplets ***********************\n");

  for (int i = 0; i < MAX_QUAD; i++)
  {
    Qdr *q = quad[i];

    if (q == NULL)
    {
      printf("\n %d - \n", i);
      break;
    }

    printf("\n %d - ( %s , %s , %s , %s )", i, q->oper, q->op1, q->op2, q->res);
    printf("\n--------------------------------------------------------\n");
  }
}
