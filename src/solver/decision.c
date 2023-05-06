#include <stdio.h>
#include "solotest/direction.h"
#include "solver/decision.h"

void print_decision(Decision const decision) {
    printf("FROM (%u,%u) JUMP ", decision.row, decision.col);
    switch (decision.dir) {
        case DIR_EAST:  puts("east");   break;
        case DIR_SOUTH: puts("south");  break;
        case DIR_WEST:  puts("west");   break;
        case DIR_NORTH: puts("north");
    }
}

unsigned char count_decisions(Decision const* const restrict decisions) {
    unsigned char count = 0;
    while (IS_VALID_DECISION(decisions[count])) count++;
    return count;
}
