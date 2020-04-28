// ** Similar to the same in gothic_light, but with a yellower emission **
textures/hub3media/hub3_gothic_light3_2K
	{
	qer_editorimage textures/gothic_light/gothic_light3.tga
	q3map_lightimage textures/hub3media/hub3_gothic_light2_blend.tga
	q3map_surfacelight 2000
	surfaceparm nomarks
		{
		map $lightmap
		rgbGen identity
		}
		{
		map textures/evil3_lights/rlight_a.tga
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		}
		{
		map textures/hub3media/hub3_gothic_light2_blend.tga
		rgbGen wave sin .6 .1 .1 .1
		blendfunc GL_ONE GL_ONE
		}
	}

// **** Similar to baseq3 beam but with a dirtier finish ****
textures/hub3media/hub3_dirtbeam
	{
	qer_editorimage textures/hub3media/hub3_dirtbeam.tga
	surfaceparm trans	
	surfaceparm nomarks	
	surfaceparm nonsolid
	surfaceparm nolightmap
    qer_trans 0.9
	cull none
		{
		map textures/hub3media/hub3_dirtbeam.tga
		tcMod Scroll .3 0
        blendFunc add
        }
	}

// **** Quake Style Teleporter ****
//This shader and textures by Decker and Jude

textures/qw_teleporter/qw_teleporter
	{
	q3map_globaltexture
	q3map_lightsubdivide 32
	q3map_surfacelight 25
	
	surfaceparm nomarks
	surfaceparm nolightmap
	nopicmip
	
	cull disable
	
		{
		map textures/qw_teleporter/qw_teleporter.tga
		tcMod turb 0 .2 0 .1
		}
	}

// **** Similar to base_light/ceil1_39 but weaker light emission
textures/hub3media/hub3_ceil1_39
	{
	qer_editorimage textures/base_light/ceil1_39.tga
	surfaceparm nomarks
	q3map_surfacelight 500
		{
		map $lightmap
		rgbGen identity
		}
		{
		map textures/evil8_lights/e8_rlighty.tga
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
		}
	}