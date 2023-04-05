#include "global.h"


int ** creer_mat_int(int row, int col){
  int ** matrice = malloc(row * sizeof(int *));
  if(matrice == NULL){
    printf("Problème d'allocation.\n");
    exit(1);
  }
  for (i=0;i<row;i++){
    matrice[i] = malloc(col * sizeof(int));
    if(matrice[i] == NULL){
      printf("Problème d'allocation.\n");
      exit(1);
    }
  }
  return matrice;
}

