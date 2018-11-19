install : main.o librerie/prepartita.o librerie/gioco.o librerie/grafica.o
	gcc -pedantic -std=gnu89 -Wall main.o librerie/prepartita.o librerie/gioco.o librerie/grafica.o -o dist/campo -lncurses

main.o : main.c librerie/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall main.c -o dist/comp/main.o

prepartita : librerie/prepartita.c librerie/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall prepartita.c -o dist/comp/prepartita.o

gioco : librerie/gioco.c librerie/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall gioco.c -o dist/comp/gioco.o

grafica : librerie/grafica.c librerie/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall grafica.c -o dist/comp/grafica.o

clean :
	rm -r dist