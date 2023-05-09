#include <stdio.h>
#include "direction.h"
#include "layout.h"
#include "util/unless.h"

void print_layout(Layout const layout) {
    for (unsigned char row = 0; row < LAYOUT_NROWS; row++)
        printf("%s\n", layout[row]);
}

/*
#define MOV_E       0
#define MOV_S       1
#define MOV_W       2
#define MOV_N       3
#define MOV_ES      4
#define MOV_EN      5
#define MOV_SW      6
#define MOV_WN      7
#define MOV_ESWN    8
#define MOV_I       { 0, 0 }
*/
unsigned char populateDecisions_layout(Decision* const restrict decisions, Layout const layout) {
    unsigned char sz = 0;
    /*
    static unsigned char const coordinates[9][9][2] = {
        { { 3, 0 }, { 3, 1 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 0, 3 }, { 1, 3 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 3, 5 }, { 3, 6 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 5, 3 }, { 6, 3 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 0, 2 }, { 1, 2 }, { 2, 0 }, { 2, 1 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 4, 0 }, { 4, 1 }, { 5, 2 }, { 6, 2 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 0, 4 }, { 1, 4 }, { 2, 5 }, { 2, 6 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 4, 5 }, { 4, 6 }, { 5, 4 }, { 6, 4 }, MOV_I, MOV_I, MOV_I, MOV_I, MOV_I },
        { { 2, 2 }, { 2, 3 }, { 2, 4 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 4, 2 }, { 4, 3 }, { 4, 4 } },
    };
    for (unsigned char i = 0; i < 2; i++) {
        unsigned char const row = coordinates[MOV_E][i][0];
        unsigned char const col = coordinates[MOV_E][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row][col + 1] == 'o' && layout[row][col + 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_EAST };
    }
    for (unsigned char i = 0; i < 2; i++) {
        unsigned char const row = coordinates[MOV_S][i][0];
        unsigned char const col = coordinates[MOV_S][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row + 1][col] == 'o' && layout[row + 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_SOUTH };
    }
    for (unsigned char i = 0; i < 2; i++) {
        unsigned char const row = coordinates[MOV_W][i][0];
        unsigned char const col = coordinates[MOV_W][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row][col - 1] == 'o' && layout[row][col - 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_WEST };
    }
    for (unsigned char i = 0; i < 2; i++) {
        unsigned char const row = coordinates[MOV_N][i][0];
        unsigned char const col = coordinates[MOV_N][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row - 1][col] == 'o' && layout[row - 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_NORTH };
    }
    for (unsigned char i = 0; i < 4; i++) {
        unsigned char const row = coordinates[MOV_ES][i][0];
        unsigned char const col = coordinates[MOV_ES][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row][col + 1] == 'o' && layout[row][col + 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_EAST };
        if (layout[row + 1][col] == 'o' && layout[row + 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_SOUTH };
    }
    for (unsigned char i = 0; i < 4; i++) {
        unsigned char const row = coordinates[MOV_EN][i][0];
        unsigned char const col = coordinates[MOV_EN][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row][col + 1] == 'o' && layout[row][col + 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_EAST };
        if (layout[row - 1][col] == 'o' && layout[row - 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_NORTH };
    }
    for (unsigned char i = 0; i < 4; i++) {
        unsigned char const row = coordinates[MOV_SW][i][0];
        unsigned char const col = coordinates[MOV_SW][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row + 1][col] == 'o' && layout[row + 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_SOUTH };
        if (layout[row][col - 1] == 'o' && layout[row][col - 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_WEST };
    }
    for (unsigned char i = 0; i < 4; i++) {
        unsigned char const row = coordinates[MOV_WN][i][0];
        unsigned char const col = coordinates[MOV_WN][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row][col - 1] == 'o' && layout[row][col - 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_WEST };
        if (layout[row - 1][col] == 'o' && layout[row - 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_NORTH };
    }
    for (unsigned char i = 0; i < 10; i++) {
        unsigned char const row = coordinates[MOV_ESWN][i][0];
        unsigned char const col = coordinates[MOV_ESWN][i][1];
        if (layout[row][col] != 'o') continue;
        if (layout[row][col + 1] == 'o' && layout[row][col + 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_EAST };
        if (layout[row + 1][col] == 'o' && layout[row + 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_SOUTH };
        if (layout[row][col - 1] == 'o' && layout[row][col - 2] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_WEST };
        if (layout[row - 1][col] == 'o' && layout[row - 2][col] == '.')
            decisions[sz++] = (Decision){ row, col, DIR_NORTH };
    }
    */

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
