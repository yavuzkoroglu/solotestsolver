#ifndef LAYOUT_H
    #define LAYOUT_H
    #include "solver/decision.h"

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
    unsigned int score_layout(Layout const);
    Decision* decisions_layout(Layout const);
    void applyDecision_layout(Layout, Decision const);
    void undoDecision_layout(Layout, Decision const);
#endif
