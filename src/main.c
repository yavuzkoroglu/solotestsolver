#include <stdio.h>
#include "decision.h"
#include "layout.h"
#include "util/until.h"

/* Every turn, one peg is removed.
 * When only one peg is remaining, the puzzle is solved.
 * Since we have NPEGS == 32 pegs initially,
 * We say (turn_id == NPEGS - 1) <-> THE_PUZZLE_IS_SOLVED.
 */
#define THE_PUZZLE_IS_SOLVED (turn_id == NPEGS - 1)

int main(void);

int main(void) {
    /* We keep two copies of the initial layout
     * layout[0] is for solving the puzzle
     * layout[1] is for printing the solution from the beginning
     */
    Layout layout[2] = { INITIAL_LAYOUT, INITIAL_LAYOUT };

    /* This value is always (NPEGS-1) or smaller, see PUZZLE_IS_SOLVED */
    unsigned char turn_id = 0;

    /* We keep a list of decisions for every turn
     * decisions[m][n] denotes the nth decision of the mth turn
     */
    Decision decisions[NPEGS][NPEGS];

    /* decision_ids[m] denotes the current decision_id of the mth turn */
    unsigned char decision_ids[NPEGS];

    /******************************
     * PHASE 1: Solve the puzzle! *
     ******************************/

    /* This is a depth-first solver */
    until (THE_PUZZLE_IS_SOLVED) {
        /* Populate the list of decisions at turn == turn_id and select the last decision */
        decision_ids[turn_id] = populateDecisions_layout(decisions[turn_id], layout[0], turn_id);

        /* BACKTRACK (when there are no unexplored decisions) */
        until (decision_ids[turn_id]) {
            /* Take back one turn */
            turn_id--;
            undoDecision_layout(layout[0], decisions[turn_id][decision_ids[turn_id]]);
        }

        /* Next turn */
        applyDecision_layout(layout[0], decisions[turn_id][--decision_ids[turn_id]]);
        turn_id++;
    }

    /*******************************
     * PHASE 2: Print the solution *
     *******************************/

    /* Print the initial layout */
    print_layout(layout[1]);

    for (unsigned char i = 0; i < turn_id; i++) {
        printf("STEP %u: ", i+1);
        print_decision(decisions[i][decision_ids[i]]);
        applyDecision_layout(layout[1], decisions[i][decision_ids[i]]);
        print_layout(layout[1]);
    }

    return 0;
}
