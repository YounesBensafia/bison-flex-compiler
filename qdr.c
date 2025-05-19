// Quad.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUAD 1000
#define MAX_STR 100

typedef struct Cellule {
    int val;
    struct Cellule* next;
} Cellule;

typedef struct {
    Cellule* sommet;
} Pile;

typedef struct qdr {
    char label[MAX_STR];
    char oper[MAX_STR];
    char op1[MAX_STR];
    char op2[MAX_STR];
    char res[MAX_STR];
} qdr;

// Tableau de quadruplets
qdr quad[MAX_QUAD];
int qc = 0; 
Pile branch;

// ---------------- Pile ----------------

void empiler_branch(int val) {
    Cellule* nouv = malloc(sizeof(Cellule));
    if (!nouv) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    nouv->val = val;
    nouv->next = branch.sommet;
    branch.sommet = nouv;
}

int depiler_branch() {
    if (branch.sommet == NULL) {
        return -1;
    }
    int val = branch.sommet->val;
    Cellule* temp = branch.sommet;
    branch.sommet = branch.sommet->next;
    free(temp);
    return val;
}

// ---------------- Quadruplets ----------------

void init_qdr() {
    for (int i = 0; i < MAX_QUAD; i++) {
        quad[i].label[0] = '\0';
        quad[i].oper[0] = '\0';
        quad[i].op1[0] = '\0';
        quad[i].op2[0] = '\0';
        quad[i].res[0] = '\0';
    }
    branch.sommet = NULL;
    qc = 0;
}

void quadr(char label[], char oper[], char op1[], char op2[], char res[]) {
    if (qc >= MAX_QUAD) {
        printf("Erreur : dépassement du nombre maximum de quadruplets\n");
        return;
    }

    strcpy(quad[qc].label, label);
    strcpy(quad[qc].oper, oper);
    strcpy(quad[qc].op1, op1);
    strcpy(quad[qc].op2, op2);
    strcpy(quad[qc].res, res);
    qc++;
}

void ajour_quad(int num_quad, int colonne, char val[]) {
    if (num_quad < 0 || num_quad >= qc) {
        printf("Erreur : numéro de quadruplet invalide\n");
        return;
    }

    switch (colonne) {
        case 0: strcpy(quad[num_quad].label, val); break;
        case 1: strcpy(quad[num_quad].oper, val); break;
        case 2: strcpy(quad[num_quad].op1, val); break;
        case 3: strcpy(quad[num_quad].op2, val); break;
        case 4: strcpy(quad[num_quad].res, val); break;
        default:
            printf("Erreur : colonne invalide (0 à 4)\n");
    }
}

void afficher_qdr() {
    printf("\n\n********************* Les Quadruplets avec Label ***********************\n");

    for (int i = 0; i < qc; i++) {
        printf("%s - ( %s , %s , %s , %s )\n", quad[i].label, 
               quad[i].oper, quad[i].op1, quad[i].op2, quad[i].res);
        printf("---------------------------------------------------------------------\n");
}}