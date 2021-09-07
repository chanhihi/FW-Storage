/*
 *		File font.c
 *		'2002.1.13
 *
 */


#include <stdio.h>
#include <string.h>

#include "libboree.h"


//-----------------------------------------------------------------------------
THangul _Hangul;

HANFONT _HanFont;
HANFONTN _HanFontN;

byte _HanFontKS[2350][32];	// 한글 2350자
byte _HanjaFont[4888][32];	// 한자 4888자
byte _SpcFont[1128][32];	// 특수문자 1128자


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
	int i, size;

    fp = fopen(hanfile, "rb");
	if (fp == NULL) return false;

    size = filesize(fp);
    if (size != 11520) return false;

	fread(&_HanFont, sizeof(HANFONT), 1, fp);
    fclose(fp);

	// 한글자모를 특수문자 영역에 배치
	
	for (i = 0; i < 51; i++)
		memcpy(_SpcFont[i + 282], _HangulJamo[i], 32);
		
    return true;
}
