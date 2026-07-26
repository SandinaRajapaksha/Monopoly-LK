#include "types.h"
#include <stdio.h>

void econEventActivate(square *board, int *roundThatEconEventHappened,
                       economicEventCardType *curruntActiveEconEvent,
                       int *curruntBoardRound) {
    // random
    economicEventCardType econEvents[8] = {
        TourismBoom,       FuelCrisis,      HeavyMonsoon,
        EconomicRecession, StockMarketBoom, GovernmentHousingProgramme,
        ForeignInvestment, PoliticalUnrest};

    if (*curruntActiveEconEvent != -1) {
        if (*curruntActiveEconEvent == TourismBoom) {
            printf("Tourism Boom is over...\n");
        } else if (*curruntActiveEconEvent == FuelCrisis) {
            printf("Fuel Crisis is over ... \n");
        } else if (*curruntActiveEconEvent == HeavyMonsoon) {
            printf("Heavy Monsoon is over ...\n");
        } else if (*curruntActiveEconEvent == EconomicRecession) {
            printf("Economic Recession is over... \n");
        } else if (*curruntActiveEconEvent == StockMarketBoom) {
            printf("Stock Market Boom is over... \n");
        } else if (*curruntActiveEconEvent == GovernmentHousingProgramme) {
            printf("Government Housing Programme is over... \n");
        } else if (*curruntActiveEconEvent == ForeignInvestment) {
            printf("Foreign Investment is over... \n");
        } else if (*curruntActiveEconEvent == PoliticalUnrest) {
            printf("Political Unrest is over... \n");
        }
        printf("\n");
    }

    int randomEconEvent = econEvents[rand() % 8];
    *curruntActiveEconEvent = randomEconEvent;

    if (randomEconEvent == TourismBoom) {
        printf("Tourism Boom Happens...\n");
    } else if (randomEconEvent == FuelCrisis) {
        printf("Fuel Crisis happens... \n");
    } else if (randomEconEvent == HeavyMonsoon) {
        printf("Heavy Monsoon happens ...\n");
    } else if (randomEconEvent == EconomicRecession) {
        printf("Economic Recession happens... \n");
    } else if (randomEconEvent == StockMarketBoom) {
        printf("Stock Market Boom happens... \n");
    } else if (randomEconEvent == GovernmentHousingProgramme) {
        printf("Government Housing Programme happens... \n");
    } else if (randomEconEvent == ForeignInvestment) {
        printf("Foreign Investment happens... \n");
    } else if (randomEconEvent == PoliticalUnrest) {
        printf("Political Unrest happens... \n");
    }
    printf("\n");
    *roundThatEconEventHappened = *curruntBoardRound;
}

void govRegulationsActivate(square *board) {
    // random
    govRegulationsType govRegulations[8] = {
        IncreasePropertyTax, ReduceLoanInterest,   HousingSubsidy,
        LuxaryPropertyTax,   RailwayModernization, ElectricityTariffRevision,
        InsuranceRegulation, AntiSpeculantAct};
}

void nationalEventActivate(int *topNationalEventcard, square *board) {
    // deck
    NationalEventType NationalEventCards[19] = {
        TourismHype,         FuelShortage,         PoliticalRally,
        StockMarketRise,     EconomicDowntime,     HousingSubsidy_NationalEvent,
        InterestRateCut,     InterestRateIncrease, TaxAmnesty,
        PowerFailure,        ForeignFunding,       PortExpansion,
        FestivalSeason,      LabourStrike,         InsuranceDiscount,
        PropertyRevaluation, CurrencyDepreciation, GovernmentGrant,
        NationalDisaster};

    NationalEventType currentNationalEvent =
        NationalEventCards[*topNationalEventcard];
    // all the shit happening accoding to event

    // push the card to bottom
    *topNationalEventcard = (*topNationalEventcard + 1) % 19;
}

void regionalDevelopmentActivate(int *topreigionaldevelopmentcard,
                                 square *board) {
    // deck
    regionalDevelopmentType regionalDevelopmentCards[12] = {

        southernTourismBoom,
        portCityExpansion,
        itIndustryGrowth,
        nothernDevelopmentProgramme,
        teaExportBoom,
        airPortExpansion,
        universityCityGrowth,
        beachPollution,
        floodDamage,
        transportStrike,
        electricityTariffIncrease,
        waterShortage};

    regionalDevelopmentType currentRegionalEvent =
        regionalDevelopmentCards[*topreigionaldevelopmentcard];

    // all the shit happening in regional devellopment

    // push the card to bottom
    *topreigionaldevelopmentcard = (*topreigionaldevelopmentcard + 1) % 12;
}

void dynamicPropertyEventActivate(square *board) { // parameters to be added
    // random event
    dynamicPropertyMarketEventType dynamicPropertyEvents[2] = {
        dynamicPropertyMarketBoom, dynamicPropertyMarketDecline};
    // all the other shit
}
