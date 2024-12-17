#!/bin/bash

# Nom du dossier à vérifier (chemin relatif)
tmp="tmp"
graphs="graphs"
exec="exec.c"
combined="$2-$3"
fichier="$1"

tmp_file="$tmp/tmp.txt"

touch "$tmp_file"


function hvbcomp {
	echo "tout roule"
	tail -n +2 "$fichier"  | cut -d ';' -f 2- | awk -F';' '{ if($1 !~ /-/ && $2 ~ /-/ ) print $1, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file"

}

function hvacomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($2 !~ /-/ && $3 ~ /-/) print $2, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file"
}


function lvall {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file"
}
	
function lvcomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/ && $5 ~ /-/ ) print $3, $(NF-1), $NF }'| awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file"
}

function lvindiv {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/ && $4 ~ /-/) print $3, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file"
}

function lvallminmax {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2- | awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' | awk '{ for (i=1; i<=NF; i++) if ($i == "-") $i = 0; print }' > "$tmp_file"
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

start_time=$(date +%s%3N)

case "$combined" in
"hvb-comp") hvbcomp;;
"hva-comp") hvacomp;;
"lv-all") lvall;;
"lv-comp") lvcomp;;
"lv-indiv") lvindiv;;
"lv-allminmax") lvallminmax;;
*) echo "rtfm"
exit;;
esac

chmod 644 "$tmp_file"
cd "CodeC" || { echo "Impossible d'accéder au dossier CodeC"; exit 1; }
make
if [ $? -ne 0 ]; then
    echo "Erreur de compilation"
    exit 1
fi

echo "Compilation réussie !"

cd ..

chmod +x ./CodeC/exec

./CodeC/exec "$tmp_file" "$combined"

end_time=$(date +%s%3N)
execution_time=$((end_time - start_time))
seconds=$((execution_time / 1000))
milliseconds=$((execution_time % 1000))

echo "Temps de traitement : ${seconds}s ${milliseconds}ms"
