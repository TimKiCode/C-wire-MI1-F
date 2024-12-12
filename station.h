#ifndef STATION_H
#define STATION_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


typedef struct Station{
  int Id;
  int capacite;
  int consommation;
  int diff;
  int eq;
  struct Station* fg;
  struct Station* fd;
}Station;
#include "fichier.h"
#include "AVL.h"

#endif
