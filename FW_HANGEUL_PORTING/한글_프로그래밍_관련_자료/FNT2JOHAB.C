/*
 *		File fnt2johab.c
 *		Font Converter (DKBB format to johab844-1 BDF format)
 *		'2002.1.13, 16
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-----------------------------------------------------------------------------
typedef unsigned char byte;
typedef enum {false, true} bool;


//-----------------------------------------------------------------------------
FILE *fp;

byte HanFont[11520];
int DWidth = 16;
int SWidth = 16 * 72000 / (16 * 75);


//-----------------------------------------------------------------------------
int filesize(FILE *fp);
bool LoadHanFont(const char *hanfile);
void WriteHeader(char *Foundry, char *FamilyName);
void WriteChar(int Encoding, byte *Buff);


//-----------------------------------------------------------------------------
int filesize(FILE *fp)
{
	int curpos, length;

	curpos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, curpos, SEEK_SET);

	return length;
}
//-----------------------------------------------------------------------------
bool LoadHanFont(const char *hanfile)
{
	FILE *fp;
	int size;

    fp = fopen(hanfile, "rb");
	if (fp == NULL) return false;

    size = filesize(fp);
    if (size != 11520) return false;

	fread(HanFont, sizeof(HanFont), 1, fp);
    fclose(fp);

    return true;
}
//-----------------------------------------------------------------------------
void WriteHeader(char *Foundry, char *FamilyName)
{
	fprintf(fp, "\
STARTFONT 2.1\n\
FONT -%s-%s-medium-r-normal--16-160-75-75-c-160-johab844-1\n\
SIZE 16 75 75\n\
FONTBOUNDINGBOX 16 16 0 -2\n\
STARTPROPERTIES 17\n\
FOUNDRY \"%s\"\n\
FAMILY_NAME \"%s\"\n\
WEIGHT_NAME \"medium\"\n\
SLANT \"r\"\n\
SETWIDTH_NAME \"normal\"\n\
ADD_STYLE_NAME \"\"\n\
PIXEL_SIZE 16\n\
POINT_SIZE 160\n\
RESOLUTION_X 75\n\
RESOLUTION_Y 75\n\
SPACING \"c\"\n\
AVERAGE_WIDTH 160\n\
CHARSET_REGISTRY \"johab844\"\n\
CHARSET_ENCODING \"1\"\n\
DEFAULT_CHAR 0\n\
FONT_ASCENT 14\n\
FONT_DESCENT 2\n\
ENDPROPERTIES\n\
CHARS 360\n\
", Foundry, FamilyName, Foundry, FamilyName);
}
//-----------------------------------------------------------------------------
void WriteChar(int Encoding, byte *Buff)
{
	int i;
	
	fprintf(fp, "STARTCHAR char%d\n", Encoding);
	fprintf(fp, "ENCODING %d\n", Encoding);
	fprintf(fp, "SWIDTH %d 0\n", SWidth);
	fprintf(fp, "DWIDTH %d 0\n", DWidth);
	fprintf(fp, "BBX 16 16 0 -2\n");
	fprintf(fp, "BITMAP\n");

	for (i = 0; i < 32; i += 2) 
		fprintf(fp, "%02X%02X\n", Buff[i], Buff[i + 1]);
	
	fprintf(fp, "ENDCHAR\n");
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int Encoding, Pos = 0;
	char dkbbfontfile[30], bdffontfile[30];

    if (argc != 3) {
        fprintf(stderr, "\nDKBB Font To johab844-1 BDF Converter 0.12");
        fprintf(stderr, "\nUsage: fnt2johab dkbb.fnt johab844.bdf\n\n");
        exit(EXIT_FAILURE);
    }

    if ((argv[1][0] == '*') || (argv[2][0] == '*')) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    strcpy(dkbbfontfile, argv[1]);
    strcpy(bdffontfile, argv[2]);
	
    fprintf(stdout, "\nConverting %s to %s\n\n", dkbbfontfile, bdffontfile);
	
	if (LoadHanFont(dkbbfontfile) == false) {
        fprintf(stderr, "\nFatal error: DKBB Hangul font not found\n");
        exit(EXIT_FAILURE);
	}

	//-------------------------------------------------------------------------
	fp = fopen(bdffontfile, "wt");
	WriteHeader("unknown", dkbbfontfile);

	for (Encoding = 0; Encoding < (11520 / 32); Encoding++)
		WriteChar(Encoding, &HanFont[Pos]), Pos += 32;

	fprintf(fp, "ENDFONT\n");
	fclose(fp);

	return 0;
}
