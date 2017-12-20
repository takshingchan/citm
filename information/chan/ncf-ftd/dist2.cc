//
//  dist2.cc
//
//  Musical Distance (after Horibe, 1985)
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
            throw "usage: dist2 file1 file2";

        // Open input files
        opmfile X(argv[1]);
        double HX = X.complexity();
        opmfile Y(argv[2]);
        double HY = Y.complexity();

        // Output musical distance
        if (HX >= HY) {
            opmfile XY(X, Y);
            double HXY = XY.complexity();
            cout << min(HX, HXY - HY) / HX << endl;
        } else {
            opmfile YX(Y, X);
            double HYX = YX.complexity();
            cout << min(HY, HYX - HX) / HY << endl;
        }
    } catch (const char *s) {
        cout << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
