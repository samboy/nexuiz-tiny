/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef COMMON_H
#define COMMON_H

// many buffers use this size
#define MAX_INPUTLINE 16384


// MSVC has a different name for several standard functions
#ifdef WIN32
# define strcasecmp stricmp
# define strncasecmp strnicmp
#endif

// Create our own define for Mac OS X
#if defined(__APPLE__) && defined(__MACH__)
# define MACOSX
#endif

#ifdef SUNOS
#include <sys/file.h>		// Needed for FNDELAY
# define model_t dp_model_t // Workaround conflict with /usr/include/sys/model.h
#endif

//============================================================================

typedef struct sizebuf_s
{
	qboolean	allowoverflow;	// if false, do a Sys_Error
	qboolean	overflowed;		// set to true if the buffer size failed
	unsigned char		*data;
	int			maxsize;
	int			cursize;
} sizebuf_t;

void SZ_Clear (sizebuf_t *buf);
unsigned char *SZ_GetSpace (sizebuf_t *buf, int length);
void SZ_Write (sizebuf_t *buf, const unsigned char *data, int length);
void SZ_HexDumpToConsole(const sizebuf_t *buf);

void Com_HexDumpToConsole(const unsigned char *data, int size);

unsigned short CRC_Block(const unsigned char *data, size_t size);

unsigned char COM_BlockSequenceCRCByteQW(unsigned char *base, int length, int sequence);

// these are actually md4sum (mdfour.c)
unsigned Com_BlockChecksum (void *buffer, int length);
void Com_BlockFullChecksum (void *buffer, int len, unsigned char *outbuf);


//============================================================================
//							Endianess handling
//============================================================================

// We use BSD-style defines: BYTE_ORDER is defined to either BIG_ENDIAN or LITTLE_ENDIAN

// Initializations
#if !defined(BYTE_ORDER) || !defined(LITTLE_ENDIAN) || !defined(BIG_ENDIAN) || (BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN)
# undef BYTE_ORDER
# undef LITTLE_ENDIAN
# undef BIG_ENDIAN
# define LITTLE_ENDIAN 1234
# define BIG_ENDIAN 4321
#endif

// If we still don't know the CPU endianess at this point, we try to guess
// normally including sys/types.h includes endian.h for the platform, which defines BYTE_ORDER, LITTLE_ENDIAN, and BIG_ENDIAN, however endian.h is a BSD-ism, and may not be present on all platforms (particularly windows)
#ifndef BYTE_ORDER
# if defined(WIN32) || defined (__i386) || defined(__amd64)
#  define BYTE_ORDER LITTLE_ENDIAN
# else
#  if defined(SUNOS)
#   if defined(__i386) || defined(__amd64)
#    define BYTE_ORDER LITTLE_ENDIAN
#   else
#    define BYTE_ORDER BIG_ENDIAN
#   endif
#  else
#   warning "Unable to determine the CPU endianess. Defaulting to little endian"
#   define BYTE_ORDER LITTLE_ENDIAN
#  endif
# endif
#endif


short ShortSwap (short l);
int LongSwap (int l);
float FloatSwap (float f);

#if BYTE_ORDER == LITTLE_ENDIAN
// little endian
#define BigShort(l) ShortSwap(l)
#define LittleShort(l) (l)
#define BigLong(l) LongSwap(l)
#define LittleLong(l) (l)
#define BigFloat(l) FloatSwap(l)
#define LittleFloat(l) (l)
#else
// big endian
#define BigShort(l) (l)
#define LittleShort(l) ShortSwap(l)
#define BigLong(l) (l)
#define LittleLong(l) LongSwap(l)
#define BigFloat(l) (l)
#define LittleFloat(l) FloatSwap(l)
#endif

unsigned int BuffBigLong (const unsigned char *buffer);
unsigned short BuffBigShort (const unsigned char *buffer);
unsigned int BuffLittleLong (const unsigned char *buffer);
unsigned short BuffLittleShort (const unsigned char *buffer);


//============================================================================

