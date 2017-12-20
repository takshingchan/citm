/*
 *  mutate.c
 *
 *  OPM File Mutator
 *
 *  This program generates a series of mutations for an input
 *  OPM file.  Mutations are restricted to the range of the
 *  input and all the notes are chosen outside the C major scale.
 *  The output is in the form of a shell archive.
 *
 *  Copyright (C) 2005 Tak-Shing Chan
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "dc.h"

/* Maximum file size */
#define LIST_MAX    8192

/* The OPM representation */
struct opm { int O, P, M; };

/* Error handler */
static void
die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

/* Mersenne Twister */
static mt_struct    *mt;

/* Range-restricted mutation */
static void
mutate(struct opm *list, int m, int n)
{
    int             i, j;
    int             lo = INT_MAX, hi = INT_MIN;
    int             *index;
    int             pc;

    /* Range determination */
    for (i = 0; i < n; i++) {
        if (lo > list[i].P)
            lo = list[i].P;
        if (hi < list[i].P)
            hi = list[i].P;
    }

    /* Use an index to keep track of the mutated notes */
    index = malloc(n * sizeof *index);
    for (i = 0; i < n; i++)
        index[i] = i;

    /* Rethrow m random dice (without replacement) */
    for (i = 0; i < m; i++) {
        j = genrand_mt(mt) % (n - i);
        do {
            /* Restrict mutated pitches to non-tonal */
            list[index[j]].P = genrand_mt(mt) % (hi - lo + 1) +
                lo;
            pc = list[index[j]].P % 12;
        } while (pc != 1 && pc != 3 && pc != 6 && pc != 8 && pc
            != 10);
        for (; j < n - i - 1; j++)
            index[j] = index[j + 1];
    }
    free(index);
}

int
main(int argc, char *argv[])
{
    FILE            *infile;
    struct opm      N[LIST_MAX], M[LIST_MAX];
    int             i, j;
    int             n;

    /* Checking parameters */
    if (argc != 2)
        die("usage: mutate infile");

    /* Reading the input file */
    if (!(infile = fopen(argv[1], "r")))
        die("Error opening input file");
    if (fscanf(infile, "%d", &n) != 1)
        die("Error reading input file");
    if (n >= LIST_MAX)
        die("Input file too large");
    for (i = 0; i < n; i++)
        if (fscanf(infile, "%d %d %d", &N[i].O, &N[i].P, &N[i].M)
            != 3)
            die("Error reading input file");
    fclose(infile);

    /* Creating a 31-bit Mersenne Twister with period 2^521-1 */
    srand(time(0));
    init_dc(rand());
    if (!(mt = get_mt_parameter(31, 521)))
        die("Error initialising the Mersenne Twister");
    sgenrand_mt(rand(), mt);

    /* Main loop */
    puts("#!/bin/sh");
    puts("# This is a shell archive.");
    for (i = 0; i < n; i += 5) {
        printf("echo x - %d.opm\n", i);
        printf("cat > %d.opm << EOF\n", i);
        printf("%d\n", n);
        memcpy(M, N, sizeof N);
        mutate(M, i, n);
        for (j = 0; j < n; j++)
            printf("%d %d %d\n", M[j].O, M[j].P, M[j].M);
        puts("EOF");
    }
    puts("exit 0");

    /* Clean up */
    free_mt_struct(mt);
    return 0;
}
