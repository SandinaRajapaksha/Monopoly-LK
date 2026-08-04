#include "types.h"
#include <stdio.h>

void econEventActivate(square *board, context *contextOfTheGame) {
    // random
    economicEventCardType econEvents[8] = {
        TourismBoom, FuelCrisis, HeavyMonsoon,
        EconomicRecession, StockMarketBoom, GovernmentHousingProgramme,
        ForeignInvestment, PoliticalUnrest};

    if (contextOfTheGame->currentActiveEconEvent != -1) {
        printf("\n");
        if (contextOfTheGame->currentActiveEconEvent == TourismBoom) {
            printf("Tourism Boom is over...\n");
            tourismBoom_Deactivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == FuelCrisis) {
            printf("Fuel Crisis is over ... \n");
            FuelCrisis_Deactivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == HeavyMonsoon) {
            printf("Heavy Monsoon is over ...\n");
            HeavyMonsoon_deActivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == EconomicRecession) {
            printf("Economic Recession is over... \n");
            recession_deActivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == StockMarketBoom) {
            printf("Stock Market Boom is over... \n");
            StockMarketBoom_deActivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == GovernmentHousingProgramme) {
            printf("Government Housing Programme is over... \n");
            GovernmentHousingProgramme_deActivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == ForeignInvestment) {
            printf("Foreign Investment is over... \n");
            ForeignInvestment_deActivate(board);
        } else if (contextOfTheGame->currentActiveEconEvent == PoliticalUnrest) {
            printf("Political Unrest is over... \n");
            PoliticalUnrest_deActivate(board);
        }
        printf("\n");
    }

    int randomEconEvent = econEvents[rand() % 8];
    contextOfTheGame->currentActiveEconEvent = randomEconEvent;

    printf("\nRound %d economic event happens now, \n",
           contextOfTheGame->currentBoardRound);
    if (randomEconEvent == TourismBoom) {
        printf("Tourism Boom Happens...\n");
        tourismBoomActivate(board);

    } else if (randomEconEvent == FuelCrisis) {
        printf("Fuel Crisis happens... \n");
        FuelCrisisActivate(board);

    } else if (randomEconEvent == HeavyMonsoon) {
        printf("Heavy Monsoon happens ...\n");
        HeavyMonsoonActivate(board);

    } else if (randomEconEvent == EconomicRecession) {
        printf("Economic Recession happens... \n");
        recessionActivate(board);

    } else if (randomEconEvent == StockMarketBoom) {
        printf("Stock Market Boom happens... \n");
        StockMarketBoomActivate(board);

    } else if (randomEconEvent == GovernmentHousingProgramme) {
        printf("Government Housing Programme happens... \n");
        GovernmentHousingProgrammeActivate(board);

    } else if (randomEconEvent == ForeignInvestment) {
        printf("Foreign Investment happens... \n");
        ForeignInvestmentActivate(board);

    } else if (randomEconEvent == PoliticalUnrest) {
        printf("Political Unrest happens... \n");
        PoliticalUnrestActivate(board);
    }
    printf("\n");
    contextOfTheGame->roundThatEconEventHappened =
        contextOfTheGame->currentBoardRound;
}

void govRegulationsActivate(square *board) {
    // random
    govRegulationsType govRegulations[8] = {
        IncreasePropertyTax, ReduceLoanInterest, HousingSubsidy,
        LuxaryPropertyTax, RailwayModernization, ElectricityTariffRevision,
        InsuranceRegulation, AntiSpeculantAct};
}

void nationalEventActivate(int *topNationalEventcard, square *board) {
    // deck
    NationalEventType NationalEventCards[19] = {
        TourismHype, FuelShortage, PoliticalRally,
        StockMarketRise, EconomicDowntime, HousingSubsidy_NationalEvent,
        InterestRateCut, InterestRateIncrease, TaxAmnesty,
        PowerFailure, ForeignFunding, PortExpansion,
        FestivalSeason, LabourStrike, InsuranceDiscount,
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

void inflationRateRelease(square *board, context *contextofgame) { // parameters to be added
    // random event after 10 rounds
    int inflationRates[6] = {-3, 0, 2, 5, 8, 12};
    // all the other shit
    int randomInflation = inflationRates[rand() % 6];
    contextofgame->currentInflation = randomInflation;

    printf("\nInflations rate for round %d releases now,\nInflation rate "
           "release : %d %% \n\n",
           contextofgame->currentBoardRound, contextofgame->currentInflation);

    for (int i = 0; i <= 39; i++) {

        board[i].curruntValue = board[i].curruntValue * (1 + (double)contextofgame->currentInflation / (double)100);
        board[i].PropertyProperties.currentRentalofProperty = board[i].PropertyProperties.currentRentalofProperty * (1 + (double)contextofgame->currentInflation / (double)100);
        board[i].PropertyProperties.initialPrice = board[i].PropertyProperties.initialPrice * (1 + (double)contextofgame->currentInflation / (double)100);
        // other affecting proerties to be added
    }
    contextofgame->roundThatInflationHappened = contextofgame->currentBoardRound;
}
