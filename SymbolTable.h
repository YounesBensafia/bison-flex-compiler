#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure definitions
typedef struct element {
    int state;
    char name[20];
    char code[20];
    char type[20];
    float val;
    int scope;          
    int line_number;  
    struct element* next;
} element;


typedef struct elt {
    int state;
    char name[20];
    char type[20];
    struct elt* next;
} elt;

//

#define MAX_STACK_SIZE 100
#define MAX_IDF_LENGTH 50

typedef struct {
    char stack[MAX_STACK_SIZE][MAX_IDF_LENGTH];
    int top;
} StackIDF;



// Hash table sizes
#define HASH_SIZE_IDF 1000
#define HASH_SIZE_KW 200
#define HASH_SIZE_SEP 200

// External declarations of the hash tables
extern element* tab[HASH_SIZE_IDF];
extern elt* tabm[HASH_SIZE_KW];
extern elt* tabs[HASH_SIZE_SEP];

// Function prototypes


void check_bounds(const char* vecteur_name, int index);
unsigned int hash_function(const char* str);
void update_constant_value(const char* nomConstante, float nouvelle_valeur);
void initialisation(void);
void inserer(char entite[], char code[], char type[], float val, int y, int scope, int line_number);
void rechercher(char entite[], char code[], char type[], float val, int y);
void afficher(void);
void update_type(char *entite, char *nouveau_type);
void updateTaille(const char* nomVecteur, int TailleMin, int TailleMax);
int double_declaration(char entite[], char type[]);
bool isConstant(char entite[]);
char* getType(char entite[]);
int isCTyped(char *typeIdf);
void push_type(const char* t);
char* pop_type();
char* peek_type();
#endif