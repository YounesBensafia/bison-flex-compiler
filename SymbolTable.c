#include <stdio.h>
#define RESET      "\033[0m"  // Reset to default color
#define RED        "\033[31m" // Red
#define GREEN      "\033[32m" // Green
#define YELLOW     "\033[33m" // Yellow
#define BLUE       "\033[34m" // Blue
#define MAGENTA    "\033[35m" // Magenta
#define CYAN       "\033[36m" // Cyan
#define WHITE      "\033[37m" // White
#include "SymbolTable.h"
#include <stdbool.h>

element* tab[HASH_SIZE_IDF];
elt* tabm[HASH_SIZE_KW];
elt* tabs[HASH_SIZE_SEP];
static int color_counter = 0;  // Compteur pour alterner les couleurs
#define STACK_SIZE 100
char* type_stack[STACK_SIZE];
int stack_top = -1;


void initialisation(void) {
    int i;
    for (i = 0; i < HASH_SIZE_IDF; i++)
    tab[i] = NULL;
    for (i = 0; i < HASH_SIZE_KW; i++)
    tabm[i] = NULL;
    for (i = 0; i < HASH_SIZE_SEP; i++)
    tabs[i] = NULL;
}

const char* get_color() {
    switch (color_counter % 3) {
        case 0: return RED;   // 0 -> Rouge
        case 1: return BLUE;  // 1 -> Bleu
        case 2: return GREEN; // 2 -> Vert
        default: return RESET;
    }
}

unsigned int hash_function(const char* str) {
    unsigned int hash = 0;      
    while (*str) {
        hash = (hash * 31) + (*str++);
    }
    return hash;
}

