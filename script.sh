#!/bin/bash

function hvbcomp {
	echo "tout roule"
	awk '{print $1, $2}' "$fichier"
}

function hvacomp {
	echo "tout roule"
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

