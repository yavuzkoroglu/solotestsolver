#include <stdio.h>
#include "solotest/direction.h"
#include "solver/decision.h"

void print_decision(const Decision decision) {
    printf("FROM (%u,%u) TO ", decision.row, decision.col);
    switch (decision.dir) {
        case DIR_EAST:  puts("east");   break;
        case DIR_SOUTH: puts("south");  break;
        case DIR_WEST:  puts("west");   break;
        case DIR_NORTH: puts("north");
    }
}
