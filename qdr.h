#ifndef QUAD_H
#define QUAD_H

#define MAX_QUAD 1000
#define MAX_STR 100

// Structure de quadruplet
typedef struct qdr {
    int label;
    char oper[MAX_STR];
    char op1[MAX_STR];
    char op2[MAX_STR];
    char res[MAX_STR];
} qdr;

// Tableau global des quadruplets
extern qdr quad[MAX_QUAD];
extern int qc;

// Structure de pile pour la gestion des branches
typedef struct Cellule {
    int val;
    struct Cellule* next;
} Cellule;

typedef struct {
    Cellule* sommet;
} Pile;

extern Pile branch;

// Fonctions pour la pile des branches
void empiler_branch(int val);
int depiler_branch();

// Fonctions pour les quadruplets
void init_qdr();
void quadr(int label, char oper[], char op1[], char op2[], char res[]);
void ajour_quad(int num_quad, int colonne, int val);
void empiler_quad(int val);
int depiler_quad();
void afficher_qdr();

#endif // QUAD_H