// these versions are purely for internal use, never sent in network protocol
// (use Protocol_EnumForNumber and Protocol_NumberToEnum to convert)
typedef enum protocolversion_e
{
	PROTOCOL_UNKNOWN,
	PROTOCOL_DARKPLACES7, // added QuakeWorld-style movement protocol to allow more consistent prediction
	PROTOCOL_DARKPLACES6, // various changes
	PROTOCOL_DARKPLACES5, // uses EntityFrame5 entity snapshot encoder/decoder which is based on a Tribes networking article at http://www.garagegames.com/articles/networking1/
	PROTOCOL_DARKPLACES4, // various changes
	PROTOCOL_DARKPLACES3, // uses EntityFrame4 entity snapshot encoder/decoder which is broken, this attempted to do partial snapshot updates on a QuakeWorld-like protocol, but it is broken and impossible to fix
	PROTOCOL_DARKPLACES2, // various changes
	PROTOCOL_DARKPLACES1, // uses EntityFrame entity snapshot encoder/decoder which is a QuakeWorld-like entity snapshot delta compression method
	PROTOCOL_QUAKEDP, // darkplaces extended quake protocol (used by TomazQuake and others), backwards compatible as long as no extended features are used
	PROTOCOL_NEHAHRAMOVIE, // Nehahra movie protocol, a big nasty hack dating back to early days of the Quake Standards Group (but only ever used by neh_gl.exe), this is potentially backwards compatible with quake protocol as long as no extended features are used (but in actuality the neh_gl.exe which wrote this protocol ALWAYS wrote the extended information)
	PROTOCOL_QUAKE, // quake (aka netquake/normalquake/nq) protocol
	PROTOCOL_QUAKEWORLD, // quakeworld protocol
}
protocolversion_t;

void MSG_WriteChar (sizebuf_t *sb, int c);
void MSG_WriteByte (sizebuf_t *sb, int c);
void MSG_WriteShort (sizebuf_t *sb, int c);
void MSG_WriteLong (sizebuf_t *sb, int c);
void MSG_WriteFloat (sizebuf_t *sb, float f);
void MSG_WriteString (sizebuf_t *sb, const char *s);
void MSG_WriteUnterminatedString (sizebuf_t *sb, const char *s);
void MSG_WriteAngle8i (sizebuf_t *sb, float f);
void MSG_WriteAngle16i (sizebuf_t *sb, float f);
void MSG_WriteAngle32f (sizebuf_t *sb, float f);
void MSG_WriteCoord13i (sizebuf_t *sb, float f);
void MSG_WriteCoord16i (sizebuf_t *sb, float f);
void MSG_WriteCoord32f (sizebuf_t *sb, float f);
void MSG_WriteCoord (sizebuf_t *sb, float f, protocolversion_t protocol);
void MSG_WriteVector (sizebuf_t *sb, float *v, protocolversion_t protocol);
void MSG_WriteAngle (sizebuf_t *sb, float f, protocolversion_t protocol);

extern	int			msg_readcount;
extern	qboolean	msg_badread;		// set if a read goes beyond end of message

void MSG_BeginReading (void);
int MSG_ReadLittleShort (void);
int MSG_ReadBigShort (void);
int MSG_ReadLittleLong (void);
int MSG_ReadBigLong (void);
float MSG_ReadLittleFloat (void);
float MSG_ReadBigFloat (void);
char *MSG_ReadString (void);
int MSG_ReadBytes (int numbytes, unsigned char *out);

#define MSG_ReadChar() (msg_readcount >= net_message.cursize ? (msg_badread = true, -1) : (signed char)net_message.data[msg_readcount++])
#define MSG_ReadByte() (msg_readcount >= net_message.cursize ? (msg_badread = true, -1) : (unsigned char)net_message.data[msg_readcount++])
#define MSG_ReadShort MSG_ReadLittleShort
#define MSG_ReadLong MSG_ReadLittleLong
#define MSG_ReadFloat MSG_ReadLittleFloat

float MSG_ReadAngle8i (void);
float MSG_ReadAngle16i (void);
float MSG_ReadAngle32f (void);
float MSG_ReadCoord13i (void);
float MSG_ReadCoord16i (void);
float MSG_ReadCoord32f (void);
float MSG_ReadCoord (protocolversion_t protocol);
void MSG_ReadVector (float *v, protocolversion_t protocol);
float MSG_ReadAngle (protocolversion_t protocol);

//============================================================================

typedef float (*COM_CharWidthFunc_t) (void *passthrough, char c);
typedef int (*COM_LineProcessorFunc) (void *passthrough, const char *line, size_t length, float width, qboolean isContination);
int COM_Wordwrap(const char *string, size_t length, float continuationSize, float maxWidth, COM_CharWidthFunc_t charWidth, void *passthroughCW, COM_LineProcessorFunc processLine, void *passthroughPL);

extern char com_token[MAX_INPUTLINE];

int COM_ParseToken_Simple(const char **datapointer, int returnnewline);
int COM_ParseToken_QuakeC(const char **datapointer, int returnnewline);
int COM_ParseToken_VM_Tokenize(const char **datapointer, int returnnewline);
int COM_ParseToken_Console(const char **datapointer);

extern int com_argc;
extern const char **com_argv;

int COM_CheckParm (const char *parm);
void COM_Init (void);
void COM_Shutdown (void);
void COM_InitGameType (void);

char	*va(const char *format, ...) DP_FUNC_PRINTF(1);
// does a varargs printf into a temp buffer


