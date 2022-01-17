textures/toxic/toxic_sky
{
        qer_editorimage textures/skies/heaven.tga
        surfaceparm noimpact
        surfaceparm nolightmap
        surfaceparm nomarks
        surfaceparm sky
        q3map_sun .9607843137254902 .7176470588235294 .3803921568627451 350 270 10
        q3map_skylight 200 4
        skyparms env/space/s - -
}

textures/toxic/frage_sky
{
        qer_editorimage env/mtg/mtg_up.tga
        surfaceparm noimpact
        surfaceparm nolightmap
        surfaceparm sky
        surfaceparm nomarks
        q3map_sun .5 .5 .7 50 0 90
        q3map_surfacelight 150
        skyparms env/mtg/mtg - -
}

textures/toxic/toxic_grate
{
	qer_editorimage textures/kaznexctf2/grate.tga
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm alphashadow
	cull none
	nopicmip
	nomipmaps
	{
		map textures/kaznexctf2/grate.tga
		//depthWrite
		alphaFunc GT0
		rgbgen vertex
	}
}

textures/toxic/toxic_slime
{
	qer_editorimage textures/liquids/slime1.tga
	surfaceparm noimpact
	surfaceparm nonsolid
	surfaceparm slime
	surfaceparm trans
	cull disable
	deformVertexes wave 150 sin 2 5 0.25 0.1
	tessSize 128
	qer_trans 0.5
	q3map_surfacelight 1200
	{
		map textures/liquids/slime1.tga
		blendfunc add
		rgbGen identity
		tcMod turb 0 0.2 0 0.04
	}
}

textures/toxic/toxic_slime_tube
{
	qer_editorimage textures/liquids/slime1.tga
	surfaceparm noimpact
	surfaceparm nonsolid
	surfaceparm slime
	surfaceparm trans
	cull disable
	//deformVertexes wave 150 sin 2 5 0.25 0.1
	tessSize 128
	qer_trans 0.5
	q3map_surfacelight 1200
	{
		map textures/liquids/slime1.tga
		blendfunc add
		rgbGen identity
		tcMod scroll 0 0.2
	}
}
