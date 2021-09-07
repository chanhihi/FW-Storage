/*
		BPSF Generator 0.1

		X서버의 폰트를 zhcon에서 사용하는 BPSF로 생성합니다.
		ksc5601.1987-0 인코딩의 16 x 16 폰트만 가능합니다.
		zhcon에 대한 것은 http://zhcon.gnuchina.org를 방문하세요.

		컴파일 : gcc getbpsf.c -o getbpsf -L/usr/X11R6/lib -lX11


		2002년 1월 20일
*/

/*
 *		File getbpsf.c
 *		BPSF Generator
 *		'2002.1.20
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <X11/Xlib.h>


//----------------------------------------------------------------------------
#pragma pack(1)	// 구조체를 1바이트 단위로 정렬

typedef unsigned long int dword;
typedef unsigned char byte;

typedef struct {
	byte psf_header[2];
	byte filemode;
	byte fontheight;
} TBPSF_Header1;

typedef struct {
	byte psf_header[2];
	byte filemode;
	byte charwidth;
	byte charheight;
	dword fontsize;
} TBPSF_Header2;


//----------------------------------------------------------------------------
Display *Display1;
Window Window1;
GC GC1;
XGCValues GCValues1;
XImage *Image1;
XFontStruct *FontStruct1;
XChar2b Char2b;
dword Black, White;

FILE *fp;

int Width, Height;
byte FillBitmap[32] = {0x00, };
byte HanBitmap[32];
dword HanPixels[16 * 16];

TBPSF_Header2 BPSF_Header2 = {
	{0x36, 0x04},	// magic number
	0x04,	// filemode 4 : big charset, no unicode_data
	0x10,	// charwidth (== 16)
	0x10,	// charheight (== 16)
	8836	// fontsize (== 94 x 94)
};


//-----------------------------------------------------------------------------
void PixelsToBitmap(byte *HanBitmap, dword *HanPixels)
{
	byte Bit8[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	byte Temp = 0x00;
	int x, y, Pos = 0;

	for (y = 0; y < 32; y++) {
		Temp = 0x00;
		for (x = 0; x < 8; x++) {
			if (HanPixels[Pos] == Black) Temp |= Bit8[x];
			Pos++;
		}
		HanBitmap[y] = Temp;
	}
}
//-----------------------------------------------------------------------------
void GetBPSF(int StartCode, int EndCode)
{
	byte StartHigh = (byte)(StartCode >> 8);
	byte StartLow = (byte)StartCode;
	byte EndHigh = (byte)(EndCode >> 8);
	byte EndLow = (byte)EndCode;
	int high, low, x, y, Pos;

	for (high = StartHigh; high <= EndHigh; high++) {
		for (low = StartLow; low <= EndLow; low++) {
			Char2b.byte1 = high - 0x80;
			Char2b.byte2 = low - 0x80;
			XClearWindow(Display1, Window1);
			XDrawString16(Display1, Window1, GC1, 0, 14, &Char2b, 1);
			XFlush(Display1);
			
			Image1 = XGetImage(Display1, Window1, 0, 0,
					Width, Height, AllPlanes, ZPixmap);
			
			Pos = 0;
			for (y = 0; y < 16; y++) {
				for (x = 0; x < 16; x++) {
					HanPixels[Pos] = XGetPixel(Image1, x, y);
					Pos++;
				}
			}
			PixelsToBitmap(HanBitmap, HanPixels);
			fwrite(HanBitmap, sizeof(HanBitmap), 1, fp);
		}
	}
}
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	char *FontName; 
	const char *BPSF = "kscm-16.bpsf";
	
    if (argc != 2) {
		fprintf(stderr, "\nBPSF Generator 0.1");
		fprintf(stderr, "\nUsage: getbpsf fontset\n\n");
		exit(EXIT_FAILURE);
	}

	FontName = argv[1];
    fprintf(stdout, "\nGenerating %s\n\n", BPSF);
	
	
	//-------------------------------------------------------------------------
	Display1 = XOpenDisplay(NULL);
	FontStruct1 = XLoadQueryFont(Display1, FontName);
	if (FontStruct1 == NULL) {
		fprintf(stderr, "Fatal error: Font not found!\n\n");
		exit(EXIT_FAILURE);
	}

	Width  = FontStruct1->max_bounds.width;
	Height = FontStruct1->max_bounds.ascent + FontStruct1->max_bounds.descent;

	if ((Width != 16) || (Height != 16)) {
		fprintf(stderr, "Fatal error: Only 16 x 16 fonts available!\n\n");
		exit(EXIT_FAILURE);
	}
		

	//-------------------------------------------------------------------------
	Black = BlackPixel(Display1, DefaultScreen(Display1));
	White = WhitePixel(Display1, DefaultScreen(Display1));
	
	Window1 = XCreateSimpleWindow(Display1, DefaultRootWindow(Display1), 0, 0, Width, Height, 1, Black, White);
	XMapWindow(Display1, Window1);
	
	GCValues1.font = FontStruct1->fid;
	GCValues1.foreground = Black;
	GCValues1.background = White;
	GC1 = XCreateGC(Display1, Window1, GCFont | GCForeground | GCBackground, &GCValues1);
	XFlush(Display1);

	fp = fopen(BPSF, "wb");
	fwrite(&BPSF_Header2, sizeof(TBPSF_Header2), 1, fp);
	GetBPSF(0xA1A1, 0xACFE);
	fwrite(FillBitmap, sizeof(FillBitmap) * 94, 3, fp);
	GetBPSF(0xB0A1, 0xC8FE);
	fwrite(FillBitmap, sizeof(FillBitmap) * 94, 1, fp);
	GetBPSF(0xCAA1, 0xFDFE);
	fwrite(FillBitmap, sizeof(FillBitmap) * 94, 1, fp);
	fclose(fp);
	

	//-------------------------------------------------------------------------
	XDestroyWindow(Display1, Window1);
	XFreeFont(Display1, FontStruct1);
	XCloseDisplay(Display1);

	return 0;
}
