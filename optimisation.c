#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qdr.h"
#include <ctype.h>

#define MAX_QUAD 1000
#define MAX_STR 100

qdr quad[MAX_QUAD];
int qc = 0;

// Check if a string is a number
int is_number(const char *s) {
    if (*s == '\0') return 0;
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i]) && s[i] != '-') return 0;
    }
    return 1;
}

// Evaluate constant expressions
int evaluate(const char *a, const char *op, const char *b, char *res_out) {
    int x = atoi(a), y = atoi(b), result;
    if (strcmp(op, "+") == 0) result = x + y;
    else if (strcmp(op, "-") == 0) result = x - y;
    else if (strcmp(op, "*") == 0) result = x * y;
    else if (strcmp(op, "/") == 0 && y != 0) result = x / y;
    else return 0;
    sprintf(res_out, "%d", result);
    return 1;
}

// Check if a variable is used later in the quadruplets
int is_used_later(const char *var, int start) {
    for (int i = start; i < qc; i++) {
        if (strcmp(quad[i].op1, var) == 0 || strcmp(quad[i].op2, var) == 0)
            return 1;
    }
    return 0;
}

// Optimization logic
void optimiser() {
    for (int i = 0; i < qc; i++) {
        qdr *q = &quad[i];

        // Constant folding
        if (is_number(q->op1) && is_number(q->op2)) {
            if (strcmp(q->oper, "+") == 0 || strcmp(q->oper, "-") == 0 ||
                strcmp(q->oper, "*") == 0 || strcmp(q->oper, "/") == 0) {
                char folded[20];
                if (evaluate(q->op1, q->oper, q->op2, folded)) {
                    strcpy(q->oper, "=");
                    strcpy(q->op1, folded);
                    q->op2[0] = '\0';
                }
            }
        }

        // Algebraic simplification: x * 2 → x + x
        if (strcmp(q->oper, "*") == 0) {
            if (strcmp(q->op2, "2") == 0) {
                strcpy(q->oper, "+");
                strcpy(q->op2, q->op1);
            } else if (strcmp(q->op1, "2") == 0) {
                strcpy(q->oper, "+");
                strcpy(q->op1, q->op2);
            }
        }

        // Copy propagation
        if (strcmp(q->oper, "=") == 0) {
            for (int j = i + 1; j < qc; j++) {
                if (strcmp(quad[j].op1, q->res) == 0)
                    strcpy(quad[j].op1, q->op1);
                if (strcmp(quad[j].op2, q->res) == 0)
                    strcpy(quad[j].op2, q->op1);
            }
        }

        // Dead code elimination
        if (strcmp(q->oper, "=") == 0 && strncmp(q->res, "t", 1) == 0) {
            if (!is_used_later(q->res, i + 1)) {
                q->oper[0] = '\0';  // mark as deleted
            }
        }
    }
}

// Read quadruples from quad.txt
void lire_quadruplets(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur ouverture quad.txt");
        exit(EXIT_FAILURE);
    }

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) < 3) continue; // skip short/empty lines

        qdr *q = &quad[qc++];
        char *token;

        token = strtok(line, ",");
        strcpy(q->label, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(q->oper, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(q->op1, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(q->op2, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(q->res, token ? token : "");

        // Trim spaces from all fields
        char *fields[] = {q->label, q->oper, q->op1, q->op2, q->res};
        for (int i = 0; i < 5; i++) {
            while (isspace((unsigned char)*fields[i]))
                memmove(fields[i], fields[i] + 1, strlen(fields[i]));
            char *end = fields[i] + strlen(fields[i]) - 1;
            while (end > fields[i] && isspace((unsigned char)*end))
                *end-- = '\0';
        }
    }

    fclose(f);
}


// Display final quadruplets
void afficher_qdr() {
    printf("\n\n********************* Les Quadruplets avec Label ***********************\n");

    for (int i = 0; i < qc; i++) {
        // Skip deleted
        if (quad[i].oper[0] == '\0') continue;

        printf("%s - ( %s , %s , %s , %s )\n",
               quad[i].label,
               quad[i].oper,
               quad[i].op1,
               quad[i].op2,
               quad[i].res);
        printf("--------------------------------------\n");
    }
}

int main() {
    lire_quadruplets("quad.txt");
    afficher_qdr();
    printf("%d \n ",qc);
    
    optimiser();
    printf("%d \n ",qc);

    afficher_qdr();
    return 0;
}
