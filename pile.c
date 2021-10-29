#include "pile.h"

#include <stdio.h>

void initPile(pile_t *pile)
{
    pile->taille = 0;
}

void empiler_i(pile_t *pile, int valeur)
{
    pile->arr[pile->taille].i = valeur;
    pile->arr[pile->taille].type = 0;
    pile->taille++;
}

void empiler_l(pile_t *pile, sequence_t *seq)
{
    pile->arr[pile->taille].l = seq;
    pile->arr[pile->taille].type = 1;
    pile->taille++;
}

void empiler_e(pile_t * pile, pile_elt_t elt)
{
    pile->arr[pile->taille] = elt;

    pile->taille++;
}

int depiler_i(pile_t *pile)
{
    pile->taille--;
    return pile->arr[pile->taille].i;
}

sequence_t *depiler_l(pile_t *pile)
{
    pile->taille--;
    return pile->arr[pile->taille].l;
}

pile_elt_t depiler_e(pile_t *pile)
{
    pile->taille--;
    return pile->arr[pile->taille];
}

int sommet_i(pile_t *pile)
{
    return pile->arr[pile->taille - 1].i; 
}

sequence_t *sommet_l(pile_t *pile)
{
    return pile->arr[pile->taille - 1].l; 
}

int getPileTaille(pile_t *pile)
{
    return pile->taille;
}

void free_element_e(pile_elt_t *elt)
{
    if(elt->type == 1){
        detruireSeq(elt->l);
    }
}

void afficherPile(pile_t *pile)
{

    for(int i = 0; i < pile->taille; i++){

        if(pile->arr[i].type == 0){
            printf("%i ", pile->arr[i].i);
        }
        else{
            printf("{");
            afficherListe(pile->arr[i].l);
            printf("}");
        }
    }
}