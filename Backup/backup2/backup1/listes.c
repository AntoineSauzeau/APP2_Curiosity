#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
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


void ajouterFinSeq(sequence_t* seq, cellule_t *cell);
void ajouterTeteSeq(sequence_t* seq, cellule_t *cell);



bool silent_mode = false;

void ajouterFinSeq(sequence_t* seq, cellule_t *cell){

    if(seq->tete == 0){
        ajouterTeteSeq(seq, cell);
        return;
    }

    cellule_t *cell_s = seq->tete;
    while(cell_s->suivant != 0){
        cell_s = cell_s->suivant;
    }

    cell->suivant = 0;
    cell_s->suivant = cell;

    seq->queue = cell;
}

void ajouterTeteSeq(sequence_t* seq, cellule_t *cell){

    if(seq->tete == 0){
        seq->tete = cell;
        seq->queue = cell;
        cell->suivant = 0;
    }
    else{
        cell->suivant = seq->tete;
        seq->tete = cell;
    }
}


cellule_t* nouvelleCellule (void)
{
    cellule_t *n_cell = malloc(sizeof(cellule_t));

    return n_cell;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}


void conversion (char *texte, sequence_t *seq)
{
    printf("\n>>>>>>>>>>> A Faire : liste.c/conversion() <<<<<<<<<<<<<<<<\n");
    if(seq->tete != 0){
        detruireSeq(seq);
    }

    for (unsigned int i = 0; i < strlen(texte); i++){

        if (texte[i] == '{'){
            i++;

            sequence_t seq_aux;
            seq_aux.tete = 0;
            seq_aux.queue = 0;

            while (texte[i] != '}'){
                cellule_t *cell = nouvelleCellule();
                cell->command = texte[i];
                cell->type = 1;
                ajouterFinSeq(&seq_aux, cell);
                seq_aux.queue = cell;
                i++;
            }
            i++;
            cellule_t *cell = nouvelleCellule();
            cell->pointeur = seq_aux.tete;
            cell->type = 0;
            ajouterFinSeq(seq, cell);
            seq->queue = cell;
        }
        else{
            cellule_t *cell = nouvelleCellule();
            cell->command = texte[i];
            cell->type = 1;
            ajouterFinSeq(seq, cell);
            seq->queue = cell;
        }
    }
    afficher(seq);
}






void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    /* À compléter */
    printf("\n>>>>>>>>>>> A Faire : liste.c/afficher() <<<<<<<<<<<<<<<<\n");

    if(seq->tete == 0){
        return;
    }
    printf("\n");
    cellule_t *cell_s = seq->tete;
    while(cell_s->suivant != 0){
        printf("%c ", cell_s->command);
        cell_s = cell_s->suivant;
    }
    printf("\n\n");

}

void detruireSeq(sequence_t *seq)
{
    cellule_t *cell_s = seq->tete;
    cellule_t *cell_p = 0;

    while(cell_s->suivant != 0){
        cell_p = cell_s;
        cell_s = cell_s->suivant;

        if(cell_p != 0){
            detruireCellule(cell_p);
        }
    }

    seq->tete = 0;
}

