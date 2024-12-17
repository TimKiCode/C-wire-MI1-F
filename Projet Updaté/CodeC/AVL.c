#include "AVL.h"

Station* creerStation(int id, long cap, long conso){
  Station* s=malloc(sizeof(Station));
  if(s==NULL){
    printf("probleme d'allocation");
    exit(1);
  }
  s->Id=id;
  s->capacite=cap;
  s->consommation=conso;
  s->diff=s->capacite-s->consommation;
  s->eq=0;
  s->fg=NULL;
  s->fd=NULL;
  return s;
}

Station* recherche(Station *st, int id){
  if(st==NULL){
    //printf("cette station n'existe pas\n");
    return NULL;
  }
  else if(id==st->Id){
    return st;
  }
  else if(id<st->Id){
    return recherche(st->fg,id);
  }
  return recherche(st->fd, id);
}

void libererStation(Station* a) {
    if (a != NULL) {
        libererStation(a->fg);
        libererStation(a->fd);
        free(a);
    }
}

int min(int a,int b){
  if(a<b){
    return a;
  }
  return b;
}

int max(int a,int b){
  if(a<b){
    return b;
  }
  return a;
}
int max3(int a,int b,int c){
  if(a<b && c<b){
    return b;
  }
  else if(a<c && b<c){
    return c;
  }
  return a;
}

int min3(int a,int b,int c){
  if(a>b && c>b){
    return b;
  }
  else if(a>c && b>c){
    return c;
  }
  return a;
}

Station* rotationGauche(Station* st){
  Station* pivot = st->fd; 
  int eq_st, eq_p;

  st->fd = pivot->fg; 
  pivot->fg = st;     
  eq_st=st->eq;
  eq_p = pivot->eq;
  st->eq = eq_st - max(eq_p, 0) - 1;
  pivot->eq = min3(eq_st - 2, eq_st + eq_p - 2, eq_p - 1);

  return pivot; 
}
Station* rotationDroite(Station* st){
  Station* pivot = st->fg; 
  int eq_st, eq_p;

  st->fg = pivot->fd; 
  pivot->fd = st;     
  eq_st = st->eq;
  eq_p = pivot->eq;

  st->eq = eq_st - min(eq_p, 0) + 1;
  pivot->eq = max3(eq_st + 2, eq_st + eq_p + 2, eq_p + 1);

  return pivot; 
}

Station* doubleRotationGauche(Station* a){
  a->fd = rotationDroite(a->fd);
  return rotationGauche(a);
}

Station* doubleRotationDroite(Station* a){
  a->fg = rotationGauche(a->fg);
  return rotationDroite(a);
}

Station* equilibrerStation(Station* a){
  if (a->eq >= 2){ 
    if (a->fd->eq >= 0){
      return rotationGauche(a);
    }
    else{
      return doubleRotationGauche(a); 
    }
  }
  else if (a->eq <= -2){
    if (a->fg->eq <= 0){
      return rotationDroite(a); 
    }
    else{
      return doubleRotationDroite(a); 
    }
  }
  return a;
}

Station* insertionStation(Station * a, int id,long cap,long conso, int *h)
{
    if (a == NULL)
    {           // Si l'arbre est vide, crée un nouveau nœud
        *h = 1; // La hauteur a augmenté
        a=creerStation(id,cap,conso);
        return a;
    }
    else if (id < a->Id){ 
        a->fg = insertionStation(a->fg, id,cap,conso, h);
        *h = -*h;
    }
    else if (id > a->Id) { 
        a->fd = insertionStation(a->fd, id,cap,conso, h);
    }
    else{ 
        *h = 0;
        return a;
    }

    if (*h != 0){
        a->eq += *h;
        a=equilibrerStation(a);
        if(a->eq==0){
           *h=0;
        }
        else{
           *h=1;
        }
    }
    return a;
}



int sommetot(Station *a) { // Calcule la somme des consommations totales
    if (a == NULL) {
        return 0;
    }
    // Debug pour vérifier la consommation de chaque station
    //printf("Station %d, consommation %ld\n", a->Id, a->consommation);
    return a->consommation + sommetot(a->fg) + sommetot(a->fd);
}

void ajoutConso(Station *a, int id, long conso) {
    if (a == NULL) return;
    if (id == a->Id) {
        a->consommation += conso; // Ajouter la consommation
        a->diff = a->capacite - a->consommation; // Recalculer la différence
    } else if (id < a->Id) {
        ajoutConso(a->fg, id, conso);
    } else {
        ajoutConso(a->fd, id, conso);
    }
}


void afficheStationPrefixe(Station*a){
  if(a!=NULL){
    printf("%d %ld %ld %ld\n",a->Id,a->capacite,a->consommation,a->diff);
    afficheStationPrefixe(a->fg);
    afficheStationPrefixe(a->fd);
  }
}
