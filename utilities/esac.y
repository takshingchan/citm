/*
 *  esac.y
 *
 *  EsAC Parser
 *
 *  Copyright (C) 2005 Tak-Shing Chan
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Pulses per quarter note */
#define PPQN    192

/* State variables */
static int      tempo = 120, ppsn, transpose = 0;
static int      onset = 0, pitch, duration;
static int      saved_pitch = 0, saved_duration = 0;
static int      triplet_mode = 0;

/* Declarations for getopt */
int             getopt(int, char * const *, const char *);
extern char     *optarg;

/* Prototypes for yylex and yyparse */
int             yylex(void), yyparse(void);

/* Error handler */
static void
yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

/* Parse key */
static void
parsekey(char *s)
{
    char        *key, *board = "A BC D EF G";

    if ((key = strchr(board, s[0]))) {
        transpose = key - board;
        switch (s[1]) {
        case '#':
            transpose++;
            return;
        case 'b':
            transpose--;
        case 0:
            return;
        }
    }
    yyerror("invalid key, using default = \"C\"");
    transpose = 3;
}

/* Pulses to milliseconds */
static int
ptoms(int pulses)
{
    return 60000.0 * pulses / PPQN / tempo;
}

/* Emit saved note and buffer current note */
static void
buffered_emit(void)
{
    if (pitch >= 0) {
        if (saved_pitch)
            printf("Note %d %d %d\n", ptoms(onset), ptoms(onset +
                saved_duration), saved_pitch);
        onset += saved_duration;
        saved_pitch = pitch;
        saved_duration = duration;
    } else {
        saved_duration += duration;
    }
}

%}

%token DEGREE

%%

melody  : event melody
        | event '/' '/' {
                            /* Flush buffer at end of melody */
                            pitch = duration = 0;
                            buffered_emit();
                            YYACCEPT;
                        }
        ;

event   : note          {
                            if (triplet_mode)
                                duration = duration * 2 / 3;
                            buffered_emit();
                        }
        | '('           {
                            if (triplet_mode) {
                                yyerror("unexpected '('");
                                YYABORT;
                            }
                            triplet_mode++;
                        }
        | ')'           {
                            if (!triplet_mode) {
                                yyerror("unexpected ')'");
                                YYABORT;
                            }
                            triplet_mode--;
                        }
        ;

note    : note '.'      { duration += duration / 2; }
        | note '_'      { duration += duration; }
        | pitch         { pitch = $1; duration = ppsn; }
        | '0'           { pitch = 0; duration = ppsn; }
        | '^'           { pitch = -1; duration = ppsn; }
        ;

pitch   : '-' pitch     { $$ = $2 - 12; }
        | '+' pitch     { $$ = $2 + 12; }
        | DEGREE '#'    { $$ = $1 + 1; }
        | DEGREE 'b'    { $$ = $1 - 1; }
        | DEGREE        { $$ = $1; }
        ;

%%

/* A simple lexer */
int
yylex(void)
{
    int         c;
    static int  solfegge[] = { 57, 59, 61, 62, 64, 66, 68 };

    while (isspace(c = getchar()));     /* Ignore white-spaces */
    if (c >= '1' && c <= '7') {
        yylval = solfegge[c - '1'] + transpose;
        return DEGREE;
    }
    return c;
}

int
main(int argc, char *argv[])
{
    int         c, shortest = 0, keyoverride = 0;
    char        buf[5];

    /* Parse command line options */
    while ((c = getopt(argc, argv, "k:t:")) > 0) {
        switch (c) {
        case 'k':
            parsekey(optarg);
            keyoverride++;
            break;
        case 't':
            if (sscanf(optarg, "%d", &tempo) != 1) {
                yyerror("invalid tempo");
                return EXIT_FAILURE;
            }
            break;
        default:
            yyerror("usage: esac [-k key] [-t tempo]");
            return EXIT_FAILURE;
        }
    }

    /* Skip the name record */
    if (scanf("%*[^\n]") < 0) {
        yyerror("NAME not found");
        return EXIT_FAILURE;
    }

    /* Look for KEY and MEL records */
    for (;;) {
        if (scanf("%4s", buf) != 1) {
            yyerror("corrupted record");
            return EXIT_FAILURE;
        }
        if (!strcmp(buf, "KEY[")) {
            if (scanf("%*s%2d%2s", &shortest, buf) != 2) {
                yyerror("invalid KEY");
                return EXIT_FAILURE;
            }
            if (!keyoverride)
                parsekey(buf);
        } else if (!strcmp(buf, "MEL[")) {
            if (!shortest) {
                yyerror("MEL encountered before KEY");
                return EXIT_FAILURE;
            }
            ppsn = 4 * PPQN / shortest;
            return yyparse() ? EXIT_FAILURE : 0;
        } else {
            /* Ignore other records */
            if (scanf("%*[^\n]") < 0) {
                yyerror("corrupted record");
                return EXIT_FAILURE;
            }
        }
    }
}
