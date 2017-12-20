//
//  info.cc
//
//  Cognitive Information
//
//  This program outputs the cognitive information of the OPM
//  file specified on the command line.
//
//  Copyright (C) 2005 Tak-Shing Chan
//

#include <iostream>
#include <cstdlib>
#include "opmfile.h"

using namespace std;

int
main(int argc, char *argv[])
{
    try {
        if (argc != 2)
            throw "usage: info file";

        // Output cognitive information
        opmfile X(argv[1]);
        cout << X.complexity() << endl;
    } catch (const char *s) {
        cout << s << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
