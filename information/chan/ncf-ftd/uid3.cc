//
//  uid3.cc
//
//  Unity in Diversity
//
//  This program calculates the unity in diversity between two
//  OPM files (using the normalised formula H x D).
//
//  Copyright (C) 2007 Tak-Shing Chan
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "opmfile.h"

using namespace std;

int
main(int argc, char *argv[])
{
    try {
        if (argc != 3)
            throw "usage: uid3 music listener";

        // Open input files
        opmfile X(argv[1]);
        double HX = X.complexity();
        opmfile Y(argv[2]);
        double HY = Y.complexity();
        opmfile XY(X, Y);
        double HXY = XY.complexity();
        double F = (HX + HY - HXY) / HX;

        // Output unity in diversity
        if (F <= 0.0)
            cout << 0.0 << endl;
        else
            cout << -1.0 / log(2.0) * (F * log(F / (1 - F)) +
                log(1 - F)) * 2.0 * pow((F - 0.5), 2.0) << endl;
    } catch (const char *s) {
        cerr << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
