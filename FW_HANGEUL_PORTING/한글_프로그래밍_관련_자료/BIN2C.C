/*
		바이너리 파일 -> C 데이터 배열 변환기
		------------------------------------------------------------

		바이너리 파일을 C 배열 데이터로 변환해 주는 유틸리티입니다.
		이러한 유틸리는 임의의 바이너리 파일을 실행 파일에
		내장시킬 때 필요합니다.

		예) 11520 바이트의 han.fnt 글꼴 파일을 C 배열로 변환시

			bin2c.exe han.fnt _hanfont1 hanfont.c

		이렇게 하면 hanfont.c 파일이 생성됩니다.
		생성된 파일의 내용은 다음과 같습니다.

		------------------------------------------------------------
		unsigned char _hanfont1[파일의크기] = {
		0x??, 0x??, 0x??, ...   // 한 줄에 16개씩 
		...
		...
		};
		------------------------------------------------------------

		이러한 내용의 소스를 생성해줍니다.

		2002년 1월 2일
*/

/*
 *		File BIN2C.C
 *		바이너리 -> C 배열 변환기
 *
 *		작성일 : 1999년 12월 18일
 *		갱신일 : 2002년 01월 02일
 *
 *		컴파일러 : Turbo C, DJGPP, GCC (Unix/Linux)
 *
 *		tcc -w bin2c.c
 *		gcc -Wall -s bin2c.c -o bin2c.exe
 *
 */



#include <stdio.h>

typedef unsigned char byte;


long filesize(FILE *stream)
{
    long curpos, length;

    curpos = ftell(stream);
    fseek(stream, 0L, SEEK_END);
    length = ftell(stream);
    fseek(stream, curpos, SEEK_SET);

    return length;
}

int main(int argc, char *argv[])
{
    byte buffer[16];
    int i, j;
    long length;
    FILE *fp1, *fp2;

    if (argc < 4) {
        puts("Binary to C Converter 1.0 (Programmed by PCHacker)");
        puts("Usage: bin2c.exe infile symname outfile\n");
        puts("   Ex) bin2c.exe han.fnt _hanfont hanfont.c");
        return -1;
    }

    fp1 = fopen(argv[1], "rb");
    if (fp1 == NULL) {
        puts("File open error...");
        return -1;
    }
    length = filesize(fp1);

    /* -------------------------------------------------------------------- */

    fp2 = fopen(argv[3], "wb");
    fprintf(fp2, "unsigned char %s[%ld] = {\n", argv[2], length);
    for (i = 0; i < (length / 16); i++) {
        fread(buffer, 16, 1, fp1);
        for (j = 0; j < 16; j++)
            fprintf(fp2, "0x%02X,", buffer[j]);
        fprintf(fp2, "\n");
    }

    if (length % 16 != 0) {
        fread(buffer, (size_t)(length % 16), 1, fp1);
        for (j = 0; j < length % 16; j++)
            fprintf(fp2, "0x%02X,", buffer[j]);
        fprintf(fp2, "\n};");
    } else fprintf(fp2, "};");

    fclose(fp1);
    fclose(fp2);

    return 0;
}
