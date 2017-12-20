/*
 *  vitz.c
 *
 *  Random Music Generator (after Vitz, 1966)
 *
 *  This program generates 384 tone sequences as per Vitz's
 *  (1966) experiments, except that loudness characteristics is
 *  ignored.  The output is in the form of a shell archive.
 *
 *  Copyright (C) 2006 Tak-Shing Chan
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dc.h"

/* Mersenne Twisters for melody and rhythm */
static mt_struct    *mtm, *mtr;

/* Frequencies translated into MIDI pitch */
static int          frequencies[] = {
    67, 69, 65, 71, 63, 73, 61, 75, 57,
    59, 77, 79,  0, 43, 53, 83, 91, 99
};

/* Frequencies table */
static int          freqtable[] = {
    2, 4, 6, 8, 12, 18
};

/* Durations in milliseconds */
static int          durations[] = {
    500, 400, 200, 600, 100, 1200, 50, 1500
};

/* Durations table */
static int          durtable[] = {
    1, 2, 4, 6, 6, 8
};

/* The main function */
int
main(void)
{
    int             i, j, k;

    /* Create two 31-bit Mersenne Twisters with period 2^521-1 */
    srand(time(0));
    init_dc(rand());
    mtm = get_mt_parameter_id(31, 521, 0);
    mtr = get_mt_parameter_id(31, 521, 1);
    if (!mtm || !mtr) {
        fprintf(stderr, "Cannot initialise Mersenne Twisters\n");
        exit(EXIT_FAILURE);
    }
    sgenrand_mt(rand(), mtm);
    sgenrand_mt(rand(), mtr);

    /* Main loop */
    puts("#!/bin/sh");
    puts("# This is a shell archive.");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 64; j++) {
            int     onset = 0;
            printf("echo x - %d-%d.notes\n", i + 1, j + 1);
            printf("cat > %d-%d.notes << EOF\n", i + 1, j + 1);
            for (k = 0; k < 40; k++) {
                int duration = durations[genrand_mt(mtr) %
                    durtable[i]];
                printf("Note %d %d %d\n", onset, onset +
                    duration, frequencies[genrand_mt(mtm) %
                    freqtable[i]]);
                onset += duration + 50;
            }
            puts("EOF");
        }
    }
    puts("exit 0");

    /* Clean up */
    free_mt_struct(mtr);
    free_mt_struct(mtm);
    return 0;
}
