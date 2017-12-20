/*
 *  nb2opm.c
 *
 *  NB to OPM Converter
 *
 *  This program converts an input file from Temperley and
 *  Sleator's NB format to the OPM format.
 *
 *  Copyright (C) 2004 Tak-Shing Chan
 */

#include <stdio.h>
#include <stdlib.h>

#define LIST_MAX            8192

static void
die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    FILE                    *infile;
    char                    buf[80 + 1];
    struct { int O, P, M; } N[LIST_MAX];
    struct { int O, M; }    B[LIST_MAX];
    int                     m = 0, n = 0, i, j;

    /* Open the input file */
    if (argc != 2)
        die("usage: nb2opm infile");
    if (!(infile = fopen(argv[1], "r")))
        die("Cannot open input file");

    /* Read the note and beat lists */
    while (fscanf(infile, "%80[^\n]%*[^\n]", buf) == 1) {
        getc(infile);
        if (sscanf(buf, "Note %d %*d %d", &N[m].O, &N[m].P)
            == 2) {
            if (++m == LIST_MAX)
                die("Out of memory");
        } else if (sscanf(buf, "Beat %d %d", &B[n].O, &B[n].M)
            == 2) {
            if (++n == LIST_MAX)
                die("Out of memory");
        }
    }
    fclose(infile);

    /* Combine the two lists */
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (N[i].O == B[j].O)
                N[i].M = B[j].M;

    /* Output combined list in OPM format */
    printf("%d\n", m);
    for (i = 0; i < m; i++)
        printf("%d %d %d\n", N[i].O, N[i].P, N[i].M);
    return 0;
}
