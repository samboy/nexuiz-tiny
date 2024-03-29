#include "quakedef.h"
#include "progsvm.h"
#include "clprogdefs.h"
#include "csprogs.h"
#include "cl_collision.h"

//============================================================================
// Client prog handling
//[515]: omg !!! optimize it ! a lot of hacks here and there also :P

#define CSQC_RETURNVAL	prog->globals.generic[OFS_RETURN]
#define CSQC_BEGIN		csqc_tmpprog=prog;prog=0;PRVM_SetProg(PRVM_CLIENTPROG);
#define CSQC_END		prog=csqc_tmpprog;
static prvm_prog_t *csqc_tmpprog;

//[515]: these are required funcs
static char *cl_required_func[] =
{
	"CSQC_Init",
	"CSQC_InputEvent",
	"CSQC_UpdateView",
	"CSQC_ConsoleCommand",
	"CSQC_Shutdown"
};

static int cl_numrequiredfunc = sizeof(cl_required_func) / sizeof(char*);

void CL_VM_Error (const char *format, ...) DP_FUNC_PRINTF(1);
void CL_VM_Error (const char *format, ...)	//[515]: hope it will be never executed =)
{
	char errorstring[4096];
	va_list argptr;

	va_start (argptr, format);
	dpvsnprintf (errorstring, sizeof(errorstring), format, argptr);
	va_end (argptr);
//	Con_Printf( "CL_VM_Error: %s\n", errorstring );

	PRVM_Crash();
	cl.csqc_loaded = false;

	Cvar_SetValueQuick(&csqc_progcrc, -1);
	Cvar_SetValueQuick(&csqc_progsize, -1);

//	Host_AbortCurrentFrame();	//[515]: hmmm... if server says it needs csqc then client MUST disconnect
	Host_Error(va("CL_VM_Error: %s", errorstring));
}

//[515]: set globals before calling R_UpdateView, WEIRD CRAP
static void CSQC_SetGlobals (void)
{
	CSQC_BEGIN
		prog->globals.client->time = cl.time;
		prog->globals.client->frametime = max(0, cl.time - cl.oldtime);
		prog->globals.client->servercommandframe = cls.servermovesequence;
		prog->globals.client->clientcommandframe = cl.movecmd[0].sequence;
		VectorCopy(cl.viewangles, prog->globals.client->input_angles);
		VectorCopy(cl.viewangles, cl.csqc_angles);
		prog->globals.client->input_buttons = cl.movecmd[0].buttons;
		VectorSet(prog->globals.client->input_movevalues, cl.movecmd[0].forwardmove, cl.movecmd[0].sidemove, cl.movecmd[0].upmove);
		//VectorCopy(cl.movement_origin, cl.csqc_origin);
		Matrix4x4_OriginFromMatrix(&cl.entities[cl.viewentity].render.matrix, cl.csqc_origin);
		VectorCopy(cl.csqc_origin, prog->globals.client->pmove_org);
		prog->globals.client->maxclients = cl.maxclients;
		//VectorCopy(cl.movement_velocity, prog->globals.client->pmove_vel);
		VectorCopy(cl.velocity, prog->globals.client->pmove_vel);
	CSQC_END
}

void CSQC_Predraw (prvm_edict_t *ed)
{
	int b;
	if(!ed->fields.client->predraw)
		return;
	b = prog->globals.client->self;
	prog->globals.client->self = PRVM_EDICT_TO_PROG(ed);
	PRVM_ExecuteProgram(ed->fields.client->predraw, "CSQC_Predraw: NULL function\n");
	prog->globals.client->self = b;
}

void CSQC_Think (prvm_edict_t *ed)
{
	int b;
	if(ed->fields.client->think)
	if(ed->fields.client->nextthink && ed->fields.client->nextthink <= prog->globals.client->time)
	{
		ed->fields.client->nextthink = 0;
		b = prog->globals.client->self;
		prog->globals.client->self = PRVM_EDICT_TO_PROG(ed);
		PRVM_ExecuteProgram(ed->fields.client->think, "CSQC_Think: NULL function\n");
		prog->globals.client->self = b;
	}
}

