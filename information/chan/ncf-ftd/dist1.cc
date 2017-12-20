//
//  dist1.cc
//
//  Musical Distance (after Rajski, 1961)
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
            throw "usage: dist1 file1 file2";

        // Open input files
        opmfile X(argv[1]);
        double HX = X.complexity();
        opmfile Y(argv[2]);
        double HY = Y.complexity();
        opmfile XY(X, Y);
        double HXY = XY.complexity();
        opmfile YX(Y, X);
        double HYX = YX.complexity();

        // Output musical distance
        cout << (min(HX, HXY - HY) + min(HY, HYX - HX)) / HXY <<
            endl;
    } catch (const char *s) {
        cout << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
