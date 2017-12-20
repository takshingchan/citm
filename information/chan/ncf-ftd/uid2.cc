//
//  uid2.cc
//
//  Unity in Diversity
//
//  This program calculates the unity in diversity between two
//  OPM files (using the formula O / C).
//
//  Copyright (C) 2007 Tak-Shing Chan
//

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "opmfile.h"

using namespace std;

int
main(int argc, char *argv[])
{
    try {
        if (argc != 3)
            throw "usage: uid2 music listener";

        // Open input files
        opmfile X(argv[1]);
        double HX = X.complexity();
        opmfile Y(argv[2]);
        double HY = Y.complexity();
        opmfile XY(X, Y);
        double HXY = XY.complexity();

        // Output unity in diversity
        cout << max(0.0, HX + HY - HXY) / min(HX, HXY - HY) <<
            endl;
    } catch (const char *s) {
        cerr << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
