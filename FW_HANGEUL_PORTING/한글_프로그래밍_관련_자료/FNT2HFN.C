/*
 *		File FNT2HFN.C
 *		Font Converter(DKBB format to HFN format)
 *		'1990.07.24 (Written by Lim, I.K.)
 *		'2002.01.05 (Modified by)
 *
 *      Compiler : Turbo C, DJGPP, GCC, BCC32 (Unix/Linux/Win32)
 *      
 *      tcc -w hfn2fnt.c (Turbo C 2.01 or above)
 *      bcc32 -w hfn2fnt.c (Borland C++ for Win32)
 *      gcc -Wall -s hfn2fnt.c -o hfn2fnt.exe (DJGPP/GCC)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANSIZE	32

typedef unsigned char byte;

/* Hangul font buffers */

byte HF1[8][19][HANSIZE];  /* 8 set */
byte HF2[4][21][HANSIZE];  /* 4 set */
byte HF3[4][27][HANSIZE];  /* 4 set */

int main(int argc, char *argv[])
{
	FILE *fp;
    int i;
    char hanfontfile[1024], dkbbfontfile[1024];

    if (argc != 3) {
        fprintf(stderr, "\nUsage: fnt2hfn dkbbfont.fnt hanfont.hfn\n");
        exit(EXIT_FAILURE);
    }
    if ((argv[1][0] == '*') || (argv[2][0] == '*')) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    strcpy(dkbbfontfile, argv[1]);
    strcpy(hanfontfile, argv[2]);

    fprintf(stdout, "\nConterting %s to %s\n", dkbbfontfile, hanfontfile);

    fp = fopen(dkbbfontfile, "rb");
    if (fp == NULL) {
        fprintf(stderr, "\nFatal error: DKBB Hangul font not found\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 8; i++) {
        fseek(fp, HANSIZE, SEEK_CUR);  /* Skip fill code font */
        fread(HF1[i], sizeof(HF1[i]), 1, fp);
    }
    for (i = 0; i < 4; i++) {
        fseek(fp, HANSIZE, SEEK_CUR);  /* Skip fill code font */
        fread(HF2[i], sizeof(HF2[i]), 1, fp);
    }
    for (i = 0; i < 4; i++) {
        fseek(fp, HANSIZE, SEEK_CUR);  /* Skip fill code font */
        fread(HF3[i], sizeof(HF3[i]), 1, fp);
    }

    fclose(fp);

	fp = fopen(hanfontfile, "wb");

    fwrite(HF1, sizeof(HF1), 1, fp);
    fwrite(HF2, sizeof(HF2), 1, fp);
    fwrite(HF3, sizeof(HF3), 1, fp);

    fclose(fp);

	return 0;
}


/*

안녕하세요! 여러분의 시지프스 자료지기 sbsch6입니다.

이 프로그램은 아래 등록한 일반 한글 자형 화일을 하라프로 외
부 자형으로 변화하여 주는 유틸리티입니다. 다음 표는 한글 일
반 자형과 한라프로 자형을 비교한 표입니다.

     +----------+----------------+--------------------+
     | 비교내용 | 일반 한글 자형 | 한라프로 한글 자형 |
     +----------+----------------+--------------------+
     | 바 이 트 |    11,520      |      11,008        |
     | 벌    수 |   8 x 4 x 4    |     8 x 4 x 4      |
     | 글 자 수 |      360       |        344         |
     | 글자크기 |    16 x 16     |      16 x 16       |
     +----------+----------------+--------------------+

 위표를 보시고 바이트와 글자수를 보시면 다르 다는 것을 느끼
셨을 겁니다. 다른 이유는 할라프로를 제작 하신 임인건님이 내
장 자형의 크기를 약간이라도 줄여서 실행 파일의 크기를 줄리 
려는 의도 였던것 같습니다.

                      < 사용 방법 >

 일반 한글 자형 HANGUL.FNT를 하하 프로 용으로 변환 하려면
 FNT2HFN.COM과 HANGUL.FNT 화일이 있는 곳에서 다음과 같이
 도스프롬 프트 상에서 키보드를 마구 누른다.

 C:\>FNT2HFN HANGUL.FNT 

 위와 같이 하면은 같은 데렉 토리에 HANGUL.HFN이라는 한라프로
 용 한글 자형으로 편한 됩니다. 
 
                      < 제작 사양 >

  시  스  템  : 486DX2-66MHz. 
 컴 파  일 러 : Turbo C 2.0
  메모리모델  : Tiny 
 EXE2BIN 버젼 : Microsoft-DOS 6.22 EXE2BIN.EXE 
 
 질문 사항이나 버그는 
 나우누리 - SBSCH6, 천 리 안 - moleman으로 역락 바랍니다.

                              언재나 어디서나 ' GO SCOM 3 '                 

*/