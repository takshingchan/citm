/*
 *  opmcat.c
 *
 *  OPM Concatenator
 *
 *  This program concatenates several OPM files together.
 *
 *  Copyright (C) 2004 Tak-Shing Chan
 */

#include <stdio.h>
#include <stdlib.h>

#define LIST_MAX    8192

static void
die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    int             i, j, k = 0, n;
    FILE            *infile;
    int             O[LIST_MAX], P[LIST_MAX], M[LIST_MAX];

    /* Read each file in turn */
    for (i = 1; i < argc; i++) {
        if (!(infile = fopen(argv[i], "r")))
            die("Cannot open input file");

        /* Read data count */
        if (fscanf(infile, "%d", &n) != 1)
            die("Corrupted input");

        /* Read data */
        for (j = 0; j < n; j++) {
            if (fscanf(infile, "%d%d%d", &O[k], &P[k], &M[k])
                != 3)
                die("Error reading input");
            if (++k == LIST_MAX)
                die("Out of memory");
        }
        fclose(infile);
    }

    /* Output concatenated list */
    printf("%d\n", k);
    for (i = 0; i < k; i++)
        printf("%d %d %d\n", O[i], P[i], M[i]);
    return 0;
}
