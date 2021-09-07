/*
 *      File SFT2HFN.C
 *      Font Converter(HANGUL.SFT format to HFN format)
 *      '90.7.25
 *      Written by Lim, I.K.
 */


#include <dir.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handrv.h"

/* Hangul font buffers */

static byte HF1[10][19][HANSIZE];  /* 10 set */
static byte HF2[4][21][HANSIZE];   /* 4  set */
static byte HF3[4][27][HANSIZE];   /* 4  set */

void main(int argc, char *argv[])
{
    int handle1, handle2, i;
    char hfnfile1[MAXPATH], hfnfile2[MAXPATH], hfnfile3[MAXPATH];
    char hwpfontfile[MAXPATH];
    char drive[MAXDRIVE], dir[MAXDIR];
    char name1[MAXFILE], name2[MAXFILE], name3[MAXFILE], ext[MAXEXT];

    if (argc != 2) {
        fprintf(stderr, "\nUsage: sft2hfn hangul[.sft]\n");
        exit(EXIT_FAILURE);
    }
    if ((fnsplit(argv[1], drive, dir, name1, ext) & WILDCARDS) != 0) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    if (ext[0] == '\0') strcpy(ext, ".sft");
    fnmerge(hwpfontfile, drive, dir, name1, ext);

    strcpy(name2, name1);
    strcpy(name3, name1);
    strcpy(ext, ".hfn");
    strcat(name1, "1");
    fnmerge(hfnfile1, drive, dir, name1, ext);
    strcat(name2, "2");
    fnmerge(hfnfile2, drive, dir, name2, ext);
    strcat(name3, "3");
    fnmerge(hfnfile3, drive, dir, name3, ext);

    fprintf(stdout, "\nConterting %s to %s, %s and %s\n",
            hwpfontfile, hfnfile1, hfnfile2, hfnfile3);

    handle1 = open(hwpfontfile, O_RDONLY | O_BINARY);
    if (handle1 == -1) {
        fprintf(stderr, "\nFatal error: HWP Hangul font not found\n");
        exit(EXIT_FAILURE);
    }

    lseek(handle1, HANSIZE, SEEK_SET);  /* Skip header */
    for (i = 0; i < 10; i++) {
        read(handle1, HF1[i], sizeof(HF1[i]));
        lseek(handle1, HANSIZE * (31 - 19), SEEK_CUR);  /* Skip old code */
    }
    for (i = 0; i < 4; i++) {
        read(handle1, HF2[i], sizeof(HF2[i]));
        lseek(handle1, HANSIZE * (29 - 21), SEEK_CUR);  /* Skip old code */
    }
    for (i = 0; i < 4; i++) {
        read(handle1, HF3[i], sizeof(HF3[i]));
        lseek(handle1, HANSIZE * (31 - 27), SEEK_CUR);  /* Skip old code */
    }

    handle2 = _creat(hfnfile1, FA_ARCH);

    write(handle2, HF1, sizeof(HF1));
    write(handle2, HF2, sizeof(HF2));
    write(handle2, HF3, sizeof(HF3));

    close(handle2);

    for (i = 0; i < 7; i++) {
        read(handle1, HF1[i], sizeof(HF1[i]));
        lseek(handle1, HANSIZE * (31 - 19), SEEK_CUR);  /* Skip old code */
    }
    for (i = 0; i < 2; i++) {
        read(handle1, HF2[i], sizeof(HF2[i]));
        lseek(handle1, HANSIZE * (29 - 21), SEEK_CUR);  /* Skip old code */
    }
    for (i = 0; i < 2; i++) {
        read(handle1, HF3[i], sizeof(HF3[i]));
        lseek(handle1, HANSIZE * (31 - 27), SEEK_CUR);  /* Skip old code */
    }

    handle2 = _creat(hfnfile2, FA_ARCH);

    write(handle2, HF1, sizeof(*HF1) * 7);
    write(handle2, HF2, sizeof(*HF2) * 2);
    write(handle2, HF3, sizeof(*HF3) * 2);

    close(handle2);

    for (i = 0; i < 6; i++) {
        read(handle1, HF1[i], sizeof(HF1[i]));
        lseek(handle1, HANSIZE * (31 - 19), SEEK_CUR);  /* Skip old code */
    }
    for (i = 0; i < 2; i++) {
        read(handle1, HF2[i], sizeof(HF2[i]));
        lseek(handle1, HANSIZE * (29 - 21), SEEK_CUR);  /* Skip old code */
    }
    for (i = 0; i < 2; i++) {
        read(handle1, HF3[i], sizeof(HF3[i]));
        lseek(handle1, HANSIZE * (31 - 27), SEEK_CUR);  /* Skip old code */
    }

    handle2 = _creat(hfnfile3, FA_ARCH);

    write(handle2, HF1, sizeof(*HF1) * 6);
    write(handle2, HF2, sizeof(*HF2) * 2);
    write(handle2, HF3, sizeof(*HF3) * 2);

    close(handle2);

    close(handle1);
}
