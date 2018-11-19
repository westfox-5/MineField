#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"

int dim_mat(FILE *pf, int* r_max, int* c_max)
{
	/*leggi r_max e c_max*/
	fscanf(pf, "%d, %d\n", r_max, c_max);

	return 0;
}

int leggi_file(FILE *pf, struct cella** mat, int* n_bombe)
{
	int cont = 0;
	int r;
	int c;

	/*aquisisci coordinate della bomba e inserisci la bomba all'interno della matrice*/
	while (!feof(pf))
	{
		fscanf(pf, "%d, %d\n" , &r , &c);
		mat[r][c].numero = -1;

		cont++;

	}
	*n_bombe = cont;

	return 0;
}

int trovato(int x, int y, int*mine_x, int*mine_y, int idx, int dim)
{
	/*cerca coppia(x,y) in array mine_x e mine_y*/
	int i, flag;
	flag = 0;
	for (i = 0; i < dim; i++) {
		if (idx != i) {
			if (x == mine_x[i] && y == mine_y[i])
				flag = 1;
		}
	}
	return flag; /*1 se trova coppia*/
}

int scrivi_file(FILE *pf, int r_max, int c_max, int n_bombe)
{
	int i, j, flag;
	int* mine_x, *mine_y;

	/*crea due array per coordinate x e y*/
	mine_y = (int*)malloc(sizeof(int) * n_bombe);
	mine_x = (int*)malloc(sizeof(int) * n_bombe);

	fprintf(pf, "%d, %d", r_max, c_max);

	/*genero n_bombe in mine_x mine_y*/
	for (i = 0; i < n_bombe; i++) {
		mine_x[i] = rand() % (r_max);
		mine_y[i] = rand() % (c_max);
	}

	/*controllo siano tutte diverse*/
	for (i = 0; i < n_bombe; i++) {
		while (trovato(mine_x[i], mine_y[i], mine_x, mine_y, i, n_bombe)) {
			mine_x[i] = rand() % r_max;
			mine_y[i] = rand() % c_max;
		}
	}

	/*le scrivo nel file*/
	for (i = 0; i < n_bombe; i++) {
		if (i == 0)
			fprintf(pf, "\n\n");
		fprintf(pf, "%d, %d\n", mine_x[i], mine_y[i]);
	}

	/*elimino i due array*/
	free(mine_y);
	free(mine_x);

	return 0;
}

int crea_mat(struct cella **mat, int r_max, int c_max)
{
	int i, j;

	for (i = 0; i < r_max; i++) {
		mat[i] = (struct cella*)malloc(c_max * sizeof(struct cella));
		if (!mat[i])
			return 1; /*errore malloc*/
	}
	return 0;
}

void inizializza_zero(struct cella **mat, int r_max, int c_max)
{
	int i, j;

	for (i = 0; i < r_max; i++)
		for (j = 0; j < c_max; j++)
			mat[i][j].numero = 0;
}


int calcola_numeri(struct cella **mat, int r, int c, int r_max, int c_max)
{
	int i, j;
	int tot = 0;

	for (i = r - 1; i <= r + 1; i++) {
		/*controllo bordi righe*/
		if (i >= 0 && i < r_max) {
			for (j = c - 1; j <= c + 1; j++) {

				/*controllo bordi colonne*/
				if (j >= 0 && j < c_max) {

					/*aumento contatore numeri attorno a cella (r,c) se mina*/
					if (mat[i][j].numero == -1)
						tot++;

				}
			}
		}
	}
	return tot; /*numero di celle intorno (r,c)*/
}

int inizializza_mat(struct cella **mat, int r_max, int c_max)
{
	int i, j;
	/*inizializzo numero, visibile e bandiera a 0*/
	for (i = 0; i < r_max; i++) {
		for (j = 0; j < c_max; j++) {
			mat[i][j].visibile = 0;
			mat[i][j].bandiera = 0;
		}
	}

	/*inserisco i numeri*/
	for (i = 0; i < r_max; i++) {
		for (j = 0; j < c_max; j++) {
			if (mat[i][j].numero != -1) {
				mat[i][j].numero = calcola_numeri(mat, i, j, r_max, c_max);
			}
		}
	}

	return 0;
}

void distruggi_mat(struct cella ***mat, int r_max)
{
	if (*mat) {
		int i;
		for (i = 0; i < r_max; i++) {
			free((*mat)[i]);
		}
		free(*mat);
	}
}

void distruggi_lista(tlista *l)
{
	if (*l) {
		distruggi_lista(&((*l)->next));
		free(*l);
	}
}

/*debug*/
void stampa_mat(struct cella** mat, int r_max, int c_max)
{
	int i, j;

	for (i = 0; i < r_max; i++) {
		for (j = 0; j < c_max; j++) {
			mvprintw(i, j, "%d ", mat[i][j].numero);
		}
		/*printf("\n");*/
	}
	/*printf("\n");*/
}

/*debug*/
void stampa_lista(tlista l)
{
	int i = 2;
	while (l) {
		mvprintw(10, i, "%d %d->", l->riga, l->colonna);
		l = l->next;
		i += 5;
	}
	mvprintw(10, i, "%p", l);
}