#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUAD 1000
#define MAX_STR 100

// Matrice des quadruplets avec LABEL : [quadruplet][colonne]
char quad[MAX_QUAD][5][MAX_STR]; // 5 colonnes : label, oper, op1, op2, res

typedef struct Cellule
{
  int val;
  struct Cellule *next;
} Cellule;

typedef struct
{
  Cellule *sommet;
} Pile;

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
    for (int j = 0; j < 5; j++)
      quad[i][j][0] = '\0'; // initialise chaque case à chaîne vide

  branch.sommet = NULL;
}

// Nouvelle version avec LABEL
void quadr(char label[], char oper[], char op1[], char op2[], char res[])
{
  if (qc >= MAX_QUAD)
  {
    printf("Erreur : dépassement du nombre maximum de quadruplets\n");
    return;
  }

  strcpy(quad[qc][0], label); // label
  strcpy(quad[qc][1], oper);  // oper
  strcpy(quad[qc][2], op1);   // op1
  strcpy(quad[qc][3], op2);   // op2
  strcpy(quad[qc][4], res);   // res

  qc++;
}

void changer_quad(int ligne, int colonne, char val[])
{
  if (ligne >= MAX_QUAD || colonne < 0 || colonne > 4)
  {
    printf("Erreur : Indice invalide (ligne=%d, colonne=%d)\n", ligne, colonne);
    return;
  }

  if (quad[ligne][1][0] == '\0') // colonne 1 = oper, on teste sa validité
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
    if (quad[i][1][0] == '\0') // colonne oper vide = fin
    {
      printf("\n %d - \n", i);
      break;
    }

    printf("\n %d - ( %s , %s , %s , %s , %s )",
           i, quad[i][0], quad[i][1], quad[i][2], quad[i][3], quad[i][4]);
    printf("\n---------------------------------------------------------------------\n");
  }
}
