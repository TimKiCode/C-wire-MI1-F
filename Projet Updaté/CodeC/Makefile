all: exec
	
fichier.o: fichier.c fichier.h
	gcc -c fichier.c -o fichier.o

AVL.o: AVL.c AVL.h
	gcc -c AVL.c -o AVL.o

main.o : main.c fichier.h
	gcc -c main.c -o main.o
	
exec: main.o fichier.o AVL.o
	gcc main.o fichier.o AVL.o -o exec
	
clean:
	rm -f *.o
	rm -f exec
