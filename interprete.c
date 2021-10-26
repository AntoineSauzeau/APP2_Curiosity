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
//Daft Punk//

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

    char commande_c;
    sequence_t *commande_l;



    //debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("XProgramme:");
    afficherListe(seq);
    printf ("\n");
    if (debug) stop();

    // À partir d'ici, beaucoup de choses à modifier dans la suite.
    printf("\n>>>>>>>>>>> A Faire : interprete.c/interprete() <<<<<<<<<<<<<<<<\n");
    int ret;         //utilisée pour les valeurs de retour
    
    int n = 0;
    sequence_t *cmd = 0;

    pile_t pile;
    initPile(&pile);

    int op1, op2 = 0;

    cellule_t *cell_s = seq->tete;
    while (cell_s != 0) { //à modifier: condition de boucle

        if(cell_s->type == 0){
            commande_c = cell_s->command_c;
            commande_l = 0;
        }
        else if(cell_s->type == 1){
            commande_c = 0;
            commande_l = cell_s->command_l;
        }

        printf("Commande : %c\n", commande_c);

        if(commande_c == '+' || commande_c == '-' || commande_c == '*'){
            op1 = depiler_i(&pile);
            op2 = depiler_i(&pile);
        }

        if(commande_c == 'A'){
            ret = avance();
            if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
            if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
        }
        else if(commande_c == 'G'){
            gauche();
        }
        else if(commande_c == 'D'){
            droite();
        }
        else if (commande_c == 'P'){
            int arg = depiler_i(&pile);
            pose(arg);
        }
        else if(commande_c == 'M'){
            int arg = depiler_i(&pile);
            ret = mesure(arg);

            empiler_i(&pile, ret);
        }
        else if(commande_c >= '0' && commande_c <= '9'){
            empiler_i(&pile, commande_c - 48);
        }
        else if(commande_c == '+'){
            empiler_i(&pile, op2 + op1);
        }
        else if(commande_c == '-'){
            empiler_i(&pile, op2 - op1);
        }
        else if(commande_c == '*'){
            empiler_i(&pile, op2 * op1);
        }
        else if(commande_c == '?'){
            sequence_t *F = depiler_l(&pile);
            sequence_t *V = depiler_l(&pile);

            int n = depiler_i(&pile);
            if(n){
                ret = interprete(V, true);
            }
            else{
                ret = interprete(F, true);
            }

            if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
            if (ret == RATE)     return RATE; 
            printf("\nValeur de retour : %i\n", ret);
        }
        else if(commande_l != 0){
            empiler_l(&pile, commande_l);
        }
        else if(commande_c == 'X'){
            
            pile_elt_t elt1 = depiler_e(&pile);
            pile_elt_t elt2 = depiler_e(&pile);

            empiler_e(&pile, elt1);
            empiler_e(&pile, elt2);
        }
        else if(commande_c == '!'){
            sequence_t *seq_ = depiler_l(&pile);

            ret = interprete(seq_, true);
            if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
            if (ret == RATE)     return RATE; 
        }
        else if(commande_c == 'B'){
            n = depiler_i(&pile);
            cmd = depiler_l(&pile);

            empiler_l(&pile, cmd);
            empiler_i(&pile, n);
        }
        else if (commande_c == 'R'){
            int x = depiler_i(&pile);
            int n_ = depiler_i(&pile);
            pile_t pile_s1;
            initPile(&pile_s1);
            pile_t pile_s2;
            initPile(&pile_s2);

            for (int i = 0; i < n_-x; i++){
                empiler_e(&pile_s1,depiler_e(&pile));
            }
            for (int i = 0; i < x; i++){
                empiler_e(&pile_s2,depiler_e(&pile));
            }
            for (int i = 0; i < n_-x; i++){
                empiler_e(&pile,depiler_e(&pile_s1));
            }
            for (int i = 0; i < x; i++){
                empiler_e(&pile,depiler_e(&pile_s2));
            }
        }
        else if(commande_c == 'C'){
            pile_elt_t elt1 = depiler_e(&pile);
            pile_elt_t elt2; 

            elt2.type = elt1.type;
            if(elt1.type == 0){
                elt2.i = elt1.i;
            }
            else{
                elt2.l = clonerList(elt1.l);
            }

            empiler_e(&pile, elt1);
            empiler_e(&pile, elt2);
        }
        else if(commande_c == 'I'){
            depiler_e(&pile);
        }
        else{
            eprintf("Caractère inconnu: '%c'\n", commande_c);
        }

        if(n > 0){
            ret = interprete(cmd, true);
            if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
            if (ret == RATE)     return RATE;

            printf("Valeur de n : %i", n);

            n--;
            depiler_i(&pile);
            empiler_i(&pile, n);

            if(n == 0){
                depiler_i(&pile);   //On dépile n
                depiler_l(&pile);   //On dépile cmd
            }
        }
        else{
            cell_s = cell_s->suivant;
        }
        printf("Pile : ");
        afficherPile(&pile);
        printf("\nListe : ");
        afficherListe(seq);
        /* Affichage pour faciliter le debug */
        printf ("\n");
        afficherCarte();
        printf ("\n##############################\n");
        if (debug) stop();
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
