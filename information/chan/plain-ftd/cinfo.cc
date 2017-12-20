//
//  cinfo.cc
//
//  Conditional Cognitive Information
//
//  This program outputs the conditional cognitive information of
//  the first OPM file given the second.
//
//  Copyright (C) 2005 Tak-Shing Chan
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
            throw "usage: cinfo file1 file2";

        // Open input files
        opmfile X(argv[1]);
        double HX = X.complexity();
        opmfile Y(argv[2]);
        double HY = Y.complexity();
        opmfile XY(X, Y);
        double HXY = XY.complexity();

        // Output conditional cognitive information
        cout << min(HX, HXY - HY) << endl;
    } catch (const char *s) {
        cout << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
