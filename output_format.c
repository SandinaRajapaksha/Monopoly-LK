#include "types.h"
#include <stdio.h>

void printMarketConditions(context *contextofgame) {
    int roundsLeftInflation = contextofgame->roundThatInflationHappened + 11 - contextofgame->currentBoardRound;
    printf("==============================================================\n");
    printf("Current Market Condition\n");
    printf("==============================================================\n\n");
    if (contextofgame->currentInflation >= 0) {
        printf("\nInflation\n-------------------------------------------------\n(+%d%%)\nround remaining : %d\n", contextofgame->currentInflation, roundsLeftInflation);
    } else {
        printf("\nInflation\n-------------------------------------------------\n(-%d%%)\n\n", contextofgame->currentInflation);
    }
};
