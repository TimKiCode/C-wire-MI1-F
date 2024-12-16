#ifndef AVL_H
#define AVL_H
#include "station.h"

Station* creerStation(int id, long cap, long conso);
Station* recherche(Station *st, int id);
int min(int a,int b);
int max(int a,int b);
int max(int a,int b);
int max3(int a,int b,int c);
int min3(int a,int b,int c);
Station* rotationGauche(Station* st);
Station* rotationDroite(Station* st);
Station* doubleRotationGauche(Station* a);
Station* doubleRotationDroite(Station* a);
Station* equilibrerStation(Station* a);
Station* insertionStation(Station * a, int id,long cap,long conso, int *h);
int sommetot(Station *a);
void libererStation(Station* a);
void afficheStationPrefixe(Station*a);
void ajoutConso(Station *a, int id, long conso);
#endif
