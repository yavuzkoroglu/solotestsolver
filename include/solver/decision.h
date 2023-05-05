#ifndef DECISION_H
    #define DECISION_H
    #include <stddef.h>

    #define IS_VALID_DECISION(decision) (decision.row || decision.col || decision.dir)

    typedef struct DecisionBody {
        unsigned char row:3;
        unsigned char col:3;
        unsigned char dir:2;
    } Decision;

    void print_decision(Decision const);
    size_t count_decisions(Decision const* const);
#endif
