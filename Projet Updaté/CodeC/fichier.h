#ifndef FICHIER_H
#define FICHIER_H
#include "AVL.h"
#include "station.h"


Station* recupDonnee(Station *a, int *h, char *nom);
void ecrireStationRecursif(FILE* fichier, Station* a);
FILE* ecrireStationDansFichier(Station* a,char*n);

#endif