extern cvar_t cl_noplayershadow;
qboolean CSQC_AddRenderEdict(prvm_edict_t *ed)
{
	int renderflags;
	float scale;
	prvm_eval_t *val;
	entity_t *e;
	model_t *model;
	matrix4x4_t tagmatrix, matrix2;

	model = CL_GetModelFromEdict(ed);
	if (!model)
		return false;

	e = CL_NewTempEntity();
	if (!e)
		return false;

	e->render.model = model;
	e->render.colormap = (int)ed->fields.client->colormap;
	e->render.frame = (int)ed->fields.client->frame;
	e->render.skinnum = (int)ed->fields.client->skin;
	e->render.effects |= e->render.model->effects;
	scale = 1;
	renderflags = 0;
	if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.renderflags)) && val->_float)	renderflags = (int)val->_float;
	if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.alpha)) && val->_float)		e->render.alpha = val->_float;
	if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.scale)) && val->_float)		e->render.scale = scale = val->_float;
	if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.colormod)) && VectorLength2(val->vector))	VectorCopy(val->vector, e->render.colormod);
	if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.effects)) && val->_float)	e->render.effects |= (int)val->_float;
	if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.tag_entity)) && val->edict)
	{
		int tagentity;
		int tagindex = 0;
		tagentity = val->edict;
		if((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.tag_index)) && val->_float)
			tagindex = (int)val->_float;
		// FIXME: calculate tag matrix
		Matrix4x4_CreateIdentity(&tagmatrix);
	}
	else
		Matrix4x4_CreateIdentity(&tagmatrix);

	if (renderflags & RF_USEAXIS)
	{
		vec3_t left;
		VectorNegate(prog->globals.client->v_right, left);
		Matrix4x4_FromVectors(&matrix2, prog->globals.client->v_forward, left, prog->globals.client->v_up, ed->fields.client->origin);
		Matrix4x4_Scale(&matrix2, scale, 1);
	}
	else
	{
		vec3_t angles;
		VectorCopy(ed->fields.client->angles, angles);
		// if model is alias, reverse pitch direction
		if (e->render.model->type == mod_alias)
			angles[0] = -angles[0];

		// set up the render matrix
		Matrix4x4_CreateFromQuakeEntity(&matrix2, ed->fields.client->origin[0], ed->fields.client->origin[1], ed->fields.client->origin[2], angles[0], angles[1], angles[2], scale);
	}

	// set up the animation data
	// self.frame is the interpolation target (new frame)
	// self.frame1time is the animation base time for the interpolation target
	// self.frame2 is the interpolation start (previous frame)
	// self.frame2time is the animation base time for the interpolation start
	e->render.frame1 = e->render.frame = ed->fields.client->frame;
	if ((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.frame2))) e->render.frame1 = val->_float;
	if ((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.frame1time))) e->render.frame2time = val->_float;
	if ((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.frame2time))) e->render.frame1time = val->_float;
	if ((val = PRVM_EDICTFIELDVALUE(ed, prog->fieldoffsets.lerpfrac))) e->render.framelerp = val->_float;

	// concat the matrices to make the entity relative to its tag
	Matrix4x4_Concat(&e->render.matrix, &tagmatrix, &matrix2);
	// make the other useful stuff
	CL_UpdateRenderEntity(&e->render);

	if(renderflags)
	{
		if(renderflags & RF_VIEWMODEL)	e->render.flags |= RENDER_VIEWMODEL;
		if(renderflags & RF_EXTERNALMODEL)e->render.flags |= RENDER_EXTERIORMODEL;
		if(renderflags & RF_DEPTHHACK)	e->render.effects |= EF_NODEPTHTEST;
		if(renderflags & RF_ADDITIVE)		e->render.effects |= EF_ADDITIVE;
	}

	// either fullbright or lit
	if (!(e->render.effects & EF_FULLBRIGHT) && !r_fullbright.integer)
		e->render.flags |= RENDER_LIGHT;
	// hide player shadow during intermission or nehahra movie
	if (!(e->render.effects & (EF_NOSHADOW | EF_ADDITIVE | EF_NODEPTHTEST))
	 &&  (e->render.alpha >= 1)
	 && !(e->render.flags & RENDER_VIEWMODEL)
	 && (!(e->render.flags & RENDER_EXTERIORMODEL) || (!cl.intermission && cls.protocol != PROTOCOL_NEHAHRAMOVIE && !cl_noplayershadow.integer)))
		e->render.flags |= RENDER_SHADOW;
	if (e->render.flags & RENDER_VIEWMODEL)
		e->render.flags |= RENDER_NOSELFSHADOW;

	return true;
}

