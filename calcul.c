#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct Station{
  int Id;
  long capacite;
  long consommation;
  long diff;
  int eq;
  struct Station* fg;
  struct Station* fd;
}Station;

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
    printf("Station %d, consommation %ld\n", a->Id, a->consommation);
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


Station* recupDonnee(Station *a, int *h, char *nom) {
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s.txt", nom); // Construction du chemin du fichier
    FILE *fichier = fopen(filepath, "r+"); 
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


void ecrireStationDansFichier(Station* a,char*n) {
    if (a == NULL) {
        fprintf(stderr, "Erreur : La station est NULL.\n");
        return;
    }
    char*nom=malloc(sizeof(char)*50);
    if(nom==NULL){
    	exit(1);
    }
    sprintf(nom,"%s_calc.txt",n);
    FILE* fichier = fopen(nom, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    ecrireStationRecursif(fichier, a);

    
    fclose(fichier);
    printf("Les données de la station et de ses sous-arbres ont été écrites dans le fichier '%s'.\n", nom);
}



void afficheStationPrefixe(Station*a){
  if(a!=NULL){
    printf("%d %ld %ld %ld\n",a->Id,a->capacite,a->consommation,a->diff);
    afficheStationPrefixe(a->fg);
    afficheStationPrefixe(a->fd);
  }
}

int main() {
    Station *a = NULL; // Initialisation de l'arbre à NULL
    int *h = malloc(sizeof(int));
    if (h == NULL) {
        fprintf(stderr, "Erreur : Allocation mémoire échouée\n");
        exit(1);
    }
    *h = 1;

    char *nom = malloc(sizeof(char) * 50);
    if (nom == NULL) {
        fprintf(stderr, "Erreur : Allocation mémoire échouée\n");
        exit(1);
    }
    printf("Entrer le nom de la station : ");
    scanf("%25s", nom);

    a = recupDonnee(a, h, nom); // Charger les données
    if (a == NULL) {
        fprintf(stderr, "Erreur : Aucun arbre n'a été créé, vérifiez vos données d'entrée.\n");
        free(h);
        free(nom);
        return 1; // Sortir avec un code d'erreur
    }

    printf("La somme totale des consommations est : %d\n", sommetot(a));
    ecrireStationDansFichier(a, nom); // Écrire les données dans un fichier

    libererStation(a); // Libérer la mémoire de l'arbre
    free(h);           // Libérer la mémoire pour `h`
    free(nom);         // Libérer la mémoire pour `nom`

    return 0;
}
