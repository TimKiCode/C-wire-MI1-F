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

Station* creerStation(int id, int cap, int conso){
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
    recherche(st->fg,id);
  }
  recherche(st->fd, id);
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

Station* insertionStation(Station * a, int id,int cap,int conso, int *h)
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



int sommetot(Station*a){ //calcule la somme des consommations totales
 if(a==NULL){
  return 0;
 }
 return a->consommation+sommetot(a->fg)+sommetot(a->fd);
}

void ajoutConso(Station*a,int id,int conso){
  if(id==a->Id){
    a->consommation+=conso;
    a->diff=a->capacite-a->consommation;
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
      a=equilibrerStation(a);
    }
    else{
      ajoutConso(a, id, conso);
    }
  }
  return a;
  fclose(fichier);
}

void ecrireStation(Station*st){
  char* f = malloc(sizeof(char) * 50);
  printf("nom de la station: ");
  char nom[100];
  scanf("%25s",nom);
  sprintf(f, "%s.txt", nom);
  FILE* fichier = NULL;
  //Ouverture du fichier en mode ajout
  fichier = fopen(f, "a");
  if (fichier == NULL) {
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno );
    exit(1);

  }
  else{
    //Fermeture du fichier
    fclose(fichier);
    //Ouverture du fichier en mode écriture
    fichier = fopen(f, "w");
    if (fichier == NULL) {
      printf("Ouverture du fichier impossible\n");
      printf("code d'erreur = %d \n", errno );

    }
    else{
      if(st!=NULL){
      	fprintf(fichier,"%d %d %d %d\n",st->Id,st->capacite,st->consommation,st->diff);
      	/*ecrireStation(st->fg);
      	ecrireStation(st->fd);*/
      }
    }
   }
   free(f);
   fclose(fichier);
}


void afficheStationPrefixe(Station*a){
  if(a!=NULL){
    printf("%d %d %d %d\n",a->Id,a->capacite,a->consommation,a->diff);
    afficheStationPrefixe(a->fg);
    afficheStationPrefixe(a->fd);
  }
}

int main(){
  Station*a=malloc(sizeof(Station));

  int*h=malloc(sizeof(int));
  *h=1;
  
  a=recupDonnee(h);
  afficheStationPrefixe(a);
  printf("la somme totale des consommations est : %d\n",sommetot(a));
  ecrireStation(a);
  /*a=insertionStation(a,11,5,2,h);
  a=insertionStation(a,16,5,21,h);
  a=insertionStation(a,18,15,256,h);
  a=insertionStation(a,11,5,2,h);
  a=insertionStation(a,20,45,23,h);
  afficheStationPrefixe(a);*/
  free(h);
  free(a);
  return 0;
}