qboolean CL_VM_InputEvent (qboolean pressed, int key)
{
	qboolean r;
	if(!cl.csqc_loaded)
		return false;
	CSQC_BEGIN
		prog->globals.client->time = cl.time;
		PRVM_G_FLOAT(OFS_PARM0) = pressed;
		PRVM_G_FLOAT(OFS_PARM1) = key;
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_InputEvent, "QC function CSQC_InputEvent is missing");
		r = CSQC_RETURNVAL;
	CSQC_END
	return r;
}

qboolean CL_VM_UpdateView (void)
{
//	vec3_t oldangles;
	if(!cl.csqc_loaded)
		return false;
	CSQC_BEGIN
		//VectorCopy(cl.viewangles, oldangles);
		prog->globals.client->time = cl.time;
		CSQC_SetGlobals();
		// clear renderable entity and light lists to prevent crashes if the
		// CSQC_UpdateView function does not call R_ClearScene as it should
		r_refdef.numentities = 0;
		r_refdef.numlights = 0;
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_UpdateView, "QC function CSQC_UpdateView is missing");
		//VectorCopy(oldangles, cl.viewangles);
	CSQC_END
	return true;
}

extern sizebuf_t vm_tempstringsbuf;
qboolean CL_VM_ConsoleCommand (const char *cmd)
{
	int restorevm_tempstringsbuf_cursize;
	qboolean r;
	if(!cl.csqc_loaded)
		return false;
	CSQC_BEGIN
		prog->globals.client->time = cl.time;
		restorevm_tempstringsbuf_cursize = vm_tempstringsbuf.cursize;
		PRVM_G_INT(OFS_PARM0) = PRVM_SetTempString(cmd);
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_ConsoleCommand, "QC function CSQC_ConsoleCommand is missing");
		vm_tempstringsbuf.cursize = restorevm_tempstringsbuf_cursize;
		r = CSQC_RETURNVAL;
	CSQC_END
	return r;
}

qboolean CL_VM_Parse_TempEntity (void)
{
	int			t;
	qboolean	r = false;
	if(!cl.csqc_loaded)
		return false;
	CSQC_BEGIN
	if(prog->funcoffsets.CSQC_Parse_TempEntity)
	{
		t = msg_readcount;
		prog->globals.client->time = cl.time;
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Parse_TempEntity, "QC function CSQC_Parse_TempEntity is missing");
		r = CSQC_RETURNVAL;
		if(!r)
		{
			msg_readcount = t;
			msg_badread = false;
		}
	}
	CSQC_END
	return r;
}

void CL_VM_Parse_StuffCmd (const char *msg)
{
	int restorevm_tempstringsbuf_cursize;
	if(msg[0] == 'c')
	if(msg[1] == 's')
	if(msg[2] == 'q')
	if(msg[3] == 'c')
	{
		// if this is setting a csqc variable, deprotect csqc_progcrc
		// temporarily so that it can be set by the cvar command,
		// and then reprotect it afterwards
		int crcflags = csqc_progcrc.flags;
		int sizeflags = csqc_progcrc.flags;
		csqc_progcrc.flags &= ~CVAR_READONLY;
		csqc_progsize.flags &= ~CVAR_READONLY;
		Cmd_ExecuteString (msg, src_command);
		csqc_progcrc.flags = crcflags;
		csqc_progsize.flags = sizeflags;
		return;
	}
	if(!cl.csqc_loaded)
	{
		Cbuf_AddText(msg);
		return;
	}
	CSQC_BEGIN
	if(prog->funcoffsets.CSQC_Parse_StuffCmd)
	{
		prog->globals.client->time = cl.time;
		restorevm_tempstringsbuf_cursize = vm_tempstringsbuf.cursize;
		PRVM_G_INT(OFS_PARM0) = PRVM_SetTempString(msg);
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Parse_StuffCmd, "QC function CSQC_Parse_StuffCmd is missing");
		vm_tempstringsbuf.cursize = restorevm_tempstringsbuf_cursize;
	}
	else
		Cbuf_AddText(msg);
	CSQC_END
}

