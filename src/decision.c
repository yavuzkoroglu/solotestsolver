#include <stdio.h>
#include "decision.h"
#include "direction.h"

void print_decision(Decision const decision) {
    printf("FROM (%u,%u) JUMP ", decision.row, decision.col);
    switch (decision.dir) {
        case DIR_EAST:  puts("east");   break;
        case DIR_SOUTH: puts("south");  break;
        case DIR_WEST:  puts("west");   break;
        case DIR_NORTH: puts("north");
    }
}
