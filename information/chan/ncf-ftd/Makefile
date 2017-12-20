#
#  Makefile
#
#  Musical Information
#
#  Copyright (C) 2007 Tak-Shing Chan
#

CC	= gcc
CXX	= g++
CXXFLAGS	= -ansi -pedantic -Wall -O3
LIBS	= -lm

all:	info cinfo dist1 dist2 dist3 uid1 uid2 uid3

info:	info.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

cinfo:	cinfo.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

dist1:	dist1.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

dist2:	dist2.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

dist3:	dist3.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

uid1:	uid1.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

uid2:	uid2.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

uid3:	uid3.o ftd.o
	$(CXX) -o $@ $^ $(LIBS)

info.o:	info.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

cinfo.o:	cinfo.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

dist1.o:	dist1.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

dist2.o:	dist2.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

dist3.o:	dist3.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

uid1.o:	uid1.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

uid2.o:	uid2.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

uid3.o:	uid3.cc opmfile.h opm.h ftd.h
	$(CXX) -c $(CXXFLAGS) $<

ftd.o:	ftd.c ftd.h
	$(CC) -c -O3 $<

clean:
	rm -f *.o
