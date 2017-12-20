#
#  Makefile
#
#  Useful Utilities
#
#  Copyright (C) 2007 Tak-Shing Chan
#

CC	= gcc
CFLAGS	= -ansi -pedantic -Wall -O3

all:	random esac nb2opm opmcat mutate opm2mid vitz

random:	random.o
	$(CC) $< -Ldcmt0.1/lib -ldcmt -o $@

esac:	esac.y
	yacc esac.y
	$(CC) $(CFLAGS) y.tab.c -ly -o $@

mutate:	mutate.o
	$(CC) $< -Ldcmt0.1/lib -ldcmt -o $@

opm2mid:	opm2mid.o melisma2003/mftext/midifile.o
	$(CC) $^ -o $@

vitz:	vitz.o
	$(CC) $< -Ldcmt0.1/lib -ldcmt -o $@

random.o:	random.c
	$(CC) $(CFLAGS) -c -Idcmt0.1/include $<

mutate.o:	mutate.c
	$(CC) $(CFLAGS) -c -Idcmt0.1/include $<

opm2mid.o:	opm2mid.c
	$(CC) $(CFLAGS) -c -Imelisma2003/mftext $<

vitz.o:	vitz.c
	$(CC) $(CFLAGS) -c -Idcmt0.1/include $<

clean:
	rm -f *.o y.tab.c
