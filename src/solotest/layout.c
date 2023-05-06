#include <stdio.h>
#include "solotest/direction.h"
#include "solotest/layout.h"
#include "util/unless.h"

void print_layout(Layout const layout) {
    for (unsigned char row = 0; row < LAYOUT_NROWS; row++) {
        printf("%s\n", layout[row]);
    }
}

unsigned char score_layout(Layout const layout) {
    unsigned char score = 0;

    for (unsigned char row = 0; row < LAYOUT_NROWS; row++) {
        for (unsigned char col = 0; col < LAYOUT_NCOLS; col++) {
            score += (layout[row][col] == 'o');
        }
    }

    return score;
}

void decisions_layout(Decision* const restrict decisions, Layout const layout) {
    unsigned char sz = 0;

    for (unsigned char row = 0; row < LAYOUT_NROWS; row++) {
        for (unsigned char col = 0; col < LAYOUT_NCOLS; col++) {
            unless (layout[row][col] == 'o') continue;
            if (col < LAYOUT_NCOLS - 2 && layout[row][col + 1] == 'o' && layout[row][col + 2] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_EAST };
            if (row < LAYOUT_NROWS - 2 && layout[row + 1][col] == 'o' && layout[row + 2][col] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_SOUTH };
            if (col > 1 && layout[row][col - 1] == 'o' && layout[row][col - 2] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_WEST };
            if (row > 1 && layout[row - 1][col] == 'o' && layout[row - 2][col] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_NORTH };
        }
    }

    /* Special value denoting list end */
    decisions[sz] = (Decision){0,0,0};
}

void applyDecision_layout(Layout layout, Decision const decision) {
    layout[decision.row][decision.col] = '.';
    switch (decision.dir) {
        case DIR_EAST:
            layout[decision.row][decision.col + 1] = '.';
            layout[decision.row][decision.col + 2] = 'o';
            break;
        case DIR_SOUTH:
            layout[decision.row + 1][decision.col] = '.';
            layout[decision.row + 2][decision.col] = 'o';
            break;
        case DIR_WEST:
            layout[decision.row][decision.col - 1] = '.';
            layout[decision.row][decision.col - 2] = 'o';
            break;
        case DIR_NORTH:
            layout[decision.row - 1][decision.col] = '.';
            layout[decision.row - 2][decision.col] = 'o';
    }
}

void undoDecision_layout(Layout layout, Decision const decision) {
    layout[decision.row][decision.col] = 'o';
    switch (decision.dir) {
        case DIR_EAST:
            layout[decision.row][decision.col + 1] = 'o';
            layout[decision.row][decision.col + 2] = '.';
            break;
        case DIR_SOUTH:
            layout[decision.row + 1][decision.col] = 'o';
            layout[decision.row + 2][decision.col] = '.';
            break;
        case DIR_WEST:
            layout[decision.row][decision.col - 1] = 'o';
            layout[decision.row][decision.col - 2] = '.';
            break;
        case DIR_NORTH:
            layout[decision.row - 1][decision.col] = 'o';
            layout[decision.row - 2][decision.col] = '.';
    }
}
