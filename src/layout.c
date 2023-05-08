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

    /*
    if (layout[0][2] == 'o') {
        if (layout[0][3] == 'o' && layout[0][4] == '.')
            decisions[sz++] = (Decision){ 0, 2, DIR_EAST };
        if (layout[1][2] == 'o' && layout[2][2] == '.')
            decisions[sz++] = (Decision){ 0, 2, DIR_SOUTH };
    }
    if (layout[0][3] == 'o' && layout[1][3] == 'o' && layout[2][3] == '.')
        decisions[sz++] = (Decision){ 0, 3, DIR_SOUTH };
    if (layout[0][4] == 'o') {
        if (layout[0][3] == 'o' && layout[0][2] == '.')
            decisions[sz++] = (Decision){ 0, 4, DIR_WEST };
        if (layout[1][4] == 'o' && layout[2][4] == '.')
            decisions[sz++] = (Decision){ 0, 2, DIR_SOUTH };
    }
    if (layout[1][2] == 'o') {
        if (layout[1][3] == 'o' && layout[1][4] == '.')
            decisions[sz++] = (Decision){ 0, 2, DIR_EAST };
        if (layout[2][2] == 'o' && layout[3][2] == '.')
            decisions[sz++] = (Decision){ 0, 2, DIR_SOUTH };
    }
    if (layout[0][3] == 'o' && layout[1][3] == 'o' && layout[2][3] == '.')
        decisions[sz++] = (Decision){ 0, 3, DIR_SOUTH };
    if (layout[0][4] == 'o') {
        if (layout[0][3] == 'o' && layout[0][2] == '.')
            decisions[sz++] = (Decision){ 0, 4, DIR_WEST };
        if (layout[1][4] == 'o' && layout[2][4] == '.')
            decisions[sz++] = (Decision){ 0, 2, DIR_SOUTH };
    }*/

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

static const char rowOffsets[4][2] = { { 0, 0 }, { 1, 2 }, { 0, 0 }, { -1, -2 } };
static const char colOffsets[4][2] = { { 1, 2 }, { 0, 0 }, { -1, -2 }, { 0, 0 } };
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
