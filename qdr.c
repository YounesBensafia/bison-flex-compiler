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
    int label;
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
        quad[i].label = -1;
        quad[i].oper[0] = '\0';
        quad[i].op1[0] = '\0';
        quad[i].op2[0] = '\0';
        quad[i].res[0] = '\0';
    }
    branch.sommet = NULL;
    qc = 0;
}

void quadr(int label, char oper[], char op1[], char op2[], char res[]) {
    if (qc >= MAX_QUAD) {
        printf("Erreur : dépassement du nombre maximum de quadruplets\n");
        return;
    }

    quad[qc].label = label;
    strcpy(quad[qc].oper, oper);
    strcpy(quad[qc].op1, op1);
    strcpy(quad[qc].op2, op2);
    strcpy(quad[qc].res, res);
    qc++;
}

void ajour_quad(int num_quad, int colonne, int val) {
    if (num_quad < 0 || num_quad >= qc) {
        printf("Erreur : numéro de quadruplet invalide\n");
        return;
    }

    switch (colonne) {
        // case 0: strcpy(quad[num_quad].label, val); break;
        case 1: snprintf(quad[num_quad].oper, MAX_STR, "%d", val); break;
        case 2: snprintf(quad[num_quad].op1, MAX_STR, "%d", val); break;
        case 3: snprintf(quad[num_quad].op2, MAX_STR, "%d", val); break;
        case 4: snprintf(quad[num_quad].res, MAX_STR, "%d", val); break;
        default:
            printf("Erreur : colonne invalide (0 à 4)\n");
    }
}

void afficher_qdr() {
    // Header with gradient effect
    printf("\n\033[38;5;63m╔═══════════════════════════════════════════════════════════════════════════════╗\033[0m\n");
    printf("\033[38;5;63m║\033[0m\033[1;38;5;51m                     ⚙️  TABLE DES QUADRUPLETS - VM MODE ⚙️                    \033[0m\033[38;5;63m║\033[0m\n");
    printf("\033[38;5;63m╠═══════╦════════════════╦════════════════════╦════════════════════╦═══════════════╣\033[0m\n");
    printf("\033[38;5;63m║\033[0m \033[1;38;5;227m%-5s \033[38;5;63m║\033[0m \033[1;38;5;39m%-14s \033[38;5;63m║\033[0m \033[1;38;5;51m%-16s \033[38;5;63m║\033[0m \033[1;38;5;51m%-16s \033[38;5;63m║\033[0m \033[1;38;5;227m%-13s \033[38;5;63m║\033[0m\n", 
           "ID", "OPÉRATION", "ARGUMENT 1", "ARGUMENT 2", "RÉSULTAT");
    printf("\033[38;5;63m╠═══════╬════════════════╬════════════════════╬════════════════════╬═══════════════╣\033[0m\n");

    // Define color palette
    const char *color_default = "\033[0m";
    const char *color_id = "\033[1;38;5;251m";         // bright white
    const char *color_op_std = "\033[1;38;5;39m";      // bright blue
    const char *color_op_jmp = "\033[1;38;5;83m";      // bright green
    const char *color_op_math = "\033[1;38;5;213m";    // pink
    const char *color_op_io = "\033[1;38;5;208m";      // orange
    const char *color_arg = "\033[1;38;5;51m";         // cyan
    const char *color_res = "\033[1;38;5;227m";        // yellow
    const char *color_borders = "\033[38;5;63m";       // softer blue for borders

    // Row counter for alternating background
    int row = 0;
    
    for (int i = 0; i < qc; i++) {
        // Determine operation type for color coding
        const char *op_color = color_op_std;
        
        // Jump and branch operations
        if (strstr("BGE BG BLE BL BE BNE BR BRF JMP", quad[i].oper)) {
            op_color = color_op_jmp;
        }
        // Math operations
        else if (strstr("ADD SUB MUL DIV MOD POW", quad[i].oper)) {
            op_color = color_op_math;
        }
        // I/O operations
        else if (strstr("READ WRITE PRINT SCAN", quad[i].oper)) {
            op_color = color_op_io;
        }
        
        // Subtle alternating row background for better readability
        const char *bg = (row % 2 == 0) ? "" : "\033[48;5;236m";
        row++;
        
        // Print the row with appropriate colors and alignments
        printf("\033[38;5;63m║\033[0m %s%s%-5d \033[0m\033[38;5;63m║\033[0m %s%s%-14s\033[0m \033[38;5;63m║\033[0m %s%s%-16s\033[0m \033[38;5;63m║\033[0m %s%s%-16s\033[0m \033[38;5;63m║\033[0m %s%s%-13s\033[0m \033[38;5;63m║\033[0m\n",
               bg, color_id, quad[i].label,
               bg, op_color, quad[i].oper,
               bg, color_arg, quad[i].op1[0] ? quad[i].op1 : "—",
               bg, color_arg, quad[i].op2[0] ? quad[i].op2 : "—",
               bg, color_res, quad[i].res[0] ? quad[i].res : "—"
        );
    }

    // Footer with statistics
    printf("\033[38;5;63m╠═══════╩════════════════╩════════════════════╩════════════════════╩═══════════════╣\033[0m\n");
    printf("\033[38;5;63m║\033[0m \033[1;38;5;251mStat: \033[1;38;5;227m%-3d\033[0m \033[1;38;5;251mquadruplets générés                                             \033[38;5;63m║\033[0m\n", qc);
    printf("\033[38;5;63m╚═══════════════════════════════════════════════════════════════════════════════╝\033[0m\n");
}

typedef struct {
    Cellule* sommet;
} PileQuad;

PileQuad pileQuad;

void empiler_quad(int val) {
    Cellule* nouv = malloc(sizeof(Cellule));
    if (!nouv) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    nouv->val = val;
    nouv->next = pileQuad.sommet;
    pileQuad.sommet = nouv;
}

int depiler_quad() {
    if (pileQuad.sommet == NULL) {
        return -1;
    }
    int val = pileQuad.sommet->val;
    Cellule* temp = pileQuad.sommet;
    pileQuad.sommet = pileQuad.sommet->next;
    free(temp);
    return val;
}
// Retourne un pointeur vers la chaîne correspondant à la colonne demandée pour une ligne donnée
// colonne: 1=oper, 2=op1, 3=op2, 4=res
char* get_colonne_qdr(int ligne, int colonne) {
    if (ligne < 0 || ligne >= qc) {
        return NULL;
    }
    switch (colonne) {
        case 1: return quad[ligne].oper;
        case 2: return quad[ligne].op1;
        case 3: return quad[ligne].op2;
        case 4: return quad[ligne].res;
        default: return NULL;
    }
}