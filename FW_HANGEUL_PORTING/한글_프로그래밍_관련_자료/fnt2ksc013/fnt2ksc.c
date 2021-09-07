/*
 *		File fnt2ksc.c
 *		Font Converter (DKBB font to ksc5601.1987 BDF format)
 *		'2002.1.13, 16, 4.6
 *
 */

#ifdef __WIN32__
#include <conio.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libboree.h"


//-----------------------------------------------------------------------------

#define CHARS	9024

//-----------------------------------------------------------------------------
FILE *fp;

int DWidth = 16;
int SWidth = 16 * 72000 / (16 * 75);


//-----------------------------------------------------------------------------
void WriteHeader(char *Foundry, char *FamilyName, char msb, int DefaultChar);
void WriteChar(int Index, int Encoding, int sw);


//-----------------------------------------------------------------------------
void WriteHeader(char *Foundry, char *FamilyName, char msb, int DefaultChar)
{
	fprintf(fp, "\
STARTFONT 2.1\n\
FONT -%s-%s-medium-r-normal--16-160-75-75-c-160-ksc5601.1987-%c\n\
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
CHARSET_REGISTRY \"ksc5601.1987\"\n\
CHARSET_ENCODING \"%c\"\n\
DEFAULT_CHAR %d\n\
FONT_ASCENT 14\n\
FONT_DESCENT 2\n\
ENDPROPERTIES\n\
CHARS %d\n\
", Foundry, FamilyName, msb, Foundry, FamilyName, msb, DefaultChar, CHARS);
}
//-----------------------------------------------------------------------------
void WriteChar(int Index, int Encoding, int sw)
{
	int i;

	fprintf(fp, "STARTCHAR char%X\n", Encoding);
	fprintf(fp, "ENCODING %d\n", Encoding);
	fprintf(fp, "SWIDTH %d 0\n", SWidth);
	fprintf(fp, "DWIDTH %d 0\n", DWidth);
	fprintf(fp, "BBX 16 16 0 -2\n");
	fprintf(fp, "BITMAP\n");

	switch (sw) {
	case 0:
		for (i = 0; i < 16; i++) fprintf(fp, "0000\n");		
		break;
	case 1:		// 특수문자
		for (i = 0; i < 32; i += 2)
			fprintf(fp, "%02X%02X\n",
					_SpcFont[Index][i], _SpcFont[Index][i + 1]);
		break;
	case 2:		// 한글
		for (i = 0; i < 32; i += 2)
			fprintf(fp, "%02X%02X\n",
					_HanFontKS[Index][i], _HanFontKS[Index][i + 1]);
		break;
	case 3:		// 한자
		for (i = 0; i < 32; i += 2)
			fprintf(fp, "%02X%02X\n",
					_HanjaFont[Index][i], _HanjaFont[Index][i + 1]);
		break;
	}
	
	fprintf(fp, "ENDCHAR\n");
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int Index, High, Low, KSC_0;
	char dkbbfontfile[30], bdffontfile[30], msb;

    if (argc != 4) {
		fprintf(stderr, "\nDKBB Font To ksc5601.1987-0 BDF Converter 0.13");
		fprintf(stderr, "\nUsage: fnt2ksc [msb : 0 or 1] src.fnt dest.bdf");
		fprintf(stderr, "\nExam: fnt2ksc 0 dkbb.fnt ksc5601.bdf\n\n");
		exit(EXIT_FAILURE);
	}

    if ((argv[1][0] != '0') && (argv[1][0] != '1')) {
        fprintf(stderr, "\nError: Use msb 0 or 1\n");
        exit(EXIT_FAILURE);
    }

	msb = argv[1][0];
	
    if ((argv[2][0] == '*') || (argv[3][0] == '*')) {
        fprintf(stderr, "\nError: Don't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    strcpy(dkbbfontfile, argv[2]);
    strcpy(bdffontfile, argv[3]);

    fprintf(stdout, "\nConverting %s to %s\n\n", dkbbfontfile, bdffontfile);

	memcpy(_SpcFont, _LinkedIn_SpcFont, sizeof(_SpcFont));
	memcpy(_HanjaFont, _LinkedIn_HanjaFont, sizeof(_HanjaFont));
	
	if (LoadHanFont(dkbbfontfile) == false) {
		fprintf(stderr, "\nFatal error: DKBB Hangul font not found\n");
		exit(EXIT_FAILURE);
	}
	
	CompleteKS2350();
	
	//-------------------------------------------------------------------------
	if (msb == '0') KSC_0 = 0x80;
	else KSC_0 = 0;
	
	fp = fopen(bdffontfile, "wt");
	WriteHeader("unknown", dkbbfontfile, msb,
			((0xA1 - KSC_0) << 8) + 0xA1 - KSC_0);

	//-------------------------------------------------------------------------
	//	1. 특수문자
	Index = 0;
	
	for (High = 0xA1; High <= 0xAC; High++) {
		WriteChar(Index, ((High - KSC_0) << 8) + (0xA0 - KSC_0), 0);
		for (Low = 0xA1; Low <= 0xFE; Low++)
			WriteChar(Index, ((High - KSC_0) << 8) + (Low - KSC_0), 1), Index++;
		WriteChar(Index, ((High - KSC_0) << 8) + (0xFF - KSC_0), 0);
	}

	//-------------------------------------------------------------------------
	//	2. 사용자 정의
	for (High = 0xAD; High <= 0xAF; High++) {
		for (Low = 0xA1 - 1; Low <= 0xFE + 1; Low++)
			WriteChar(Index, ((High - KSC_0) << 8) + (Low - KSC_0), 0);
	}
	
	//-------------------------------------------------------------------------
	//	3. 한글
	Index = 0;
	
	for (High = 0xB0; High <= 0xC8; High++) {
		WriteChar(Index, ((High - KSC_0) << 8) + (0xA0 - KSC_0), 0);
		for (Low = 0xA1; Low <= 0xFE; Low++)
			WriteChar(Index, ((High - KSC_0) << 8) + (Low - KSC_0), 2), Index++;
		WriteChar(Index, ((High - KSC_0) << 8) + (0xFF - KSC_0), 0);
	}

	//-------------------------------------------------------------------------
	//	4. 사용자 정의
	High = 0xC9;
	for (Low = 0xA1 - 1; Low <= 0xFE + 1; Low++)
		WriteChar(Index, ((High - KSC_0) << 8) + (Low - KSC_0), 0);
	
	//-------------------------------------------------------------------------
	//	5. 한자
	Index = 0;
	
	for (High = 0xCA; High <= 0xFD; High++) {
		WriteChar(Index, ((High - KSC_0) << 8) + (0xA0 - KSC_0), 0);
		for (Low = 0xA1; Low <= 0xFE; Low++)
			WriteChar(Index, ((High - KSC_0) << 8) + (Low - KSC_0), 3), Index++;
		WriteChar(Index, ((High - KSC_0) << 8) + (0xFF - KSC_0), 0);
	}

	//-------------------------------------------------------------------------
	//	6. 사용자 정의
	High = 0xFE;
	for (Low = 0xA1 - 1; Low <= 0xFE + 1; Low++)
		WriteChar(Index, ((High - KSC_0) << 8) + (Low - KSC_0), 0);

	fprintf(fp, "ENDFONT\n");
	fclose(fp);

	return 0;
}

