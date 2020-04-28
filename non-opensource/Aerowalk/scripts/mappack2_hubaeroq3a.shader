textures/base_floor/achtung_clang
{
	{
		map textures/evil8_floor/e8clangfloor04warn2red.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_floor/proto_rustygrate
{
	surfaceparm	metalsteps	
  	surfaceparm trans	
	surfaceparm alphashadow
	cull none
      nopicmip
	{
		map textures/evil1_grates/smllgrt_h.tga
		tcMod scale 2 2
		blendFunc GL_ONE GL_ZERO
		alphaFunc GE128
		depthWrite
		rgbGen identity
	}
	{
		map $lightmap
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
}

textures/base_floor/proto_grate4
{
	surfaceparm	metalsteps	
    	surfaceparm trans	
	surfaceparm alphashadow
	cull none
      nopicmip
	{
		map textures/evil1_grates/smllgrt_h.tga
		tcMod scale 2 2
		blendFunc GL_ONE GL_ZERO
		alphaFunc GE128
		depthWrite
		rgbGen identity
	}
	{
		map $lightmap
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}

}

textures/base_floor/tilefloor7
{
	{
		map textures/evil1_floors/floortile1bbrown.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_light/baslt4_1_2k
{
	{
		map textures/eX/ex_lightpanel_01
		tcMod scale 2 2
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_light/baslt4_1_4k
{
	{
		map textures/eX/ex_lightpanel_01
		tcMod scale 2 2
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_light/ceil1_38_20k
{
	{
		map textures/evil8_lights/e8_rlighty.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_light/light1_1500
{
	{
		map textures/evil3_lights/rlight_a.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_light/proto_lightred2
{
	{
		map textures/evil8_lights/e8tinylightr.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}


textures/base_support/cable
{
	{
		map textures/evil2_misc/mtl_grtx.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_support/x_support
{
	surfaceparm	metalsteps	
    	surfaceparm trans	
	surfaceparm alphashadow
	cull none
      nopicmip
	{
		map textures/evil1_grates/smllgrt_h.tga
		tcMod scale 2 2
		blendFunc GL_ONE GL_ZERO
		alphaFunc GE128
		depthWrite
		rgbGen identity
	}
	{
		map $lightmap
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
}


textures/base_support/x_support2
{
	surfaceparm	metalsteps	
    	surfaceparm trans	
	surfaceparm alphashadow
	cull none
      nopicmip
	{
		map textures/evil1_grates/smllgrt_h.tga
		tcMod scale 2 2
		blendFunc GL_ONE GL_ZERO
		alphaFunc GE128
		depthWrite
		rgbGen identity
	}
	{
		map $lightmap
		rgbGen identity
		blendFunc GL_DST_COLOR GL_ZERO
		depthFunc equal
	}
}

textures/base_support/z_support
{
	cull disable
	{
		map textures/evil8_grate/e8xgirder_small2.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
		depthFunc equal
	}
}


textures/base_trim/pewter_shiney
{
	{
		map textures/evil5_floor/confllr.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_trim/proto_fence
{
	qer_editorimage textures/kaznexctf2/grate.tga
	surfaceparm nomarks
	surfaceparm trans
	cull none
	nopicmip
	{
		map textures/kaznexctf2/grate.tga
		rgbGen identity
		depthWrite
		//alphaFunc GE128
		blendfunc blend
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}

}

textures/base_trim/spidertrim
{
	{
		map textures/evil5_metal/drkrstmtl.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_wall/concrete_dark
{
	{
		map textures/evil5_floor/confllr.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}


textures/base_wall/glass01
{
	surfaceparm trans
	cull disable
	qer_trans 0.5

	{
		map textures/dsi/dsiglass2.tga
		blendfunc add
		//rgbGen vertex
		tcgen environment
		tcmod scale 4 4
	}	
}

textures/base_wall/grill
{
	{
		map textures/evil1_grates/flr_grt.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_wall/patch10_beatup2
{
	{
		map textures/evil2_basemetal/mtl_rstb.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/base_wall/redmet4small
{
	{
		map textures/evil8_base/e8base_red.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}


textures/gothic_block/killtrim
{
	{
		map textures/evil3_floors/bdirt.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/gothic_ceiling/woodceiling1b_dark
{
	{
		map textures/e7/e7panelwood2.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}


textures/gothic_floor/blocks17floor
{
	{
		map textures/evil8_base/e8metal03b
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}

textures/gothic_trim/pitted_rust
{
	{
		map textures/evil2_basemetal/mtl_rstb.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}
}

textures/gothic_trim/pitted_rust3_black
{
	{
		map textures/evil3_metals/mtldrk0.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}
}


textures/gothic_trim/zinc_shiny
{
	{
		map textures/evil5_wall/concrete.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}
}

textures/liquids/clear_calm1
{
	qer_editorimage textures/water/water0.tga
	qer_trans 20
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm water
	surfaceparm nolightmap
	cull none
	q3map_globaltexture
	{
		map textures/water/water0.tga
		tcMod scroll 0.07 0.07
		tcmod scale 1.2 0.7
		blendfunc blend
	}
	dp_water 0.1 0.8  2 2  1 1 1  1 1 1  0.125
}


textures/liquids/clear_ripple1_q3dm1
{
	qer_editorimage textures/water/water0.tga
	qer_trans 20
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm water
	surfaceparm nolightmap
	cull none
	q3map_globaltexture
	{
		map textures/water/water0.tga
		tcMod scroll 0.07 0.07
		tcmod scale 1.2 0.7
		blendfunc blend
	}
	dp_water 0.1 0.8  2 2  1 1 1  1 1 1  0.125
}

textures/liquids/clear_ripple2
{
	qer_editorimage textures/water/water0.tga
	qer_trans 20
	surfaceparm nomarks
	surfaceparm trans
	surfaceparm water
	surfaceparm nolightmap
	cull none
	q3map_globaltexture
	{
		map textures/water/water0.tga
		tcMod scroll 0.07 0.07
		tcmod scale 1.2 0.7
		blendfunc blend
	}
	dp_water 0.1 0.8  2 2  1 1 1  1 1 1  0.125
}

textures/liquids/lavahell_1000
{
	qer_editorimage textures/savdm6ish/#lava1.jpg
	#qer_nocarve
	surfaceparm noimpact
	surfaceparm lava
	surfaceparm nolightmap
	q3map_surfacelight 2000
	cull disable
	#tessSize 256
	#deformVertexes wave 100sin 5 5 .5 0.02
	{
		map textures/savdm6ish/#lava1.jpg
	}
}


textures/liquids/lavahell_2000
{
	qer_editorimage textures/savdm6ish/#lava1.jpg
	#qer_nocarve
	surfaceparm noimpact
	surfaceparm lava
	surfaceparm nolightmap
	q3map_surfacelight 2000
	cull disable
	#tessSize 256
	#deformVertexes wave 100sin 5 5 .5 0.02
	{
		map textures/savdm6ish/#lava1.jpg
	}
}

textures/organics/dirt2
{
	{
		map textures/evil3_floors/bdirt2.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}
}

textures/organics/pjrock7d
{
	{
		map textures/evil3_misc/b_rock.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}
}

textures/sfx/beam_dusty2
{
	qer_editorimage textures/strength/e8beam_yellow.tga
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm nonsolid
	surfaceparm trans
	cull disable
	qer_trans 0.6
	{
		map textures/strength/e8beam_yellow.tga
		blendfunc add
		tcMod scroll 0.3 0
	}
}

textures/sfx/clangdark_bounce
{
	q3map_lightimage textures/strength/strength_jp_glow.tga
	surfaceparm metalsteps
	q3map_surfacelight 400
	
	{
		map textures/strength/strength_jp
		animmap 10 textures/strength/strength_jp textures/strength/strength_jp-1 textures/strength/strength_jp-2 textures/strength/strength_jp-3 textures/strength/strength_jp-4 textures/strength/strength_jp-5 textures/strength/strength_jp-6
	}
	{
		map $lightmap
		tcGen lightmap
		blendfunc filter
	}
}

textures/sfx/metaltech12final_bounce
{
	q3map_lightimage textures/strength/strength_jp_glow.tga
	surfaceparm metalsteps
	q3map_surfacelight 400
	
	{
		map textures/strength/strength_jp
		animmap 10 textures/strength/strength_jp textures/strength/strength_jp-1 textures/strength/strength_jp-2 textures/strength/strength_jp-3 textures/strength/strength_jp-4 textures/strength/strength_jp-5 textures/strength/strength_jp-6
	}
	{
		map $lightmap
		tcGen lightmap
		blendfunc filter
	}

}

textures/sfx/testconstantfog
{
	surfaceparm trans
	cull disable
	qer_trans 0.5

	{
		map textures/sfx/xblackfog.tga
		blendfunc add
		//rgbGen vertex
		tcgen environment
		tcmod scale 4 4
	}	
}

//BAD APPROXIMATION
textures/sfx/xian_dm3padwall
{
	{
		map textures/evil6_walls/e6simpwallsupp_rst.tga
		tcMod scale 2 2
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}
}

textures/skies/nightsky_xian_dm4
{
	qer_editorimage env/stralenex5/greennebula_bk.tga

	surfaceparm nolightmap
	surfaceparm noimpact
	surfaceparm nomarks
	surfaceparm sky

	skyparms env/stralenex5/greennebula - -
	q3map_surfacelight 80
	q3map_lightimage textures/stralenex5/stralenex5_up.tga
	q3map_sun 0.3 0.33 0.3 60 80 20
	/*q3map_sun <red> <green> <blue> <intensity> <degrees> <elevation>*/
}

textures/skies/pj_arena2sky
{
	qer_editorimage textures/harlequin_sky/nebula_qer1.tga
	surfaceparm sky
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	q3map_surfacelight 50
// note: Change the surfacelight value if you want more ambient light from the sky.
	q3map_sun 1 .98 .9 100 0 90
// note: Change the fourth value (100) if you want a brighter or dimmer sun
	skyparms textures/harlequin_sky/env/nebular - -

}

textures/stone/pjrock17
{
	{
		map textures/evil4_walls/d_stone.tga
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
	}

}