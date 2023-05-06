#include <stdio.h>
#include "solver/decision.h"
#include "solotest/layout.h"
#include "util/until.h"

#define CAP 32

int main(void);

int main(void) {
    unsigned char sz = 0;
    Layout layout[2] = { INITIAL_LAYOUT, INITIAL_LAYOUT };
    Decision decisionStack[CAP][CAP];
    unsigned char trace[CAP];

    /* Stack-based Solver */
    until (score_layout(layout[0]) == 1) {
        decisions_layout(decisionStack[sz], layout[0]);
        trace[sz] = count_decisions(decisionStack[sz]);
        until (trace[sz]) {
            sz--;
            undoDecision_layout(layout[0], decisionStack[sz][trace[sz]]);
        }
        applyDecision_layout(layout[0], decisionStack[sz][--trace[sz]]);
        sz++;
    }

    /* Print the solution! */
    print_layout(layout[1]);
    for (unsigned char i = 0; i < sz; i++) {
        printf("STEP %u: ", i+1);
        print_decision(decisionStack[i][trace[i]]);
        applyDecision_layout(layout[1], decisionStack[i][trace[i]]);
        print_layout(layout[1]);
    }

    return 0;
}
