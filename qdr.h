// Quad.h
#ifndef QUAD_H
#define QUAD_H

#define MAX_QUAD 1000
#define MAX_STR 100

// Matrice des quadruplets : chaque ligne a 5 colonnes (label, oper, op1, op2, res)
extern char quad[MAX_QUAD][5][MAX_STR];
extern int qc; // compteur de quadruplets

// Structure de pile pour la gestion des branches
typedef struct Cellule
{
    int val;
    struct Cellule *next;
} Cellule;

typedef struct
{
    Cellule *sommet;
} Pile;

extern Pile branch;

// Fonctions pour les quadruplets
void init_qdr();
void quadr(char label[], char oper[], char op1[], char op2[], char res[]);
void changer_quad(int ligne, int colonne, char val[]);
void afficher_qdr();

// Fonctions pour la pile des branches
void empiler_branch(int val);
int depiler_branch();

#endif // QUAD_H
