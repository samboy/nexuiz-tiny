//This shaderfile by Killer - http://www.planetquake.com/killer

//************************************************************//
// Square orange light with 10000 light value                 //
//************************************************************//
textures/mkoxide/ceil_orange_10000
   {
   surfaceparm nomarks
   q3map_surfacelight 10000
   light 1
   qer_editorimage textures/mkoxide/ceil_orange.tga
      {
      map $lightmap
      rgbGen identity
      }
      {
      map textures/mkoxide/ceil_orange.tga
      blendFunc GL_DST_COLOR GL_ZERO
      rgbGen identity
      }
      {
      map textures/mkoxide/ceil_orangeglow.tga
      blendfunc GL_ONE GL_ONE
      }
   }


//************************************************************//
// Square red light with 5000 light value                    //
//************************************************************//
textures/mkoxide/ceil_red_5000
   {
   surfaceparm nomarks
   q3map_surfacelight 5000
   light 1
   qer_editorimage textures/mkoxide/ceil_red.tga
      {
      map $lightmap
      rgbGen identity
      }
      {
      map textures/mkoxide/ceil_red.tga
      blendFunc GL_DST_COLOR GL_ZERO
      rgbGen identity
      }
      {
      map textures/mkoxide/ceil_redglow.tga
      blendfunc GL_ONE GL_ONE
      }
   }


//************************************************************//
// Flourescent white strip light with 5000 light value        //
//************************************************************//
textures/mkoxide/baselt1_5000
   {
   surfaceparm nomarks
   q3map_surfacelight 5000
   q3map_lightsubdivide 32
   light 1
   qer_editorimage textures/mkoxide/baselt1.tga
      {
      map $lightmap
      rgbGen identity
      }
      {
      map textures/mkoxide/baselt1.tga
      blendFunc GL_DST_COLOR GL_ZERO
      rgbGen identity
      }
      {
      map textures/mkoxide/baselt1glow.tga
      blendfunc GL_ONE GL_ONE
      }
   }


//************************************************************//
// Flourescent white strip light with 2000 light value        //
//************************************************************//
textures/mkoxide/baselt1_2000
   {
   surfaceparm nomarks
   q3map_surfacelight 2000
   q3map_lightsubdivide 32
   light 1
   qer_editorimage textures/mkoxide/baselt1.tga
      {
      map $lightmap
      rgbGen identity
      }
      {
      map textures/mkoxide/baselt1.tga
      blendFunc GL_DST_COLOR GL_ZERO
      rgbGen identity
      }
      {
      map textures/mkoxide/baselt1glow.tga
      blendfunc GL_ONE GL_ONE
      }
   }


//************************************************************//
// Flourescent orange strip light with 5000 light value       //
//************************************************************//
textures/mkoxide/wastelt1_5000
   {
   surfaceparm nomarks
   q3map_surfacelight 5000
   q3map_lightsubdivide 32
   light 1
   qer_editorimage textures/mkoxide/wastelt1_ed.tga
      {
      map $lightmap
      rgbGen identity
      }
      {
      map textures/mkoxide/wastelt1.tga
      blendFunc GL_DST_COLOR GL_ZERO
      rgbGen identity
      }
      {
      map textures/mkoxide/wastelt1glow.tga
      blendfunc GL_ONE GL_ONE
      }
   }


//************************************************************//
// Flourescent orange strip light with 2000 light value       //
//************************************************************//
textures/mkoxide/wastelt1_2000
   {
   surfaceparm nomarks
   q3map_surfacelight 2000
   light 1
   qer_editorimage textures/mkoxide/wastelt1_ed.tga
      {
      map $lightmap
      rgbGen identity
      }
      {
      map textures/mkoxide/wastelt1.tga
      blendFunc GL_DST_COLOR GL_ZERO
      rgbGen identity
      }
      {
      map textures/mkoxide/wastelt1glow.tga
      blendfunc GL_ONE GL_ONE
      }
   }


//************************************************************//
// Strogg emblem that hasn't been rusted and chipped off      //
//************************************************************//
textures/mkoxide/metal4_1shiny
   {
      {
      map textures/mkoxide/metal4_1shiny.tga
      }
      {
		map $lightmap
		blendfunc filter
		rgbGen identity
		tcGen lightmap
      }
   }


//************************************************************//
// Greenish semi-transparent sludge                           //
//************************************************************//
textures/mkoxide/goo1
   {
   qer_editorimage textures/mkoxide/goo2.tga
   qer_trans 0.2
   surfaceparm water
   surfaceparm trans
   surfaceparm noimpact
   surfaceparm nomarks
   tesssize 64
   deformVertexes wave 100 sin 2 2 0 .125
      {
      map textures/mkoxide/goo1.tga
      blendFunc GL_DST_COLOR GL_ZERO
      tcMod rotate 1
      tcMod scroll -0.025 -0.045
      }
      {
      map textures/mkoxide/goo2.tga
      blendFunc GL_ONE GL_ONE
      tcMod scale 1 -1
      tcMod scroll 0.045 0.025
      }
      {
      map $lightmap
      blendFunc GL_DST_COLOR GL_ZERO
      }
   }


//************************************************************//
// Yellow flourescent strip light beam texture                //
//************************************************************//
textures/mkoxide/orangebeam
   {
   surfaceparm trans	
   surfaceparm nomarks	
   surfaceparm nonsolid
   surfaceparm nolightmap
   cull none
      {
      map textures/mkoxide/orangebeam.tga
      tcMod Scroll .3 0
      blendFunc add
      }
   }


//************************************************************//
// Bounce pad on dark diamond floor                           //
//************************************************************//
textures/mkoxide/bounce_floor1
   {
   surfaceparm nodamage
   q3map_lightimage textures/sfx/jumppadsmall.tga	
   q3map_surfacelight 400
      {
      map textures/mkoxide/bounce_floor1.tga
      rgbGen identity
      }
      {
      map $lightmap
      rgbGen identity
      blendfunc filter
      }
      {
      map textures/sfx/bouncepad01b_layer1.tga
      blendfunc add
      rgbGen wave sin .5 .5 0 1.5
      }
      {
      clampmap textures/sfx/jumppadsmall.tga
      blendfunc add
      tcMod stretch sin 1.2 .8 0 1.5
      rgbGen wave square .5 .5 .25 1.5
      }
   }

//************************************************************//
// Sky texture shader copied from ik_sky.shader              //
// http://www.planetquake.com/ikq                             //
//************************************************************//
textures/mkoxide/ik_sky_night
   {
   surfaceparm noimpact
   surfaceparm nolightmap
   surfaceparm sky
   qer_editorimage textures/mkoxide/ik_sky_night_back.tga
   q3map_lightimage textures/mkoxide/ik_sky_night_back.tga
   q3map_surfacelight 200
   skyparms - 512 -
      {
      map textures/mkoxide/ik_sky_night_back.tga
      tcMod scale 2 2
      tcMod scroll 0.01 0.01
      depthWrite
      }
      {
      map textures/mkoxide/ik_sky_night_front.tga
      blendFunc GL_ONE GL_ONE
      tcMod scale 3 3
      tcMod scroll 0.02 0.02
      }
   }