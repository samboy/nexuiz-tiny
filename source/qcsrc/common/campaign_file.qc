// CampaignFileLoad(offset, n)
// - Loads campaign level data (up to n entries starting at offset)
//   into the globals
// - Returns the number of entries successfully read
float CampaignFile_Load(float offset, float n)
{
	float fh;
	float lineno;
	float entlen;
	float i;
	string l, a;
	string fn;

	if(n > CAMPAIGN_MAX_ENTRIES)
		n = CAMPAIGN_MAX_ENTRIES;

	campaign_offset = offset;
	campaign_entries = 0;

	fn = strcat("maps/campaign", campaign_name, ".txt");
	fh = fopen(fn, FILE_READ);
	if(fh >= 0)
	{
		for(lineno = 0; (l = fgets(fh)); )
		{
			if(strlen(l) == 0)
				continue; // empty line
			if(substring(l, 0, 2) == "//")
				continue; // comment
			if(substring(l, 0, 3) == "\"//")
				continue; // comment
			if(lineno >= offset)
			{
				entlen = tokenize(l);

#define CAMPAIGN_GETARG0                  if(i >= entlen)
#define CAMPAIGN_GETARG1 CAMPAIGN_GETARG0     error("syntax error in campaign file: line has not enough fields");
#define CAMPAIGN_GETARG2 CAMPAIGN_GETARG1 a = argv(i++);
#define CAMPAIGN_GETARG3 CAMPAIGN_GETARG2 if(a == ",")
#define CAMPAIGN_GETARG4 CAMPAIGN_GETARG3     a = "";
#define CAMPAIGN_GETARG5 CAMPAIGN_GETARG4 else
#define CAMPAIGN_GETARG  CAMPAIGN_GETARG5     ++i
// What you're seeing here is what people will do when your compiler supports
// C-style macros but no line continuations.

				i = 0;
				CAMPAIGN_GETARG; campaign_gametype[campaign_entries] = strzone(a);
				CAMPAIGN_GETARG; campaign_mapname[campaign_entries] = strzone(a);
				CAMPAIGN_GETARG; campaign_bots[campaign_entries] = stof(a);
				CAMPAIGN_GETARG; campaign_botskill[campaign_entries] = stof(a);
				CAMPAIGN_GETARG; campaign_fraglimit[campaign_entries] = stof(a);
				CAMPAIGN_GETARG; campaign_mutators[campaign_entries] = strzone(a);
				CAMPAIGN_GETARG; campaign_shortdesc[campaign_entries] = strzone(a);
				CAMPAIGN_GETARG; campaign_longdesc[campaign_entries] = strzone(a);
				campaign_entries = campaign_entries + 1;

				if(campaign_entries >= n)
					break;
			}
			lineno = lineno + 1;
		}
		fclose(fh);
	}

	return campaign_entries;
}

void CampaignFile_Unload()
{
	float i;
	for(i = 0; i < campaign_entries; ++i)
	{
		strunzone(campaign_gametype[i]);
		strunzone(campaign_mapname[i]);
		strunzone(campaign_mutators[i]);
		strunzone(campaign_shortdesc[i]);
		strunzone(campaign_longdesc[i]);
	}
	campaign_entries = 0;
}
