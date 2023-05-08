#include <stdio.h>
#include "decision.h"
#include "direction.h"

void print_decision(Decision const decision) {
    static char const directions[4][6] = { "east", "south", "west", "north" };
    printf("FROM (%u,%u) JUMP %s\n", decision.row, decision.col, directions[decision.dir]);
}
