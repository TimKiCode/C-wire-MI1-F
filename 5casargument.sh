#!/bin/bash

function hvbcomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' '{ if($1 !~ /-/ && $2 ~ /-/ ) print $1, $(NF-1), $NF }' t.csv

}

function hvacomp {
	echo "tout roule"
	tail -n +2 "$fichier" | cut -d ';' -f 2-> t.csv
	awk -F';' -v a=2 '{ if($a !~ /-/ && $(($a+1)) !~ /-/) print $a, $(NF-1), $NF }' t.csv
}

function lvall {
	echo "tout roule"
}
	
function lvcomp {
	echo "tout roule"
}

function lvindiv {
	echo "tout roule"
}

combined="$2-$3"
fichier="$1"



case "$combined" in
"hvb-comp") hvbcomp;;
"hva-comp") hvacomp;;
"lv-all") lvall;;
"lv-comp") lvcomp;;
"lv-indiv") lvindiv;;
*) echo "rtfm";;
esac