// snprintf and vsnprintf are NOT portable. Use their DP counterparts instead
#define snprintf DO_NOT_USE_SNPRINTF__USE_DPSNPRINTF
#define vsnprintf DO_NOT_USE_VSNPRINTF__USE_DPVSNPRINTF

// dpsnprintf and dpvsnprintf
// return the number of printed characters, excluding the final '\0'
// or return -1 if the buffer isn't big enough to contain the entire string.
// buffer is ALWAYS null-terminated
extern int dpsnprintf (char *buffer, size_t buffersize, const char *format, ...) DP_FUNC_PRINTF(3);
extern int dpvsnprintf (char *buffer, size_t buffersize, const char *format, va_list args);

// A bunch of functions are forbidden for security reasons (and also to please MSVS 2005, for some of them)
// LordHavoc: added #undef lines here to avoid warnings in Linux
#undef strcat
#define strcat DO_NOT_USE_STRCAT__USE_STRLCAT_OR_MEMCPY
#undef strncat
#define strncat DO_NOT_USE_STRNCAT__USE_STRLCAT_OR_MEMCPY
#undef strcpy
#define strcpy DO_NOT_USE_STRCPY__USE_STRLCPY_OR_MEMCPY
#undef strncpy
#define strncpy DO_NOT_USE_STRNCPY__USE_STRLCPY_OR_MEMCPY
//#undef sprintf
//#define sprintf DO_NOT_USE_SPRINTF__USE_DPSNPRINTF


//============================================================================

extern	struct cvar_s	registered;
extern	struct cvar_s	cmdline;

typedef enum gamemode_e
{
	GAME_NORMAL,
	GAME_HIPNOTIC,
	GAME_ROGUE,
	GAME_NEHAHRA,
	GAME_NEXUIZ,
	GAME_TRANSFUSION,
	GAME_GOODVSBAD2,
	GAME_TEU,
	GAME_BATTLEMECH,
	GAME_ZYMOTIC,
	GAME_SETHERAL,
	GAME_SOM,
	GAME_TENEBRAE, // full of evil hackery
	GAME_NEOTERIC,
	GAME_OPENQUARTZ, //this game sucks
	GAME_PRYDON,
	GAME_NETHERWORLD,
	GAME_THEHUNTED,
	GAME_DEFEATINDETAIL2,
	GAME_DARSANA,
	GAME_CONTAGIONTHEORY,
}
gamemode_t;

extern gamemode_t gamemode;
extern const char *gamename;
extern const char *gamedirname1;
extern const char *gamedirname2;
extern const char *gamescreenshotname;
extern const char *gameuserdirname;
extern char com_modname[MAX_OSPATH];

void COM_ToLowerString (const char *in, char *out, size_t size_out);
void COM_ToUpperString (const char *in, char *out, size_t size_out);
int COM_StringBeginsWith(const char *s, const char *match);

int COM_ReadAndTokenizeLine(const char **text, char **argv, int maxargc, char *tokenbuf, int tokenbufsize, const char *commentprefix);

size_t COM_StringLengthNoColors(const char *s, size_t size_s, qboolean *valid);
qboolean COM_StringDecolorize(const char *in, size_t size_in, char *out, size_t size_out, qboolean escape_carets);
void COM_ToLowerString (const char *in, char *out, size_t size_out);
void COM_ToUpperString (const char *in, char *out, size_t size_out);

typedef struct stringlist_s
{
	// maxstrings changes as needed, causing reallocation of strings[] array
	int maxstrings;
	int numstrings;
	char **strings;
} stringlist_t;

int matchpattern(const char *in, const char *pattern, int caseinsensitive);
void stringlistinit(stringlist_t *list);
void stringlistfreecontents(stringlist_t *list);
void stringlistappend(stringlist_t *list, char *text);
void stringlistsort(stringlist_t *list);
void listdirectory(stringlist_t *list, const char *path);

char *SearchInfostring(const char *infostring, const char *key);

void InfoString_GetValue(const char *buffer, const char *key, char *value, size_t valuelength);
void InfoString_SetValue(char *buffer, size_t bufferlength, const char *key, const char *value);
void InfoString_Print(char *buffer);

// strlcat and strlcpy, from OpenBSD
// Most (all?) BSDs already have them
#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined(MACOSX)
# define HAVE_STRLCAT 1
# define HAVE_STRLCPY 1
#endif

#ifndef HAVE_STRLCAT
/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t strlcat(char *dst, const char *src, size_t siz);
#endif  // #ifndef HAVE_STRLCAT

#ifndef HAVE_STRLCPY
/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t strlcpy(char *dst, const char *src, size_t siz);

#endif  // #ifndef HAVE_STRLCPY

#endif

