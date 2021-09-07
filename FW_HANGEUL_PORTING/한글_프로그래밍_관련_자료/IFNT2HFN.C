/*
		안녕하세요. eleccom 김재우입니다.
		군대 제대하고 처음 인사드립니다.

		제대인사로 이야기 6.1 정품의 글꼴을 한라용으로 
		변환시켜주는 풀그림을 만들어 봤습니다.

		임인건님의 소스를 약간 변환 했고, 이야기 6.1에 
		있는 13056byte의 한글 글꼴만이 8벌체 글꼴로 변
		환이 가능합니다.

		사용예)
				ifnt2hfn ih01.fnt
				
		  라고 입력하면 ih01.hfn 화일 (11008 byte) 이 
		  생성된다.     

*/

/*
 *      File IFNT2HFN.C
 *      Font Converter(IYAGI 6.1 Font foramt to HFN format)
 *      '95.1.29
 *      Converted by Kim, j.w. ( Original : Lim, I.K ) 
 */


#include <dir.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE  (256)
#define HANSIZE      (32)
#define HF1SKIPSIZE  (4*HANSIZE)
#define HF2SKIPSIZE  (2*HANSIZE)
#define HF3SKIPSIZE  (4*HANSIZE)

/* Hangul font buffers */
static unsigned char HF1[8][19][HANSIZE];  /* 8 set */
static unsigned char HF2[4][21][HANSIZE];  /* 4 set */
static unsigned char HF3[4][27][HANSIZE];  /* 4 set */

void main(int argc, char *argv[])
{
    int handle, i;
    char hanfontfile[MAXPATH], dkbbfontfile[MAXPATH];
    char drive[MAXDRIVE], dir[MAXDIR];
    char name[MAXFILE], ext[MAXEXT];

    if (argc != 2) {
        fprintf(stderr, "\nUsage: Ifnt2hfn iyagifnt[.fnt]\n");
        exit(EXIT_FAILURE);
    }
    if ((fnsplit(argv[1], drive, dir, name, ext) & WILDCARDS) != 0) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    if (ext[0] == '\0') strcpy(ext, ".fnt");
    fnmerge(dkbbfontfile, drive, dir, name, ext);
    strcpy(ext, ".hfn");
    fnmerge(hanfontfile, drive, dir, name, ext);

    fprintf(stdout, "\nConterting %s to %s\n", dkbbfontfile, hanfontfile);

    handle = open(dkbbfontfile, O_RDONLY | O_BINARY);
    if (handle == -1) {
        fprintf(stderr, "\nFatal error: IYAGI Hangul font not found\n");
        exit(EXIT_FAILURE);
    }

    lseek(handle, HEADER_SIZE, SEEK_SET);  /* Skip iyagi font header */

    for (i = 0; i < 8; i++) {
        read(handle, HF1[i], sizeof(HF1[i]));
        lseek(handle, HF1SKIPSIZE, SEEK_CUR);  /* Skip fill code font */
    }
    for (i = 0; i < 4; i++) {
        read(handle, HF2[i], sizeof(HF2[i]));
		lseek(handle, HF2SKIPSIZE, SEEK_CUR);  /* Skip fill code font */
    }
    for (i = 0; i < 4; i++) {
        read(handle, HF3[i], sizeof(HF3[i]));
		lseek(handle, HF3SKIPSIZE, SEEK_CUR);  /* Skip fill code font */
    }

    close(handle);

    handle = _creat(hanfontfile, FA_ARCH);

    write(handle, HF1, sizeof(HF1));
    write(handle, HF2, sizeof(HF2));
    write(handle, HF3, sizeof(HF3));

    close(handle);
}
