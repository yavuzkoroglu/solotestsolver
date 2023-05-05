#include <stdio.h>
#include <stdlib.h>
#include "solver/decision.h"
#include "solotest/layout.h"
#include "util/until.h"

int main(void);

int main(void) {
    size_t count = 0;
    size_t sz = 0;
    size_t cap = BUFSIZ;
    Layout layout[2] = { INITIAL_LAYOUT, INITIAL_LAYOUT };
    Decision** decisionStack = NULL;
    size_t* trace = NULL;

    decisionStack = malloc(cap * sizeof(Decision*));
    trace = malloc(cap * sizeof(size_t));

    /* Stack-based Solver */
    decisionStack[sz] = decisions_layout(layout[0]);
    until (score_layout(layout[0]) == 1) {
        count = count_decisions(decisionStack[sz]);
        if (count) {
            trace[sz] = count - 1;
            applyDecision_layout(layout[0], decisionStack[sz][trace[sz]]);
        } else {
            free(decisionStack[sz--]);
            undoDecision_layout(layout[0], decisionStack[sz][trace[sz]]);
            until (trace[sz]) {
                free(decisionStack[sz--]);
                undoDecision_layout(layout[0], decisionStack[sz][trace[sz]]);
            }
            trace[sz]--;
            applyDecision_layout(layout[0], decisionStack[sz][trace[sz]]);
        }
        decisionStack[++sz] = decisions_layout(layout[0]);
        if (sz >= cap) {
            decisionStack = realloc(decisionStack, (cap <<= 1) * sizeof(Decision*));
            trace = realloc(trace, (cap <<= 1) * sizeof(size_t));
        }
    }

    /* Print the solution! */
    print_layout(layout[1]);
    for (size_t i = 0; i < sz; i++) {
        print_decision(decisionStack[i][trace[i]]);
        applyDecision_layout(layout[1], decisionStack[i][trace[i]]);
        print_layout(layout[1]);
        free(decisionStack[i]);
    }
    free(decisionStack);
    free(trace);

    printf("Solved the SoloTest in %zu steps!\n", sz);

    return 0;
}
