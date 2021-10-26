#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "pile.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug)
{
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.

    char commande;
    struct cellule *pointeur = NULL;
    int type;



    //debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("xProgramme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();

    // À partir d'ici, beaucoup de choses à modifier dans la suite.
    printf("\n>>>>>>>>>>> A Faire : interprete.c/interprete() <<<<<<<<<<<<<<<<\n");
    int ret;         //utilisée pour les valeurs de retour

    pile_t pile;
    initPile(&pile);

    int op1, op2, d = 0;
    struct cellule *pointeur1 = NULL;
    struct cellule *pointeur2 = NULL;


    cellule_t *cell_s = seq->tete;
    while (cell_s != 0) { //à modifier: condition de boucle

        commande = cell_s->command;
        pointeur = cell_s->pointeur;
        type =  cell_s->type;
        cell_s = cell_s->suivant;

        if (type == 0){
        // Cas ou on tombe sur le pointeur vers un liste chainée
            empiler(&pile, &pointeur);
        }
        // Cas ou on tombe sur un char
        else if (type == 1){
            if (commande == '?'){
                pointeur1 = depiler(&pile);
                pointeur2 = depiler(&pile);
                d = depiler(&pile);
                if (d == 0){
                    seq->queue = pointeur;
                }
                else{
                    seq->queue = pointeur;
                }
            }
            else if(commande == '+' || commande == '-' || commande == '*'){
                op1 = depiler(&pile);
                op2 = depiler(&pile);
            }
            else if(commande == 'A'){
                ret = avance();
                if (ret == VICTOIRE) return VICTOIRE; 
                if (ret == RATE)     return RATE;     
            }
            else if(commande == 'G'){
                gauche();
            }
            else if(commande == 'D'){
                droite();
            }
            else if (commande == 'P'){
                int arg = depiler(&pile);
                pose(arg);
            }
            else if(commande == 'M'){
                int arg = depiler(&pile);
                mesure(arg);
            }
            else if(commande >= '1' && commande <= '9'){
                empiler(&pile, commande - 48);
            }
            else if(commande == '+'){
                empiler(&pile, op2 + op1);
            }
            else if(commande == '-'){
                empiler(&pile, op2 - op1);
            }
            else if(commande == '*'){
                empiler(&pile, op2 * op1);
            }
            else{
                eprintf("Caractère inconnu: '%c'\n", commande);
            }
        }
        //afficherPile(&pile);

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
