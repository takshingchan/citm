//
//  opm.h
//
//  The OPM representation with extra functionalities:
//
//    -- subtraction;
//
//    -- rectification.
//
//  Copyright (C) 2005 Tak-Shing Chan
//

#ifndef OPM_H
#define OPM_H

#include <iostream>
#include <algorithm>

using namespace std;

struct opm {
    int                 o, p, m;
    explicit opm(int a = 0, int b = 0, int c = 0) : o(a), p(b),
        m(c) {}

    // Subtraction
    opm operator -(const opm &that) const {
        return opm(o - that.o, p - that.p, m - that.m);
    }

    // Rectification
    opm operator +() const {
        return opm(max(0, o), max(0, p), max(0, m));
    }
};

#endif
