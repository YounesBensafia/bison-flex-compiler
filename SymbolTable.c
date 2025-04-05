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

element* tab[HASH_SIZE_IDF];
elt* tabm[HASH_SIZE_KW];
elt* tabs[HASH_SIZE_SEP];


void initialisation(void) {
    int i;
    for (i = 0; i < HASH_SIZE_IDF; i++)
    tab[i] = NULL;
    for (i = 0; i < HASH_SIZE_KW; i++)
    tabm[i] = NULL;
    for (i = 0; i < HASH_SIZE_SEP; i++)
    tabs[i] = NULL;
}

unsigned int hash_function(const char* str) {
    unsigned int hash = 0;      
    while (*str) {
        hash = (hash * 31) + (*str++);
    }
    return hash;
}

void inserer(char entite[], char code[], char type[], float val, int y) {
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
                    inserer(entite, code, type, val, 0);
            }
            break;
        case 1: 
            index %= HASH_SIZE_KW;
            {
                elt* curr = tabm[index];
                while (curr != NULL && strcmp(entite, curr->name) != 0)
                    curr = curr->next;
                if (curr == NULL)
                    inserer(entite, code, type, val, 1);
            }
            break;
        case 2:
        index %= HASH_SIZE_SEP;
        {
            elt* curr = tabs[index];
            while (curr != NULL && strcmp(entite, curr->name) != 0)
                curr = curr->next;
            
            if (curr == NULL) {
                inserer(entite, code, type, val, 2);
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
                    inserer(entite, code, type, val, 0);
                else
                    printf("entité existe déjà\n");
            }
            break;
    }
}


void afficher(void) {
    int i;

    // Table des symboles IDF
    printf(YELLOW "/***************Table des symboles IDF*************/\n" RESET);
    printf("____________________________________________________________________\n");
    printf("\t| " GREEN "Nom_Entite" RESET " | " GREEN "Code_Entite" RESET " | " GREEN "Type_Entite" RESET " | " GREEN "Val_Entite" RESET "\n");
    printf("____________________________________________________________________\n");
    for (i = 0; i < HASH_SIZE_IDF; i++) {
        element* curr = tab[i];
        while (curr != NULL) {
            if (curr->state == 1) {
                printf("\t| %s%-10s" RESET " | %-15s | %-12s | %-12f\n",
                       CYAN, curr->name, curr->code, curr->type, curr->val);
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

