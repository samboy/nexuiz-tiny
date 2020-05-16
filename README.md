# Nexuiz and netbooks

Nexuiz is (was?) an open source first person shooter in the style of
Quake 3 or Unreal Tournament.  In the late 2000s and early 2010s, when
low cost small “netbook” computers based on the Intel Atom chipset
were popular, multiple efforts to make a version of Nexuiz for netbooks
came out, including one I did back in 2010.

Recently, during the COVID-19 quarantine, I returned to this work
and have updated it for the 2020s.

The remix I made for Netbooks in 2010 isn’t the first Nexuiz remix for
netbooks out there.  There is also [Nexuiz 
remix](http://ubuntuforums.org/showthread.php?t=1121992) as well as
[Darn small Nexuiz](http://sourceforge.net/projects/dsn/files/).

The advantage of this remix is that it has all of Nexuiz’s graphics
intact.  This particular remix of Nexuiz is based on Nexuiz 2.3, which
has better performance on slower hardware than newer versions of Nexuiz,
with the number of maps and models reduced to a minimum.  While this
version of Nexuiz only has seven smaller maps, all of the textures used
in the maps available are still present.

While the Intel Atom N455-based Netbook I originally made this fork of
Nexuiz for is not around, I have a recent Atom Cherry Trail I have tested
this version on, as well as a Thinkpad T60 from 2007 or so.  On the Atom
Cherry Trail, I get about 150 frames per second at “low” settings
and 1280x800 resolution; on the T60, I get about 60 frames per second
at the same settings.

# Building this

This version of Nexuiz is for Windows machines.  Full sources
are supplied in the `source/` directory, but making Linux or MacOS
binaries is left as an exercise for the reader.

To build this requires:

* A UNIX-like environment, such as [Cygwin](https://cygwin.com/)
* The “zip” tool, which is readily available as an optional package in
  Cygwin or in Linux distributions.
* The “make” tool, a bog standard *NIX devlopment tool

To make a file with the name `nexuiz-tiny.zip`, type in the following
command:

```
make
```

This will make a nexuiz-tiny.zip file which contains a working
Windows version of Nexuiz.

# Downloading the Windows binary

The version of this project pre-built to run on Windows can be downloaded
[from Sourceforge](https://sourceforge.net/projects/nexuiz-tiny/files/2020-05-07/).

# The Maps

This fork of Nexuiz comes with seven maps.  All of the maps are small maps
which can be played for 1-on-1 games:

* **Aerowalk**  This is a Nexuiz conversion of a Quake 3 remake of the 
  classic Quake (and Quake2) map Aerowalk.  This is a small, tight, vertical
  level with one main vertical area, and paths with twist around that
  area very closely.  A version of this map with higher resolution
  textures remains a popular map used frequently in Xonotic
  duel tournaments.  License: Not for commercial sale; can be
  redistributed on the Internet.

* **Blood Prison**  This map became one of Nexuiz’s included maps starting
  with Nexuiz 2.0.  This is a small, tight, two-level map.  In the basement,
  we have an area with a jump pad to go upstairs (as well as stairs), a 
  rocket locker, a hallway with the mega health, and a teleport.  The 
  upper floor is two-tier, with a long stairway separating the tiers that
  spans most of the upper floor.  Four medium healths and the rest of the 
  weapons can be obtained upstairs.  This map is very tight, best for 
  1-on-1 duels.  While attempts to update this map for Xonotic have been 
  done, this is best played as a Nexuiz map.  Open source.

* **Downer**  This is a small-to-medium sized three level map.  In the
  lowest level, we have a cave with a mega armor and the machine gun.
  A teleport leads out, as do stairs.  Next to the basement is an area
  with another mega armor and a jump pad to the upper floor.  Stairs leads up 
  to the middle floor, which includes a wing with both another mega armor
  and a mega health, two medium healths and a mortar in the middle of the 
  level, and both a teleport and jump pad to take one to the upper floor.
  The upper floor has a rocket launcher and a lovely view of the sky.
  While originally designed for 3-4 players, it’s perfectly playable as
  a 1-on-1 duel map.  There has been a remake of this map for Xonotic, with
  significant changes from this original Nexuiz map, but this original
  version of the map is probably the best version.  Not widely played in 
  Xonotic, but an excellent Nexuiz map.  Open source, and it has been 
  included with Nexuiz since version 1.

* **Final Rage**  This is the old Nexuiz 2 version of a map which remains
  a popular Xonotic duel map.  This maps is large enough to be played with
  up to four players, but plays really nicely as a duel map.  There are 
  two main areas:  A large atrium with lots of tiers; there a number of 
  maze-like passages out of this atrium, but they all lead to a smaller 
  two-level room with the machine gun and mega armor.  Next to the large 
  atrium is a smaller area with a mega health; teleports take one to and 
  from the mega health area and the mega armor room.  There is also, next 
  to the mega armor room, an area with the crylink available.  The map
  remains popular as a Xonotic map, albeit one with a lot of changes
  from this original Nexuiz version of the map.  Open source, available
  as one of the included maps for both Nexuiz 2.3+ and Xonotic.

* **Graphite** This is an Xonotic, not Nexuiz map, but I liked this map
  enough to spend a couple days to make a proper Nexuiz conversion of 
  the map (including back porting all of the textures in to a 
  Nexuiz-compatible format).  Don’t be fooled by the simple concrete-like 
  texturing (which, yes, is nicely lit); this is a very fun tight map with
  four rooms.  While mainly horizontal instead of vertical, it’s a really
  fun map which remains very popular as a Xonotic duel map.  Open source;
  GPLv3 licensed.  Not an official map, but a very popular one.
  
* **Soylent** This is the one space map I include with this tiny version
  of Nexuiz.  This is one of the maps included with Nexuiz 2.  While space 
  maps were very popular during Quake 3’s heyday and when Nexuiz came out, 
  they have gone out of favor.  Xonotic includes a remake of this map, 
  called “Xoylent”, but it is not played as often as other Xonotic maps.  
  This map is quite small, best played as a 1-on-1 map.  Open source.

* **Toxic** This map, also one of the maps included with Nexuiz 2, is
  a fairly small map which works well as a 1-on-1 map, but can work as
  a 4-way or 2-vs-2 map.  This is the only map, of the seven maps
  included with this tiny remix of Nexuiz, that does not have a jump
  pad; like Soylent, it also does not have any teleports.  It does not
  appear to have been converted in to a Xonotic map but remains a fun
  classic Nexuiz map.  Open source.

## Note on the non-opensource Aerowalk map

Since Aerowalk is one of my favorite maps, I have included a copy of this
map in the nexuiz-tiny.zip file.  While this map is not open source (i.e.
one can not distribute this on any for-sale media, and can only distribute
this over the Internet and “BBS systems”), the map can be downloaded 
and used free of charge. 

