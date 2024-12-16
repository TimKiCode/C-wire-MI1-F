#include <stdio.h>
#include "fichier.h"

int main(int argc, char**argv) {

    	Station *a = NULL; // Initialisation de l'arbre à NULL
    	int *h = malloc(sizeof(int));
    	if (h == NULL) {
        	fprintf(stderr, "Erreur : Allocation mémoire échouée\n");
        	exit(1);
    	}
    	*h = 1;
    	if (argv[1]== NULL) {
        	fprintf(stderr, "Erreur : Allocation mémoire échouée\n");
        	exit(1);
    	}
 	FILE*f=NULL;
    	a = recupDonnee(a, h, argv[1]); // Charger les données
    	if (a == NULL) {
        	fprintf(stderr, "Erreur : Aucun arbre n'a été créé, vérifiez vos données d'entrée.\n");
        	free(h);
        
        	return 1; // Sortir avec un code d'erreur
    	}
        //char *b;
	//b="tmp.txt";
    	printf("La somme totale des consommations est : %d\n", sommetot(a));
    	f=ecrireStationDansFichier(a, argv[2]); // Écrire les données dans un fichier

    	libererStation(a); // Libérer la mémoire de l'arbre
    	free(h);           // Libérer la mémoire pour `h`

    	return 0;
}
