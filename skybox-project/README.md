This is a single compact skybox which is used in Blood Prison, Soylent, and
Aerowalk.

This allows us to make a smaller version of nexuiz-tiny where all three
of those maps use the same skybox.

The internal name of the skybox in nexuiz-tiny is `env/space/s`

# Original skybox

To generate the original skybox:

* Go to https://tools.wwwtyro.net/space-3d/index.html or to index.html
  in this directory.
* Select seed `3d7za2x8311c`
* Generate skybox

The skybox has been rotated so the sun (moon?) is in roughly the right 
place on the Blood Prison map.

# Making a skybox to build the Graphite map

We have to add a skybox to the Xonotic assets to correctly build the
Graphite map.

To do this, run the `make.xonotic.shader.sh` shell script; make sure
to have the `zip` utility.

