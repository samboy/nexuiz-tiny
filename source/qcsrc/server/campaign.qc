// campaign cvars:
//   _campaign_index: index of CURRENT map
//   _campaign_name: name of the current campaign
//   g_campaign(name)_index: index of current LAST map (saved)
//   g_campaign_skill: bot skill offset

float campaign_level;
float campaign_won;
string campaign_index_var;
float checkrules_equality;

void(string s) CampaignBailout =
{
	cvar_set("g_campaign", "0");
	ServerConsoleEcho(strcat("campaign initialization failed: ", s), TRUE);
	return;
}

void() CampaignPreInit =
{
	float baseskill;
	string title;
	campaign_level = cvar("_campaign_index");
	campaign_name = strzone(cvar_string("_campaign_name"));
	campaign_index_var = strzone(strcat("g_campaign", campaign_name, "_index"));
	CampaignFile_Load(campaign_level, 2);
	if(campaign_entries < 1)
		return CampaignBailout("unknown map");
	cvar_set("bot_number", ftos(campaign_bots[0]));

	baseskill = cvar("g_campaign_skill");
	baseskill = baseskill + campaign_botskill[0];
	if(baseskill < 0)
		baseskill = 0;
	cvar_set("skill", ftos(baseskill));

	cvar_set("sv_public", "0");
	cvar_set("pausable", "1");

	title = campaign_shortdesc[0];
	title = strzone(strcat("Level ", ftos(campaign_level + 1), ": ", title));
	campaign_message = strzone(strcat("\n\n\n\n\n\n\n\n\n\n^1\n", title, "\n^3\n", wordwrap(campaign_longdesc[0], 50), "\n\n^1press jump to enter the game"));
	strunzone(title);
}

string GetMapname();
void() CampaignPostInit =
{
	// now some sanity checks
	string thismapname, wantedmapname;
	thismapname = GetMapname();
	wantedmapname = campaign_gametype[0];
	wantedmapname = strcat(wantedmapname, "_", campaign_mapname[0]);
	if(wantedmapname != thismapname)
		return CampaignBailout(strcat("wrong map: ", wantedmapname, " != ", thismapname));
	cvar_set("fraglimit", ftos(campaign_fraglimit[0]));
	cvar_set("timelimit", "0");
}

void CampaignSaveCvar(string cvarname, float value)
{
	float fh;
	float len;
	string contents;
	string l;

	registercvar(cvarname, ftos(value));
	cvar_set(cvarname, ftos(value));
	// note: cvarname must be remembered

	fh = fopen("campaign.cfg", FILE_READ);
	contents = "";
	if(fh >= 0)
	{
		while((l = fgets(fh)))
		{
			cvarname = strcat1(cvarname);
			contents = strcat1(contents);
			len = tokenize(l);
			if(len != 3)
				continue;
			if(argv(0) != "set")
				continue;
			if(argv(1) == cvarname)
				continue;
			contents = strcat(contents, "set ", argv(1), " ", argv(2), "\n");
		}
		fclose(fh);
	}
	contents = strcat(contents, "set ", cvarname,  " ", ftos(value), "\n");
	fh = fopen("campaign.cfg", FILE_WRITE);
	if(fh >= 0)
	{
		fputs(fh, contents);
	}
	else
	{
		error("Cannot write to campaign file");
	}
}

void() CampaignPreIntermission =
{
	entity head;
	float won;
	float lost;
	local string savevar;

	won = 0;

	head = findchain(classname, "player");
	while(head)
	{
		if(clienttype(head) == CLIENTTYPE_REAL)
		{
			if(head.winning)
				won = won + 1;
			else
				lost = lost + 1;
		}
		head = head.chain;
	}

	if(won == 1 && lost == 0 && checkrules_equality == 0)
	{
		campaign_won = 1;
		bprint("The current level has been WON.\n");
		// sound!
	}
	else
	{
		campaign_won = 0;
		bprint("The current level has been LOST.\n");
		// sound!
	}

	if(campaign_won)
	{
		if(campaign_entries < 2)
		{
			// I have won
			savevar = strcat("g_campaign", campaign_name, "_won");
			CampaignSaveCvar(savevar, 1);
		}
		else if(campaign_level == cvar(campaign_index_var))
		{
			// advance level
			CampaignSaveCvar(campaign_index_var, campaign_level + 1);
		}
	}
}

void() CampaignPostIntermission =
{
	// NOTE: campaign_won is 0 or 1, that is, points to the next level

	if(campaign_won && campaign_entries < 2)
	{
		// last map won!
		localcmd("togglemenu\n");
		CampaignFile_Unload();
		return;
	}

	CampaignSetup(campaign_won);
	CampaignFile_Unload();
	strunzone(campaign_message);
	strunzone(campaign_index_var);
	strunzone(campaign_name);
	campaign_name = "";
}



void(float n) CampaignLevelWarp =
{
	if(!sv_cheats)
		return;
	CampaignFile_Unload();
	CampaignFile_Load(n, 1);
	if(campaign_entries)
		CampaignSetup(0);
	else
		error("Sorry, cheater. You are NOT WELCOME.");
	CampaignFile_Unload();
}
