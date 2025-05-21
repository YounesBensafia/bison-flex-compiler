// Quad.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
        // N'affiche pas les quadruplets vides (opération ET résultat vides)
        if (quad[i].oper[0] == '\0' && quad[i].res[0] == '\0')
            continue;

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
    printf("\033[38;5;63m╠═══════╩════════════════╩════════════════════╩════════════════════╩════════════╣\033[0m\n");
    printf("\033[38;5;63m╚═══════════════════════════════════════════════════════════════════════════════╝\033[0m\n");
}


void afficher_qdr_apres_opti() {
    printf("\n\033[1;38;5;240m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\033[0m\n");
    printf("\033[1;38;5;240m┃\033[0m \033[1;38;5;39m                         🧠 TABLE DES QUADRUPLETS - VM MODE                         \033[0m \033[1;38;5;240m┃\033[0m\n");
    printf("\033[1;38;5;240m┣━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┓\033[0m\n");
    printf("\033[1;38;5;240m┃\033[0m \033[1;38;5;250m%-3s \033[1;38;5;240m┃\033[0m \033[1;38;5;44m%-12s \033[1;38;5;240m┃\033[0m \033[1;38;5;51m%-16s \033[1;38;5;240m┃\033[0m \033[1;38;5;51m%-16s \033[1;38;5;240m┃\033[0m \033[1;38;5;227m%-14s \033[1;38;5;240m┃\033[0m\n",
           "ID", "OPÉRATION", "ARGUMENT 1", "ARGUMENT 2", "RÉSULTAT");
    printf("\033[1;38;5;240m┣━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━┫\033[0m\n");

    // Couleurs
    const char *color_default = "\033[0m";
    const char *color_id = "\033[1;38;5;250m";         // gris clair
    const char *color_op_std = "\033[1;38;5;45m";      // bleu clair
    const char *color_op_jmp = "\033[1;38;5;34m";      // vert
    const char *color_op_math = "\033[1;38;5;198m";    // magenta
    const char *color_op_io = "\033[1;38;5;208m";      // orange
    const char *color_arg = "\033[1;38;5;51m";         // cyan
    const char *color_res = "\033[1;38;5;227m";        // jaune

    int row = 0;
    for (int i = 0; i < qc; i++) {
        if (quad[i].oper[0] == '\0' && quad[i].res[0] == '\0')
            continue;

        const char *op_color = color_op_std;
        if (strstr("BGE BG BLE BL BE BNE BR BRF JMP", quad[i].oper)) {
            op_color = color_op_jmp;
        } else if (strstr("ADD SUB MUL DIV MOD POW", quad[i].oper)) {
            op_color = color_op_math;
        } else if (strstr("READ WRITE PRINT SCAN", quad[i].oper)) {
            op_color = color_op_io;
        }

        const char *bg = (row % 2 == 0) ? "" : "\033[48;5;236m";
        row++;

        printf("\033[1;38;5;240m┃\033[0m %s%s%-3d \033[0m\033[1;38;5;240m┃\033[0m %s%s%-12s\033[0m \033[1;38;5;240m┃\033[0m %s%s%-16s\033[0m \033[1;38;5;240m┃\033[0m %s%s%-16s\033[0m \033[1;38;5;240m┃\033[0m %s%s%-14s\033[0m \033[1;38;5;240m┃\033[0m\n",
               bg, color_id, quad[i].label,
               bg, op_color, quad[i].oper,
               bg, color_arg, quad[i].op1[0] ? quad[i].op1 : "—",
               bg, color_arg, quad[i].op2[0] ? quad[i].op2 : "—",
               bg, color_res, quad[i].res[0] ? quad[i].res : "—"
        );
    }

    // Footer
    printf("\033[1;38;5;240m┗━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┛\033[0m\n");
}


