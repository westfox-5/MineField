#include "lib/libreria.h"

int main() {

	struct cella **matrice;
	/*
		r_max: dimensione righe matrice
		c_max: dimensione colonne matrice
		n_bombe: quante bombe ci sono nel campo
		n_mosse: quante mosse è possibile annullare
		volte: quante volte ho annullato una mossa
	*/
	int r_max, c_max, n_bombe, n_mosse, volte;
	int continua_gioco = 1;
	int scelta_ai;

	tlista l_mosse;

	WINDOW *menu;
	WINDOW *campo;
	WINDOW *opzioni;
	WINDOW *genera;
	WINDOW *chiedi;
	WINDOW *ai;
	WINDOW *annullamento;

	FILE *file;

	int scelta_menu; /*cosa si sceglie dal menu*/
	int altre_opzioni;

	/*PARAMETRI PER LE FINESTRE DA STAMPARE*/
	int startcol_menu, startlin_menu, cols_menu, lines_menu;
	int startcol_campo, startlin_campo, cols_campo, lines_campo;
	int startcol_genera, startlin_genera, cols_genera, lines_genera;
	int startcol_annulla, startlin_annulla, cols_annulla, lines_annulla;
	int startcol_chiedi, startlin_chiedi, cols_chiedi, lines_chiedi;
	int startcol_opzioni, startlin_opzioni, cols_opzioni, lines_opzioni;
	int startcol_ai, startlin_ai, cols_ai, lines_ai;

	/*inizializzo seed per generazione bombe*/
	srand(time(NULL));

	initscr(); /* inizio ncurses */

	clear();
	cbreak();
	noecho();
	curs_set(0); /*non mostro cursore*/
	keypad(stdscr, TRUE); /*attivo tastiera*/

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK); 		/*colore menu*/
	init_pair(2, COLOR_GREEN, COLOR_BLACK); 	/*colore titolo*/
	init_pair(3, COLOR_GREEN, COLOR_BLACK); 	/*colore menu selezionato*/
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);	/*colore titolo menu*/
	init_pair(5, COLOR_BLUE, COLOR_BLACK); 		/*colore campo*/
	init_pair(6, COLOR_RED, COLOR_BLACK); 		/*colore box campo*/

	/*colori vittoria*/
	init_pair(10, COLOR_GREEN, COLOR_BLACK);
	init_pair(11, COLOR_YELLOW, COLOR_BLACK);
	init_pair(12, COLOR_RED, COLOR_BLACK);
	init_pair(13, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(14, COLOR_BLUE, COLOR_BLACK);
	init_pair(15, COLOR_CYAN, COLOR_BLACK);


	/*CREA FINESTRA MENU*/
	lines_menu = 17;
	cols_menu = 50;
	startcol_menu = (COLS - cols_menu) / 2;
	startlin_menu = (LINES - lines_menu) / 2;

	/*CREA FINESTRA ALTRE OPZIONI*/
	lines_opzioni = 17;
	cols_opzioni = 50;
	startlin_opzioni = (LINES - lines_opzioni) / 2;
	startcol_opzioni = (COLS - cols_opzioni) / 2;

	/*CREA FINESTRA GENERA*/
	lines_genera = 20;
	cols_genera = 60;
	startcol_genera = (COLS - cols_genera) / 2;
	startlin_genera = (LINES - lines_genera) / 2;

	/*CREA FINESTRA CAMPO*/
	startcol_campo = 2;
	startlin_campo = 10;
	cols_campo = (COLS - startcol_campo - 44);
	lines_campo = (LINES - startlin_campo - 1);

	/*CREA FINESTRA ANNULLA*/
	lines_annulla = 15;
	cols_annulla = 43;
	startcol_annulla = COLS - cols_menu + 6;
	startlin_annulla = LINES - lines_menu - 2;

	/*CREA FINESTRA CHIEDI MOSSE ANNULLARE*/
	lines_chiedi = 15;
	cols_chiedi = 60;
	startcol_chiedi = (COLS - cols_chiedi) / 2;
	startlin_chiedi = (LINES - lines_chiedi) / 2;

	/*CREA FINESTRA GIOCA CON AI*/
	lines_ai = 15;
	cols_ai = 60;
	startcol_ai = (COLS - cols_ai) / 2;
	startlin_ai = (LINES - lines_ai) / 2;



	do {
		menu = newwin(lines_menu, cols_menu, startlin_menu, startcol_menu);
		opzioni = newwin(lines_opzioni, cols_opzioni, startlin_opzioni, startcol_opzioni);
		genera = newwin(lines_genera, cols_genera, startlin_genera, startcol_genera);
		campo = newwin(lines_campo, cols_campo, startlin_campo, startcol_campo);
		annullamento = newwin(lines_annulla, cols_annulla, startlin_annulla, startcol_annulla);
		chiedi = newwin(lines_chiedi, cols_chiedi, startlin_chiedi, startcol_chiedi);
		ai = newwin(lines_ai, cols_ai, startlin_ai, startcol_ai);
		wbkgd(campo, COLOR_PAIR(5));

		volte = 1;
		/*campo inizialmente a 0*/
		r_max = 0;
		c_max = 0;
		l_mosse = NULL;

		erase();
		stampa_titolo();
		refresh();

		/*SCELTA DEL MENU*/
		scelta_menu = gioca_menu(menu, lines_menu, cols_menu);

		if (scelta_menu == 0) {
			destroy_win(menu);
			/*GENERA DA ZERO*/
			file = fopen("campi/campo.txt", "w"); /*se genero, devo scrivere nel file*/


			keypad(stdscr, FALSE);

			/*PARTE SCHERMATA GENERAZIONE*/
			generazione(genera, cols_genera, lines_genera, &r_max, &c_max, &n_bombe, lines_campo, cols_campo);
			keypad(stdscr, TRUE);

			/*scrivo su file dimensione e genero le bombe*/
			scrivi_file(file, r_max, c_max, n_bombe);

			fclose(file);

			destroy_win(genera);

			file = fopen("campi/campo.txt", "r");

			/*LEGGI DA FILE*/
			dim_mat(file, &r_max, &c_max);

			matrice = (struct cella**)malloc(sizeof(struct cella *)*r_max);
			crea_mat(matrice, r_max, c_max);

			/*inizializza numeri a zero*/
			inizializza_zero(matrice, r_max, c_max);

			/* mette bombe in matrice e scrive nbombe*/
			leggi_file(file, matrice, &n_bombe);

			fclose(file);


			/*inizializza tutto a zero e mette i numeri*/
			inizializza_mat(matrice, r_max, c_max);

			/*chede mosse annullare e le scrive*/
			stampa_chiedi_annullare(chiedi, cols_chiedi, lines_chiedi, &n_mosse);
			destroy_win(chiedi);

			scelta_ai = stampa_chiedi_ai(ai, cols_ai, lines_ai);
			destroy_win(ai);

			if (!scelta_ai) {
				/*gioco*/
				continua_gioco = gioca_campo(campo, cols_campo, lines_campo, r_max , c_max, matrice, annullamento, &l_mosse, &n_mosse, &volte, n_bombe);
			} else {
				A_I(campo, matrice, r_max, c_max, cols_campo, lines_campo, &n_mosse, &volte, annullamento, n_bombe, &l_mosse);
			}

			destroy_win(campo);
			destroy_win(genera);
			destroy_win(annullamento);
			destroy_win(chiedi);

			distruggi_lista(&l_mosse);
			distruggi_mat(&matrice, r_max);
			refresh();

		}
		else if (scelta_menu == 1) {
			destroy_win(menu);

			/*LEGGI DA FILE*/
			/*apro file in lettura*/
			file = fopen("campi/campo.txt", "r");

			/*legge r_max e c_max*/
			dim_mat(file, &r_max, &c_max);

			matrice = (struct cella**)malloc(sizeof(struct cella *)*r_max);
			crea_mat(matrice, r_max, c_max);

			/*inizializza numeri a zero*/
			inizializza_zero(matrice, r_max, c_max);

			/*legge file e mette bome in matrice e scrive nbombe*/
			leggi_file(file, matrice, &n_bombe);

			fclose(file);

			/*inizializza tutto a zero e mette i numeri*/
			inizializza_mat(matrice, r_max, c_max);

			/*chede mosse annullare e le scrive*/
			stampa_chiedi_annullare(chiedi, cols_chiedi, lines_chiedi, &n_mosse);
			destroy_win(chiedi);

			scelta_ai = stampa_chiedi_ai(ai, cols_ai, lines_ai);
			destroy_win(ai);
			if (!scelta_ai) {
				/*gioco*/
				continua_gioco = gioca_campo(campo, cols_campo, lines_campo, r_max , c_max, matrice, annullamento, &l_mosse, &n_mosse, &volte, n_bombe);
			} else {
				A_I(campo, matrice, r_max, c_max, cols_campo, lines_campo, &n_mosse, &volte, annullamento, n_bombe, &l_mosse);
			}
			distruggi_lista(&l_mosse);
			distruggi_mat(&matrice, r_max);
		}
		else if (scelta_menu == 2) {
			altre_opzioni = gioca_altre_scelte(opzioni, lines_opzioni, cols_opzioni);

			if (altre_opzioni == 0) {
				/*FACILE*/
				n_bombe = 10;
				n_mosse = 10;
				file = fopen("campi/default_facile.txt", "w");
				scrivi_file(file, 15, 15, n_bombe);
				fclose(file);
				file = fopen("campi/default_facile.txt", "r");
			}
			else if (altre_opzioni == 1) {
				/*MEDIO*/
				n_bombe = 60;
				n_mosse = 6;
				file = fopen("campi/default_medio.txt", "w");
				scrivi_file(file, 30, 25, n_bombe);
				fclose(file);
				file = fopen("campi/default_medio.txt", "r");
			}
			else if (altre_opzioni == 2) {
				/*DIFFICILE*/
				n_bombe = 120;
				n_mosse = 3;
				file = fopen("campi/default_difficile.txt", "w");
				scrivi_file(file, 40, 30, n_bombe);
				fclose(file);
				file = fopen("campi/default_difficile.txt", "r");
			}
			else if (altre_opzioni == 3) {
				destroy_win(menu);
				destroy_win(opzioni);
			}

			if (altre_opzioni != 3) {
				destroy_win(menu);
				destroy_win(opzioni);
				/*legge r_max e c_max*/
				dim_mat(file, &r_max, &c_max);

				matrice = (struct cella**)malloc(sizeof(struct cella *)*r_max);
				crea_mat(matrice, r_max, c_max);

				/*inizializza numeri a zero*/
				inizializza_zero(matrice, r_max, c_max);

				/*legge file e mette bome in matrice e scrive nbombe*/
				leggi_file(file, matrice, &n_bombe);

				fclose(file);

				/*inizializza tutto a zero e mette i numeri*/
				inizializza_mat(matrice, r_max, c_max);

				scelta_ai = stampa_chiedi_ai(ai, cols_ai, lines_ai);

				destroy_win(ai);
				if (!scelta_ai) {
					/*gioco*/
					continua_gioco = gioca_campo(campo, cols_campo, lines_campo, r_max , c_max, matrice, annullamento, &l_mosse, &n_mosse, &volte, n_bombe);
				} else {
					A_I(campo, matrice, r_max, c_max, cols_campo, lines_campo, &n_mosse, &volte, annullamento, n_bombe, &l_mosse);
				}

				distruggi_lista(&l_mosse);
				distruggi_mat(&matrice, r_max);

			}
		}
		else
			continua_gioco = 0;
	} while (continua_gioco);
	/*exit da menu*/
	destroy_win(menu);
	endwin(); /* Fine ncurses */

	return 0;
}