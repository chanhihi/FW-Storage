/*
 *		File completeks2350.c
 *		'2002.1.13
 *		
 */


#include <string.h>
#include "libboree.h"


#if __BORLANDC__
void _complete(bool mode, byte *dest, byte *src, int nums)
{
	int i;
	
	if (mode == true) memcpy(dest, src, nums);
	else for (i = 0; i < nums; i++) dest[i] |= src[i];
}

#else 
void _complete(bool mode, byte *dest, byte *src, int nums)
{
    __asm__ __volatile__("
        movl %3, %%ecx
        movl %1, %%edi
        movl %2, %%esi
        cmpl $1, %0
        jnz completehan__next2
        cld
        REP
        movsw

        jmp completehan__quit

completehan__next2:

        lodsw
        orw %%ax, (%%edi)
        incl %%edi
        incl %%edi
        loop completehan__next2

completehan__quit:
        "
        :
        : "g" (mode), "g" (dest), "g" (src), "g" (nums)
        : "ax", "cx", "si", "di", "memory"
    );
}
#endif 

#if __BORLANDC__
#pragma warn -8004
#endif

void CompleteKS2350(void)
{
    int i, F1 = 0, F2 = 0, F3 = 0;
	int F1B = 0, F2B = 0, F3B = 0;
    bool flag;
    byte buff[32];

	for (i = 0; i < 2350; i++) {
	    _Hangul.HanByte.Byte0 = (byte)(_JohabHangulTable[i] >> 8);
	    _Hangul.HanByte.Byte1 = (byte)(_JohabHangulTable[i]);

	    F1 = _CodeTable[0][_Hangul.HanCode.F1];
	    F2 = _CodeTable[1][_Hangul.HanCode.F2];
	    F3 = _CodeTable[2][_Hangul.HanCode.F3];

	    F3B = _F3B[F2];
	    F2B = _F2B[F1 * 2 + (F3 != 0)];
	    F1B = _F1B[F2 * 2 + (F3 != 0)];

	    flag = true;
	    if (F1) _complete(true, buff, _HanFont.F1[F1B][F1], 16), flag = false;
	    if (F2) _complete(flag, buff, _HanFont.F2[F2B][F2], 16), flag = false;
	    if (F3)	_complete(flag, buff, _HanFont.F3[F3B][F3], 16), flag = false;

		memcpy(_HanFontKS[i], buff, 32);
	}
}
