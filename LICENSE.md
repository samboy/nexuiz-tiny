As per Xonotic’s license, most of the data here is licensed under 
both version 2 and any later version of the GPL.  As per the
[GNU FAQ](https://www.gnu.org/licenses/gpl-faq.html#v2v3Compatibility),
this allows the data to be freely redistributed.

Some of the data (read: *not* code) is GPLv3 licensed; it is my 
understanding that a GPLv2+ licensed program can load GPLv3 licensed 
data.  This data is in the folder `GPLv3-data/` and generates a
separate `GPLv3-data.pak3` file.  The source for the GPLv3-licensed
data is in the folder `source/GPLv3`.

Some of the other data is distributed under terms which are different
from the GPL (free distribution over the Internet is allowed, but 
selling the data on a CD-rom is not allowed).  Again, a GPLv2+ 
licensed program can load this data without the license being
violated.  This data is in a separate directory, `non-opensource/`,
and the resulting generated files have the names
`aerowalk-notOpenSource.pk3` and `quintdm3-song-notOpenSource.pk3`.

To comply with the GPL, the source code for this software is available
at the following locations:

https://github.com/samboy/nexuiz-tiny/
https://sourceforge.net/projects/nexuiz-tiny/

# Modifications

As per the GPL, I need to note any modifications.  The only modifications
have been to text configuration files, the names of sky boxes used in 
binary .bsp files, the names of Internet servers in nexuiz.exe (changed
to disable connection to servers on the Internet; having a 2007 binary
connect to untrusted servers here in 2022 is a security risk), and the
graphite.bsp file has been recompiled.

Note that this is a good faith attempt to list all files modified;
however, the Git log of this repo is the authoritative source listing
all modified files and the dates they were modified.

## Maps

* `bloodprison.bsp` is the same binary file as included with Nexuiz 2.3
* `downer.bsp` is based on the binary file included with Nexuiz 1.1, but 
  `sav-graysky1_skybox` is now `sav-grayskyH_skybox`.  This allows Downer
  to use a different skybox.  The `.map` file uses the new skybox name,
  but was compiled with the old skybox.
* `final_rage.bsp` is based on the binary file included with Nexuiz 2.3,
  but `toxic_sky` has been made `toxic_sky`.  This allows Final Rage to use
  a different skybox than Toxic.  The `.map` file uses the new skybox
  name, but was compiled with the old skybox.
* `soylent.bsp` is the same binary file as included with Nexuiz 2.3
* `toxic.bsp` is the same binary file as included with Nexuiz 2.3
* `graphite.bsp` is a recompile.  The *only* modification is the skybox
  name; since a different skybox was used when recompiling, the resulting
  `.bsp` file has different lighting than the original.  This map uses one
  skybox (the heaven one with the sun moved) when compiling, and another one 
  (the new green space skybox I have made) when being played.
* `aerowalk_nextiny.bsp` is not GPL-licensed, and is unmodified from its
  original.

## Shaders

The following shader files in `data/scripts` have been modified from 
the form they have in Nexuiz 2.3:

* `sav-graysky1.shader`
* `shaderlist.txt`
* `skies_heaven.shader`
* `stralenex1.shader`
* `stralenex8.shader`
* `toxic.shader`

## Other files

Other files in the `maps` folder have been changed:

* Songs for a given level have been changed
* Item placement has been changed
* Map description and pictures have been changed (all map pictures,
  except the one for Downer, have been replaced)

`campaign.txt` has been modified to only use the seven maps included
with nexuiz-tiny.  

`default.cfg` has been modified to update the game rules (no health
regeneration, max health/armor 250, weaker rocket launcher).

