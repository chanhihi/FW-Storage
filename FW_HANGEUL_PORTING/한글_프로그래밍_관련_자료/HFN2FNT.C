/*
		HFN format to DKBB format converter

		11008 바이트의 한라프로 글꼴을 11520 바이트의
		8x4x4 도깨비 한글 글꼴로 변환하는 유틸리티입니다.

		컴파일 :

		tcc -w hfn2fnt.c (Turbo C 2.01 or above)
		bcc32 -w hfn2fnt.c (Borland C++ for Win32)
		gcc -Wall -s hfn2fnt.c -o hfn2fnt.exe (DJGPP/GCC)

		2002년 1월 13일
*/

/*
 *      File HFN2FNT.C
 *      Font Converter(HFN format to DKBB format)
 *      '1990.07.24 (Original by Lim, I.K.)
 *      '1999.09.18 (Modified by)
 *		'2002.01.02 (Modified by)
 * 
 *      Compiler : Turbo C, DJGPP, GCC, BCC32 (Unix/Linux)
 *      
 *      tcc -w hfn2fnt.c (Turbo C 2.01 or above)
 *      bcc32 -w hfn2fnt.c (Borland C++ for Win32)
 *      gcc -Wall -s hfn2fnt.c -o hfn2fnt.exe (DJGPP/GCC)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANSIZE 32

typedef unsigned char byte;

/* Hangul font buffers */

static byte HF1[8][19][HANSIZE];  /* 8 set */
static byte HF2[4][21][HANSIZE];  /* 4 set */
static byte HF3[4][27][HANSIZE];  /* 4 set */
static byte HFFILL[HANSIZE];      /* fill code */


long filesize(FILE *fp)
{
	long curpos, length;

	curpos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, curpos, SEEK_SET);

	return length;
}

int main(int argc, char *argv[])
{
    FILE *fp;
	int i;
    char hanfontfile[1024], dkbbfontfile[1024];

    if (argc != 3) {
        fprintf(stderr, "Hangul font converter (11008 byte -> 11520 byte)\n");
        fprintf(stderr, "Usage: hfn2fnt hanfont.hfn hanfont.fnt\n");
        exit(EXIT_FAILURE);
    }
    if ((argv[1][0] == '*') || (argv[2][0] == '*')) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    strcpy(hanfontfile, argv[1]);
    strcpy(dkbbfontfile, argv[2]);

    fprintf(stdout, "\nConverting %s (11008 byte) to %s (11520 byte)\n",
            hanfontfile, dkbbfontfile);

    fp = fopen(hanfontfile, "rb");
    if (fp == NULL) {
        fprintf(stderr, "\nFatal error: HAN Hangul font not found\n");
        exit(EXIT_FAILURE);
    }

    if (filesize(fp) != 11008) {
        fprintf(stderr, "\nFatal error: This file can not convert (only 11008 byte)\n");
        exit(EXIT_FAILURE);
    }

    fread(HF1, sizeof(HF1), 1, fp);
    fread(HF2, sizeof(HF2), 1, fp);
    fread(HF3, sizeof(HF3), 1, fp);

    fclose(fp);

    fp = fopen(dkbbfontfile, "wb");

    for (i = 0; i < 8; i++) {
        fwrite(HFFILL, sizeof(HFFILL), 1, fp);
        fwrite(HF1[i], sizeof(HF1[i]), 1, fp);
    }
    for (i = 0; i < 4; i++) {
        fwrite(HFFILL, sizeof(HFFILL), 1, fp);
        fwrite(HF2[i], sizeof(HF2[i]), 1, fp);
    }
    for (i = 0; i < 4; i++) {
        fwrite(HFFILL, sizeof(HFFILL), 1, fp);
        fwrite(HF3[i], sizeof(HF3[i]), 1, fp);
    }

    fclose(fp);

    return 0;
}
