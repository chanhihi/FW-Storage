/*
		Eng256 font to BPSF converter

		4096 바이트의 영문 글꼴을 zhcon에서 사용하는 BPSF로 변환합니다.
		zhcon에 대한 것은 http://zhcon.gnuchina.org를 방문하세요.

		4096 바이트의 영문 글꼴은 글꼴의 크기가 8x16으로서
		한 글자당 16 바이트를 차지하며 그 갯수가 ASCII
		문자와 동일한 256개입니다.

		즉, 16 x 256 = 총합 4096 바이트입니다.

		컴파일 : 

		gcc -Wall -s eng2bpsf.c -o eng2bpsf
		bcc32 -w eng2bpsf.c


		2002년 1월 19일
*/

/*
 * 		File eng2bpsf.c
 * 		Font Converter (Eng256 font to BPSF)
 * 		'2002.1.19
 * 		
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-----------------------------------------------------------------------------
#pragma pack(push, 1)	// 구조체를 1바이트 단위로 정렬

typedef unsigned char byte;
typedef unsigned long int dword;
typedef enum {false, true} bool;

typedef struct {
	byte psf_header[2];
	byte filemode;
	byte fontheight;
} TBPSF_Header1;

typedef struct {
	byte psf_header[2];
	byte filemode;
	byte charheight;
	byte charwidth;
	dword fontsize;
} TBPSF_Header2;

#pragma pack(pop)	// 구조체를 1바이트 단위로 정렬

//-----------------------------------------------------------------------------
byte EngFont[16 * 256];

TBPSF_Header2 BPSF_Header2 = {
	{0x36, 0x04},	// magic number
	0x04,	// filemode 4 : big charset, no unicode_data
	0x10,	// charheight (== 16)
	0x08,	// charwidth (== 8)
	256		// fontsize (== 94 x 94)
};


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
int main(int argc, char *argv[])
{
	FILE *fp;
	char eng256fontfile[30], bpsffontfile[30];

    if (argc != 3) {
        fprintf(stderr, "\nEng256 font to BPSF Converter 0.1");
        fprintf(stderr, "\nUsage: eng2bpsf eng256.fnt asc16.bpsf\n\n");
        exit(EXIT_FAILURE);
    }

    if ((argv[1][0] == '*') || (argv[2][0] == '*')) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    strcpy(eng256fontfile, argv[1]);
    strcpy(bpsffontfile, argv[2]);
	
    fprintf(stdout, "\nConverting %s to %s\n\n", eng256fontfile, bpsffontfile);
	
	if (LoadEngFont(eng256fontfile) == false) {
        fprintf(stderr, "\nFatal error: Eng256 English font not found\n");
        exit(EXIT_FAILURE);
	}

	//-------------------------------------------------------------------------
	fp = fopen(bpsffontfile, "wb");
	fwrite(&BPSF_Header2, sizeof(TBPSF_Header2), 1, fp);
	fwrite(EngFont, sizeof(EngFont), 1, fp);
	fclose(fp);

	return 0;
}
