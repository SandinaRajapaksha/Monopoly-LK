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
        printf("\nInflation\n-------------------------------------------------\n(-%d%%)\n\n", -contextofgame->currentInflation);
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

    // disaster
    printf("\nDisaster\n------------------------------------------------------\n");
    switch (contextofgame->currentDisaster) {
    case fire:
        printf("Fire\n");
        break;
    case flood:
        printf("Flood\n");
        break;
    case riot:
        printf("Riot\n");
        break;
    case buildingCollapse:
        printf("Building Collapse\n");
        break;
    case electricalFailure:
        printf("Electrical Failure\n");
        break;
    default:
        printf("No disaster active\n");
        break;
    }

    // tax and loan interest rates
    printf("\nTax Rate\n------------------------------------------------------\n%d%%\n", contextofgame->currentTaxRate);
    printf("\nLoan Interest Rate\n------------------------------------------------------\n%d%%\n", contextofgame->currentInterestRate);

    // government regulation
    printf("\nGovernment Regulation\n------------------------------------------------------\n");
    if (contextofgame->currentActiveGovRegulation != (govRegulationsType)-1) {
        printf("%s\nround remaining : %d\n",
               getGovRegulationName(contextofgame->currentActiveGovRegulation),
               contextofgame->govRegulationRoundsRemaining);
    } else {
        printf("No regulation active\n");
    }

    // dynamic property market boom / decline
    printf("\nDynamic Property Market\n------------------------------------------------------\n");
    if (contextofgame->dynamicEventRoundsRemaining > 0) {
        printf("Boom group : %s\nDecline group : %s\nround remaining : %d\n",
               getGroupName(contextofgame->dynamicBoomGroup),
               getGroupName(contextofgame->dynamicDeclineGroup),
               contextofgame->dynamicEventRoundsRemaining);
    } else {
        printf("No boom or decline active\n");
    }

    // regional development effects
    printf("\nRegional Development Effects\n------------------------------------------------------\n");
    if (contextofgame->numActiveRegionalEffects > 0) {
        for (int i = 0; i < contextofgame->numActiveRegionalEffects; i++) {
            printf("%s - round remaining : %d\n",
                   getRegionalEventName(contextofgame->activeRegionalEffects[i].effect),
                   contextofgame->activeRegionalEffects[i].roundsRemaining);
        }
    } else {
        printf("No regional development effect active\n");
    }

    printf("==============================================================\n\n\n\n");
};
