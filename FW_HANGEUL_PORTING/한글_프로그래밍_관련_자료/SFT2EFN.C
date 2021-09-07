/*
 *      File SFT2EFN.C
 *      Font Converter(ASCII.SFT format to EFN format)
 *      '90.8.2
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

/* English font buffers */

static byte BFN[11][ENGSIZE];
static byte EFS[94][ENGSIZE];
static byte SPF[51][ENGSIZE];

void main(int argc, char *argv[])
{
    int handle1, handle2, i;
    char hwpfontfile[MAXPATH];
    char bfnfile[MAXPATH], efsfile[MAXPATH], spffile[MAXPATH];
    char drive[MAXDRIVE], dir[MAXDIR];
    char name1[MAXFILE], name2[MAXFILE], ext[MAXEXT];
    char num[2];

    if (argc != 2) {
        fprintf(stderr, "\nUsage: sft2hfn ascii[.sft]\n");
        exit(EXIT_FAILURE);
    }
    if ((fnsplit(argv[1], drive, dir, name1, ext) & WILDCARDS) != 0) {
        fprintf(stderr, "\nDon't use wildcards\n");
        exit(EXIT_FAILURE);
    }

    if (ext[0] == '\0') strcpy(ext, ".sft");
    fnmerge(hwpfontfile, drive, dir, name1, ext);

    handle1 = open(hwpfontfile, O_RDONLY | O_BINARY);
    if (handle1 == -1) {
        fprintf(stderr, "\nFatal error: HWP ASCII font not found\n");
        exit(EXIT_FAILURE);
    }

    lseek(handle1, ENGSIZE * 34, SEEK_SET);

    /* Extract box fonts */

    for (i = 0; i < 7; i++) {
        strcpy(ext, ".bfn");
        strcpy(name2, name1);
        strcat(name2, itoa(i + 1, num, 10));
        fnmerge(bfnfile, drive, dir, name2, ext);
        fprintf(stdout, "\nExtracting box fonts from %s to %s",
                hwpfontfile, bfnfile);
        read(handle1, BFN, sizeof(BFN));
        handle2 = _creat(bfnfile, FA_ARCH);
        write(handle2, BFN, sizeof(BFN));
        close(handle2);
    }

    /* Extract English fonts and special fonts */

    for (i = 0; i < 6; i++) {

        strcpy(ext, ".efs");
        strcpy(name2, name1);
        strcat(name2, itoa(i + 1, num, 10));
        fnmerge(efsfile, drive, dir, name2, ext);
        fprintf(stdout, "\nExtracting English fonts from %s to %s",
                hwpfontfile, efsfile);

        lseek(handle1, ENGSIZE, SEEK_CUR);  /* Skip Space */
        read(handle1, EFS, sizeof(EFS));
        lseek(handle1, ENGSIZE, SEEK_CUR);  /* Skip Del */

        handle2 = _creat(efsfile, FA_ARCH);
        write(handle2, EFS, sizeof(EFS));
        close(handle2);

        if (i < 2) {
            strcpy(ext, ".spf");
            fnmerge(spffile, drive, dir, name2, ext);
            fprintf(stdout, "\nExtracting special fonts from %s to %s",
                    hwpfontfile, spffile);
            read(handle1, SPF, sizeof(SPF));
            handle2 = _creat(spffile, FA_ARCH);
            write(handle2, SPF, sizeof(SPF));
            close(handle2);
        } else lseek(handle1, sizeof(SPF), SEEK_CUR);
    }

    close(handle1);

    printf("\n");
}
