#!/bin/bash -e

# This is a script which packages up the graphite_b2 map in to a Nexuiz
# compatible format.  The resulting packages (it has to be two files,
# because graphite_b2 is GPLv3, while the needed textures are GPLv2+)
# can be put in the data directory for Nexuiz 2.3 or Nexuiz 2.5.2 to add
# the graphite_b2 map to Nexuiz.

# REQUIRED: The "zip" tool to make zipfiles
# OPTIONAL: unix2dos; advzip from AdvanceCOMP

## MAP FILE (GPL-3) ##
mkdir graphite_b2_Nexuiz_map
mkdir graphite_b2_Nexuiz_map/maps
cp GPL-3 graphite_b2_Nexuiz_map/LICENSE
cat > graphite_b2_Nexuiz_map/README.TXT << EOF
This is a port of graphite_b2 to Nexuiz 2.3.

Because graphite_b2 is GPLv3 licensed, this has only the converted map.
The textures are under a different license (GPLv2+, i.e. GPL version 2 or
any later version), so need to be separated from the GPLv3 mapdata.

More discussion:

https://forums.xonotic.org/showthread.php?tid=7537

EOF
unix2dos graphite_b2_Nexuiz_map/README.TXT || true
cp GPLv3-data/maps/* graphite_b2_Nexuiz_map/maps/
cp source/GPLv3/graphite_b2.map graphite_b2_Nexuiz_map/maps/
cd graphite_b2_Nexuiz_map/
zip -r ../graphite_b2_Nexuiz_map.zip *
cd ..
advzip -z -4 graphite_b2_Nexuiz_map.zip || true
mv graphite_b2_Nexuiz_map.zip graphite_b2_Nexuiz_map.pk3

## TEXTURES (GPLv2+) ##
mkdir graphite_b2_Nexuiz_textures
mkdir graphite_b2_Nexuiz_textures/env
mkdir graphite_b2_Nexuiz_textures/env/heaven
mkdir graphite_b2_Nexuiz_textures/scripts
mkdir graphite_b2_Nexuiz_textures/textures
mkdir graphite_b2_Nexuiz_textures/textures/effects_warpzone
mkdir graphite_b2_Nexuiz_textures/textures/exx
cp data/env/heaven/* graphite_b2_Nexuiz_textures/env/heaven/
cp data/textures/effects_warpzone/* graphite_b2_Nexuiz_textures/textures/effects_warpzone/
cp data/textures/exx/* graphite_b2_Nexuiz_textures/textures/exx/
cp data/scripts/sav-graysky1.shader graphite_b2_Nexuiz_textures/scripts/
cat > graphite_b2_Nexuiz_textures/README.TXT << EOF
These are the textures which the map graphite_b2 needs to run in
Nexuiz.  These textures are licensed under version 2 or any later
version of the GNU General Public License.
EOF
unix2dos graphite_b2_Nexuiz_textures/README.TXT || true
cd graphite_b2_Nexuiz_textures/
zip -r ../graphite_b2_Nexuiz_textures.zip *
cd ..
advzip -z -4 graphite_b2_Nexuiz_textures.zip || true
mv graphite_b2_Nexuiz_textures.zip graphite_b2_Nexuiz_textures.pk3

## CLEAN UP ##
rm -fr graphite_b2_Nexuiz_map/
rm -fr graphite_b2_Nexuiz_textures/
