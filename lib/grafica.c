#include "libreria.h"

void stampa_titolo()
{
	char titolo[] = "   _______  _______  __   __  _______  _______    __   __  ___   __    _  _______  _______  _______ ";
	attron(COLOR_PAIR(2));
	mvprintw(1, COLS / 2 - strlen(titolo) / 2, "  _______  _______  __   __  _______  _______     __   __  ___   __    _  _______  _______  _______ \n");
	mvprintw(2, COLS / 2 - strlen(titolo) / 2, " |       ||   _   ||  |_|  ||       ||       |   |  |_|  ||   | |  |  | ||   _   ||       ||       |\n");
	mvprintw(3, COLS / 2 - strlen(titolo) / 2, " |       ||  |_|  ||       ||    _  ||   _   |   |       ||   | |   |_| ||  |_|  ||_     _||   _   |\n");
	mvprintw(4, COLS / 2 - strlen(titolo) / 2, " |       ||       ||       ||   |_| ||  | |  |   |       ||   | |       ||       |  |   |  |  | |  |\n");
	mvprintw(5, COLS / 2 - strlen(titolo) / 2, " |      _||       ||       ||    ___||  |_|  |   |       ||   | |  _    ||       |  |   |  |  |_|  |\n");
	mvprintw(6, COLS / 2 - strlen(titolo) / 2, " |     |_ |   _   || ||_|| ||   |    |       |   | ||_|| ||   | | | |   ||   _   |  |   |  |       |\n");
	mvprintw(7, COLS / 2 - strlen(titolo) / 2, " |_______||__| |__||_|   |_||___|    |_______|   |_|   |_||___| |_|  |__||__| |__|  |___|  |_______|\n");
	attroff(COLOR_PAIR(2));
	refresh();

	/*CREA IL BORDO*/
	box(stdscr, 0, 0);
	refresh();
}

void stampa_perso()
{
	char str1[] = " ::::::::   ::::::::   ::::::::  ::::    ::: :::::::::: ::::::::::: ::::::::::: ::::::::::: :::     ";
	char str2[] = "Premere ESC per uscire";
	int flag = 0;
	int i = 0;
	mvprintw(LINES / 2 + 5, COLS / 2 - strlen(str2) / 2, "%s", str2);
	refresh();

	nodelay(stdscr, TRUE);

	/*finchè non premo esc, blink della scritta*/
	while (!flag) {
		if (getch() == 27) {
			flag = 1;
		} else {
			napms(500); /*delay di blink*/
			if (i == 0)
				attron(A_DIM);
			else
				attron(A_BOLD);
			attron(COLOR_PAIR(1));
			mvprintw(LINES / 2 - 3, COLS / 2 - strlen(str1) / 2, " ::::::::   ::::::::   ::::::::  ::::    ::: :::::::::: :::::::::: ::::::::::: ::::::::::: :::     ");
			mvprintw(LINES / 2 - 2, COLS / 2 - strlen(str1) / 2, ":+:    :+: :+:    :+: :+:    :+: :+:+:   :+: :+:           :+:         :+:         :+:   :+: :+:   ");
			mvprintw(LINES / 2 - 1, COLS / 2 - strlen(str1) / 2, "+:+        +:+        +:+    +:+ :+:+:+  +:+ +:+           +:+         +:+         +:+  +:+   +:+  ");
			mvprintw(LINES / 2,     COLS / 2 - strlen(str1) / 2, "+#++:++#++ +#+        +#+    +:+ +#+ +:+ +#+ :#::+::#      +#+         +#+         +#+ +#++:++#++: ");
			mvprintw(LINES / 2 + 1, COLS / 2 - strlen(str1) / 2, "       +#+ +#+        +#+    +#+ +#+  +#+#+# +#+           +#+         +#+         +#+ +#+     +#+ ");
			mvprintw(LINES / 2 + 2, COLS / 2 - strlen(str1) / 2, "#+#    #+# #+#    #+# #+#    #+# #+#   #+#+# #+#           #+#         #+#         #+# #+#     #+# ");
			mvprintw(LINES / 2 + 3, COLS / 2 - strlen(str1) / 2, " ########   ########   ########  ###    #### ###        ##########     ###         ### ###     ### ");
			attroff(COLOR_PAIR(1));
			if (i == 0) {
				attroff(A_DIM);
				i++;
			}
			else {
				attroff(A_BOLD);
				i = 0;
			}
			refresh();
		}
	}
}

