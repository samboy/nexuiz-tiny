
#include "quakedef.h"
#include "r_shadow.h"

void R_Model_Sprite_Draw_TransparentCallback(const entity_render_t *ent, const rtlight_t *rtlight, int numsurfaces, int *surfacelist)
{
	int i;
	model_t *model = ent->model;
	vec3_t left, up, org, mforward, mleft, mup;
	float scale;

	// nudge it toward the view to make sure it isn't in a wall
	Matrix4x4_ToVectors(&ent->matrix, mforward, mleft, mup, org);
	VectorSubtract(org, r_view.forward, org);
	switch(model->sprite.sprnum_type)
	{
	case SPR_VP_PARALLEL_UPRIGHT:
		// flames and such
		// vertical beam sprite, faces view plane
		scale = ent->scale / sqrt(r_view.forward[0]*r_view.forward[0]+r_view.forward[1]*r_view.forward[1]);
		left[0] = -r_view.forward[1] * scale;
		left[1] = r_view.forward[0] * scale;
		left[2] = 0;
		up[0] = 0;
		up[1] = 0;
		up[2] = ent->scale;
		break;
	case SPR_FACING_UPRIGHT:
		// flames and such
		// vertical beam sprite, faces viewer's origin (not the view plane)
		scale = ent->scale / sqrt((org[0] - r_view.origin[0])*(org[0] - r_view.origin[0])+(org[1] - r_view.origin[1])*(org[1] - r_view.origin[1]));
		left[0] = (org[1] - r_view.origin[1]) * scale;
		left[1] = -(org[0] - r_view.origin[0]) * scale;
		left[2] = 0;
		up[0] = 0;
		up[1] = 0;
		up[2] = ent->scale;
		break;
	default:
		Con_Printf("R_SpriteSetup: unknown sprite type %i\n", model->sprite.sprnum_type);
		// fall through to normal sprite
	case SPR_VP_PARALLEL:
		// normal sprite
		// faces view plane
		VectorScale(r_view.left, ent->scale, left);
		VectorScale(r_view.up, ent->scale, up);
		break;
	case SPR_ORIENTED:
		// bullet marks on walls
		// ignores viewer entirely
		VectorCopy(mleft, left);
		VectorCopy(mup, up);
		break;
	case SPR_VP_PARALLEL_ORIENTED:
		// I have no idea what people would use this for...
		// oriented relative to view space
		// FIXME: test this and make sure it mimicks software
		left[0] = mleft[0] * r_view.forward[0] + mleft[1] * r_view.left[0] + mleft[2] * r_view.up[0];
		left[1] = mleft[0] * r_view.forward[1] + mleft[1] * r_view.left[1] + mleft[2] * r_view.up[1];
		left[2] = mleft[0] * r_view.forward[2] + mleft[1] * r_view.left[2] + mleft[2] * r_view.up[2];
		up[0] = mup[0] * r_view.forward[0] + mup[1] * r_view.left[0] + mup[2] * r_view.up[0];
		up[1] = mup[0] * r_view.forward[1] + mup[1] * r_view.left[1] + mup[2] * r_view.up[1];
		up[2] = mup[0] * r_view.forward[2] + mup[1] * r_view.left[2] + mup[2] * r_view.up[2];
		break;
	}

	R_Mesh_Matrix(&identitymatrix);

	// LordHavoc: interpolated sprite rendering
	for (i = 0;i < 4;i++)
	{
		if (ent->frameblend[i].lerp >= 0.01f)
		{
			mspriteframe_t *frame = model->sprite.sprdata_frames + ent->frameblend[i].frame;
			texture_t *texture = model->data_textures + ent->frameblend[i].frame;
			R_UpdateTextureInfo(ent, texture);
			// FIXME: negate left and right in loader
			R_DrawSprite(texture->currentlayers[0].blendfunc1, texture->currentlayers[0].blendfunc2, texture->basetexture, texture->currentskinframe->fog, (texture->currentmaterialflags & MATERIALFLAG_NODEPTHTEST), (texture->currentmaterialflags & MATERIALFLAG_SHORTDEPTHRANGE), org, left, up, frame->left, frame->right, frame->down, frame->up, texture->currentlayers[0].color[0], texture->currentlayers[0].color[1], texture->currentlayers[0].color[2], ent->alpha * ent->frameblend[i].lerp);
		}
	}
}

void R_Model_Sprite_Draw(entity_render_t *ent)
{
	vec3_t org;
	if (ent->frameblend[0].frame < 0)
		return;

	Matrix4x4_OriginFromMatrix(&ent->matrix, org);
	R_MeshQueue_AddTransparent(ent->effects & EF_NODEPTHTEST ? r_view.origin : org, R_Model_Sprite_Draw_TransparentCallback, ent, 0, rsurface.rtlight);
}

