textures/sav-graysky1/sav-graysky1_skybox
{
	qer_editorimage env/med-troubadour-gray/med-troubadour-gray_up.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky
	surfaceparm nomarks
	q3map_sun .5 .5 .7 200 0 90
	q3map_surfacelight 300
	skyparms env/med-troubadour-gray/med-troubadour-gray - -
}

textures/sav-graysky1/sav-graysky2_skybox
{
	qer_editorimage env/med-troubadour-gray/med-troubadour-gray_up.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky
	surfaceparm nomarks
	q3map_sun .5 .5 .7 50 0 90
	q3map_surfacelight 300
	skyparms env/med-troubadour-gray/med-troubadour-gray - -
}

textures/sav-graysky1/sav-graysky3lowerlight_skybox
{
	qer_editorimage env/med-troubadour-gray/med-troubadour-gray_up.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky
	surfaceparm nomarks
	q3map_sun .5 .5 .7 50 0 90
	q3map_surfacelight 150
	skyparms env/med-troubadour-gray/med-troubadour-gray - -
}
textures/sav-graysky1/sav-grayskyH_skybox
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
textures/skies/heaven
{
	qer_editorimage textures/skies/heaven.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm sky
	q3map_sun .9607843137254902 .7176470588235294 .3803921568627451 350 270 10
	q3map_skylight 200 4
	skyparms env/heaven/heaven - -
}

textures/skies/samiamspace
{
        qer_editorimage textures/skies/samiamspace.tga

        surfaceparm noimpact
        surfaceparm nolightmap
        surfaceparm nomarks
        q3map_globaltexture
        q3map_surfacelight 120
        surfaceparm sky

        //q3map_sun <red> <green> <blue> <intensity> <degrees> <elevation>
        q3map_sun .9607843137254902 .7176470588235294 .3803921568627451 350 20 40
        q3map_skylight 300 4
        skyparms env/space/s - -
}