void check_bounds(const char* vecteur_name, int index) {
    unsigned int idx = hash_function(vecteur_name) % HASH_SIZE_IDF;
    element* curr = tab[idx];
    int taille_min = 0, taille_max = 0;

    // Recherche du vecteur dans la table des symboles
    while (curr != NULL) {
        if (strcmp(curr->name, vecteur_name) == 0) {
            taille_min = curr->scope;
            taille_max = curr->line_number;
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Erreur : Vecteur '%s' non trouvé dans la table des symboles.\n", vecteur_name);
        exit(EXIT_FAILURE);
    }

    if (index < taille_min || index > taille_max) {
        printf("Erreur : Dépassement de bornes pour le vecteur '%s'. Index = %d, Bornes = [%d, %d]\n",
               vecteur_name, index, taille_min, taille_max);
        exit(EXIT_FAILURE);
    }
}

void inserer(char entite[], char code[], char type[], float val, int y, int scope, int line_number)
 {
    unsigned int index = hash_function(entite);
    switch (y) {
        case 0:
            index %= HASH_SIZE_IDF;
            element* new_elem = (element*)malloc(sizeof(element));
            new_elem->state = 1;
            strcpy(new_elem->name, entite);
            strcpy(new_elem->code, code);
            strcpy(new_elem->type, type);
            new_elem->val = val;
            new_elem->next = tab[index];
            new_elem->scope = scope;
            new_elem->line_number = line_number;

            tab[index] = new_elem;
            break;
            case 1: 
            index %= HASH_SIZE_KW;
            elt* new_elt_m = (elt*)malloc(sizeof(elt));
            new_elt_m->state = 1;
            strcpy(new_elt_m->name, entite);
            strcpy(new_elt_m->type, code);
            new_elt_m->next = tabm[index];
            tabm[index] = new_elt_m;
            break;
            case 2: 
            index %= HASH_SIZE_SEP;
            elt* new_elt_s = (elt*)malloc(sizeof(elt));
            new_elt_s->state = 1;
            strcpy(new_elt_s->name, entite);
            strcpy(new_elt_s->type, code);
            new_elt_s->next = tabs[index];
            tabs[index] = new_elt_s;
            break;
        }
    }

void rechercher(char entite[], char code[], char type[], float val, int y) {
        unsigned int index = hash_function(entite);
        switch (y) {
            case 0:
            index %= HASH_SIZE_IDF;
            {
                element* curr = tab[index];
                while (curr != NULL && strcmp(entite, curr->name) != 0)
                curr = curr->next;
                if (curr == NULL)
                inserer(entite, code, type, val, 0, 0, 0);
            }
            break;
            case 1: 
            index %= HASH_SIZE_KW;
            {
                elt* curr = tabm[index];
                while (curr != NULL && strcmp(entite, curr->name) != 0)
                curr = curr->next;
                if (curr == NULL)
                inserer(entite, code, type, val, 1, 0, 0);
            }
            break;
            case 2:
            index %= HASH_SIZE_SEP;
            {
                elt* curr = tabs[index];
                while (curr != NULL && strcmp(entite, curr->name) != 0)
                curr = curr->next;
                
                if (curr == NULL) {
                    inserer(entite, code, type, val, 2, 0, 0);
                }
        }
        break;
        
        case 3: // Same as case 0
        index %= HASH_SIZE_IDF;
        {
            element* curr = tab[index];
            while (curr != NULL && strcmp(entite, curr->name) != 0)
            curr = curr->next;
            if (curr == NULL)
            inserer(entite, code, type, val, 0, 0, 0);
            else
            printf("entité existe déjà\n");
        }
        break;
    }
}

void afficher(void) {
    int i;
    const char* color = get_color();
    
    // Table des symboles IDF
    printf(YELLOW "/***************Table des symboles IDF*************/\n" RESET);
    printf("____________________________________________________________________\n");
    printf("\t| " GREEN "Nom_Entite" RESET " | " GREEN "Code_Entite" RESET " | " GREEN "Type_Entite" RESET " | " GREEN "Val_Entite" RESET " | " GREEN "TailleMIN" RESET " | " GREEN "TailleMAX" RESET "\n");
    printf("___________________________________________________________________________________\n");
    printf("____________________________________________________________________\n");
    for (i = 0; i < HASH_SIZE_IDF; i++) {
        element* curr = tab[i];
        while (curr != NULL) {
            if (curr->state == 1) {
                if (strncmp(curr->type, "C_", 2) == 0) {
                   printf("\t| %s%-10s" RESET " | %-15s | " GREEN "%-12s" RESET " | %-12f | %-5d | %-5d\n",
                    CYAN, curr->name, curr->code, curr->type, curr->val, curr->scope, curr->line_number);

                } else if (strcmp(curr->type, "INTEGER") == 0) {
                    printf("\t| %s%-10s" RESET " | %-15s | " GREEN "%-12s" RESET " | %-12f | %-5d | %-5d\n",
                        CYAN, curr->name, curr->code, curr->type, curr->val, curr->scope, curr->line_number);

                } else if (strcmp(curr->type, "FLOAT") == 0) {
                    printf("\t| %s%-10s" RESET " | %-15s | " GREEN "%-12s" RESET " | %-12f | %-5d | %-5d\n",
                        CYAN, curr->name, curr->code, curr->type, curr->val, curr->scope, curr->line_number);

                } else {
                    printf("\t| %s%-10s" RESET " | %-15s | " GREEN "%-12s" RESET " | %-12f | %-5d | %-5d\n",
                        CYAN, curr->name, curr->code, curr->type, curr->val, curr->scope, curr->line_number);
                }
                
        
            }
            curr = curr->next;
        }
    }

    // Table des symboles mots clés
    printf(YELLOW "\n/***************Table des symboles mots clés*************/\n" RESET);
    printf("_____________________________________\n");
    printf("\t| " GREEN "NomEntite" RESET " | " GREEN "CodeEntite" RESET " |\n");
    printf("_____________________________________\n");
    for (i = 0; i < HASH_SIZE_KW; i++) {
        elt* curr = tabm[i];
        while (curr != NULL) {
            if (curr->state == 1) {
                printf("\t| %s%-10s" RESET " | %-12s |\n", CYAN, curr->name, curr->type);
            }
            curr = curr->next;
        }
    }

    // Table des symboles séparateurs
    printf(YELLOW "\n/***************Table des symboles séparateurs*************/\n" RESET);
    printf("_____________________________________\n");
    printf("\t| " GREEN "NomEntite" RESET " | " GREEN "CodeEntite" RESET " |\n");
    printf("_____________________________________\n");
    for (i = 0; i < HASH_SIZE_SEP; i++) {
        elt* curr = tabs[i];
        while (curr != NULL) {
            if (curr->state == 1) {
                printf("\t| %s%-10s" RESET " | %-12s |\n", CYAN, curr->name, curr->type);
            }
            curr = curr->next;
        }
    }
}

int double_declaration (char entite[], char type[]){
    unsigned int indice = hash_function(entite) % HASH_SIZE_IDF;
    element* curr = tab[indice];

    
    while (curr != NULL && strcmp(curr->name, entite) != 0) curr = curr->next;

    if (curr == NULL) {
        return -1;
    }


    if (strcmp(curr->type, "") == 0) return 1;
    else
    { 
        if (curr->type != type)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
}


void update_constant_value(const char* nomConstante, float nouvelle_valeur) {
    unsigned int index = hash_function(nomConstante) % HASH_SIZE_IDF;
    element* curr = tab[index];

    while (curr != NULL) {
        if (strcmp(curr->name, nomConstante) == 0) {
            if (strncmp(curr->type, "C_", 2) == 0) {
                curr->val = nouvelle_valeur;
                return;
            } else {
                printf("Erreur : %s n'est pas une constante.\n", nomConstante);
                return;
            }
        }
        curr = curr->next;
    }
    printf("Constante %s non trouvée dans la table des symboles.\n", nomConstante);
}


void updateTaille(const char* nomVecteur, int TailleMin, int TailleMax) {
    unsigned int index = hash_function(nomVecteur) % HASH_SIZE_IDF;
    element* curr = tab[index];

    while (curr != NULL) {
        if (strcmp(curr->name, nomVecteur) == 0) {
            curr->scope = TailleMin;
            curr->line_number = TailleMax;
            return;
        }
        curr = curr->next;
    }
    printf("Vecteur %s non trouvé dans la table des symboles.\n", nomVecteur);
}


void update_type(char *entite, char *nouveau_type) {
    unsigned int index = hash_function(entite) % HASH_SIZE_IDF;
    element *curr = tab[index];
    
    while (curr != NULL) {
        if (strcmp(curr->name, entite) == 0) {
            strcpy(curr->type, nouveau_type);
            return;
        }
        curr = curr->next;
    }
}

bool isConstant(char *entite)
{   unsigned int indice = hash_function(entite) % HASH_SIZE_IDF;
    element* curr = tab[indice];

    
    while (curr != NULL && strcmp(curr->name, entite) != 0) curr = curr->next;
    if (curr == NULL) {
        return false;
    }
    if (strcmp(curr->type, "C_INTEGER") == 0 || strcmp(curr->type, "C_STRING") == 0 || strcmp(curr->type, "C_CHAR") == 0 || strcmp(curr->type, "C_FLOAT") == 0)
    {
        return true;
    }
    return false;
}

char* getType(char entite[])
{
    unsigned int index = hash_function(entite) % HASH_SIZE_IDF;
    element *curr = tab[index];
    
    while (curr != NULL) {
        if (strcmp(curr->name, entite) == 0) return curr->type;
    }

    return "";        
}

int isCTyped(char *typeIdf) {
    if (typeIdf == NULL) return 0;
    return strcmp(typeIdf, "C_INTEGER") == 0 ||
           strcmp(typeIdf, "C_CHAR") == 0 ||
           strcmp(typeIdf, "C_STRING") == 0 ||
           strcmp(typeIdf, "C_FLOAT") == 0;
}

void push_type(const char* t) {
    if (stack_top < STACK_SIZE - 1) {
        type_stack[++stack_top] = strdup(t);
    } else {
        fprintf(stderr, "Type stack overflow\n");
        exit(1);
    }
}

char* pop_type() {
    if (stack_top >= 0) {
        return type_stack[stack_top--];
    } else {
        fprintf(stderr, "Type stack underflow\n");
        exit(1);
    }
}

char* peek_type() {
    if (stack_top >= 0) {
        return type_stack[stack_top];
    }
    return NULL;
}
