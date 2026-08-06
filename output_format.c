#include "types.h"
#include <stdio.h>

void printMarketConditions(context *contextofgame) {
    int roundsLeftInflation = contextofgame->roundThatInflationHappened + 11 - contextofgame->currentBoardRound;
    int roundsLeftEconEvent = contextofgame->roundThatEconEventHappened + 16 - contextofgame->currentBoardRound;

    printf("==============================================================\n");
    printf("Current Market Condition\n");
    printf("==============================================================\n\n");
    if (contextofgame->currentInflation >= 0) {
        printf("\nInflation\n-------------------------------------------------\n(+%d%%)\nround remaining : %d\n", contextofgame->currentInflation, roundsLeftInflation);
    } else {
        printf("\nInflation\n-------------------------------------------------\n(-%d%%)\n\n", contextofgame->currentInflation);
    }

    // econ event
    printf("\nEconomic Event\n------------------------------------------------------\n");

    switch (contextofgame->currentActiveEconEvent) {
    case TourismBoom:
        printf("Tourism Boom: hotel rents double, Yellow group value +15%%\n");
        break;
    case FuelCrisis:
        printf("Fuel Crisis: railway rents double, build costs +20%%\n");
        break;
    case HeavyMonsoon:
        printf("Heavy Monsoon: Yellow group value -10%%\n");
        break;
    case EconomicRecession:
        printf("Economic Recession: property value -15%%, rents -10%%\n");
        break;
    case StockMarketBoom:
        printf("Stock Market Boom: property value +10%%\n");
        break;
    case GovernmentHousingProgramme:
        printf("Government Housing Programme: house build cost -25%%\n");
        break;
    case ForeignInvestment:
        printf("Foreign Investment: Orange & Red group value +20%%\n");
        break;
    case PoliticalUnrest:
        printf("Political Unrest: hotel rents -50%%\n");
        break;
    default:
        printf("No economic event active\n");
        break;
    }
    printf("Rounds remaining : %d\n", roundsLeftEconEvent + 1);
    printf("==============================================================\n\n\n\n");
};
