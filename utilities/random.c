/*
 *  random.c
 *
 *  Random Music Generator (after Jeong et al., 1998)
 *
 *  This program generates 1/f, white, brown or constant streams
 *  of melody and rhythm (each selectable from the command line).
 *  The output is in the form of a shell archive.
 *
 *  Copyright (C) 2005 Tak-Shing Chan
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dc.h"

/* Mersenne Twisters for melody and rhythm */
static mt_struct    *mtm, *mtr;

/* Uniform random numbers (mod n) for the melody stream */
static int
unifm(int n)
{
    return genrand_mt(mtm) % n;
}

/* Uniform random numbers (mod n) for the rhythm stream */
static int
unifr(int n)
{
    return genrand_mt(mtr) % n;
}

/* Brownian random numbers (mod n) for the melody stream */
static int
brownm(int n)
{
    static int      seed = -1;

    /* Uniform on first call, one-step random walk afterwards */
    seed = (seed < 0) ? unifm(n) : (seed + unifm(3) - 1 + n) % n;
    return seed;
}

/* Brownian random numbers (mod n) for the rhythm stream */
static int
brownr(int n)
{
    static int      seed = -1;

    /* Uniform on first call, one-step random walk afterwards */
    seed = (seed < 0) ? unifr(n) : (seed + unifr(3) - 1 + n) % n;
    return seed;
}

/* 1/f random numbers (mod n) for the melody stream */
static int
invfm(int n)
{
    static int      dice[20] = { -1 };
    int             i, sum = 0;

    if (dice[0] < 0) {
        /* Initialise all twenty dice on first trial */
        for (i = 0; i < 20; i++)
            dice[i] = unifm(6);
    } else {
        /* Use an index to keep track of dice numbers */
        int         index[20];
        for (i = 0; i < 20; i++)
            index[i] = i;

        /* Rethrow seven random dice (without replacement) */
        for (i = 0; i < 7; i++) {
            int j = unifm(20 - i);
            for (dice[index[j]] = unifm(6); j < 19 - i; j++)
                index[j] = index[j + 1];
        }
    }

    /* Calculate the sum of all twenty dice and rescale to fit */
    for (i = 0; i < 20; i++)
        sum += dice[i];
    return sum / 120.0 * n;
}

/* 1/f random numbers (mod n) for the rhythm stream */
static int
invfr(int n)
{
    static int      dice[20] = { -1 };
    int             i, sum = 0;

    if (dice[0] < 0) {
        /* Initialise all twenty dice on first trial */
        for (i = 0; i < 20; i++)
            dice[i] = unifr(6);
    } else {
        /* Use an index to keep track of dice numbers */
        int         index[20];
        for (i = 0; i < 20; i++)
            index[i] = i;

        /* Rethrow seven random dice (without replacement) */
        for (i = 0; i < 7; i++) {
            int j = unifr(20 - i);
            for (dice[index[j]] = unifr(6); j < 19 - i; j++)
                index[j] = index[j + 1];
        }
    }

    /* Calculate the sum of all twenty dice and rescale to fit */
    for (i = 0; i < 20; i++)
        sum += dice[i];
    return sum / 120.0 * n;
}

/* Constant random numbers (mod n) for the melody stream */
static int
constm(int n)
{
    return 9;
}

/* Constant random numbers (mod n) for the rhythm stream */
static int
constr(int n)
{
    return 1;
}


/* The main function */
int
main(int argc, char *argv[])
{
    int             runs;               /* Number of runs */
    int             steps;              /* Time steps */
    int             (*melody)(int);     /* Melody generator */
    int             (*rhythm)(int);     /* Rhythm generator */
    int             onset;              /* Onset time */
    int             duration;           /* Current duration */

    /* Specify appropriate parameters from the command line */
    if (argc != 5) {
        fprintf(stderr, "usage: %s runs steps melody rhythm\n",
            argv[0]);
        return EXIT_FAILURE;
    }

    /* First argument specifies the number of runs */
    if (sscanf(argv[1], "%d", &runs) != 1 || runs < 1) {
        fprintf(stderr, "Invalid number of runs\n");
        return EXIT_FAILURE;
    }

    /* Second argument specifies the number of time steps */
    if (sscanf(argv[2], "%d", &steps) != 1 || steps < 256) {
        fprintf(stderr, "Invalid number of time steps\n");
        return EXIT_FAILURE;
    }

    /* Third argument specifies the melody generator */
    switch (argv[3][0]) {
    case '1':
        melody = invfm;
        break;
    case 'w':
        melody = unifm;
        break;
    case 'b':
        melody = brownm;
        break;
    case 'c':
        melody = constm;
        break;
    default:
        fprintf(stderr, "Invalid melody generator\n");
        return EXIT_FAILURE;
    }

    /* Fourth argument specifies the rhythm generator */
    switch (argv[4][0]) {
    case '1':
        rhythm = invfr;
        break;
    case 'w':
        rhythm = unifr;
        break;
    case 'b':
        rhythm = brownr;
        break;
    case 'c':
        rhythm = constr;
        break;
    default:
        fprintf(stderr, "Invalid rhythm generator\n");
        return EXIT_FAILURE;
    }

    /* Create two 31-bit Mersenne Twisters with period 2^521-1 */
    srand(time(0));
    init_dc(rand());
    mtm = get_mt_parameter_id(31, 521, 0);
    mtr = get_mt_parameter_id(31, 521, 1);
    if (!mtm || !mtr) {
        fprintf(stderr, "Cannot initialise Mersenne Twisters\n");
        return EXIT_FAILURE;
    }
    sgenrand_mt(rand(), mtm);
    sgenrand_mt(rand(), mtr);

    /* Main loop */
    puts("#!/bin/sh");
    puts("# This is a shell archive.");
    do {
        printf("echo x - %d.notes\n", runs);
        printf("cat > %d.notes << EOF\n", runs);
        for (onset = 0; onset < steps; onset += duration) {
            duration = rhythm(16) + 1;
            printf("Note %d %d %d\n", onset * 125,
                (onset + duration) * 125, melody(36) + 43);
        }
        puts("EOF");
    } while (--runs);
    puts("exit 0");

    /* Clean up */
    free_mt_struct(mtr);
    free_mt_struct(mtm);
    return 0;
}
