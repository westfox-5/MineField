#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>

struct cella {
	int numero; /*-1 se bomba*/
	int visibile;
	int bandiera;
};

struct posizione {
	int riga;
	int colonna;
	struct posizione* next;
};
typedef struct posizione* tlista;

/*scrive nel file se sceglie di generare*/
int scrivi_file(FILE *pf, int r_max, int c_max, int n_bombe);

/*legge dal file r_max e c_max*/
int dim_mat(FILE *pf, int* r_max, int* c_max);

/*per non duplicare i numeri casuali*/
int trovato(int x, int y, int*mine_x, int*mine_y, int idx, int dim);

/*legge da file le bombe*/
int leggi_file(FILE *pf, struct cella** mat, int*n_bombe);

/*crea una matrice r*c in heap*/
int crea_mat(struct cella **mat, int r_max, int c_max);

/*inizializza i numeri a 0*/
void inizializza_zero(struct cella **mat, int r_max, int c_max);

/*inizializza ogni cella a non visibile e mette le mine lette da file*/
int inizializza_mat(struct cella **mat, int r, int c);

/*ritorna il numero di mine attorno alla cella passata in parametro(r,c)*/
int calcola_numeri(struct cella **mat, int r, int c, int r_max, int c_max);

/*scopre (r,c) e le altre che sono 0*/
int scopri(struct cella** matrice, int r, int c, int r_max, int c_max);

/*cambia il flag bandiera (secondo condizioni)*/
int bandiera(struct cella**mat, int r, int c);

/*annulla l'ultima mossa (dello stack)*/
int annulla_mossa(tlista *l, int* n_mosse, int* volte, struct cella** matrice , int r_max, int c_max);

/*copre (r,c) e le altre che sono 0*/
void copri(struct cella** matrice, int r, int c, int r_max, int c_max);

/*check se è finito il gioco*/
int vittoria(struct cella** matrice, int r_max, int c_max); /* 'r' e 'c' vengono passati (0,0);*/

/*elimina da heap la matrice*/
void distruggi_mat(struct cella ***mat, int r_max);

/*elimina da heap una lista*/
void distruggi_lista(tlista *l);

/*inserisce in testa una posizione*/
int push(tlista* l, int r, int c );


int A_I(WINDOW* local_win, struct cella** matrice, int r_max, int c_max, int col_campo, int lin_campo, int *m_annulla, int *volte, WINDOW* wannulla, int n_bombe, tlista *l);

void check_bandiere(struct cella**matrice, int r, int c, int r_max, int c_max);



/*	FUNZIONI PER LA GRAFICA		*/

/*stampa comandi laterali*/
void stampa_comandi_stdr();

int gioca_altre_scelte(WINDOW *local_win, int height, int width);

void print_altre_scelte(WINDOW* win, int highlight, int x_max, int y_max, char **menu_str);

/*scelta del menu*/
int gioca_menu(WINDOW *local_win, int h, int w);
/*stampa del menu*/
void print_menu(WINDOW* win, int highlight, int x_max, int y_max, char **choices);

/*distrugge completamente una window*/
void destroy_win(WINDOW *local_win);

/*FUNZIONE DI GIOCO VERA E PROPRIA*/
int gioca_campo(WINDOW *local_win, int col_campo, int lin_campo, int r_max, int c_max, struct cella** mat, WINDOW*wannulla, tlista *l, int *m_annulla, int *volte, int n_bombe);

/*stampa il campo*/
void stampa_campo(WINDOW* win, int col_campo, int lin_campo, int scelta_i, int scelta_j, int r_max, int c_max, struct cella** mat);

/*generazione nuovo campo*/
void generazione(WINDOW* win, int col_genera, int lin_genera, int *r_max, int *c_max, int* n_bombe, int lines_campo, int col_campo);

/*stampa box annullamento con scelta (si/no)*/
void stampa_scelte_annulla(WINDOW* win, int highlight, int col_max, int lin_max, char **annulla_str);

/*ritorna la scelta di annullare (si/no)*/
int stampa_annulla(WINDOW *win, int col_annulla, int lin_annulla, int mosse_da_annullare);

/*chiede mosse da annullare*/
void stampa_chiedi_annullare(WINDOW* win, int col_chiedi, int lin_chiedi, int*mosse_annullare);

int stampa_chiedi_ai(WINDOW * win, int col_ai, int lin_ai);

void stampa_scelte_ai(WINDOW * win, int highlight, int col_max, int lin_max, char **scelte);

/*stampa titolo in cima*/
void stampa_titolo();

/*stampa scritta vittoria*/
void stampa_vittoria();

/*stampa scritta sconfitta*/
void stampa_perso();

/*stampa lista (debug)*/
void stampa_lista(tlista l);

/*debug*/
void stampa_mat(struct cella** mat, int r_max, int c_max);

#endif
