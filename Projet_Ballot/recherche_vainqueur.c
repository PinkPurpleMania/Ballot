#include "global.h"

char * vainqueur(char * filename, int nbCandidats, int * imax){
  int i = 0, j = 0;
  char line[1024];
  char * nom_candidat[nbCandidats];
  
  FILE * file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }
  
  char * firstline = fgets(line, 1024, file);
  char * nom = strtok(firstline, ",");

  while (nom != NULL && j < 4){
    nom = strtok(NULL, ",");
    j++;
  }

  while (nom != NULL && j >= 4){
    nom_candidat[i] = nom;
    nom = strtok(NULL, ",");
    i++;
  }
  
  printf(" ");
  return nom_candidat[*imax];
}

char * vainqueurDuel(char * filename, int nbCandidats, int * imax){
  int i = 0, j = 0;
  char line[1024];
  char * nom_candidat[nbCandidats];
  
  FILE * file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }
  
  char * entete = fgets(line, 1024, file);
  char * nom = strtok(entete, ",");

  while (nom != NULL){
    nom_candidat[i] = nom;
    nom = strtok(NULL, ",");
    i++;
  }

  /*for(i = 0; i < nbCandidats; i++)
    printf("%s\n", nom_candidat[i]);
  */
  printf(" ");
  return nom_candidat[*imax];
}