void stampa_vittoria()
{
	char str1[] = ":::    ::: ::::::::::: ::::::::::: ::::::::::: ::::::::  :::::::::  :::::::::::     :::   ";
	char str2[] = "Premere ESC per uscire";
	int i = 10;
	int flag = 0;
	mvprintw(LINES / 2 + 5, COLS / 2 - strlen(str2) / 2, "%s", str2);
	refresh();

	nodelay(stdscr, TRUE);

	/*finchè non clicco esc, cambia colore*/
	while (!flag) {
		if (getch() == 27) {
			flag = 1;
		} else {
			napms(400); /*delay del cambio*/
			attroff(A_BOLD);
			attron(COLOR_PAIR(i));
			mvprintw(LINES / 2 - 3, COLS / 2 - strlen(str1) / 2, ":::     ::: :::::::::: ::::::::::: ::::::::::: ::::::::  :::::::::  ::::::::::     :::   ");
			mvprintw(LINES / 2 - 2, COLS / 2 - strlen(str1) / 2, ":+:     :+:    :+:         :+:         :+:    :+:    :+: :+:    :+:    :+:       :+: :+:   ");
			mvprintw(LINES / 2 - 1, COLS / 2 - strlen(str1) / 2, "+:+     +:+    +:+         +:+         +:+    +:+    +:+ +:+    +:+    +:+      +:+   +:+  ");
			mvprintw(LINES / 2,     COLS / 2 - strlen(str1) / 2, "+#+     +:+    +#+         +#+         +#+    +#+    +:+ +#++:++#:     +#+     +#++:++#++: ");
			mvprintw(LINES / 2 + 1, COLS / 2 - strlen(str1) / 2, " +#+   +#+     +#+         +#+         +#+    +#+    +#+ +#+    +#+    +#+     +#+     +#+ ");
			mvprintw(LINES / 2 + 2, COLS / 2 - strlen(str1) / 2, "  #+#+#+#      #+#         #+#         #+#    #+#    #+# #+#    #+#    #+#     #+#     #+# ");
			mvprintw(LINES / 2 + 3, COLS / 2 - strlen(str1) / 2, "    ###     ##########     ###         ###     ########  ###    ### ########## ###     ### ");
			attroff(COLOR_PAIR(i));
			attroff(A_BOLD);
			if (i == 15)
				i = 10;
			else
				i++;
			refresh();
		}
	}
}

void stampa_comandi_stdr(int r_max, int c_max, int n_bombe, int n_mosse)
{
	char str2[] = "(E) TORNA AL MENU";

	mvprintw(LINES / 2 - 10, COLS - 23, "RIGHE:  %d   ", r_max);

	mvprintw(LINES / 2 - 7, COLS - 24, "COLONNE:  %d   ", c_max);

	mvprintw(LINES / 2 - 4, COLS - 23, "BOMBE:  %d     ", n_bombe);

	mvprintw(LINES / 2 , COLS - 30, "MOSSE DA ANNULLARE:  %d    ", n_mosse);

	mvprintw(LINES / 2 + 5, COLS - 10 - strlen(str2), "%s", str2);
}

void destroy_win(WINDOW * local_win)
{
	werase(local_win);
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	erase();
	stampa_titolo();
}

int gioca_altre_scelte(WINDOW *local_win, int height, int width)
{

	int fine = 0;
	int scelta = 0;
	int c;

	char *menu_str[] = {
		"FACILE",
		"MEDIO",
		"DIFFICILE",
		"TORNA INDIETRO"
	};

	do {
		print_altre_scelte(local_win, scelta, height, width, menu_str);
		c = getch();
		if (c == KEY_UP && scelta >= 0)
			if (scelta == 0)
				scelta = 3;
			else
				scelta--;
		else if (c == KEY_DOWN && scelta <= 3)
			if (scelta == 3)
				scelta = 0;
			else
				scelta++;
		else if (c == '\n') {
			/*clicco invio su una scelta*/
			if (scelta == 3 || c == 27)
				/*ESCI*/
				fine = 1;
			return scelta;
		}
	} while (c != 27 && !fine);

	return 4;
}