static void CL_VM_Parse_Print (const char *msg)
{
	int restorevm_tempstringsbuf_cursize;
	prog->globals.client->time = cl.time;
	restorevm_tempstringsbuf_cursize = vm_tempstringsbuf.cursize;
	PRVM_G_INT(OFS_PARM0) = PRVM_SetTempString(msg);
	PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Parse_Print, "QC function CSQC_Parse_Print is missing");
	vm_tempstringsbuf.cursize = restorevm_tempstringsbuf_cursize;
}

void CSQC_AddPrintText (const char *msg)
{
	size_t i;
	if(!cl.csqc_loaded)
	{
		Con_Print(msg);
		return;
	}
	CSQC_BEGIN
	if(prog->funcoffsets.CSQC_Parse_Print)
	{
		// FIXME: is this bugged?
		i = strlen(msg)-1;
		if(msg[i] != '\n' && msg[i] != '\r')
		{
			if(strlen(cl.csqc_printtextbuf)+i >= MAX_INPUTLINE)
			{
				CL_VM_Parse_Print(cl.csqc_printtextbuf);
				cl.csqc_printtextbuf[0] = 0;
			}
			else
				strlcat(cl.csqc_printtextbuf, msg, MAX_INPUTLINE);
			return;
		}
		strlcat(cl.csqc_printtextbuf, msg, MAX_INPUTLINE);
		CL_VM_Parse_Print(cl.csqc_printtextbuf);
		cl.csqc_printtextbuf[0] = 0;
	}
	else
		Con_Print(msg);
	CSQC_END
}

void CL_VM_Parse_CenterPrint (const char *msg)
{
	int restorevm_tempstringsbuf_cursize;
	if(!cl.csqc_loaded)
	{
		SCR_CenterPrint((char*)msg);
		return;
	}
	CSQC_BEGIN
	if(prog->funcoffsets.CSQC_Parse_CenterPrint)
	{
		prog->globals.client->time = cl.time;
		restorevm_tempstringsbuf_cursize = vm_tempstringsbuf.cursize;
		PRVM_G_INT(OFS_PARM0) = PRVM_SetTempString(msg);
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Parse_CenterPrint, "QC function CSQC_Parse_CenterPrint is missing");
		vm_tempstringsbuf.cursize = restorevm_tempstringsbuf_cursize;
	}
	else
		SCR_CenterPrint((char*)msg);
	CSQC_END
}

float CL_VM_Event (float event)		//[515]: needed ? I'd say "YES", but don't know for what :D
{
	float r = 0;
	if(!cl.csqc_loaded)
		return 0;
	CSQC_BEGIN
	if(prog->funcoffsets.CSQC_Event)
	{
		prog->globals.client->time = cl.time;
		PRVM_G_FLOAT(OFS_PARM0) = event;
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Event, "QC function CSQC_Event is missing");
		r = CSQC_RETURNVAL;
	}
	CSQC_END
	return r;
}

void CSQC_ReadEntities (void)
{
	unsigned short entnum, oldself, realentnum;
	CSQC_BEGIN
		prog->globals.client->time = cl.time;
		oldself = prog->globals.client->self;
		while(1)
		{
			entnum = MSG_ReadShort();
			if(!entnum)
				return;
			realentnum = entnum & 0x7FFF;
			prog->globals.client->self = cl.csqc_server2csqcentitynumber[realentnum];
			if(entnum & 0x8000)
			{
				if(prog->globals.client->self)
				{
					PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Ent_Remove, "QC function CSQC_Ent_Remove is missing");
					cl.csqc_server2csqcentitynumber[realentnum] = 0;
				}
				else
					Con_Printf("Smth bad happens in csqc...\n");	//[515]: never happens ?
			}
			else
			{
				if(!prog->globals.client->self)
				{
					prvm_edict_t	*ed;
					ed = PRVM_ED_Alloc();
					ed->fields.client->entnum = realentnum;
					prog->globals.client->self = cl.csqc_server2csqcentitynumber[realentnum] = PRVM_EDICT_TO_PROG(ed);
					PRVM_G_FLOAT(OFS_PARM0) = 1;
				}
				else
					PRVM_G_FLOAT(OFS_PARM0) = 0;
				PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Ent_Update, "QC function CSQC_Ent_Update is missing");
			}
		}
		prog->globals.client->self = oldself;
	CSQC_END
}

