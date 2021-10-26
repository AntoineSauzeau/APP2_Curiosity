#pragma once

typedef struct {
    int arr[1000];
    int taille;
} pile_t;

void initPile(pile_t *pile);
void empiler(pile_t *pile, int valeur);
int depiler(pile_t *pile);

void afficherPile(pile_t *pile);

