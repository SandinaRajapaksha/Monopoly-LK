#include "types.h"
#include <stdio.h>

void printMarketConditions(context *contextofgame) {
    printf("==============================================================\n");
    printf("Current Market Condition\n");
    printf("==============================================================\n\n");
    if (contextofgame->currentInflation >= 0) {
        printf("\nInflation\n-------------------------------------------------\n(+%d%%)\n\n", contextofgame->currentInflation);
    } else {
        printf("\nInflation\n-------------------------------------------------\n(-%d%%)\n\n", contextofgame->currentInflation);
    }
};
