#ifndef DECISION_H
    #define DECISION_H

    typedef struct DecisionBody {
        unsigned char row:3;
        unsigned char col:3;
        unsigned char dir:2;
    } Decision;

    void print_decision(Decision const);
#endif
