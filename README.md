# C-Wire

Le projet C-Wire consiste à développer une solution logicielle capable de synthétiser les données liées à un système de distribution d’électricité en France.
Ce projet combine un script Shell pour le filtrage des données et un programme en C pour le traitement et les calculs.
Les données sont extraites d'un fichier CSV contenant des informations sur la production et la consommation d'énergie à différents niveaux (centrales électriques, stations HV-B, HV-A, postes LV, entreprises, particuliers).
L'objectif est d'analyser ces stations afin de détecter des situations de surproduction ou sous-production et de produire des rapports structurés.


Pré-requis : 

- Avoir gnuplot 

- Avoir un compilateur (GNU Compiler Collection)

- Avoir un terminal linux (Debian, Ubuntu)


Utilisation : 

- Mettez le fichier à traiter dans le dossier Input/ du projet.
- Puis exécuter le fichier shell nommé c-wire.sh ensuite vous devez passer en 1er argument le chemin de votre fichier.

Par exemple Input/c-wire_v00.dat puis en 2ème et 3ème arguments l'une des possibilitées suivantes : hvb comp, hva comp, lv all, lv comp, lv indiv.
- Enfin vous pouvez rajouter un 4ème argument pour filtrer en fonction d'une centrale précise.

Par exemple : /c-wire.sh Input/c-wire_v25.dat lv all 1.
Vous trouverez donc dans le dossier Output/ votre fichier de sortie qui correspond aux options sélectionnées.
Dans le dossier graphs vous trouverez les graphiques qui correspondent aux traitements lv all ou lv all avec numéro de centrale.

En entrant dans la commande l'option "-h" vous receverez une aide dans le terminal si nécessaire.


En vous souhaitant une agréable utilisation et de bonnes fêtes!
