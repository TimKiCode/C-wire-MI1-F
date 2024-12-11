#!/bin/bash

function hvbcomp {
	echo "tout roule"
	tail -n +2 "$fichier"  | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($1 !~ /-/ && $2 ~ /-/ ) print $1, $(NF-1), $NF }' t.csv > tmp.csv

}

function hvacomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($2 !~ /-/ && $3 ~ /-/) print $2, $(NF-1), $NF }' t.csv > tmp.csv
}


function lvall {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' t.csv > tmp.csv
}
	
function lvcomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($3 !~ /-/ && $4 !~ /-/ ) print $3, $(NF-1), $NF }' t.csv > tmp.csv
}

function lvindiv {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($3 !~ /-/ && $4 ~ /-/) print $3, $(NF-1), $NF }' t.csv
}


function lvallminmax {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($3 !~ /-/) print $3, $(NF-1), $NF }' t.csv > tmp.csv
}

combined="$2-$3"
fichier="$1"

touch tmp.csv

case "$combined" in
"hvb-comp") hvbcomp;;
"hva-comp") hvacomp;;
"lv-all") lvall;;
"lv-comp") lvcomp;;
"lv-indiv") lvindiv;;
"lv-allminmax") lvallminmax;;
*) echo "rtfm";;
esac
