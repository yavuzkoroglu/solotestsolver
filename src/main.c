#include <stdio.h>
#include <stdlib.h>
#include "solver/decision.h"
#include "solotest/layout.h"

int main(void);

int main(void) {
    Layout layout = INITIAL_LAYOUT;
    Decision* decisions = decisions_layout(layout);

    print_layout(layout);

    puts("");
    printf("SCORE = %u\n", score_layout(layout));

    for (unsigned int i = 0; IS_VALID_DECISION(decisions[i]); i++)
        print_decision(decisions[i]);

    free(decisions);

    return 0;
}
