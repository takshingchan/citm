//
//  opm.h
//
//  The OPM representation.
//
//  Copyright (C) 2005 Tak-Shing Chan
//

#ifndef OPM_H
#define OPM_H

struct opm {
    int                 o, p, m;
    explicit opm(int a = 0, int b = 0, int c = 0) : o(a), p(b),
        m(c) {}
};

#endif
