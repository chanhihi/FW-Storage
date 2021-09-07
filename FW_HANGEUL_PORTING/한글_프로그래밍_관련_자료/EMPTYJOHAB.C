/*
	empty johab844-1 BDF Generator 0.11

	픽셀 사이즈, 글자의 폭, 글자의 높이를 입력으로 받아서
	그에 맞는 johab844-1 인코딩의 BDF를 생성합니다.
	물론 모든 비트맵은 0으로 채워집니다.

	16x16 이외에 다른 크기의 johab844-1 글꼴을 제작하고자 할 때
	그 조합을 테스트하고자 작성한 것입니다. bdf2bmp, bmp2bdf,
	그리고 함께 제공하는 844toksc 유틸리티를 사용하여
	그 최종 결과물을 확인해 보실 수 있습니다.

	컴파일 :

	gcc -Wall -s emptyjohab.c -o emptyjohab
	bcc32 -w emptyjohab.c


	2002년 1월 13일
*/

/*
 *		File emptyjohab.c
 *		johab844-1 FillBitmap BDF Generator
 *		'2002.1.13, 16
 *
 *		Written by Seokmin Lee (pchacker@pchacker.pe.kr)
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-----------------------------------------------------------------------------
FILE *fp;

int NibbleCount;
int Size, Width, Height;

int DWidth, SWidth;


//-----------------------------------------------------------------------------
void WriteChar(int Encoding)
{
	int x, y;
	
	fprintf(fp, "STARTCHAR char%X\n", Encoding);
	fprintf(fp, "ENCODING %d\n", Encoding);
	fprintf(fp, "SWIDTH %d 0\n", SWidth);
	fprintf(fp, "DWIDTH %d 0\n", DWidth);
	fprintf(fp, "BBX %d %d 0 -2\n", Width, Height);
	fprintf(fp, "BITMAP\n");

	for (y = 0; y < Height; y++) {
		for (x = 0; x < NibbleCount; x++)
			fprintf(fp, "0");
		fprintf(fp, "\n");
	}
	
	fprintf(fp, "ENDCHAR\n");
}
//-----------------------------------------------------------------------------
void PrintUsage(void)
{
	fprintf(stderr, "\nempty johab844-1 BDF Generator 0.12");
	fprintf(stderr, "\nUsage: emptyjohab pixelsize width height johab844.bdf\n\n");
	exit(EXIT_FAILURE);
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int i;

    if (argc != 5) PrintUsage();
	
	Size = atoi(argv[1]);
	Width = atoi(argv[2]);
	Height = atoi(argv[3]);

	if ((Size == 0) || (Width == 0) || (Height == 0))
		PrintUsage();
	
	//-------------------------------------------------------------------------
	NibbleCount = Width / 4;
	if (Width % 4 != 0) NibbleCount++;
	
	DWidth = Width;
	SWidth = DWidth * 72000 / (Size * 75);

	//-------------------------------------------------------------------------
	fp = fopen(argv[4], "wt");

	fprintf(fp, "STARTFONT 2.1\n");
	fprintf(fp, "FONT -unknown-%s-medium-r-normal--%d-%d-75-75-c-%d-johab844-1\n", argv[4], Size, Size * 10, Width * 10);
	fprintf(fp, "SIZE %d 75 75\n", Size);
	
	fprintf(fp, "FONTBOUNDINGBOX %d %d 0 -2\n", Width, Height);
	fprintf(fp, "STARTPROPERTIES 3\n");
	fprintf(fp, "DEFAULT_CHAR 0\n");
	fprintf(fp, "FONT_ASCENT %d\n", Size - 2);
	fprintf(fp, "FONT_DESCENT 2\n");
	fprintf(fp, "ENDPROPERTIES\n");
	fprintf(fp, "CHARS 360\n");
	
	for (i = 0; i < 360; i++)
		WriteChar(i);
	
	fprintf(fp, "ENDFONT\n");
	fclose(fp);
	
	return 0;
}
