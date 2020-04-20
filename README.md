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
with the number of maps and models reduced to a minimum.  All of the
textures used in the maps available are still present.

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

