#!/bin/sh

# This script helps us find out which textures a given .bsp file needs

cd data/maps
for a in *bsp ; do 
	strings $a | grep textures | awk '
		{sub(/^[^t]+/,"");print $0 " '$a'"}' 
done | sort
