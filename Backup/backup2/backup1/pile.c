#include "pile.h"


#include <stdio.h>

void initPile(pile_t *pile)
{
    pile->taille = 0;
}

void empiler(pile_t *pile, int valeur)
{
    pile->arr[pile->taille] = valeur;
    pile->taille++;
}

int depiler(pile_t *pile)
{
    pile->taille--;
    return pile->arr[pile->taille];
}

void afficherPile(pile_t *pile){
    for(int i = 0; i < pile->taille; i++){
        printf("%i ", pile->arr[i]);
    }
}