void print_altre_scelte(WINDOW* win, int highlight, int x_max, int y_max, char **menu_str)
{
	char str[] = " MODALITA' ";
	int i, n, x, y;

	box(win, 0, 0); /*stampa la box menu*/

	mvwprintw(win, 0, y_max / 2 - strlen(str) / 2, "%s", str);
	wrefresh(win);

	for (i = 0; i < 4; i++)	{
		wattron(win, COLOR_PAIR(1));

		if (i == 0)				/*dove far stampare le tre stringhe*/
			n = -2;
		else if (i == 1)
			n = 0;
		else if (i == 2)
			n = 2;
		else
			n = 6;

		x = x_max / 2 + n;
		y = (y_max - strlen(menu_str[i])) / 2;  /*ora so dove stamparli*/

		if (highlight == i ) {
			wattroff(win, COLOR_PAIR(1));
			wattron(win, COLOR_PAIR(3));
			mvwprintw(win, x, y, "%s", menu_str[i]);
			wattroff(win, COLOR_PAIR(3));
		}
		else
			mvwprintw(win, x, y, "%s", menu_str[i]);

		wattroff(win, COLOR_PAIR(1));
	}

	wrefresh(win);
}


int gioca_menu(WINDOW *local_win, int height, int width)
{

	int fine = 0;
	int scelta = 0;
	int c;

	char *menu_str[] = {
		"GENERA CAMPO",
		"CARICA CAMPO SALVATO",
		"ALTRE OPZIONI",
		"ESCI"
	};

	do {
		print_menu(local_win, scelta, height, width, menu_str);
		c = getch();
		if (c == KEY_UP && scelta >= 0)
			if (scelta == 0)
				scelta = 3;
			else
				scelta--;
		else if (c == KEY_DOWN && scelta <= 3)
			if (scelta == 3)
				scelta = 0;
			else
				scelta++;
		else if (c == '\n') {
			/*clicco invio su una scelta*/
			if (scelta == 3 || c == 27)
				/*ESCI*/
				fine = 1;
			else
				return scelta; /*0 genera, 1 carica campo*/
		}
	} while (c != 27 && !fine);

	return 5; /*deve uscire dal gioco!*/
}

void print_menu(WINDOW* win, int highlight, int x_max, int y_max, char **menu_str)
{
	char str[] = " MENU ";
	int i, n, x, y;

	box(win, 0, 0); /*stampa la box menu*/

	wattron(win, COLOR_PAIR(4));
	mvwprintw(win, 0, y_max / 2 - strlen(str) / 2, "%s", str);
	wrefresh(win);
	wattroff(win, COLOR_PAIR(4));

	for (i = 0; i < 4; i++)	{
		wattron(win, COLOR_PAIR(1));

		if (i == 0)					/*dove far stampare le tre stringhe*/
			n = -2;
		else if (i == 1)
			n = 0;
		else if (i == 2)
			n = 2;
		else
			n = 6;

		x = x_max / 2 + n;
		y = y_max / 2 - strlen(menu_str[i]) / 2;  /*ora so dove stamparli*/

		if (highlight == i ) {
			wattroff(win, COLOR_PAIR(1));
			wattron(win, COLOR_PAIR(3));
			mvwprintw(win, x, y, "%s", menu_str[i]);
			wattroff(win, COLOR_PAIR(3));
		}
		else
			mvwprintw(win, x, y, "%s", menu_str[i]);

		wattroff(win, COLOR_PAIR(1));
	}

	wrefresh(win);
}

