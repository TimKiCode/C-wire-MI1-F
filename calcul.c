#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct Station{
  int Id;
  int capacite;
  int consommation;
  int eq;
  struct Station* fg;
  struct Station* fd;
}Station;

Station* creerStation(int id, int cap, int conso){
  Station* s=malloc(sizeof(Station));
  if(s==NULL){
    printf("probleme d'allocation");
    exit(1);
  }
  s->Id=id;
  s->capacite=cap;
  s->consommation=conso;
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
  if(id<st->Id){
    recherche(st->fg,id);
  }
  else if(id>st->Id){
    recherche(st->fd, id);
  }
  else if(id==st->Id){
    return st;
  }
  return 0;
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
  int eq_st = st->eq, eq_p = pivot->eq;

  st->fd = pivot->fg; 
  pivot->fg = st;     

  st->eq = eq_st - max(eq_p, 0) - 1;
  pivot->eq = min3(eq_st - 2, eq_st + eq_p - 2, eq_p - 1);

  return pivot; 
}
Station* rotationDroite(Station* st){
  Station* pivot = st->fg; 
  int eq_st = st->eq, eq_p = pivot->eq;

  st->fg = pivot->fd; 
  pivot->fd = st;     


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

Station* insertionStation(Station * a, int id,int cap,int conso, int *h)
{
    if (a == NULL)
    {           // Si l'arbre est vide, crée un nouveau nœud
        *h = 1; // La hauteur a augmenté
        a=creerStation(id,cap,conso);
        return a;
    }
    else if (id < a->Id)
    { // Si l'élément est plus petit, insérer à gauche
        a->fg = insertionStation(a->fg, id,cap,conso, h);
        *h = -*h; // Inverse l'impact de la hauteur
    }
    else if (id > a->Id)
    { // Si l'élément est plus grand, insérer à droite
        a->fd = insertionStation(a->fd, id,cap,conso, h);
    }
    else
    { // Élément déjà présent
        *h = 0;
        return a;
    }

    // Mise à jour du facteur d'équilibre et rééquilibrage si nécessaire
    if (*h != 0)
    {
        a->eq += *h;
        a = equilibrerStation(a);
        *h = (a->eq == 0) ? 0 : 1; // Mise à jour de la hauteur
    }
    return a;
}



int sommetot(Station*a){ //calcule la somme des consommations totales
 if(a==NULL){
  return 0;
 }
 return a->consommation+sommetot(a->fg)+sommetot(a->fd);
}

void ajoutConso(Station*a,int id,int conso){
  if(id==a->Id){
    a->consommation+=conso;
  }
  else if(id<a->Id){
    ajoutConso(a->fg, id, conso);
  }
  else{
    ajoutConso(a->fd, id, conso);
  }
}


Station* recupDonnee(int *h){
  char nom[100];
  printf("entrer le nom du ficher : ");
  scanf("%50s", nom);
  FILE*fichier=fopen(nom,"r+");
  if(fichier==NULL){
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno );
    exit(1);
  }
  ;
  Station*a=malloc(sizeof(Station));
  int id, capacite,conso;
  while(fscanf(fichier,"%d %d %d",&id, &capacite,&conso)==3){
    if(recherche(a,id)==NULL){
      a=insertionStation(a, id, capacite,conso, h);
    }
    else{
      ajoutConso(a, id, conso);
    
    printf("%d %d %d\n",id,capacite,conso);
    }
  }
  return a;
  fclose(fichier);
}

void afficheStationPrefixe(Station*a){
  if(a!=NULL){
    printf("%d %d %d\n",a->Id,a->capacite,a->consommation);
    afficheStationPrefixe(a->fg);
    afficheStationPrefixe(a->fd);
  }
}

int main(){
  Station*a=malloc(sizeof(Station));
  a=creerStation(5,10,0);
  int*h=malloc(sizeof(int));
  *h=1;
  
  a=recupDonnee(h);
  afficheStationPrefixe(a);
  printf("la somme totale des consommations est : %d\n",sommetot(a));
  return 0;
}