void generer_code_objet() {
    printf("\n\033[1;38;5;45m// ===== Code Objet Généré =====\033[0m\n");

    // En-tête de tableau
    printf("\n\033[1;38;5;240m┏━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\033[0m\n");
    printf("\033[1;38;5;240m┃ ID  ┃ INSTRUCTION                                                           ┃\033[0m\n");
    printf("\033[1;38;5;240m┣━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\033[0m\n");

    int ligne = 0;
    for (int i = 0; i < qc; i++) {
        const char *op = quad[i].oper;
        const char *a1 = quad[i].op1;
        const char *a2 = quad[i].op2;
        const char *res = quad[i].res;

        if (op[0] == '\0') continue;

        // Génération de l'instruction
        char buffer[256] = "";
        if (strcmp(op, "+") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | ADD %s | STORE %s", a1, a2, res);
        } else if (strcmp(op, "-") == 0) {
            if (res[0] != '\0')
                snprintf(buffer, sizeof buffer, "LOAD %s | SUB %s | STORE %s", a1, a2, res);
            else
                snprintf(buffer, sizeof buffer, "LOAD %s | SUB %s", a1, a2);
        } else if (strcmp(op, "*") == 0 || strcmp(op, "MUL") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | MUL %s | STORE %s", a1, a2, res);
        } else if (strcmp(op, "/") == 0 || strcmp(op, "DIV") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | DIV %s | STORE %s", a1, a2, res);
        } else if (strcmp(op, "=") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | STORE %s", a1, res);
        } else if (strcmp(op, "BG") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | JG %s", a1, a2);
        } else if (strcmp(op, "BL") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | JL %s", a1, a2);
        } else if (strcmp(op, "BGE") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | JGE %s", a1, a2);
        } else if (strcmp(op, "BLE") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | JLE %s", a1, a2);
        } else if (strcmp(op, "BE") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | JE %s", a1, a2);
        } else if (strcmp(op, "BNE") == 0) {
            snprintf(buffer, sizeof buffer, "LOAD %s | JNE %s", a1, a2);
        } else if (strcmp(op, "BR") == 0) {
            snprintf(buffer, sizeof buffer, "JMP %s", a2);
        } else if (strcmp(op, "READ") == 0) {
            snprintf(buffer, sizeof buffer, "IN %s", a1);
        } else if (strcmp(op, "DISPLAY") == 0 || strcmp(op, "PRINT") == 0) {
            snprintf(buffer, sizeof buffer, "OUT %s", a1);
        } else if (strcmp(op, "ADEC") == 0) {
            snprintf(buffer, sizeof buffer, "DECL %s", a1);
        } else if (strcmp(op, "BOUNDS") == 0) {
            snprintf(buffer, sizeof buffer, "BOUNDS %s %s", a1, a2);
        } else {
            snprintf(buffer, sizeof buffer, "// ⚠️ Instruction inconnue : %s", op);
        }

        // Alternance de couleurs
        const char *bg = (ligne++ % 2) ? "\033[48;5;236m" : "";

        // Affichage de la ligne
        printf("\033[1;38;5;240m┃\033[0m %s\033[1;38;5;250m%-3d\033[0m \033[1;38;5;240m┃\033[0m %s%-70s\033[0m \033[1;38;5;240m┃\033[0m\n",
               bg, i, bg, buffer);
    }

    // Pied de tableau
    printf("\033[1;38;5;240m┗━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n");
    printf("\033[1;38;5;45m// =============================\033[0m\n");
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

void eliminer_sous_expressions_communes() {
    for (int i = 0; i < qc; i++) {
        for (int j = 0; j < i; j++) {
            // Comparaison des opérateurs et opérandes
            if (strcmp(quad[i].oper, quad[j].oper) == 0 &&
                strcmp(quad[i].op1, quad[j].op1) == 0 &&
                strcmp(quad[i].op2, quad[j].op2) == 0) {
                printf("🔁 Sous-expression commune détectée entre %d et %d : (%s %s %s)\n", j, i, quad[i].oper, quad[i].op1, quad[i].op2);
                // Remplacement par une affectation
                strcpy(quad[i].oper, "=");
                strcpy(quad[i].op1, quad[j].res);
                quad[i].op2[0] = '\0';
                // garder la même destination
                break;
            }
        }
    }
}


int est_utilisee(char* var, int debut) {
    for (int i = debut; i < qc; i++) {
        if (strcmp(quad[i].op1, var) == 0 || strcmp(quad[i].op2, var) == 0 || strcmp(quad[i].res, var) == 0) {
            return 1;
        }
    }
    return 0;
}

void eliminer_instructions_inutiles() {
    for (int i = 0; i < qc; i++) {
        if (quad[i].res[0] == '\0') continue;
        if (!est_utilisee(quad[i].res, i + 1) ) {
            printf("🗑️ Instruction inutile détectée à %d : %s ← %s %s %s\n", i, quad[i].res, quad[i].oper, quad[i].op1, quad[i].op2);
            quad[i].oper[0] = '\0';
            quad[i].op1[0] = '\0';
            quad[i].op2[0] = '\0';
            quad[i].res[0] = '\0';
        }
    }
}

void eliminer_variables_induction() {
    for (int i = 0; i < qc - 1; i++) {
        if (strcmp(quad[i].oper, "+") == 0 && strcmp(quad[i].res, quad[i].op1) == 0) {
            // Ex : I = I + 1
            char var_induction[MAX_STR];
            char const1[MAX_STR];
            strcpy(var_induction, quad[i].op1);
            strcpy(const1, quad[i].op2);

            for (int j = i + 1; j < qc; j++) {
                if (strcmp(quad[j].oper, "+") == 0 &&
                    strcmp(quad[j].op1, var_induction) == 0) {
                    // Ex : J = I + 6 → devient J = (I+1)+6 = I+7
                    printf("🔁 Variable d'induction optimisée entre %d et %d\n", i, j);

                    // Fusion des constantes
                    int c1 = atoi(const1);
                    int c2 = atoi(quad[j].op2);
                    int fusion = c1 + c2;
                    
                    // Modifier quad j
                    snprintf(quad[j].op2, MAX_STR, "%d", fusion);

                    // Supprimer l'instruction d'induction si plus utilisée après cette modification
                    bool encore_utilisee = false;
                    bool est_reaffectee = false;
                    
                    for (int k = j + 1; k < qc; k++) {
                        // Vérifier si la variable est utilisée comme opérande
                        if ((strcmp(quad[k].op1, var_induction) == 0) || 
                            (strcmp(quad[k].op2, var_induction) == 0)) {
                            encore_utilisee = true;
                            break;
                        }
                        
                        // Vérifier si la variable est réaffectée
                        if (strcmp(quad[k].res, var_induction) == 0) {
                            est_reaffectee = true;
                            break;
                        }
                    }
                    
                    // Ne supprimer que si la variable n'est plus utilisée ou si elle est réaffectée
                    if (!encore_utilisee || est_reaffectee) {
                        quad[i].oper[0] = '\0';
                        quad[i].op1[0] = '\0';
                        quad[i].op2[0] = '\0';
                        quad[i].res[0] = '\0';
                    }
                }
            }
        }
    }
}

int est_constant(char* var) {
    // Hypothèse simplifiée : si ce n’est pas une variable temporaire (T...)
    return !(var[0] == 'T' || var[0] == 't');
}

int est_utilise_apres(int i_debut, char *nom) {
    for (int i = i_debut + 1; i < qc; i++) {
        if (
            strcmp(quad[i].op1, nom) == 0 ||
            strcmp(quad[i].op2, nom) == 0
        ) {
            return 1;
        }
    }
    return 0;
}


void eliminer_affectations_inutiles() {
    for (int i = 0; i < qc; i++) {
        char *res = quad[i].res;
        if (strcmp(quad[i].oper, "=") == 0 && quad[i].op2[0] == '\0' && strcmp(quad[i].op1, res) == 0) {
            

            if (!est_utilise_apres(i, res)) {
            quad[i].oper[0] = '\0';
            quad[i].op1[0] = '\0';
            quad[i].op2[0] = '\0';
            quad[i].res[0] = '\0';
            }
        }
    }
}

void eliminer_operations_neutres() {
    for (int i = 0; i < qc; i++) {
        char *op = quad[i].oper;
        char *a1 = quad[i].op1;
        char *a2 = quad[i].op2;
        char *res = quad[i].res;

        if (strcmp(op, "+") == 0) {
            if (strcmp(a2, "0") == 0 || strcmp(a1, "0") == 0) {
                char *val = (strcmp(a1, "0") == 0) ? a2 : a1;

                if (!est_utilise_apres(i, res)) {
                    quad[i].oper[0] = '\0'; // inutile => on supprime
                } else {
                    strcpy(op, "=");
                    strcpy(a1, val);
                    quad[i].op2[0] = '\0';
                }
            }
        } else if (strcmp(op, "-") == 0 && strcmp(a2, "0") == 0) {
            if (!est_utilise_apres(i, res)) {
                quad[i].oper[0] = '\0';
            } else {
                strcpy(op, "=");
                quad[i].op2[0] = '\0';
            }
        } else if ((strcmp(op, "*") == 0 || strcmp(op, "MUL") == 0) &&
                   (strcmp(a1, "1") == 0 || strcmp(a2, "1") == 0)) {
            char *val = (strcmp(a1, "1") == 0) ? a2 : a1;

            if (!est_utilise_apres(i, res)) {
                quad[i].oper[0] = '\0';
            } else {
                strcpy(op, "=");
                strcpy(a1, val);
                quad[i].op2[0] = '\0';
            }
        } else if ((strcmp(op, "/") == 0 || strcmp(op, "DIV") == 0) &&
                    strcmp(a2, "1") == 0) {
            if (!est_utilise_apres(i, res)) {
                quad[i].oper[0] = '\0';
            } else {
                strcpy(op, "=");
                quad[i].op2[0] = '\0';
            }
        }
    }
}







// Hypothèse : boucle délimitée par labels "DEBLOOP" et "ENDLOOP"
void optimiser_boucles() {
    int deb = -1, fin = -1;
    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "LBL") == 0 && strcmp(quad[i].res, "DEBLOOP") == 0) {
            deb = i;
        } else if (strcmp(quad[i].oper, "LBL") == 0 && strcmp(quad[i].res, "ENDLOOP") == 0) {
            fin = i;
        }
    }

    if (deb == -1 || fin == -1) return;

    for (int i = deb + 1; i < fin; i++) {
        if ((strcmp(quad[i].oper, "ADD") == 0 || strcmp(quad[i].oper, "MUL") == 0) &&
            est_constant(quad[i].op1) && est_constant(quad[i].op2)) {
            printf("📤 Invariant de boucle détecté à %d (%s %s %s)\n", i, quad[i].oper, quad[i].op1, quad[i].op2);
        }
    }
}


