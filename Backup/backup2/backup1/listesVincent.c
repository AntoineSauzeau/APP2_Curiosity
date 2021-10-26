#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void)
{
    cellule_t* cell = malloc(sizeof(cellule_t));
    return cell;
}


void detruireCellule (cellule_t* cel)
{
    /* À compléter (utiliser free) */
    printf("\n>>>>>>>>>>> A Faire : liste.c/detruireCellule() <<<<<<<<<<<<<<<<\n");
}

void ajouter_tete(sequence_t *seq, char r){
    cellule_t *cell = nouvelleCellule();
    cell->command = r;
    cell->suivant = NULL;
    
    if (seq->tete == NULL){
        seq->tete = cell;
    }
    else{
        cell->suivant = seq->tete;
        seq->tete = cell->suivant;
    }   
}

void conversion (char *texte, sequence_t *seq){

    for(unsigned int i = strlen(texte)-1; i >= 0; i=i-1){
        ajouter_tete(seq,texte[i]);
    }
}


void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *cell_s = nouvelleCellule();
    cell_s = seq->tete;
    while (cell_s->suivant != NULL){
        printf("%c ", cell_s->command);
        cell_s = cell_s->suivant;
    }
}

