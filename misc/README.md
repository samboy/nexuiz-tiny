# z_2020.pk3

This will cause the 2022 version of nexuiz-tiny to have the
same item placement in maps, same campaign, and same rules (health
regeneration, more powerful rocket launcher) as the 2020 version
of Nexuiz.

# z_allweapons series

The z_allweapons series consists of the files `z_allweapons.pk3`,
`z_allweapons2.pk3`, and `z_allweapons3.pk3`.

If you put one, and only one, of these in the `data/` folder, all
of the maps will have all weapons available.  `z_allweapons2.pk3`
ensures we still have two big armors in the Toxic and BloodPrison maps.
`z_allweapons3.pk3`, in addition, also puts two big armors in the hard
to reach armor locations in Aerowalk and Graphite, to better play like
how these maps play in games with three different levels of armor.

Note that these files are incompatible with `z_nohealth.pk3`, 
`z_norocketlauncher.pk3`, `z_noRLnohealth.pk3`, and one another.

# z_balance.pk3

This disables health regeneration, and lowers the maximum health and
armor to 250.  It also makes the rocket launcher weaker.

To use, put the `z_balance.pk3` file in the `data/` folder.

# z_newcampaign.pk3

This replaces the basic, easy five-map campaign with a 21-map more 
challenging campaign.  Each map is a 1-on-1 battle, and all seven
maps are played three times each, with the bots getting harder as
you advance in the campaign.

# z_nohealth.pk3

If you put this in the `data/` folder, all of the maps will have no 
health on them.  By combining this with a `Health regeneration speed` 
of 0.00, it makes games more balanced by allowing a weaker player
to have any damage they do against a stronger player be present until
the stronger player gets fragged.

To disable health regeneration, put the `z_balance.pk3` in the
`data/` folder.

To adjust `Health regeneration speed` in the game:

* Create → Game Settings → Misc
* Scroll down
* Put the mouse over `Health regeneration speed`
* Use the arrow keys and keyboard to type in `0.00`

Note that this file is incompatible with `z_2020.pk3`, `z_allweapons.pk3`,
`z_allweapons2.pk3`, `z_allweapons3.pk3`,
`z_norocketlauncher.pk3`, and `z_noRLnohealth.pk3`.

# z_norocketlauncher.pk3

The rocket launcher may be over powered in Nexuiz.  That in mind,
this file eliminates the rocket launcher from all maps.

If you put this in the `data/` folder, all of the maps will have all
weapons *except the rocket launcher* available.

Note that this file is incompatible with `z_2020.pk3`, `z_allweapons.pk3`,
`z_allweapons2.pk3`, `z_allweapons3.pk3`, `z_nohealth.pk3`, 
and `z_noRLnohealth.pk3`.

# z_noRLnohealth.pk3

This is a version of the “no rocket launcher” mod, but, in addition, all
health has been replaced with additional ammunition.

By combining this with a `Health regeneration speed` of 0.00, it makes
games more balanced by allowing a weaker player to have any damage they
do against a stronger player be present until the stronger player gets
fragged.  

See above for notes on how to adjust `Health regeneration speed`.

Note that this file is incompatible with `z_2020.pk3`, `z_allweapons.pk3`,
`z_allweapons2.pk3`, `z_allweapons3.pk3`, `z_norocketlauncher.pk3`, 
and `z_nohealth.pk3`.
