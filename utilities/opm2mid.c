/*
 *  opm2mid.c
 *
 *  OPM to MIDI Converter
 *
 *  This program converts an OPM file into a MIDI file.
 *
 *  Copyright (C) 2006 Tak-Shing Chan
 */

#include <stdio.h>
#include <stdlib.h>
#include "midifile.h"

#define LIST_MAX    8192
#define PPQN        192

static void
die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

/* Prototypes for midifilelib */
void mf_write_tempo(unsigned long);
int mf_write_midi_event(unsigned long, unsigned, unsigned,
    unsigned char *, unsigned long);

static FILE         *outfile;
static int          O[LIST_MAX], P[LIST_MAX], M[LIST_MAX];
static int          k = 0;              /* Number of events */

static int
myputc(int c)
{
    return(putc(c, outfile));
}

static int
mywritetrack(int track)
{
    int             i, delta;
    unsigned char   note[2];

    mf_write_tempo(500000);
    note[0] = 0;                        /* Pitch */
    note[1] = 64;                       /* Velocity */

    for (i = 0; i < k; i++) {
        /* Turn off the previous note */
        if (note[0]) {
            /* Assume the input data are sorted by onsets */
            delta = (O[i] - O[i - 1]) / 60000.0 * PPQN * 120;
            if (delta < 0)
                return -1;
            if (!mf_write_midi_event(delta, note_off, 1, note, 2))
                return -1;
        }

        /* Turn on the current note */
        note[0] = P[i];
        if (!mf_write_midi_event(0, note_on, 1, note, 2))
            return -1;
    }

    /* Turn off the last note */
    if (note[0])
        if (!mf_write_midi_event(PPQN, note_off, 1, note, 2))
            return -1;
    return 1;
}

int
main(int argc, char *argv[])
{
    int             i, n;
    FILE            *infile;

    if (argc != 3)
        die("usage: opm2mid infile outfile");

    /* Read the input file */
    if (!(infile = fopen(argv[1], "r")))
        die("Cannot open input file");

    /* Read data count */
    if (fscanf(infile, "%d", &n) != 1)
        die("Corrupted input");

    /* Read data */
    for (i = 0; i < n; i++) {
        if (fscanf(infile, "%d%d%d", &O[k], &P[k], &M[k]) != 3)
            die("Error reading input");
        if (++k == LIST_MAX)
            die("Out of memory");
    }
    fclose(infile);

    /* Write to the output file */
    if (!(outfile = fopen(argv[2], "w")))
        die("Cannot open output file");
    Mf_putc = myputc;
    Mf_writetrack = mywritetrack;
    mfwrite(0, 1, PPQN, outfile);
    return 0;
}
