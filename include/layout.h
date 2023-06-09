#ifndef LAYOUT_H
    #define LAYOUT_H
    #include "decision.h"

    /* There are 32 pegs in the initial layout. */
    #define NPEGS 32

    #define LAYOUT_NROWS 7
    #define LAYOUT_NCOLS 7

    #define INITIAL_LAYOUT {    \
        "  ooo  ",              \
        "  ooo  ",              \
        "ooooooo",              \
        "ooo.ooo",              \
        "ooooooo",              \
        "  ooo  ",              \
        "  ooo  "               \
    }

    typedef char Layout[LAYOUT_NROWS][LAYOUT_NCOLS+1];

    void print_layout(Layout const);
    unsigned char populateDecisions_layout(Decision* const restrict, Layout const, unsigned char const);
    void applyDecision_layout(Layout, Decision const);
    void undoDecision_layout(Layout, Decision const);
#endif
