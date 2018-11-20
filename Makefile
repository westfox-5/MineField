install : dir main prepartita gioco grafica
	gcc -pedantic -std=gnu89 -Wall dist/comp/main.o dist/comp/prepartita.o dist/comp/gioco.o dist/comp/grafica.o -o dist/campo -lncurses
	make clean

dir : 
	mkdir -p dist/comp/

main : main.c lib/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall main.c -o dist/comp/main.o

prepartita : lib/prepartita.c lib/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall lib/prepartita.c -o dist/comp/prepartita.o

gioco : lib/gioco.c lib/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall lib/gioco.c -o dist/comp/gioco.o

grafica : lib/grafica.c lib/libreria.h
	gcc -c -pedantic -std=gnu89 -Wall lib/grafica.c -o dist/comp/grafica.o

clean :
	rm -r dist/comp