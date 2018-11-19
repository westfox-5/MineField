#include "libreria.h"

int push(tlista *l, int r, int c )
{
	tlista nuova;

	nuova = (tlista)malloc(sizeof(struct posizione));
	if (!nuova) {
		return 1; /*errore malloc*/
	}
	nuova->next = *l;
	nuova->riga = r;
	nuova->colonna = c;
	*l = nuova;
	return 0;
}

void scopri_stack(tlista l, struct cella ** mat) {
	if (l) {
		int r, c;
		r = l->riga;
		c = l->colonna;
		if (mat[r][c].visibile == 0)
			mat[r][c].visibile = 1;

		scopri_stack(l->next, mat);
	}
}

int annulla_mossa(tlista *l, int* n_mosse, int* volte, struct cella** matrice , int r_max, int c_max)
{
	/*se ho mosse da annullare in lista e non ho finito il numero max da annullare*/
	if (*l && *n_mosse > 0) {

		int m = *volte; /*salvo numero di volte per decrementarla*/
		tlista tmp;

		while (m > 0 ) { /*numero di volte che ho chiamato annulla_mossa*/
			if (*l != NULL) {
				tmp = *l; /*pop della prima cella della lista*/
				copri(matrice, tmp->riga, tmp->colonna, r_max, c_max); /*funzione che annulla l'ultima mossa effettuata nel campo minato*/
				*l = (*l)->next;
				free(tmp);
			}
			m--;
		}
		scopri_stack(*l, matrice);

		(*volte) += 1; /*aumento le volte che ho fatto l'annullamento*/
		(*n_mosse) -= 1; /*decremento il massimo che posso annullare*/
		return 0;
	}
	else {
		return 1;
	}
}

int scopri(struct cella** matrice, int r, int c, int r_max, int c_max)
{
	int i, j;

	/*scopre se non visibile e non bandiera*/
	if (matrice[r][c].bandiera == 0 && matrice[r][c].visibile == 0) {

		matrice[r][c].visibile = 1;

		if ((matrice[r][c]).numero == -1) {
			/*ho cliccato una BOOMBA!!!*/
			return 2;
		}

		if (matrice[r][c].numero == 0) {

			/*VA IN DIAGONALE*/
			/*se numero=0, scopro l'intorno*/
			for (i = r - 1; i <= r + 1; i++) {

				/*controllo bordi righe*/
				if (i >= 0 && i < r_max) {
					for (j = c - 1; j <= c + 1; j++) {

						/*controllo bordi colonne*/
						if (j >= 0 && j < c_max) {

							if (matrice[i][j].numero != -1)
								scopri(matrice, i, j, r_max, c_max);

						}
					}
				}
			}

			/*VA A CROCE*/
			/*
			if (r - 1 >= 0 && r - 1 < r_max)
				scopri(matrice, r - 1, c, r_max, c_max);
			if (c - 1 >= 0 && c - 1 < c_max)
				scopri(matrice, r, c - 1, r_max, c_max);
			if (c + 1 >= 0 && c + 1 < c_max)
				scopri(matrice, r, c + 1, r_max, c_max);
			if (r + 1 >= 0 && r + 1 < r_max)
				scopri(matrice, r + 1, c, r_max, c_max);
			*/

		}
		return 0;
	}
	else
		return 1; /*bandiera oppure visibile=1*/
}

void copri(struct cella** matrice, int r, int c, int r_max, int c_max)
{
	int i, j;

	/*copro se visibile e non bandiera*/
	if (matrice[r][c].bandiera == 0 && matrice[r][c].visibile == 1) {

		matrice[r][c].visibile = 0;

		if ((matrice[r][c]).numero == -1) {
			/*copro l'ultima bomba e basta*/
		}

		else if (matrice[r][c].numero == 0) {
			/*se numero=0 copro l'intorno*/

			for (i = r - 1; i <= r + 1; i++) {
				/*controllo bordi righe*/
				if (i >= 0 && i < r_max) {
					for (j = c - 1; j <= c + 1; j++) {

						/*controllo bordi colonne*/
						if (j >= 0 && j < c_max) {

							if (matrice[i][j].numero != -1)
								copri(matrice, i, j, r_max, c_max);
						}
					}
				}
			}
		}
	}
}

void check_bandiere(struct cella**matrice, int r, int c, int r_max, int c_max)
{
	int i, j, contatore;
	contatore = 0;

	/*METTE TUTTE LE BANIDERE CERTE*/

	for (i = r - 1; i <= r + 1; i++) {
		/*controllo bordi righe*/
		if (i >= 0 && i < r_max) {
			for (j = c - 1; j <= c + 1; j++) {
				/*controllo bordi colonne*/
				if (j >= 0 && j < c_max) {

					if (matrice[i][j].visibile == 0)
						contatore++;
				}
			}
		}
	}

	for (i = r - 1; i <= r + 1; i++) {
		/*controllo bordi righe*/
		if (i >= 0 && i < r_max) {
			for (j = c - 1; j <= c + 1; j++) {
				/*controllo bordi colonne*/
				if (j >= 0 && j < c_max) {

					if (matrice[r][c].numero == contatore)
						if (matrice[i][j].visibile == 0)
							matrice[i][j].bandiera = 1;
				}
			}
		}
	}
}

