#pragma once

#include "listes.h"

typedef struct {
    int i;
    sequence_t *l;
    int type;
}   pile_elt_t;

typedef struct {
    int taille;
    pile_elt_t arr[5000];
} pile_t;

void initPile(pile_t *pile);

void empiler_i(pile_t *pile, int valeur);
void empiler_l(pile_t *pile, sequence_t *seq);
void empiler_e(pile_t * pile, pile_elt_t elt);

int depiler_i(pile_t *pile);
sequence_t *depiler_l(pile_t *pile);
pile_elt_t depiler_e(pile_t *pile);

int sommet_i(pile_t *pile);
sequence_t *sommet_l(pile_t *pile);

void afficherPile(pile_t *pile);