void nettoyer_quadruplets_triviaux() {
    int j = 0;
    for (int i = 0; i < qc; i++) {
        // Si ligne vide, on saute
        if (quad[i].oper[0] == '\0') continue;

        // Ignorer les identités triviales comme i = i
        if (strcmp(quad[i].oper, "=") == 0 &&
            strcmp(quad[i].op1, quad[i].res) == 0) {
            printf("⚠️ Affectation triviale supprimée à %d : %s = %s\n", i, quad[i].res, quad[i].op1);
            continue;
        }

        // Sinon, on garde
        if (i != j) {
            quad[j] = quad[i];
        }
        j++;
    }
    qc = j;
}

void eliminer_copies_expressives() {
    for (int i = 0; i < qc - 1; i++) {
        // Ex : t2 = a + b
        if ((strcmp(quad[i].oper, "+") == 0 || strcmp(quad[i].oper, "-") == 0 ||
             strcmp(quad[i].oper, "*") == 0 || strcmp(quad[i].oper, "/") == 0)) {
            
            char temp_result[MAX_STR];
            strcpy(temp_result, quad[i].res);

            for (int j = i + 1; j < qc; j++) {
                // Ex : t3 = t2
                if (strcmp(quad[j].oper, "=") == 0 && strcmp(quad[j].op1, temp_result) == 0) {
                    printf("🔁 Copie supprimée entre lignes %d et %d (%s remplacé)\n", i, j, temp_result);

                    // Modifier ligne j : remplacer t2 par a + b directement
                    strcpy(quad[j].oper, quad[i].oper);
                    strcpy(quad[j].op1, quad[i].op1);
                    strcpy(quad[j].op2, quad[i].op2);

                    // Résultat reste le même (quad[j].res)

                    // Supprimer ligne i (ancienne op)
                    quad[i].oper[0] = '\0';
                    quad[i].op1[0] = '\0';
                    quad[i].op2[0] = '\0';
                    quad[i].res[0] = '\0';

                    break;
                }
            }
        }
    }
}




void optimiser_quadruplets() {
    printf("\n🚀 Démarrage de l'optimisation...\n");
    eliminer_instructions_inutiles();
    eliminer_affectations_inutiles();
    eliminer_copies_expressives();
    eliminer_operations_neutres();
    eliminer_sous_expressions_communes();
    eliminer_variables_induction();
    optimiser_boucles();
    nettoyer_quadruplets_triviaux();
    printf("✅ Optimisation terminée.\n");
}