void CL_VM_CB_BeginIncreaseEdicts(void)
{
	int i;
	prvm_edict_t *ent;

	// links don't survive the transition, so unlink everything
	for (i = 0, ent = prog->edicts;i < prog->max_edicts;i++, ent++)
	{
		if (!ent->priv.server->free)
			World_UnlinkEdict(prog->edicts + i);
		memset(&ent->priv.server->areagrid, 0, sizeof(ent->priv.server->areagrid));
	}
	World_Clear(&cl.world);
}

void CL_VM_CB_EndIncreaseEdicts(void)
{
	int i;
	prvm_edict_t *ent;

	// link every entity except world
	for (i = 1, ent = prog->edicts;i < prog->max_edicts;i++, ent++)
		if (!ent->priv.server->free)
			CL_LinkEdict(ent);
}

void CL_VM_CB_InitEdict(prvm_edict_t *e)
{
	e->priv.server->move = false; // don't move on first frame
}

void CL_VM_CB_FreeEdict(prvm_edict_t *ed)
{
	World_UnlinkEdict(ed);
	memset(ed->fields.client, 0, sizeof(*ed->fields.client));
}

void CL_VM_CB_CountEdicts(void)
{
	int		i;
	prvm_edict_t	*ent;
	int		active = 0, models = 0, solid = 0;

	for (i=0 ; i<prog->num_edicts ; i++)
	{
		ent = PRVM_EDICT_NUM(i);
		if (ent->priv.server->free)
			continue;
		active++;
		if (ent->fields.client->solid)
			solid++;
		if (ent->fields.client->model)
			models++;
	}

	Con_Printf("num_edicts:%3i\n", prog->num_edicts);
	Con_Printf("active    :%3i\n", active);
	Con_Printf("view      :%3i\n", models);
	Con_Printf("touch     :%3i\n", solid);
}

qboolean CL_VM_CB_LoadEdict(prvm_edict_t *ent)
{
	return true;
}

void Cmd_ClearCsqcFuncs (void);

