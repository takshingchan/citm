//
//  dist3.cc
//
//  Musical Distance (after Kvalseth, 1987)
//
//  This program outputs the musical distance between two OPM
//  files specified on the command line.
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
            throw "usage: dist3 file1 file2";

        // Open input files
        opmfile X(argv[1]);
        double HX = X.complexity();
        opmfile Y(argv[2]);
        double HY = Y.complexity();
        opmfile XY(X, Y);
        double HXY = XY.complexity();

        // Output musical distance
        cout << 1.0 - 2.0 * max(0.0, HX + HY - HXY) / (HX + HY) <<
            endl;
    } catch (const char *s) {
        cout << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
