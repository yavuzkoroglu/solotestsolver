#include <stdio.h>
#include "direction.h"
#include "layout.h"
#include "util/unless.h"

void print_layout(Layout const layout) {
    for (unsigned char row = 0; row < LAYOUT_NROWS; row++)
        printf("%s\n", layout[row]);
}

unsigned char populateDecisions_layout(Decision* const restrict decisions, Layout const layout) {
    unsigned char sz = 0;

    for (unsigned char row = 0; row < LAYOUT_NROWS; row++) {
        for (unsigned char col = 0; col < LAYOUT_NCOLS; col++) {
            /* If no peg, no moves! */
            unless (layout[row][col] == 'o') continue;

            /* EAST */
            if (col < LAYOUT_NCOLS - 2 && layout[row][col + 1] == 'o' && layout[row][col + 2] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_EAST };

            /* SOUTH */
            if (row < LAYOUT_NROWS - 2 && layout[row + 1][col] == 'o' && layout[row + 2][col] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_SOUTH };

            /* WEST */
            if (col > 1 && layout[row][col - 1] == 'o' && layout[row][col - 2] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_WEST };

            /* NORTH */
            if (row > 1 && layout[row - 1][col] == 'o' && layout[row - 2][col] == '.')
                decisions[sz++] = (Decision){ row, col, DIR_NORTH };
        }
    }

    /* Return size */
    return sz;
}

static char const rowOffsets[4][2] = { { 0, 0 }, { 1, 2 }, { 0, 0 }, { -1, -2 } };
static char const colOffsets[4][2] = { { 1, 2 }, { 0, 0 }, { -1, -2 }, { 0, 0 } };
void applyDecision_layout(Layout layout, Decision const decision) {
    layout[decision.row][decision.col] = '.';
    layout[decision.row + rowOffsets[decision.dir][0]][decision.col + colOffsets[decision.dir][0]] = '.';
    layout[decision.row + rowOffsets[decision.dir][1]][decision.col + colOffsets[decision.dir][1]] = 'o';
}
void undoDecision_layout(Layout layout, Decision const decision) {
    layout[decision.row][decision.col] = 'o';
    layout[decision.row + rowOffsets[decision.dir][0]][decision.col + colOffsets[decision.dir][0]] = 'o';
    layout[decision.row + rowOffsets[decision.dir][1]][decision.col + colOffsets[decision.dir][1]] = '.';
}
