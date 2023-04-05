#include "global.h"

char *multi_tok(char *input, char *delimiter) {
  static char *string;
  if (input != NULL)
    string = input;

  if (string == NULL)
    return string;

  char *end = strstr(string, delimiter);
  if (end == NULL) {
    char *temp = string;
    string = NULL;
    return temp;
  }

  char *temp = string;

  *end = '\0';
  string = end + strlen(delimiter);
  return temp;
}

int colonnes(char * filename){
  char line[1024];
  
  FILE * file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }


  int dim = 0;
  
  char * heading = fgets(line, 1024, file);
  char * token_heading = multi_tok(heading, ",");

  while (token_heading != NULL) {
    token_heading = multi_tok(NULL, ",");
    dim++;
  }

  fclose(file);

    file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }
  
  heading = fgets(line, 1024, file);
  token_heading = multi_tok(heading, ",");

  char ** tab_heading = malloc(dim * 100 * sizeof(char *));
  i = 0;

  while (token_heading != NULL) {
    tab_heading[i] = token_heading; i++;
    token_heading = multi_tok(NULL, ",");
  }
  return dim;
}

int lignes(char * filename){
  int nbLignes = 0;
  FILE * file = fopen(filename, "r");
  char ch;

   //compte le nombre de lignes du fichier
   while((ch=fgetc(file))!=EOF) {
      if(ch=='\n')
         nbLignes++;
   }
  return nbLignes;
}


void result_ballot(char * filename,int col, int ** mat_ballot){
  FILE * file = fopen(filename, "r");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    int j = 0;
    char * ptr = strtok(line, ",");
    int n = 0;
    while(n < 4 && ptr != NULL){
      n++;
      ptr = strtok(NULL, ",");
    }

    if (i != 0){
      while(ptr != NULL && j != col )
      {
        mat_ballot[i-1][j] = atoi(ptr);
        j++;
        ptr = strtok(NULL, ",");
      }
    }
  i++;
  }
}


void duel_mat(char * filename, int ** matDuels){
  FILE * file = fopen(filename, "r");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  
  while ((read = getline(&line, &len, file)) != -1){
    int j = 0;
    
    char * ptr = strtok(line, ",");

    if (i != 0)
    {
      while(ptr != NULL)
      {
        matDuels[i-1][j] = atoi(ptr);
        j++;
        ptr = strtok(NULL, ",");
      }
    }
    i++;
  }
}

int ** matduel_ballot(int ** mat_ballot, int nbligne, int nbCandidats){

    int ** resultat = creer_mat_int(nbCandidats, nbCandidats);

  for(i = 0; i<nbCandidats; i++){
    for(int j = 0; j<nbCandidats; j++){
      resultat[i][j] = 0;
    }
  }

  for(int j=0; j<nbCandidats; j++){

    int tab[nbligne-1];
    for(i = 0; i < nbligne-1; i++){
      tab[i] = mat_ballot[i][j];
    }

    for(int b = 0; b < nbCandidats; b++){
      
      for(int a = 0; a < nbligne-1; a++){
        if(tab[a]<=mat_ballot[a][b] && j != b){
          resultat[j][b] += 1;
        }
      }
    }
  }
    
  return resultat;
}