#include "types.h"
#include <stdio.h>

void disasterAcitivate(square *board, context *contextOfTheGame) {
    contextOfTheGame->currentDisaster = (rand() % 5) + 1;
    printf("=========================================================\n");
    switch (contextOfTheGame->currentDisaster) {
    case 1:
        printf("Disaster happens : Fire\n");
        break;
    case 2:
        printf("Disaster happens : Flood\n");
        break;
    case 3:
        printf("Disaster happens : Riot\n");
        break;
    case 4:
        printf("Disaster happens : Building Collapse\n");
        break;
    case 5:
        printf("Disaster happens : Elecetrical Failure\n");
        break;
    }

    int temp[40] = {};
    int countPropertiesWithBuildings = 0;

    for (int i = 0; i <= 39; i++) {
        if (board[i].PropertyProperties.noOfHouses > 0 || board[i].PropertyProperties.noOfHotels > 0) {
            countPropertiesWithBuildings++;
        }
    }

    square *propertiesWithBuildings[countPropertiesWithBuildings];
    for (int i = 0, j = 0; i <= 39; i++) {
        if (board[i].PropertyProperties.noOfHouses > 0 || board[i].PropertyProperties.noOfHotels > 0) {
            propertiesWithBuildings[j] = &board[i];
            j++;
        }
    }

    if (countPropertiesWithBuildings == 0) {
        printf("No property affected\n");
        printf("=========================================================\n");
        contextOfTheGame->rounfThatDisasterHappend = contextOfTheGame->currentBoardRound;
        return;
    }
    int randomProperty = rand() % countPropertiesWithBuildings;
    printf("Affected property : %s\nowner : %s\n", propertiesWithBuildings[randomProperty]->name, propertiesWithBuildings[randomProperty]->owner->name);
    if (propertiesWithBuildings[randomProperty]->PropertyProperties.insuranceCompany != none) {
        // insurance logic to be implemented
    }
    propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHotels = 0;

    if (propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHouses != 0) {
        int total_loss_houses_value = propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHouses *
                                      propertiesWithBuildings[randomProperty]->PropertyProperties.houseConstructionCost;
        // if not insured, repairing logic
        if (propertiesWithBuildings[randomProperty]->owner->cash >= total_loss_houses_value) {

            propertiesWithBuildings[randomProperty]->owner->cash -= propertiesWithBuildings[randomProperty]->PropertyProperties.houseConstructionCost;
            printf("%s repaired the property by paying LKR %d\n", propertiesWithBuildings[randomProperty]->owner->name, total_loss_houses_value);

        } else {
            propertiesWithBuildings[randomProperty]->owner->noOfHousesOwned -= propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHouses;
            propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHouses = 0;
        }
    }
    if (propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHotels != 0) {
        int total_loss_hotel_value = propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHotels;
        // if not insured, repairing logic
        if (propertiesWithBuildings[randomProperty]->owner->cash >= total_loss_hotel_value) {

            propertiesWithBuildings[randomProperty]->owner->cash -= propertiesWithBuildings[randomProperty]->PropertyProperties.hotelConstructionCost;
            printf("%s repaired the property by paying LKR %d\n", propertiesWithBuildings[randomProperty]->name, total_loss_hotel_value);
        } else {

            propertiesWithBuildings[randomProperty]->owner->noOfHotelsOwned--;
            propertiesWithBuildings[randomProperty]->PropertyProperties.noOfHotels = 0;
        }
    }

    printf("=========================================================\n");
    contextOfTheGame->rounfThatDisasterHappend = contextOfTheGame->currentBoardRound;
}

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

        board[i].curruntValue = board[i].curruntValue * doubleToInt(1.0000 + (double)contextofgame->currentInflation / (double)100);
        board[i].PropertyProperties.currentRentalofProperty = board[i].PropertyProperties.currentRentalofProperty * doubleToInt(1.0000 + (double)contextofgame->currentInflation / (double)100);
        board[i].PropertyProperties.initialPrice = board[i].PropertyProperties.initialPrice * doubleToInt(1.0000 + (double)contextofgame->currentInflation / (double)100);
        board[i].PropertyProperties.houseConstructionCost = board[i].PropertyProperties.houseConstructionCost * doubleToInt(1.0000 + (double)contextofgame->currentInflation / (double)100);
        board[i].PropertyProperties.hotelConstructionCost = board[i].PropertyProperties.hotelConstructionCost * doubleToInt(1.0000 + (double)contextofgame->currentInflation / (double)100);
    }
    contextofgame->roundThatInflationHappened = contextofgame->currentBoardRound;
}
