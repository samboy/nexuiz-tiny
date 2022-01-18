#!/bin/bash

# Make a Xonotic shader file so that graphite can be correctly rebuilt
# This script may have Bashisms
# Non-standard but readily available "zip" program needed to build this

HERE=`/bin/pwd`

if [ ! -d ~/tmp ] ; then
	mkdir ~/tmp
	echo ~/tmp directory made
fi

cd ~/tmp
mkdir $$
cd $$
mkdir env/
mkdir env/space
mkdir scripts/
mkdir dds/
mkdir dds/textures/
mkdir dds/textures/skies/
cp ${HERE}/*png env/space/
cp ${HERE}/*jpg env/space/
cp ${HERE}/*dds dds/textures/skies
cp ${HERE}/*shader scripts/
zip -r ${HERE}/nexuizspace.pk3 *
cd
rm -fr ~/tmp/$$
