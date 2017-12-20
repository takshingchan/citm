#
#  Makefile
#
#  Musical Information
#
#  Copyright (C) 2005 Tak-Shing Chan
#

CC	= gcc
CXX	= g++
CXXFLAGS	= -ansi -pedantic -Wall -O3
LIBS	= -lm

all:	info cinfo

info:	info.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

cinfo:	cinfo.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

info.o:	info.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

cinfo.o:	cinfo.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

ftd.o:	ftd.c ftd.h
	$(CC) -c -O3 $<

clean:
	rm -f *.o
