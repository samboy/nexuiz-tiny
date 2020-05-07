#!/bin/sh

# This script helps us find out which textures a given .bsp file needs

for a in data/maps/*bsp GPLv3-data/maps/*bsp non-opensource/Aerowalk/maps/*bsp 
do
	DIR=${a%%/*}
	# Only the Graphite map is GPLv3+; the textures are GPLv2+
	if [ "$DIR" == "GPLv3-data" ] ; then
		DIR="data"
	fi
	# The Aerowalk textures are in a sub-directory
	if [ "$DIR" == "non-opensource" ] ; then
		DIR="non-opensource/Aerowalk"
	fi
	strings $a | grep textures | awk '
		{sub(/^[^t]+/,"");print "'$DIR'/" $0 " '$a'"}' 
done | sort
