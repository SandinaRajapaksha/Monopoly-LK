#include "types.h"
#include <stdio.h>

void printMarketConditions(int *currentInflation, economicEventCardType *econEvent, int *currentRound) {
    printf("==============================================================\n");
    printf("Current Market Condition");
    printf("==============================================================\n\n");
    printf("Inlflation\n-------------------------------------------------\n(%d%%)\n\n", *currentInflation);
};