void CL_VM_Init (void)
{
	unsigned char *csprogsdata;
	fs_offset_t csprogsdatasize;
	int csprogsdatacrc, requiredcrc;
	int requiredsize;

	// reset csqc_progcrc after reading it, so that changing servers doesn't
	// expect csqc on the next server
	requiredcrc = csqc_progcrc.integer;
	requiredsize = csqc_progsize.integer;
	Cvar_SetValueQuick(&csqc_progcrc, -1);
	Cvar_SetValueQuick(&csqc_progsize, -1);

	cl.csqc_loaded = false;
	memset(cl.csqc_model_precache, 0, sizeof(cl.csqc_model_precache));
	memset(&cl.csqc_vidvars, true, sizeof(csqc_vidvars_t));

	// if the server is not requesting a csprogs, then we're done here
	if (requiredcrc < 0)
		return;

	// see if the requested csprogs.dat file matches the requested crc
	csprogsdatacrc = -1;
	csprogsdata = FS_LoadFile(va("dlcache/%s.%i.%i", csqc_progname.string, requiredsize, requiredcrc), tempmempool, true, &csprogsdatasize);
	if (!csprogsdata)
		csprogsdata = FS_LoadFile(csqc_progname.string, tempmempool, true, &csprogsdatasize);
	if (csprogsdata)
	{
		csprogsdatacrc = CRC_Block(csprogsdata, csprogsdatasize);
		Mem_Free(csprogsdata);
		if (csprogsdatacrc != requiredcrc || csprogsdatasize != requiredsize)
		{
			if (cls.demoplayback)
			{
				Con_Printf("^1Warning: Your %s is not the same version as the demo was recorded with (CRC/size are %i/%i but should be %i/%i)\n", csqc_progname.string, csprogsdatacrc, (int)csprogsdatasize, requiredcrc, requiredsize);
				return;
			}
			else
			{
				Con_Printf("^1Your %s is not the same version as the server (CRC is %i/%i but should be %i/%i)\n", csqc_progname.string, csprogsdatacrc, (int)csprogsdatasize, requiredcrc, requiredsize);
				CL_Disconnect();
				return;
			}
		}
	}
	else
	{
		if (requiredcrc >= 0)
		{
			if (cls.demoplayback)
				Con_Printf("CL_VM_Init: demo requires CSQC, but \"%s\" wasn't found\n", csqc_progname.string);
			else
				Con_Printf("CL_VM_Init: server requires CSQC, but \"%s\" wasn't found\n", csqc_progname.string);
			CL_Disconnect();
		}
		return;
	}

	PRVM_Begin;
	PRVM_InitProg(PRVM_CLIENTPROG);

	// allocate the mempools
	prog->progs_mempool = Mem_AllocPool(csqc_progname.string, 0, NULL);
	prog->headercrc = CL_PROGHEADER_CRC;
	prog->edictprivate_size = 0; // no private struct used
	prog->name = CL_NAME;
	prog->num_edicts = 1;
	prog->max_edicts = 512;
	prog->limit_edicts = CL_MAX_EDICTS;
	prog->reserved_edicts = 0;
	prog->edictprivate_size = sizeof(edict_engineprivate_t);
	prog->extensionstring = vm_sv_extensions;
	prog->builtins = vm_cl_builtins;
	prog->numbuiltins = vm_cl_numbuiltins;
	prog->begin_increase_edicts = CL_VM_CB_BeginIncreaseEdicts;
	prog->end_increase_edicts = CL_VM_CB_EndIncreaseEdicts;
	prog->init_edict = CL_VM_CB_InitEdict;
	prog->free_edict = CL_VM_CB_FreeEdict;
	prog->count_edicts = CL_VM_CB_CountEdicts;
	prog->load_edict = CL_VM_CB_LoadEdict;
	prog->init_cmd = VM_CL_Cmd_Init;
	prog->reset_cmd = VM_CL_Cmd_Reset;
	prog->error_cmd = CL_VM_Error;

	PRVM_LoadProgs(csqc_progname.string, cl_numrequiredfunc, cl_required_func, 0, NULL, 0, NULL);

	if (!prog->loaded)
	{
		CL_VM_Error("CSQC ^2failed to load\n");
		if(!sv.active)
			CL_Disconnect();
		return;
	}

	Con_Printf("CSQC ^5loaded (crc=%i, size=%i)\n", csprogsdatacrc, (int)csprogsdatasize);

	// check if OP_STATE animation is possible in this dat file
	if (prog->fieldoffsets.nextthink >= 0 && prog->fieldoffsets.frame >= 0 && prog->fieldoffsets.think >= 0 && prog->globaloffsets.self >= 0)
		prog->flag |= PRVM_OP_STATE;

	if (cl.worldmodel)
	{
		VectorCopy(cl.worldmodel->normalmins, cl.world.areagrid_mins);
		VectorCopy(cl.worldmodel->normalmaxs, cl.world.areagrid_maxs);
	}
	else
	{
		VectorSet(cl.world.areagrid_mins, -4096, -4096, -4096);
		VectorSet(cl.world.areagrid_maxs, 4096, 4096, 4096);
	}
	World_Clear(&cl.world);

	// set time
	prog->globals.client->time = cl.time;

	prog->globals.client->mapname = PRVM_SetEngineString(cl.worldmodel->name);
	prog->globals.client->player_localentnum = cl.playerentity;

	// call the prog init
	PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Init, "QC function CSQC_Init is missing");

	PRVM_End;
	cl.csqc_loaded = true;

	cl.csqc_vidvars.drawcrosshair = false;
	cl.csqc_vidvars.drawenginesbar = false;
}

void CL_VM_ShutDown (void)
{
	Cmd_ClearCsqcFuncs();
	Cvar_SetValueQuick(&csqc_progcrc, -1);
	Cvar_SetValueQuick(&csqc_progsize, -1);
	if(!cl.csqc_loaded)
		return;
	CSQC_BEGIN
		prog->globals.client->time = cl.time;
		PRVM_ExecuteProgram(prog->funcoffsets.CSQC_Shutdown, "QC function CSQC_Shutdown is missing");
		PRVM_ResetProg();
	CSQC_END
	Con_Print("CSQC ^1unloaded\n");
	cl.csqc_loaded = false;
}
