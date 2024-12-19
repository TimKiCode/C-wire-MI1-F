#!/bin/bash

# Nom du dossier à vérifier (chemin relatif)
tmp="tmp"
graphs="graphs"
exec="CodeC/exec"
combined="$2-$3"
fichier="$1"

tmp_file="$tmp/tmp.txt"
tmp_file2="$tmp/tmp2.txt"

touch "$tmp_file"
touch "$tmp_file2"

echo "     ____      __          __   _    ____     _____ "
echo "    /  __)     \ \        / /  | |  /  _ \   | ____|"
echo "    | /     __  \ \ /\/\ / /   | |  | (_) |  | |_"
echo "    | |    (__)  \ V    V /    | |  |    /   | __|"
echo "    | \__         \      /     | |  |  _ \   | |___"
echo "    \____)         \_/\_/      |_|  |_| \_\  |_____|"
echo ""

for arg in "$@"; do
	if [[ "$arg" == "-h" ]]; then
		echo "Vous avez utilisez la commande "-h" voici une aide sur le fonctionnement du programme."
		exit 0
	fi
done

# Vérification du nombre d'arguments
if [ "$#" -gt 4 ]; then
	echo "Erreur : Le nombre d'arguments ne doit pas dépasser 4."
	echo "Utilisez la commande \"-h\" pour afficher l'aide."
	exit 1
fi

if [ ! -f "$fichier" ]; then
    echo "Erreur : Le fichier spécifié \"$fichier\" n'existe pas dans le dossier Input."
    exit 1
fi

function hvbcomp {
	tail -n +2 "$tmp_file"  | cut -d ';' -f 2- | awk -F';' '{ if($1 !~ /-/ && $2 ~ /-/ ) print $1, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file2"

}

function hvacomp {
	tail -n +2 "$tmp_file" | cut -d ';' -f 2- | awk -F';' '{ if($2 !~ /-/ && $3 ~ /-/) print $2, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file2"
}


function lvall {
	tail -n +2 "$tmp_file" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file2"
}
	
function lvcomp {
	tail -n +2 "$tmp_file" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/ && $5 ~ /-/ ) print $3, $(NF-1), $NF }'| awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file2"
}

function lvindiv {
	tail -n +2 "$tmp_file" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/ && $4 ~ /-/) print $3, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file2"
}

# Vérification des dossiers temporaires et graphiques
if [ -d "$tmp" ]; then
	if [ -n "$(ls -A "$tmp")" ]; then
		rm -rf "$tmp"/*
	fi
else
	mkdir "$tmp"
fi

if [ ! -d "$graphs" ]; then
	mkdir "$graphs"
fi

start_time=$(date +%s%3N)

if [ -n "$4" ]; then
	echo "Vérification de la présence du numéro de centrale $4 dans le fichier temporaire."
	if  grep "^$4;" "$fichier" > /dev/null; then
		grep "^$4;" "$fichier" > "$tmp_file"
		
	else
		echo "Erreur : Le numéro de centrale $4 n'est pas présent dans le fichier"
		exit 1
	fi
else
	cp $fichier $tmp_file

fi

case "$combined" in
"hvb-comp") hvbcomp;;
"hva-comp") hvacomp;;
"lv-all") lvall;;
"lv-comp") lvcomp;;
"lv-indiv") lvindiv;;
*) echo -e "Mauvaise saisie des arguments! Utilisez la commande \"-h\" pour afficher l'aide.\nTemps de traitement : 0s 0ms"
exit;;
esac

cd "CodeC" || { echo "Impossible d'accéder au dossier CodeC"; exit 1; }
make
if [ $? -ne 0 ]; then
	echo "Erreur de compilation"
	echo "Temps de traitement : 0s 0ms"
	exit 1
fi

echo "Compilation réussie !"

cd ..

chmod +x ./CodeC/exec

./CodeC/exec "$tmp_file2" "$combined"

if [ "$combined" = "lv-all" ]; then
	touch tmp/sorted.txt
	sort -k4,4n Output/calc_lv-all.txt > tmp/sorted.txt
	touch tmp/smallest.txt
	touch tmp/largest.txt
	touch Output/result.txt
	head -n 10 tmp/sorted.txt > tmp/smallest.txt
	tail -n 10 tmp/sorted.txt > tmp/largest.txt
	cat tmp/smallest.txt tmp/largest.txt > Output/result.txt
fi

end_time=$(date +%s%3N)
execution_time=$((end_time - start_time))
seconds=$((execution_time / 1000))
milliseconds=$((execution_time % 1000))

echo "Temps de traitement : ${seconds}s ${milliseconds}ms"
