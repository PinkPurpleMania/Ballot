/**
 *@file global.h
 *@author ANDRIANJAKA MIALY
 */
#define _GNU_SOURCE
#include <sys/types.h>

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "elementliste.h"

#define MAXCANDIDATE 30 // nombre maximum de candidats

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAXI(a,b) (((a)>(b))?(a):(b))

int i, j;



//lecture_csv.c
/**
 *@brief *multi_tok 
 *@param[in] char *input
 *@param[in] char *delimiter
 *@return char*
 */
char *multi_tok(char *input, char *delimiter);
/**
 *@brief matduel_ballot crée une matrice de duel à partir des données d'un fichier ballot.
 *@param[in] int ** mat_ballot
 *@param[in]  int row
 *@param[in]  int nbCandidats
 *@return int **
 */
int ** matduel_ballot(int ** mat_ballot, int nbligne, int nbCandidats);

/**
 *@brief colonnes  compte les colonnes nécessaires dans le fichier pour créer la matrice contenant les résultats des votes.
 *@param[in] char * filename
 *@return int
 */
int colonnes(char * filename);
/**
 *@brief lignes  compte les lignes nécessaires dans le fichier pour créer la matrice contenant les résultats des votes.
 *@param[in] char* filename
 *@return int
 */
int lignes(char * filename);

/**
 *@brief result_ballot  transforme les résultats d'un fichier_csv ballot en matrice d'entiers
 *@param[in] char * filename
 *@param[in] int column
  *@param[in] int ** mat_ballot
 *@return void
 */
void result_ballot(char * filename,int col, int ** mat_ballot);

/**
 *@brief duel_mat crée une matrice de duel à partir des fichiers csv dont les résultats se présentent déjà sous forme de matrice de duel
 *@param[in] char * filename
 *@return void
 */
void duel_mat(char * filename, int ** matDuels);

//utils_sd.c
/**
 *@brief creer_mat_int effectue les allocations nécessaires à une matrice d'entier.
 *@param[in] int row
 *@param[in] int col
 *@return int **
 */
int ** creer_mat_int(int row, int col); 


// condorcet.c
/**
 *@brief minimax_duel applique la méthode minimax sur les résultats d'un fichier csv matrice de duel.
 *@param[in] char * filename
 *@param[in]  liste liste
 *@param[in]  int nbCandidats
 *@param[in]  int row
 *@return void
 */
void minimax_duel(char * filename,liste liste, int nbCandidats, int nblignes);
/**
 *@brief minimax_ballot applique la méthode minimax sur les résultats d'un fichier csv ballot.
 *@param[in] char * filename
 *@param[in]  liste liste
 *@param[in]  int nbCandidats
 *@param[in]  int row
 *@return void
 */
void minimax_ballot(char * filename,liste liste, int nbCandidats, int nblignes);


//Uninominale.c
/**
 *@brief i_Uninominal_un_tour applique la méthode uninominale à un tour
 *@param[in] char * filename
 *@param[in] int ** mat_ballot
 *@param[in]  int nblignes
 *@param[in]  int nbCandidat
 *@return void
 */
void uninominal1(char * filename, int ** mat_ballot, int nblignes, int nbCandidat);
/**
 *@brief uninominal2  applique la méthode uninominale à deux tours
 *@param[in] char * filename
 *@param[in] int ** matrice_ballot
 *@param[in]  int* imax
 *@param[in]  int * imax2
 *@param[in]  int * igagnant
 *@param[in]  int nblignes
 *@param[in]  int nbCandidat
 *@param[in]  int * vote_max
 *@param[in]  int * vote_max2
 *@return void
 */
void uninominal2(char * filename,int ** matrice_ballot, int nblignes, int nbCandidat, int * imax,int * imax2, int * vote_max, int * vote_max2);
/**
 *@brief minimax_ballot applique la methode condorcet minimax avec l'option -i
 *@param[in] char * filename
 *@param[in] liste liste
 *@param[in]  int ** mat_duel
 *@param[in]  int nbCandidats
 *@param[in]  int nblignes
 *@return void
*/
void minimax_ballot(char * filename,liste liste, int nbCandidats, int nblignes);
/**
 *@brief minimax_duel applique la methode condorcet minimax avec l'option -d
 *@param[in] char * filename
 *@param[in] liste liste
 *@param[in]  int ** mat_duel
 *@param[in]  int nbCandidats
 *@param[in]  int nblignes
 *@return void
*/
void minimax_duel(char * filename,liste liste, int nbCandidats, int nblignes);
/**
 *@brief creerArcMinimax crée la liste des arcs orientés à partir d'une matrice duel
 *@param[in] Elementliste * e
 *@param[in] liste * liste
 *@param[in]  int ** mat_duel
 *@param[in]  int nbCandidats
 *@return void
*/
void creerArcMinimax(Elementliste * e,liste * liste, int ** mat_duel, int nbCandidats);
/**
 *@brief Arc_Schulze crée les arcs à partir d'une matrice de duel pour appliquer la méthode de schulze
 *@param[in] Elementliste * e
 *@param[in] liste * liste
 *@param[in]  int ** mat_duel
 *@param[in]  int nbCandidats
 *@return void
*/
void Arc_Schulze(Elementliste * e,liste * liste, int ** mat_duel, int nbCandidats);

/**
 *@brief schulze_ballot applique la méthode de schulze sur les données d'un csv ballot représentées sous une matrice de duel
 *@param[in] char * filename
 *@param[in] int **mat_duel
 *@param[in] int ** mat_duel
 *@param[in] int nbCandidat
 *@param[in] int nb_ligne;
 *@return void
*/
void schulze_ballot(char * filename,int **mat_duel, int nbCandidats, int nb_ligne);

/**
 *@brief schulze_duel applique la méthode de schulze sur les données d'un csv matrice de duel
 *@param[in] char * filename
 *@param[in] int **mat_duel
 *@param[in] int ** mat_duel
 *@param[in] int nbCandidat
 *@param[in] int nb_ligne;
 *@return void
*/
void schulze_duel(char * filename,int **mat_duel, int nbCandidats, int nb_ligne);

//recherche_vainqueur.c
/**
 *@brief vainqueur cherche le vainqueur dans un csv ballot à partir de l'indice donnée en paramètre.
 *@param[in] char * filename
 *@param[in]  int *imax
 *@param[in]  int nbColumn
 *@return char*
 */
char * vainqueur(char * filename, int nbCandidats, int * imax);
/**
 *@brief vainqueurDuel cherche le vainqueur dans un csv matrice de duel à partir de l'indice donnée en paramètre.
 *@param[in] char * filename
 *@param[in]  int nbCandidats
 *@param[in]  int * imax
 *@return char*
 */
char * vainqueurDuel(char * filename, int nbCandidats, int * imax);

#endif