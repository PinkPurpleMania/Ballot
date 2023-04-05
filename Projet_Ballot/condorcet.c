#include "global.h"

void minimax_duel(char * filename,liste liste, int nbCandidats, int nblignes){
  int max = liste.Tabliste[0].poids, imax = liste.Tabliste[0].orig;
  for(i = 1; i < nbCandidats; i++){
    if(liste.Tabliste[i].poids > max){
      max = liste.Tabliste[i].poids;
      imax = liste.Tabliste[i].orig;
    }
  }
  float somme = 0.0;

  for(i = 0; i < nbCandidats; i++){
    somme += liste.Tabliste[i].poids;
  }

  float score = max*100/somme;

  char * vainqueur = vainqueurDuel(filename, nbCandidats, &imax);
 
  printf("Mode de scrutin : Condorcet minimax, %d candidats, n/a votants, vainqueur = %s, score = %f%%\n", nblignes-1, vainqueur, score);
}

void minimax_ballot(char * filename,liste liste, int nbCandidats, int nblignes){
  int max = liste.Tabliste[0].poids, imax = liste.Tabliste[0].orig;
  for(i = 1; i < nbCandidats; i++){
    if(liste.Tabliste[i].poids > max){
      max = liste.Tabliste[i].poids;
      imax = liste.Tabliste[i].orig;
    }
  }
  float somme = 0.0;

  for(i = 0; i < nbCandidats; i++){
    somme += liste.Tabliste[i].poids;
  }

  float score = max*100/somme;

  char * vainq = vainqueur(filename, nbCandidats, &imax);
 
  printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidats, nblignes-1, vainq, score);
}

void creerArcMinimax(Elementliste * e,liste * liste, int ** mat_duel, int nbCandidats){

  int  min, j_min;
  for(i = 0; i < nbCandidats; i++){
    if(i == 0){
      min = mat_duel[i][1];
      j_min = 1;
    }
    else{
      min = mat_duel[i][0];
      j_min = 0;
    }
    for(j = 0; j < nbCandidats; j++){
      if( mat_duel[i][j] < min && i != j){
        min = mat_duel[i][j];
        j_min = j;
      }
    }
    e->orig = i;
    e->dest = j_min;
    e->poids = min;
    addTailList(liste, *e);
  }
}



void Arc_Schulze(Elementliste * e,liste * liste, int ** mat_duel, int nbCandidate){

  int  max, j_o,j_d,j;

  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      if(i>j){
        if(mat_duel[i][j] > mat_duel[j][i]){
          max = mat_duel[i][j];
          j_o = i;
          j_d = j;
        }
        else if(mat_duel[i][j] < mat_duel[j][i]){
          max = mat_duel[j][i];
          j_o = j;
          j_d = i;
        }
        e->orig = j_o;
        e->dest = j_d;
        e->poids = max;
        addTailList(liste, *e);
      }
    }
  }
}


void schulze_duel(char * filename,int **mat_duel, int nbCandidats, int nb_ligne){

  int **resultat = creer_mat_int(nbCandidats,nbCandidats);
  int orig, dest;

  for(i = 0;i < nbCandidats; i++){
    for(j = 0;j < nbCandidats; j++){
      resultat[i][j] = 0;
    }
  }  
   
  for(i = 0; i < nbCandidats; i++){
    for(j = 0; j < nbCandidats; j++){
      if(i != j){
        if(mat_duel[i][j]>mat_duel[j][i]){
          resultat[i][j] = mat_duel[i][j];
        }
        else{
          resultat[i][j] = 0;
        }
      }
    }
  }

  for(i = 0; i < nbCandidats; i++){
    for(j = 0; j < nbCandidats; j++){
      if(i != j){
        for(int k = 0; k < nbCandidats; k++){
          if(i != k && j != k){
            resultat[j][k] = MAXI(resultat[j][k], MIN(resultat[j][i],resultat[i][k]));
          }
        }
      }
    }
  }


  int max = 0, somme = 0;
  int somme_totale = 0, imax;

  for(i = 0; i < nbCandidats; i++){
    for(j = 0; j < nbCandidats; j++){
      somme += resultat[i][j];
      somme_totale += resultat[i][j];
    }
    if(somme > max){
      max = somme;
      imax = i;
    }
    somme = 0;
  }
  
  int score = max*100/somme_totale;

  char * vainqueur = vainqueurDuel(filename, nbCandidats, &imax);

  printf("Mode de scrutin : Condorcet schulze, %d candidats, n/a votants, vainqueur = %s, score = %d%%\n",nbCandidats, vainqueur, score);
}


void schulze_ballot(char * filename,int **mat_duel, int nbCandidats, int nb_ligne){

  int **resultat = creer_mat_int(nbCandidats,nbCandidats);

  for(i = 0;i < nbCandidats; i++){
    for(j = 0;j < nbCandidats; j++){
      resultat[i][j] = 0;
    }
  }  
   
  for(i = 0; i < nbCandidats; i++){
    for(j = 0; j < nbCandidats; j++){
      if(i != j){
        if(mat_duel[i][j]>mat_duel[j][i]){
          resultat[i][j] = mat_duel[i][j];
        }
        else{
          resultat[i][j] = 0;
        }
      }
    }
  }

  for(i = 0; i < nbCandidats; i++){
    for(j = 0; j < nbCandidats; j++){
      if(i != j){
        for(int k = 0; k < nbCandidats; k++){
          if(i != k && j != k){
            resultat[j][k] = MAXI(resultat[j][k], MIN(resultat[j][i],resultat[i][k]));
          }
        }
      }
    }
  }


  int max = 0, somme = 0;
  int somme_de_tout = 0;
  int i_vainqueur;

  for(i = 0; i < nbCandidats; i++){
    for(j = 0; j < nbCandidats; j++){
      somme += resultat[i][j];
      somme_de_tout += resultat[i][j];
    }
    if(somme > max){
      max = somme;
      i_vainqueur = i;
    }
    somme = 0;
  }
  
  int score = max*100/somme_de_tout;

  
  char * gagnant = vainqueur(filename, nbCandidats, &i_vainqueur);

  printf("Mode de scrutin : Condorcet schulze, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",nbCandidats,nb_ligne-1, gagnant, score);
}