#include "global.h"
#include <stdio.h>

void print_usage() {
	printf("Usage: main -i <fichier csv> | -d <fichier csv> -o  <fichier txt> "
		   "-m <méthode>\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	int option;

	int iflag = 0, dflag = 0, mflag = 1, m = 0;

	char *csv = NULL;
	char *txt = NULL;
	char *methode = NULL;

	while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
		switch (option) {
		case 'i':
			iflag = 1;
			csv = optarg;
			break;

		case 'd':
			dflag = true;
			csv = optarg;
			break;

		case 'o':
			txt = optarg;
			printf("Txt fichier %s", txt);
			break;

		case 'm':
			mflag = 0;
			m++;
			methode = optarg;
			break;

		case '?':
			if (optopt == 'i' || optopt == 'd' || optopt == 'o' ||
				optopt == 'm')
				print_usage();
			break;

		default:
			print_usage();
			break;
		}
	}

	if (iflag && dflag) {
		printf("Erreur: options -i et -d sont indépendants !\n");
		exit(EXIT_FAILURE);
	}

	else if (argc < 4) {
		print_usage();
	}

	else if (m != 1) {
		print_usage();
	}

	else if (iflag) { // pour les fichiers ballot

		if (strcmp(methode, "uni1") == 0) {
			int nbligne = lignes(csv);
			int nbVotant = nbligne - 1;

			int col = colonnes(csv);
			int nbCandidatBallot = col - 4;

			int **matrice_ballot = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot); // transformation ballot en matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, nbligne, nbCandidatBallot);

			int imax, imax2, vote_max, vote_max2;
			uninominal1(csv, matrice_ballot, nbligne, nbCandidatBallot);
		}

		else if (strcmp(methode, "uni2") == 0) {
			int nbligne = lignes(csv);
			int nbVotant = nbligne - 1;

			int col = colonnes(csv);
			int nbCandidatBallot = col - 4;

			int **matrice_ballot = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot); // transformation ballot en matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, nbligne, nbCandidatBallot);

			int imax, imax2, vote_max, vote_max2;
			uninominal2(
				csv,
				matrice_ballot,
				nbligne,
				nbCandidatBallot,
				&imax,
				&imax2,
				&vote_max,
				&vote_max2);
		}

		else if (strcmp(methode, "cm") == 0) {
			int nbligne = lignes(csv);
			int nbVotant = nbligne - 1;

			int col = colonnes(csv);
			int nbCandidatBallot = col - 4;

			int **matrice_ballot = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot); // transformation ballot en matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, nbligne, nbCandidatBallot);

			Elementliste e;
			liste liste;
			createList(&liste);
			creerArcMinimax(&e, &liste, matrice_duel_ballot, nbCandidatBallot);
			minimax_ballot(csv, liste, nbCandidatBallot, nbligne);
		}

		else if (strcmp(methode, "cs") == 0) {
			int nbligne = lignes(csv);
			int nbVotant = nbligne - 1;

			int col = colonnes(csv);
			int nbCandidatBallot = col - 4;

			int **matrice_ballot = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot); // transformation ballot en matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, nbligne, nbCandidatBallot);

			schulze_ballot(csv, matrice_duel_ballot, nbCandidatBallot, nbligne);
		}

		else if (strcmp(methode, "all") == 0) {
			int nbligne = lignes(csv);
			int nbVotant = nbligne - 1;

			int col = colonnes(csv);
			int nbCandidatBallot = col - 4;

			// Uninominal 1
			int **matrice_ballot = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot); // transformation ballot en matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, nbligne, nbCandidatBallot);

			int imax, imax2, vote_max, vote_max2;
			uninominal1(csv, matrice_ballot, nbligne, nbCandidatBallot);

			// Uninominal 2
			int **matrice_ballot2 = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot2); // transformation ballot en matrice

			int **matrice_duel_ballot2 =
				matduel_ballot(matrice_ballot2, nbligne, nbCandidatBallot);

			int imax1, imax21, vote_max1, vote_max21;
			uninominal2(
				csv,
				matrice_ballot,
				nbligne,
				nbCandidatBallot,
				&imax1,
				&imax21,
				&vote_max1,
				&vote_max21);

			// Minimax
			int **matrice_ballot3 = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot3); // transformation ballot en matrice

			int **matrice_duel_ballot3 =
				matduel_ballot(matrice_ballot3, nbligne, nbCandidatBallot);

			// Schulze
			Elementliste e;
			liste liste;
			createList(&liste);
			creerArcMinimax(&e, &liste, matrice_duel_ballot, nbCandidatBallot);
			minimax_ballot(csv, liste, nbCandidatBallot, nbligne);

			int **matrice_ballot4 = creer_mat_int(
				nbligne, nbCandidatBallot); // allocation matrice pour le ballot
			result_ballot(
				csv, col, matrice_ballot); // transformation ballot en matrice

			int **matrice_duel_ballot4 =
				matduel_ballot(matrice_ballot4, nbligne, nbCandidatBallot);

			schulze_ballot(csv, matrice_duel_ballot, nbCandidatBallot, nbligne);
		}

		else {
			print_usage();
		}
	}

	if (dflag) { // Matrice de duel
		if (strcmp(methode, "uni1") == 0) {
			printf("Erreur: la méthode uninominale à 1 tour est bloquée pour "
				   "le fichier donné, veuillez saisir un fichier ballot.\n");
			exit(EXIT_FAILURE);
		}

		else if (strcmp(methode, "uni2") == 0) {
			printf("Erreur: la méthode uninominale à 2 tours est bloquée pour "
				   "le fichier donné, veuillez saisir un fichier ballot.\n");
			exit(EXIT_FAILURE);
		}

		else if (strcmp(methode, "cm") == 0) {
			int nbCandidat = colonnes(csv);

			int **matrice = creer_mat_int(nbCandidat, nbCandidat);
			duel_mat(csv, matrice);

			Elementliste e;
			liste liste;
			createList(&liste);
			creerArcMinimax(&e, &liste, matrice, nbCandidat);
			minimax_duel(csv, liste, nbCandidat, nbCandidat);
		}

		else if (strcmp(methode, "cs") == 0) {
			printf("t");
			int nbCandidat = colonnes(csv);

			int **matrice = creer_mat_int(nbCandidat, nbCandidat);
			duel_mat(csv, matrice);

			schulze_duel(csv, matrice, nbCandidat, nbCandidat);
		}

		else if (strcmp(methode, "all") == 0) {
			printf("t");
			int nbCandidat = colonnes(csv);

			int **matrice_mini = creer_mat_int(nbCandidat, nbCandidat);
			duel_mat(csv, matrice_mini);

			// Méthode Minimax
			Elementliste e;
			liste liste2;
			createList(&liste2);
			creerArcMinimax(&e, &liste2, matrice_mini, nbCandidat);
			minimax_duel(csv, liste2, nbCandidat, nbCandidat);

			int **matrice = creer_mat_int(nbCandidat, nbCandidat);
			duel_mat(csv, matrice);

			// Méthode Schulze
			schulze_duel(csv, matrice, nbCandidat, nbCandidat);
		}

		else {
			print_usage();
		}
	}

	return 0;
}