/*
		Eng256 font to BDF format converter

		4096 바이트의 영문 글꼴을 BDF 파일로 변환합니다.
		물론 인코딩은 iso8859-1 입니다.

		4096 바이트의 영문 글꼴은 글꼴의 크기가 8x16으로서
		한 글자당 16 바이트를 차지하며 그 갯수가 ASCII
		문자와 동일한 256개입니다.

		즉, 16 x 256 = 총합 4096 바이트입니다.

		컴파일 : 

		gcc -Wall -s eng2bdf.c -o eng2bdf
		bcc32 -w eng2bdf.c


		2002년 1월 13일
*/

/*
 * 		File eng2bdf.c
 * 		Font Converter (Eng256 font to BDF format)
 * 		'2002.1.13, 16
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

byte EngFont[16 * 256];

int dwidth = 8;
int swidth = 8 * 72000 / (16 * 75);


//-----------------------------------------------------------------------------
int filesize(FILE *fp);
bool LoadEngFont(const char *engfile);
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
bool LoadEngFont(const char *engfile)
{
	FILE *fp;
	int size;

    fp = fopen(engfile, "rb");
	if (fp == NULL) return false;

    size = filesize(fp);
    if (size != 4096) return false;

	fread(EngFont, sizeof(EngFont), 1, fp);
    fclose(fp);

    return true;
}
//-----------------------------------------------------------------------------
void WriteHeader(char *Foundry, char *FamilyName)
{
	fprintf(fp, "\
STARTFONT 2.1\n\
FONT -%s-%s-medium-r-normal--16-160-75-75-m-80-iso8859-1\n\
SIZE 16 75 75\n\
FONTBOUNDINGBOX 8 16 0 -2\n\
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
SPACING \"m\"\n\
AVERAGE_WIDTH 80\n\
CHARSET_REGISTRY \"iso8859\"\n\
CHARSET_ENCODING \"1\"\n\
DEFAULT_CHAR 0\n\
FONT_ASCENT 14\n\
FONT_DESCENT 2\n\
ENDPROPERTIES\n\
CHARS 256\n\
", Foundry, FamilyName, Foundry, FamilyName);
}
//-----------------------------------------------------------------------------
void WriteChar(int Encoding, byte *Buff)
{
	int i;
	
	fprintf(fp, "STARTCHAR char%d\n", Encoding);
	fprintf(fp, "ENCODING %d\n", Encoding);
	fprintf(fp, "SWIDTH %d 0\n", swidth);
	fprintf(fp, "DWIDTH %d 0\n", dwidth);
	fprintf(fp, "BBX 8 16 0 -2\n");
	fprintf(fp, "BITMAP\n");

	for (i = 0; i < 16; i++) 
		fprintf(fp, "%02X\n", Buff[i]);
	
	fprintf(fp, "ENDCHAR\n");
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int Encoding, Pos = 0;
	char eng256fontfile[30], bdffontfile[30];

    if (argc != 3) {
        fprintf(stderr, "\nEng256 font to BDF Converter 0.11");
        fprintf(stderr, "\nUsage: eng2bdf eng256.fnt iso8859-1.bdf\n\n");
        exit(EXIT_FAILURE);
    }

    if ((argv[1][0] == '*') || (argv[2][0] == '*')) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    strcpy(eng256fontfile, argv[1]);
    strcpy(bdffontfile, argv[2]);
	
    fprintf(stdout, "\nConverting %s to %s\n\n", eng256fontfile, bdffontfile);
	
	if (LoadEngFont(eng256fontfile) == false) {
        fprintf(stderr, "\nFatal error: Eng256 English font not found\n");
        exit(EXIT_FAILURE);
	}

	//-------------------------------------------------------------------------
	fp = fopen(bdffontfile, "wt");
	
	WriteHeader("unknown", eng256fontfile);

	for (Encoding = 0; Encoding < (4096 / 16); Encoding++)
		WriteChar(Encoding, &EngFont[Pos]), Pos += 16;

	fprintf(fp, "ENDFONT\n");
	fclose(fp);

	return 0;
}
