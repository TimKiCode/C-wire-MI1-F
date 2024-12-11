#!/bin/bash

# Nom du dossier à vérifier (chemin relatif)
tmp="tmp"
graphs="graphs"
exec="exec.c"

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

if [ -d "$exec" ]; then
	echo "Le dossier '$exec' existe."
else
	echo "Erreur sur l'excutable .c '$exec' n'existe pas."
    
fi
