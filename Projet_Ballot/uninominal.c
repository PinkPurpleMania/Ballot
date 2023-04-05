#include "global.h"

void uninominal1(char * filename, int ** mat_ballot, int nblignes, int nbCandidat){

  int * tab = malloc((nbCandidat) * sizeof(int));
  
  for(i = 0; i < nbCandidat; i++){
    tab[i] = 0;
  }
 
  for(i = 0 ;i < nblignes-1; i++){ 

    for(int j = 0;j < nbCandidat; j++){

      int valeur = mat_ballot[i][j];
      for(int k = 0; k < nbCandidat; k++){
        if(valeur < mat_ballot[i][k] && j != k){  
        tab[j] = tab[j] + 1;
       }
      }
    }
  }

  int vote_max, imax;
  vote_max = tab[0];
  imax = 0;
  
  int somme = 0;
  for (i =0; i < nbCandidat; i++){
    somme += tab[i];
  }

  for (i = 0; i < nbCandidat; i++){
    if (tab[i] > vote_max){
      vote_max = tab[i];
      imax = i;
    }
  }

  int score = tab[imax] / somme;
  
  char * vainq = vainqueur(filename, nbCandidat, &imax);

  printf("Mode de scrutin : uninominal à un tours, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",nbCandidat, nblignes-1, vainq, score);
  
}

void uninominal2(char * filename,int ** matrice_ballot, int nblignes, int nbCandidat, int * imax, int * imax2, int * vote_max, int * vote_max2){

  int * tab = malloc((nbCandidat) * sizeof(int));
  
  for(i = 0; i < nbCandidat; i++){
    tab[i] = 0;
  }
  
  for(i = 0 ;i < nblignes-1; i++){ 
    for(int j = 0;j < nbCandidat; j++){
      int valeur = matrice_ballot[i][j];
      for(int k = 0; k < nbCandidat; k++){
        if(valeur < matrice_ballot[i][k] && j != k){  
        tab[j] = tab[j] + 1;
       }
      }
    }
  }

  *vote_max = tab[0];
  *imax = 0;
  
  for(i = 0; i < nbCandidat; i++){
    if( tab[i] > *vote_max){
      *vote_max = tab[i];
      *imax = i;
    }
  }
  
  *vote_max2 = tab[0];
  *imax2 = 0;

  for(i = 0; i < nbCandidat; i++){
    if(tab[i] > *vote_max2 && i != *imax){
      *vote_max2 = tab[i];
      *imax2 = i;
    }
  }

  float somme = 0.0;

  for (i = 0; i < nbCandidat; i++)
    somme += tab[i];

  float score1 = (*vote_max)*100 / somme;
  float score2 = (*vote_max2)*100 / somme;

  int igagnant1 = *imax, igagnant2 = *imax2;

  char * g1 = vainqueur(filename, nbCandidat, &igagnant1);
  char * g2 = vainqueur(filename, nbCandidat, &igagnant2);

  printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidat, nblignes-1, g1, score1);

  printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidat, nblignes-1, g2, score2);  
 
 if(score1 <= 50.0 || score2 <= 50.0){
    int ** mat = creer_mat_int(2,2);
    
    for(i = 0; i < 2; i++){
      for(int j = 0; j < 2; j++){
        mat[i][j] = 0;
      }
    }
      

   int tab1[100], tab2[100];

   for(i = 0; i < nblignes-1; i++){
    tab1[i] = matrice_ballot[i][*imax];
    tab2[i] = matrice_ballot[i][*imax2];
   }

   for(i = 0; i < nblignes-1; i++){
    if( tab1[i] < tab2[i]){
      mat[0][1] += 1;
    }
    else if( tab1[i] > tab2[i])
      mat[1][0] += 1;
   }

    score1 = mat[0][1]*100/(mat[0][1]+mat[1][0]);
    score2 = mat[1][0]*100/(mat[0][1]+mat[1][0]);
    
    if (mat[0][1] > mat[1][0])
      printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidat, nblignes-1, g1, score1);
    else if (mat[1][0] < mat[0][1])
      printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidat, nblignes-1, g1, score2);
    else{
      printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = egalité entre %s et %s",nbCandidat, nblignes-1, g1, g2); 
    }
 }
 else{
   if(score1 > 50.0){
     printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur par majorité absolue = %s, score = %f%%\n",nbCandidat, nblignes-1, g1, score1);
   }
   if(score2 > 50.0){
     printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur par majorité absolue = %s, score = %f%%\n",nbCandidat, nblignes-1, g2, score2);
   }
 }
}