/*VERA FUNZIONE DI GIOCO*/
int gioca_campo(WINDOW *local_win, int col_campo, int lin_campo, int r_max, int c_max, struct cella** mat, WINDOW *wannulla, tlista *l, int* m_annulla, int *volte, int n_bombe)
{

	int fine = 0; /*per finire il gioco*/
	int r = 0; /*riga e colonna che considero*/
	int c = 0;
	int tasto_premuto;
	int vinto;

	wrefresh(local_win);

	do {
		/*DEBUG
		stampa_mat(mat, r_max, c_max);
		stampa_lista(*l);
		*/

		/*check se è finito il gioco*/
		vinto = vittoria(mat, r_max, c_max);
		if (vinto == 1) {
			/*STAMPA VITTORIA*/
			destroy_win(local_win);
			refresh();
			stampa_vittoria();
			fine = 1;
		} else {
			/*debug*/
			/*stampa_lista(*l);*/
			stampa_comandi_stdr(r_max, c_max, n_bombe, *m_annulla);
			stampa_campo(local_win, col_campo, lin_campo, r, c, r_max, c_max, mat);

			tasto_premuto = getch();

			if (tasto_premuto == KEY_UP) {
				/*sposto su se riga>0*/
				if (r > 0) {
					r--;
				}
			}
			else if (tasto_premuto == KEY_DOWN) {
				/*sposto giù se riga<rmax-1*/
				if (r < r_max - 1 ) {
					r++;
				};
			}
			else if (tasto_premuto == KEY_LEFT) {
				/*sposto sinistra se c>0*/
				if (c > 0) {
					c--;
				}
			}
			else if (tasto_premuto == KEY_RIGHT) {
				/*sposto destra se c<cmax-1*/
				if (c < c_max - 1) {
					c++;
				}
			}
			else if (tasto_premuto == '1') {
				/*CLICK PER SCOPRIRE*/
				int ris, ann;
				if (mat[r][c].visibile == 0) {
					push(l, r, c); /*push della mossa in lista*/

					ris = scopri(mat, r , c , r_max, c_max);
					if (ris == 2) {
						/*HO CLICCATO BOMBA!*/
						if (*m_annulla > 0) { /*chiedo di annullare*/
							ris = stampa_annulla(wannulla, 50, 15, *volte);
							if (ris) {
								/*scelto di annullare*/
								ann = annulla_mossa(l, m_annulla, volte, mat, r_max, c_max);
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
				}
			}
			else if (tasto_premuto == '2') {

				/**qui clicco con 2*/
				bandiera(mat, r , c);
			}
			else if (tasto_premuto == 'E' || tasto_premuto == 'e' || tasto_premuto == 27) {
				/*CLICCO PER USCIRE*/
				destroy_win(local_win);

				fine = 1;
			}
		}
	} while (!fine);

	return -1;
}

void stampa_campo(WINDOW * win, int col_campo, int lin_campo, int scelta_i, int scelta_j, int r_max, int c_max, struct cella** mat)
{
	int i, j;
	int lin, col1, col; /*linea e col dove inizia la stampa*/

	wattron(win, COLOR_PAIR(6)); /*colore rosso*/
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(6));
	wrefresh(win);

	/*dove inizia stampa del campo*/
	lin = lin_campo / 2 - r_max / 2;
	col1 = col_campo / 2 - c_max * 2 ;
	wattroff(win, A_BOLD);
	wattroff(win, A_DIM);
	wattron(win, A_REVERSE);

	for (i = 0; i < r_max; i++) {
		col = col1;
		wrefresh(win);
		for (j = 0; j < c_max; j++) {
			if (scelta_i == i && scelta_j == j) { /*cella selezionata*/
				wattron(win, A_BOLD);
				wattron(win, COLOR_PAIR(4));
				if (mat[i][j].bandiera == 1) {

					wattron(win, COLOR_PAIR(2));
					mvwprintw(win, lin, col, "[*]"); /*bandiera*/
					wattroff(win, COLOR_PAIR(2));

					wrefresh(win);
				}
				else if (mat[i][j].visibile == 0) {
					mvwprintw(win, lin, col, "[ ]"); /*non visibile*/
					wrefresh(win);
				}
				else if (mat[i][j].numero == -1) {
					mvwprintw(win, lin, col, "[B]"); /*bomba*/
					wrefresh(win);
				}
				else if (mat[i][j].numero != 0) {
					/*stampa numero della matrice*/
					mvwprintw(win, lin, col, "[%d]", mat[i][j].numero); /*scopro numero*/
					wrefresh(win);
				}
				else {
					wattroff(win, A_REVERSE);
					mvwprintw(win, lin, col, "[ ]"); /*scopro numero ma è 0*/
					wrefresh(win);
					wattron(win, A_REVERSE);
				}
				wattroff(win, A_BOLD);
				wattroff(win, COLOR_PAIR(4));
			}/* fine selezionata*/
			else { /*tutte le altre*/
				if (mat[i][j].bandiera == 1) {
					wattron(win, COLOR_PAIR(2));
					mvwprintw(win, lin, col, "[*]");/*bandiera*/
					wattroff(win, COLOR_PAIR(2));
					wrefresh(win);
				}
				else if (mat[i][j].visibile == 0) {
					mvwprintw(win, lin, col, "[ ]"); /*non visibile*/
					wrefresh(win);
				}
				else if (mat[i][j].numero == -1) {
					mvwprintw(win, lin, col, "[B]"); /*bomba visibile*/
					wrefresh(win);
				}
				else if (mat[i][j].numero != 0) {
					/*stampa numero della matrice*/
					mvwprintw(win, lin, col, "[%d]", mat[i][j].numero); /*scopro numero*/
					wrefresh(win);
				}
				else {
					wattroff(win, A_REVERSE);
					mvwprintw(win, lin, col, "[ ]"); /*scopro numero*/
					wrefresh(win);
					wattron(win, A_REVERSE);
				}
			}
			wrefresh(win);
			col += 4;
		}/*J*/
		wrefresh(win);
		lin++;
	}/*I*/
	wattroff(win, A_REVERSE);
}

void generazione(WINDOW * win, int col_genera, int lin_genera, int *r_max, int *c_max, int* n_bombe, int lines_campo, int col_campo)
{
	char str1[] = "Inserire RIGHE (max   ):";
	char str2[] = "Inserire COLONNE (max   ):";
	char str3[] = "Inserire numero di bombe:";
	curs_set(1);
	echo();

	wattron(win, COLOR_PAIR(4));
	box(win, 0, 0);
	wattroff(win, COLOR_PAIR(4));


	mvwprintw(win, 4, (col_genera - strlen(str1)) / 2, "Inserire RIGHE (max %d):", (lines_campo) - 2);
	mvwprintw(win, 8, (col_genera - strlen(str2)) / 2, "Inserire COLONNE (max %d):", (col_campo / 4) - 1);

	mvwprintw(win, 14, (col_genera - strlen(str3)) / 2, "%s", str3);

	do {
		wrefresh(win);
		mvwscanw(win, 6, col_genera / 2, "%d", r_max);
		mvwscanw(win, 10, col_genera / 2, "%d", c_max);
		if (*r_max > (lines_campo) - 2 || *c_max > (col_campo / 4) - 1) {
			mvwprintw(win, 6, col_genera / 2, "                 ");
			mvwprintw(win, 10, col_genera / 2, "                 ");
			wattron(win, COLOR_PAIR(1));
			mvwprintw(win, 11, col_genera / 2 - 9, "OPZIONE NON VALIDA");
			wattroff(win, COLOR_PAIR(1));
		}
		else
			mvwprintw(win, 11, col_genera / 2 - 9, "                   ");
	} while (*r_max > (lines_campo) - 2 || *c_max > (col_campo / 4) - 1 );


	do {
		mvwscanw(win, 16, col_genera / 2, "%d", n_bombe);
		if (*n_bombe > (*c_max) * (*r_max) - 1) {
			mvwprintw(win, 16, col_genera / 2, "                 ");
			wattron(win, COLOR_PAIR(1));

			if ((*c_max) * (*r_max) != 1)
				mvwprintw(win, 18, col_genera / 2 - 9, "MASSIMO %d BOMBE", (*c_max) * (*r_max));
			else
				mvwprintw(win, 18, col_genera / 2 - 7, "MASSIMO 1 BOMBA");

			wattroff(win, COLOR_PAIR(1));

		}
	} while (*n_bombe > (*c_max) * (*r_max));

	wrefresh(win);
	noecho();
	curs_set(0);
	wrefresh(win);
}

int stampa_annulla(WINDOW * win, int col_annulla, int lin_annulla, int mosse_da_annullare)
{
	char *annulla_str[] = {
		"HAI TROVATO UNA BOMBA!",
		"Annullare le ultime  mosse?",
		"Annullare l'ultima mossa?"
	};

	char *str[] = {
		"NO",
		"SI"
	};
	int c, selezionato = 1, fine = 0;

	wattron(win, COLOR_PAIR(1));
	wattron(win, A_REVERSE);
	box(win, 0, 0);
	wattroff(win, A_REVERSE);
	wattroff(win, COLOR_PAIR(1));

	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 4, ((col_annulla - strlen(annulla_str[0])) / 2) - 2, "%s", annulla_str[0]);
	wattroff(win, COLOR_PAIR(1));

	/*titolo della box*/
	if (mosse_da_annullare == 1) {
		mvwprintw(win, 7, ((col_annulla - strlen(annulla_str[2])) / 2) - 2, "%s", annulla_str[2]);

	} else {
		mvwprintw(win, 7, ((col_annulla - strlen(annulla_str[1])) / 2 ) - 2, "Annullare le ultime %d mosse? ", mosse_da_annullare);
	}
	wrefresh(win);

	/*scelta se annullare o no*/
	do {
		stampa_scelte_annulla(win, selezionato, col_annulla, lin_annulla , str);
		c = getch();
		if (c == KEY_RIGHT) {
			if (selezionato == 0)
				selezionato = 1;
		}
		else if (c == KEY_LEFT) {
			if (selezionato == 1)
				selezionato = 0;
		}
		else if (c == '\n') {
			fine = 1;
			destroy_win(win);
			return selezionato;
		}
	} while (c != 21 && !fine);
	return 5;
}

void stampa_scelte_annulla(WINDOW * win, int highlight, int col_max, int lin_max, char **annulla_str)
{
	int i, col, lin;

	lin = lin_max - 4;

	for (i = 0; i <= 1; i++)	{
		if (i == 0)					/*dove far stampare le tre stringhe*/
			col = 2;
		else if (i == 1)
			col = col_max - 11;

		if (highlight == i ) {
			wattron(win, A_REVERSE);
			mvwprintw(win, lin, col, "%s", annulla_str[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, lin, col, "%s", annulla_str[i]);
	}

	wrefresh(win);
}

void stampa_chiedi_annullare(WINDOW * win, int col_chiedi, int lin_chiedi, int*mosse_annullare)
{
	char str1[] = "Quante mosse vuoi annullare al massimo?";

	curs_set(1);
	echo();

	box(win, 0, 0);

	mvwprintw(win, lin_chiedi / 2 - 1, (col_chiedi - strlen(str1)) / 2, "%s", str1);
	mvwscanw(win, lin_chiedi / 2 + 1, col_chiedi / 2, "%d", mosse_annullare);

	noecho();
	curs_set(0);
	wrefresh(win);
}

int stampa_chiedi_ai(WINDOW * win, int col_ai, int lin_ai)
{
	char *scelte[] = {
		"NO",
		"SI"
	};
	char str1[] = "Vuoi far giocare l'Intelligenza Artificiale?";
	int selezionato = 0;
	int c;
	int fine = 0;

	box(win, 0, 0);

	mvwprintw(win, lin_ai / 2 - 1, (col_ai - strlen(str1)) / 2, "%s", str1);
	do {
		stampa_scelte_ai(win, selezionato, col_ai, lin_ai, scelte);
		c = getch();
		if (c == KEY_RIGHT) {
			if (selezionato == 0)
				selezionato = 1;
		}
		else if (c == KEY_LEFT) {
			if (selezionato == 1)
				selezionato = 0;
		}
		else if (c == '\n') {
			fine = 1;
			return selezionato;
		}
	} while (c != 21 && !fine);
	wrefresh(win);

	return -1;
}


void stampa_scelte_ai(WINDOW * win, int highlight, int col_max, int lin_max, char **scelte)
{

	int i, col, lin;

	lin = lin_max - 4;

	for (i = 0; i <= 1; i++)	{
		if (i == 0)					/*dove far stampare le tre stringhe*/
			col = 4;
		else if (i == 1)
			col = col_max - 6;

		if (highlight == i ) {
			wattron(win, A_REVERSE);
			mvwprintw(win, lin, col, "%s", scelte[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, lin, col, "%s", scelte[i]);
	}

	wrefresh(win);
}
