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
    cellule_t *n_cell = malloc(sizeof(cellule_t));

    return n_cell;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}


void conversion (char *texte, sequence_t *seq)
{
    if(seq->tete != 0){
        detruireSeq(seq);
    }

    bool bracket = false;
    sequence_t *r_seq = NULL;

    for (unsigned int i = 0; i < strlen(texte); i++){

        if(texte[i] == ' ' || texte[i] == '\n'){
            continue;
        }

        if(texte[i] == '{'){
            bracket = true;
            r_seq = malloc(sizeof(sequence_t));
            r_seq->tete = 0;
        }
        else if(texte[i] == '}'){
            bracket = false;

            cellule_t *cell = nouvelleCellule();
            cell->command_l = r_seq;
            cell->type = 1;

            ajouterFinSeq(seq, cell);
        }
        else if(bracket == true){
            cellule_t *cell = nouvelleCellule();
            cell->command_c = texte[i];
            cell->type = 0;

            ajouterFinSeq(r_seq, cell);
        }
        else{
            cellule_t *cell = nouvelleCellule();
            cell->command_c = texte[i];
            cell->type = 0;

            ajouterFinSeq(seq, cell);
        }
    }

    afficherListe(seq);
}

/*void conversion (char *texte, sequence_t *seq)
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

            conversion(texte + i + 1, r_seq);

            cellule_t *cell = nouvelleCellule();
            cell->command_l = r_seq;
            cell->type = 1;

            ajouterFinSeq(seq, cell);
        }
        else if(texte[i] == '}'){
            return;
        }
        else{
            cellule_t *cell = nouvelleCellule();
            cell->command_c = texte[i];
            cell->type = 0;

            ajouterFinSeq(seq, cell);
        }

        afficherListe(seq);
    }
}*/




void afficherListe(sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    /* À compléter */

    if(seq->tete == 0){
        return;
    }

    cellule_t *cell_s = seq->tete;
    while(cell_s->suivant != 0){
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