void check_scopri(struct cella**matrice, int r, int c, int r_max, int c_max)
{
	int i, j, contatore;
	contatore = 0;

	/*METTE TUTTE LE BANIDERE CERTE*/

	for (i = r - 1; i <= r + 1; i++) {
		/*controllo bordi righe*/
		if (i >= 0 && i < r_max) {
			for (j = c - 1; j <= c + 1; j++) {
				/*controllo bordi colonne*/
				if (j >= 0 && j < c_max) {

					if (matrice[i][j].visibile == 0)
						contatore++;
				}
			}
		}
	}

	for (i = r - 1; i <= r + 1; i++) {
		/*controllo bordi righe*/
		if (i >= 0 && i < r_max) {
			for (j = c - 1; j <= c + 1; j++) {
				/*controllo bordi colonne*/
				if (j >= 0 && j < c_max) {

					if (matrice[r][c].numero == contatore)
						if (matrice[i][j].visibile == 0 && matrice[i][j].bandiera == 0)
							matrice[i][j].visibile = 1;
				}
			}
		}
	}
}


int A_I(WINDOW* local_win, struct cella** matrice, int r_max, int c_max, int col_campo, int lin_campo, int *m_annulla, int *volte, WINDOW* wannulla, int n_bombe, tlista *l)
{

	int r, c, i , j;
	int vinto, primo;
	int fine = 0;
	int ris, ann;
	primo = 1;

	do {

		stampa_comandi_stdr(r_max, c_max, n_bombe, *m_annulla);
		mvprintw(LINES / 2 + 5, COLS - 30, "                          ");
		refresh();
		vinto = vittoria(matrice, r_max, c_max);
		if (vinto == 1) {
			/*STAMPA VITTORIA*/
			destroy_win(local_win);
			refresh();
			stampa_vittoria();
			fine = 1;
		}
		else {

			do {
				r = rand() % r_max;
				c = rand() % c_max;
			} while (matrice[r][c].visibile == 1 || matrice[r][c].bandiera == 1);

			ris = scopri(matrice, r , c , r_max, c_max);
			push(l, r, c); /*push della mossa in lista*/
			stampa_campo(local_win, col_campo, lin_campo, r, c, r_max, c_max, matrice);
			napms(1000);

			if (ris == 2) {

				/*HO CLICCATO BOMBA!*/
				if (*m_annulla > 0) { /*chiedo di annullare*/

					ris = stampa_annulla(wannulla, 50, 15, *volte);
					if (ris) {
						/*scelto di annullare*/
						ann = annulla_mossa(l, m_annulla, volte, matrice, r_max, c_max);
						matrice[r][c].bandiera = 1;
						if (ann == 1) {
							/*impossibile annullare altre mosse*/
							destroy_win(local_win);
							stampa_perso();
							fine = 1;
						}
					}
					else {

						/*altrimenti ho scelto di terminare il gioco*/
						destroy_win(local_win);
						stampa_perso();
						fine = 1;
					}
				} else {
					/*non hai più mosse da annullare*/

					destroy_win(local_win);
					stampa_perso();
					fine = 1;
				}
			}


			for (i = 0; i < r_max; i++) {
				for (j = 0; j < c_max; j++) {
					if (matrice[i][j].numero > 0 && matrice[i][j].visibile == 1 ) {
						check_bandiere(matrice, i, j, r_max, c_max);

						check_scopri(matrice, i, j, r_max, c_max);
					}
				}
			}
		}

	} while (!fine);
	return 0;
}

int vittoria(struct cella** matrice, int r_max, int c_max)
{
	/*check di tutta la matrice*/
	int v;
	int i, j;
	v = 1;

	for (i = 0; i < r_max; i++) {
		for (j = 0; j < c_max; j++) {
			/*vinco se numeri sono scoperti*/
			/*if (matrice[i][j].bandiera == 0 && matrice[i][j].numero == -1)
				v = 0;*/
			if (matrice[i][j].numero >= 0 && matrice[i][j].visibile == 0)
				v = 0;
		}
	}
	return v; /*0-> vittoria*/
}

int bandiera(struct cella** mat, int r, int c)
{
	/*posso mettere bandiera solo su non visibili*/
	if (mat[r][c].visibile == 0) {

		mat[r][c].bandiera = (mat[r][c].bandiera == 0) ? 1 : 0;

		return 0;
	}
	else
		return 1; /*impossibile mettere bandiera*/
}
