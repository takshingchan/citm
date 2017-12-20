//
//  opmfile.h
//
//  OPM File Reader
//
//  This class converts input files into vectors and provides
//  an interface for the T-complexity measure (Titchener, 2000).
//
//  Copyright (C) 2005 Tak-Shing Chan
//

#ifndef OPMFILE_H
#define OPMFILE_H

#include <vector>
#include <fstream>
#include "opm.h"

using namespace std;

// Prototype for func_Calculate
extern "C" {
#   include "ftd.h"
}

class opmfile {
    vector<opm>         opmv;
public:
    explicit opmfile(const char *path) {
        // Opening input file
        ifstream        in(path);
        int             n;
        if (!(in && (in >> n)))
            throw "opmfile: error opening input";

        // Converting input file into vectors
        for (int i = 0; i < n; i++) {
            int         a, b, c;
            if (!(in >> a >> b >> c))
                throw "opmfile: error reading input";
            opmv.push_back(opm(a, b, c));
        }
    }

    // Joint OPM file
    opmfile(const opmfile &a, const opmfile &b) {
        // Concatenating OPM vectors
        opmv = a.opmv;
        opmv.insert(opmv.end(), b.opmv.begin(), b.opmv.end());
    }

    // T-complexity
    double complexity() const {
        double          d_Tcomplexity, d_Tinformation,
                        d_Tentropy;

        // Returning zero if opmv is empty
        if (!opmv.size())
            return 0;

        // Serialising into 32-bit signed integers
        vector<char>    serialised;
        for (vector<opm>::const_iterator i = opmv.begin(); i !=
            opmv.end(); ++i) {
            for (int j = 24; j >= 0; j -= 8)
                serialised.push_back((i->o >> j) & 0xff);
            for (int j = 24; j >= 0; j -= 8)
                serialised.push_back((i->p >> j) & 0xff);
            for (int j = 24; j >= 0; j -= 8)
                serialised.push_back((i->m >> j) & 0xff);
        }

        // Calculating complexity
        if (func_Calculate(reinterpret_cast<const char
            *>(&serialised[0]), serialised.size() - 1,
            &d_Tcomplexity, &d_Tinformation, &d_Tentropy,
            OPT_NO_PRINTOUT) != OK_TANALYZE)
            throw "opmfile: ftd error";
        return d_Tcomplexity;
    }
};

#endif
