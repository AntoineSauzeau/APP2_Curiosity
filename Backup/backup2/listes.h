#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales 
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne 
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif

extern bool silent_mode;




struct cellule {
    /* vous pouvez rajouter d'autres champs ici */
    int type;
    union {
        char command_c;
        struct sequence *command_l;
    };
    struct cellule *suivant;
};

struct sequence {
    struct cellule *tete;
};

typedef struct sequence sequence_t;
typedef struct cellule cellule_t;

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);

void detruireSeq(sequence_t *seq);

void conversion (char *texte, sequence_t *seq);

void afficherListe (sequence_t* seq);


#endif
