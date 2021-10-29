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
}

void ajouterTeteSeq(sequence_t* seq, cellule_t *cell){

    if(seq->tete == 0){
        seq->tete = cell;
        cell->suivant = 0;
    }
    else{
        cell->suivant = seq->tete;
        seq->tete = cell;
    }
}


cellule_t* nouvelleCellule (void)
{
    cellule_t *n_cell = 0;

    n_cell = malloc(sizeof(cellule_t));
    if(n_cell == 0){
        perror("Erreur : ");
    }

    return n_cell;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}

int conversion (char *texte, sequence_t *seq)
{
    if(seq->tete != 0){
        detruireSeq(seq);
    }

    sequence_t *r_seq = NULL;

    for (unsigned int i = 0; i < strlen(texte); i++){

        if(texte[i] == ' ' || texte[i] == '\n'){
            continue;
        }

        if(texte[i] == '{'){
            r_seq = malloc(sizeof(sequence_t));
            r_seq->tete = 0;

            i += conversion(texte + i + 1, r_seq) + 1;

            cellule_t *cell = nouvelleCellule();
            cell->command_l = r_seq;
            cell->type = 1;

            ajouterFinSeq(seq, cell);
        }
        else if(texte[i] == '}'){
            return i;
        }
        else{
            cellule_t *cell = nouvelleCellule();
            cell->command_c = texte[i];
            cell->type = 0;

            ajouterFinSeq(seq, cell);
        }
    }

    return strlen(texte);
}




void afficherListe(sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    /* À compléter */

    if(seq->tete == 0){
        return;
    }

    //printf("\n");

    cellule_t *cell_s = seq->tete;
    while(cell_s != 0){
        if(cell_s->type == 0){
            printf("%c ", cell_s->command_c);
        }
        else{
            printf("{");
            afficherListe(cell_s->command_l);
            printf("}");
        }

        cell_s = cell_s->suivant;
    }

    //printf("\n");

}

void detruireSeq(sequence_t *seq)
{

    if(seq->tete == 0){
        return;
    }

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

sequence_t *clonerList(sequence_t *seq)
{
    sequence_t *n_list = NULL;

    n_list = malloc(sizeof(sequence_t));
    if(n_list == NULL){
        perror("Erreur : ");
    }

    cellule_t *cell_s = NULL;
    cell_s = seq->tete;
    while(cell_s != 0){

        cellule_t *n_cell = NULL;
        n_cell = malloc(sizeof(cellule_t));
        if(n_cell == NULL){
            perror("Erreur : ");
        }

        n_cell->type = cell_s->type;

        if(cell_s->type == 0){
            n_cell->command_c = cell_s->command_c;
        }
        else{
            n_cell->command_l = cell_s->command_l;
        }

        ajouterFinSeq(n_list, n_cell);
        cell_s = cell_s->suivant;
    }

    return n_list;
}
