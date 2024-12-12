#include "fichier.h"



Station* recupDonnee(Station *a, int *h, char *nom) {
    FILE *fichier = fopen(nom, "r+"); 
    if (fichier == NULL) {
        printf("Ouverture du fichier impossible\n");
        printf("Code d'erreur = %d\n", errno);
        exit(1);
    }
    int id;
    long capacite;
    long conso;

    // Lecture ligne par ligne du fichier
    while (fscanf(fichier, "%d %ld %ld", &id, &capacite, &conso) == 3) {
        printf("Ligne lue : id=%d, capacite=%ld, conso=%ld\n", id, capacite, conso); // Debug
        if (id != 0 && capacite != 0) {
                a = insertionStation(a, id, capacite, conso, h);
                }
            else {
                ajoutConso(a, id, conso);
            }

    }

    fclose(fichier); // Toujours fermer le fichier après la lecture
    return a;        // Retourner l'arbre construit (peut être NULL si aucune station n'a été insérée)
}


void ecrireStationRecursif(FILE* fichier, Station* a) {
    if(fichier==NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur = %d \n", errno );
        exit(1);
    }
    if (a == NULL) {
        return;
    }
    fprintf(fichier, "%d %ld %ld %ld\n", a->Id,a->capacite,a->consommation,a->diff);
    
    if (a->fg != NULL) {
        ecrireStationRecursif(fichier, a->fg);
    }
    
    if (a->fd != NULL) {
        ecrireStationRecursif(fichier, a->fd);
    }
}


FILE* ecrireStationDansFichier(Station* a,char*n) {
    if (a == NULL) {
        fprintf(stderr, "Erreur : La station est NULL.\n");
        return NULL;
    }
    char*nom=malloc(sizeof(char)*50);
    if(nom==NULL){
    	exit(1);
    }
    sprintf(nom,"calc_%s",n);
    FILE* fichier = fopen(nom, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    ecrireStationRecursif(fichier, a);

    
    fclose(fichier);
    printf("Les données de la station et de ses sous-arbres ont été écrites dans le fichier '%s'.\n", nom);
    return fichier;

}


