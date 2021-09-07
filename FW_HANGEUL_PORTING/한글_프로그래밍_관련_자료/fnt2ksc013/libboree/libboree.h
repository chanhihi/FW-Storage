/*
 *		File libboree.h
 *		'2002.1.13
 *
 */


#ifndef __LIBBOREE_H
#define __LIBBOREE_H

#include <stdio.h>


//-----------------------------------------------------------------------------
typedef unsigned char byte;
typedef unsigned short int word;
#if __BORLANDC__
	typedef unsigned int dword;
#else
	typedef unsigned long int dword;	
#endif
typedef enum {false, true} bool;

typedef struct {
    dword F3	: 5;	// 종성
    dword F2	: 5;	// 중성
    dword F1	: 5;	// 초성
    dword MSB	: 1;	// MSB (최상위 비트) 1 - 한글, 0 - 영문
	dword Dummy	: 16;	// dummy
} THanCode;

typedef struct {
    byte Byte1;		// 한글의 하위 바이트 (오른쪽)
    byte Byte0;		// 한글의 상위 바이트 (왼쪽)
	byte Dymmy[2];
} THanByte;

typedef union {
	THanCode HanCode;
	THanByte HanByte;
} THangul;

typedef struct {
	byte F1[8][20][320];
	byte F2[4][22][320];
	byte F3[4][28][320];
} HANFONTN;

typedef struct {
	byte F1[8][20][32];
	byte F2[4][22][32];
	byte F3[4][28][32];
} HANFONT;


//-----------------------------------------------------------------------------
extern THangul _Hangul;

extern dword _JohabHangulTable[2350];
extern byte *_CodeTable[3];
extern byte *_F1B;
extern byte *_F2B;
extern byte *_F3B;

extern byte _LinkedIn_HanjaFont[156416];
extern byte _LinkedIn_SpcFont[36096];

extern byte _HanFontKS[2350][32];
extern byte _HanjaFont[4888][32];
extern byte _SpcFont[1128][32];

extern byte *_HangulJamo[51];
extern byte *_HangulJamoN[51];

extern HANFONT _HanFont;
extern HANFONTN _HanFontN;

void _complete(bool mode, byte *dest, byte *src, int nums);
void CompleteKS2350(void);
bool LoadHanFont(const char *hanfile);

#endif
