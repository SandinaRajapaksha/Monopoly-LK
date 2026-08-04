#include "types.h"
#include <stdio.h>

void printMarketConditions(context *contextofgame) {
    printf("==============================================================\n");
    printf("Current Market Condition");
    printf("==============================================================\n\n");
    printf("Inlflation\n-------------------------------------------------\n(%d%%)\n\n", contextofgame->currentInflation);
};
