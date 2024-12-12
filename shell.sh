#!/bin/bash

# Nom du dossier à vérifier (chemin relatif)
tmp="tmp"
graphs="graphs"
exec="exec.c"
combined="$2-$3"
fichier="$1"

touch tmp.txt

function hvbcomp {
	echo "tout roule"
	tail -n +2 "$fichier"  | cut -d ';' -f 2- | awk -F';' '{ if($1 !~ /-/ && $2 ~ /-/ ) print $1, $(NF-1), $NF }' > tmp.txt

}

function hvacomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($2 !~ /-/ && $3 ~ /-/) print $2, $(NF-1), $NF }' > tmp.txt
}


function lvall {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' > tmp.txt
}
	
function lvcomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/ && $4 !~ /-/ ) print $3, $(NF-1), $NF }' > tmp.txt
}

function lvindiv {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/ && $4 ~ /-/) print $3, $(NF-1), $NF }' > tmp.txt
}


function lvallminmax {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' > tmp.txt
}

# Vérification
if [ -d "$tmp" ]; then
	echo "Le dossier '$tmp' existe. Je verifie qu'il est vide."
	if [ -n "$(ls -A "$tmp")" ]; then
		echo "Le dossier '$tmp' n'est pas vide. Je supprime son contenu."
		rm -rf "$tmp"/*
	else
		echo "Le dossier '$tmp' est déjà vide."
	fi
else
	echo "Le dossier '$tmp' n'existe pas. Donc je vais le créer."
	mkdir "$tmp"
fi

if [ -d "$graphs" ]; then
	echo "Le dossier '$graphs' existe."
else
	echo "Le dossier '$graphs' n'existe pas. Donc je vais le créer."
	mkdir "$graphs"
    
fi

if [ -f "$exec" ]; then
	echo "Le dossier '$exec' existe."
else
	echo "Erreur sur l'excutable .c '$exec' n'existe pas."
    
fi

case "$combined" in
"hvb-comp") hvbcomp;;
"hva-comp") hvacomp;;
"lv-all") lvall;;
"lv-comp") lvcomp;;
"lv-indiv") lvindiv;;
"lv-allminmax") lvallminmax;;
*) echo "rtfm";;
esac
