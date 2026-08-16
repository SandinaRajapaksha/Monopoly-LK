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
        if (board[i].owner != NULL &&
            (board[i].PropertyProperties.noOfHouses > 0 || board[i].PropertyProperties.noOfHotels > 0)) {
            countPropertiesWithBuildings++;
        }
    }

    square *propertiesWithBuildings[countPropertiesWithBuildings];
    for (int i = 0, j = 0; i <= 39; i++) {
        if (board[i].owner != NULL &&
            (board[i].PropertyProperties.noOfHouses > 0 || board[i].PropertyProperties.noOfHotels > 0)) {
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
    square *affected = propertiesWithBuildings[randomProperty];
    printf("Affected property : %s\nowner : %s\n", affected->name, affected->owner->name);

    int repairCost = 0;
    bool hotelDestroyed = false;
    int lostRent = affected->PropertyProperties.currentRentalofProperty;
    if (affected->PropertyProperties.noOfHotels == 1) {
        repairCost = affected->PropertyProperties.hotelConstructionCost;
        affected->PropertyProperties.noOfHotels = 0;
        if (affected->owner->noOfHotelsOwned > 0) {
            affected->owner->noOfHotelsOwned--;
        }
        hotelDestroyed = true;
        printf("Hotel destroyed at %s\n", affected->name);
    } else if (affected->PropertyProperties.noOfHouses > 0) {
        repairCost = affected->PropertyProperties.houseConstructionCost;
        affected->PropertyProperties.noOfHouses--;
        affected->owner->noOfHousesOwned--;
        printf("A house destroyed at %s\n", affected->name);
    }
    recalcRent(affected);
    affected->owner->hasFacedDisaster = true;

    bool covered = false;
    switch (affected->PropertyProperties.insurancePolicy) {
    case basic:
        covered = (contextOfTheGame->currentDisaster == fire || contextOfTheGame->currentDisaster == flood);
        break;
    case comprehensive:
        covered = (contextOfTheGame->currentDisaster == fire || contextOfTheGame->currentDisaster == flood || contextOfTheGame->currentDisaster == riot);
        break;
    case buisiness:
        covered = true;
        break;
    default:
        break;
    }

    if (covered) {
        double coverageRatio = 1.00;
        if (affected->PropertyProperties.insurancePolicy == basic) {
            coverageRatio = 0.80;
        }
        int compensation = doubleToInt(repairCost * coverageRatio);
        if (affected->PropertyProperties.insurancePolicy == buisiness) {
            compensation += 5 * lostRent;
        }
        affected->owner->cash += compensation;
        printf("%s received LKR %d insurance compensation for %s\n", affected->owner->name, compensation, affected->name);

        // the compensation money plus the remaining cash is used to repair
        if (affected->owner->cash >= repairCost) {
            affected->owner->cash -= repairCost;
            if (hotelDestroyed) {
                affected->PropertyProperties.noOfHotels = 1;
                affected->owner->noOfHotelsOwned++;
            } else {
                affected->PropertyProperties.noOfHouses++;
                affected->owner->noOfHousesOwned++;
            }
            recalcRent(affected);
            printf("%s repaired %s\n", affected->owner->name, affected->name);
        } else {
            printf("%s cannot afford repairs of %s\n", affected->owner->name, affected->name);
        }
    } else {
        if (affected->owner->cash >= repairCost) {
            affected->owner->cash -= repairCost;
            if (hotelDestroyed) {
                affected->PropertyProperties.noOfHotels = 1;
                affected->owner->noOfHotelsOwned++;
            } else {
                affected->PropertyProperties.noOfHouses++;
                affected->owner->noOfHousesOwned++;
            }
            recalcRent(affected);
            printf("%s paid LKR %d for repairs of %s\n", affected->owner->name, repairCost, affected->name);
        } else {
            printf("%s cannot afford repairs of %s\n", affected->owner->name, affected->name);
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
            contextOfTheGame->currentInterestRate += 3;
        } else if (contextOfTheGame->currentActiveEconEvent == StockMarketBoom) {
            printf("Stock Market Boom is over... \n");
            StockMarketBoom_deActivate(board);
            contextOfTheGame->currentInterestRate -= 2;
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
        contextOfTheGame->currentInterestRate -= 3;
        printf("Central bank cuts loan interest to %d%%\n", contextOfTheGame->currentInterestRate);

    } else if (randomEconEvent == StockMarketBoom) {
        printf("Stock Market Boom happens... \n");
        StockMarketBoomActivate(board);
        contextOfTheGame->currentInterestRate += 2;
        printf("Loan interest raised to %d%%\n", contextOfTheGame->currentInterestRate);

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

char *getGovRegulationName(govRegulationsType regulation) {
    switch (regulation) {
    case IncreasePropertyTax:
        return "Increase Property Tax";
    case ReduceLoanInterest:
        return "Reduce Loan Interest";
    case HousingSubsidy:
        return "Housing Subsidy";
    case LuxaryPropertyTax:
        return "Luxury Property Tax";
    case RailwayModernization:
        return "Railway Modernization";
    case ElectricityTariffRevision:
        return "Electricity Tariff Revision";
    case AntiSpeculantAct:
        return "Anti-Speculant Act";
    default:
        return "Unknown";
    }
}

void housingSubsidy_gov_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost * 0.80);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost * 0.80);
        }
    }
}
void housingSubsidy_gov_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost / 0.80);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost / 0.80);
        }
    }
}

void railwayModernization_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == railway) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
        }
    }
}
void railwayModernization_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == railway) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
        }
    }
}

void govRegulationDeactivate(square *board, context *contextOfTheGame) {
    switch (contextOfTheGame->currentActiveGovRegulation) {
    case IncreasePropertyTax:
        contextOfTheGame->currentTaxRate = doubleToInt(contextOfTheGame->currentTaxRate / 1.50);
        break;
    case ReduceLoanInterest:
        contextOfTheGame->currentInterestRate = doubleToInt(contextOfTheGame->currentInterestRate / 0.50);
        break;
    case HousingSubsidy:
        housingSubsidy_gov_deactivate(board);
        break;
    case RailwayModernization:
        railwayModernization_deactivate(board);
        break;
    case ElectricityTariffRevision:
        break;
    default:
        break;
    }
}

void govRegulationsActivate(square *board, context *contextOfTheGame, playerPointers *playerObject) {
    // end any leftover regulation from a previous draw first
    if (contextOfTheGame->govRegulationRoundsRemaining > 0 &&
        contextOfTheGame->currentActiveGovRegulation != (govRegulationsType)-1) {
        govRegulationDeactivate(board, contextOfTheGame);
        printf("%s regulation expired\n", getGovRegulationName(contextOfTheGame->currentActiveGovRegulation));
    }

    // random regulation
    govRegulationsType govRegulations[7] = {
        IncreasePropertyTax, ReduceLoanInterest, HousingSubsidy,
        LuxaryPropertyTax, RailwayModernization, ElectricityTariffRevision,
        AntiSpeculantAct};

    govRegulationsType regulation = govRegulations[rand() % 7];

    printf("\n=========================================================\n");
    printf("Government Regulation : %s\n", getGovRegulationName(regulation));
    printf("---------------------------------------------------------\n");

    switch (regulation) {
    case IncreasePropertyTax:
        printf("Property tax rate increased by 50%% for 15 rounds\n");
        contextOfTheGame->currentTaxRate = doubleToInt(contextOfTheGame->currentTaxRate * 1.50);
        break;
    case ReduceLoanInterest:
        printf("Loan interest reduced by 50%% for 15 rounds\n");
        contextOfTheGame->currentInterestRate = doubleToInt(contextOfTheGame->currentInterestRate * 0.50);
        break;
    case HousingSubsidy:
        printf("House and hotel construction costs reduced by 20%% for 15 rounds\n");
        housingSubsidy_gov_activate(board);
        break;
    case LuxaryPropertyTax: {
        player *all[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
        for (int i = 0; i < 4; i++) {
            if (all[i]->isBankrupt) {
                continue;
            }
            for (int j = 0; j < 40; j++) {
                if (board[j].type == property && board[j].PropertyProperties.propertyGroup == darkBlue && board[j].owner == all[i]) {
                    int tax = all[i]->cash;
                    if (all[i]->cash >= 3000) {
                        tax = 3000;
                    }
                    all[i]->cash -= tax;
                    printf("%s paid LKR %d luxury property tax on %s\n", all[i]->name, tax, board[j].name);
                }
            }
        }
        break;
    }
    case RailwayModernization:
        printf("Railway station values increase by 20%% for 15 rounds\n");
        railwayModernization_activate(board);
        break;
    case ElectricityTariffRevision:
        printf("Utility income halved for 15 rounds\n");
        break;
    case AntiSpeculantAct: {
        player *all[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
        for (int i = 0; i < 4; i++) {
            if (all[i]->isBankrupt) {
                continue;
            }
            for (int j = 0; j < 40; j++) {
                if (board[j].type == property && board[j].owner == all[i] &&
                    board[j].PropertyProperties.noOfHouses == 0 && board[j].PropertyProperties.noOfHotels == 0) {
                    int fine = all[i]->cash;
                    if (all[i]->cash >= 1500) {
                        fine = 1500;
                    }
                    all[i]->cash -= fine;
                    printf("%s paid LKR %d anti-speculant fine on unimproved %s\n", all[i]->name, fine, board[j].name);
                }
            }
        }
        break;
    }
    default:
        break;
    }
    printf("=========================================================\n");

    contextOfTheGame->currentActiveGovRegulation = regulation;
    contextOfTheGame->govRegulationRoundsRemaining = 15;
    contextOfTheGame->roundThatGovRegulationHappened = contextOfTheGame->currentBoardRound;
}

void decayGovRegulationEffects(context *contextOfTheGame, square *board) {
    if (contextOfTheGame->govRegulationRoundsRemaining <= 0) {
        return;
    }
    contextOfTheGame->govRegulationRoundsRemaining--;
    if (contextOfTheGame->govRegulationRoundsRemaining > 0) {
        return;
    }

    if (contextOfTheGame->currentActiveGovRegulation != (govRegulationsType)-1) {
        govRegulationDeactivate(board, contextOfTheGame);
        printf("%s regulation expired\n", getGovRegulationName(contextOfTheGame->currentActiveGovRegulation));
        contextOfTheGame->currentActiveGovRegulation = (govRegulationsType)-1;
    }
}

char *getNatlEventName(NationalEventType effect) {
    switch (effect) {
    case TourismHype:
        return "Tourism Hype";
    case FuelShortage:
        return "Fuel Shortage";
    case HeavyFloods:
        return "Heavy Floods";
    case PoliticalRally:
        return "Political Rally";
    case StockMarketRise:
        return "Stock Market Rise";
    case EconomicDowntime:
        return "Economic Downturn";
    case HousingSubsidy_NationalEvent:
        return "Housing Subsidy";
    case InterestRateCut:
        return "Interest Rate Cut";
    case InterestRateIncrease:
        return "Interest Rate Increase";
    case TaxAmnesty:
        return "Tax Amnesty";
    case PowerFailure:
        return "Power Failure";
    case ForeignFunding:
        return "Foreign Funding";
    case PortExpansion:
        return "Port Expansion";
    case FestivalSeason:
        return "Festival Season";
    case LabourStrike:
        return "Labour Strike";
    case InsuranceDiscount:
        return "Insurance Discount";
    case PropertyRevaluation:
        return "Property Revaluation";
    case CurrencyDepreciation:
        return "Currency Depreciation";
    case GovernmentGrant:
        return "Government Grant";
    case NationalDisaster:
        return "National Disaster";
    }
    return "Unknown";
}

void addNatlEffect(player *player_x, NationalEventType effect, int rounds, groupType group, int squareIdx) {
    if (player_x->numActiveNatlEffects >= 5) {
        return;
    }
    int i = player_x->numActiveNatlEffects++;
    player_x->activeNatlEffects[i].effect = effect;
    player_x->activeNatlEffects[i].roundsRemaining = rounds;
    player_x->activeNatlEffects[i].affectedGroup = group;
    player_x->activeNatlEffects[i].affectedSquare = squareIdx;
}

void stockMarketRise_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.10);
    }
}
void stockMarketRise_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.10);
    }
}

void economicDownturn_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        board[i].curruntValue = doubleToInt(board[i].curruntValue * 0.85);
        if (board[i].type == property) {
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty * 0.90);
        }
    }
}
void economicDownturn_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        board[i].curruntValue = doubleToInt(board[i].curruntValue / 0.85);
        if (board[i].type == property) {
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty / 0.90);
        }
    }
}

void housingSubsidy_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost * 0.70);
        }
    }
}
void housingSubsidy_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost / 0.70);
        }
    }
}

void foreignFunding_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property &&
            (board[i].PropertyProperties.propertyGroup == orange || board[i].PropertyProperties.propertyGroup == red)) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.15);
        }
    }
}
void foreignFunding_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property &&
            (board[i].PropertyProperties.propertyGroup == orange || board[i].PropertyProperties.propertyGroup == red)) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.15);
        }
    }
}

void portExpansion_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == railway) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
        }
    }
}
void portExpansion_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == railway) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
        }
    }
}

void currencyDepreciation_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost * 1.10);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost * 1.10);
        }
    }
}
void currencyDepreciation_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost / 1.10);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost / 1.10);
        }
    }
}

groupType propertyRevaluation_activate(square *board) {
    groupType group = (groupType)(brown + (rand() % 8));
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == group) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.15);
        }
    }
    return group;
}
void propertyRevaluation_deactivate(square *board, groupType group) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == group) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.15);
        }
    }
}

void recalcRent(square *sq) {
    int n = sq->PropertyProperties.noOfHouses;
    if (sq->PropertyProperties.noOfHotels == 1) {
        n = 5;
    }
    switch (n) {
    case 1:
        sq->PropertyProperties.currentRentalofProperty = 2 * sq->PropertyProperties.baseRental;
        break;
    case 2:
        sq->PropertyProperties.currentRentalofProperty = 3 * sq->PropertyProperties.baseRental;
        break;
    case 3:
        sq->PropertyProperties.currentRentalofProperty = 5 * sq->PropertyProperties.baseRental;
        break;
    case 4:
        sq->PropertyProperties.currentRentalofProperty = 7 * sq->PropertyProperties.baseRental;
        break;
    case 5:
        sq->PropertyProperties.currentRentalofProperty = 10 * sq->PropertyProperties.baseRental;
        break;
    default:
        sq->PropertyProperties.currentRentalofProperty = sq->PropertyProperties.baseRental;
        break;
    }
}

void damageBuilding(square *sq) {
    if (sq->owner == NULL) {
        printf("No owner - nothing damaged\n");
        return;
    }
    if (sq->PropertyProperties.noOfHotels == 1) {
        sq->PropertyProperties.noOfHotels = 0;
        if (sq->owner->noOfHotelsOwned > 0) {
            sq->owner->noOfHotelsOwned--;
        }
        printf("Hotel destroyed at %s\n", sq->name);
    } else if (sq->PropertyProperties.noOfHouses > 0) {
        sq->PropertyProperties.noOfHouses--;
        sq->owner->noOfHousesOwned--;
        printf("A house destroyed at %s\n", sq->name);
    } else {
        printf("No buildings at %s - nothing damaged\n", sq->name);
        return;
    }
    recalcRent(sq);
}

void nationalEventActivate(player *player_x, square *board, context *contextOfTheGame, playerPointers *playerObject) {
    // 20-card deck, top card drawn, then returned to the bottom
    NationalEventType deck[20] = {
        TourismHype, FuelShortage, HeavyFloods, PoliticalRally,
        StockMarketRise, EconomicDowntime, HousingSubsidy_NationalEvent,
        InterestRateCut, InterestRateIncrease, TaxAmnesty,
        PowerFailure, ForeignFunding, PortExpansion,
        FestivalSeason, LabourStrike, InsuranceDiscount,
        PropertyRevaluation, CurrencyDepreciation, GovernmentGrant,
        NationalDisaster};

    NationalEventType card = deck[contextOfTheGame->topNationalEventCard];
    contextOfTheGame->topNationalEventCard = (contextOfTheGame->topNationalEventCard + 1) % 20;

    printf("\n=========================================================\n");
    printf("National Event Card : %s\n", getNatlEventName(card));
    printf("Drawn by : %s\n", player_x->name);
    printf("---------------------------------------------------------\n");

    switch (card) {
    case TourismHype:
        printf("Hotels earn double rent for 5 rounds\n");
        addNatlEffect(player_x, card, 5, 0, -1);
        break;
    case FuelShortage:
        printf("Railway rent doubles for 5 rounds\n");
        addNatlEffect(player_x, card, 5, 0, -1);
        break;
    case HeavyFloods: {
        int coastal[40], n = 0;
        for (int i = 0; i < 40; i++) {
            if (board[i].type == property && board[i].PropertyProperties.propertyGroup == yellow && board[i].owner == player_x) {
                coastal[n++] = i;
            }
        }
        if (n > 0) {
            int idx = coastal[rand() % n];
            printf("Heavy floods damage %s\n", board[idx].name);
            damageBuilding(&board[idx]);
        } else {
            printf("No coastal property owned - no damage\n");
        }
        break;
    }
    case PoliticalRally: {
        int owned[40], n = 0;
        for (int i = 0; i < 40; i++) {
            if (board[i].type == property && board[i].owner == player_x) {
                owned[n++] = i;
            }
        }
        if (n > 0) {
            int idx = owned[rand() % n];
            board[idx].isClosed = true;
            printf("%s is closed for 2 rounds\n", board[idx].name);
            addNatlEffect(player_x, card, 2, 0, idx);
        } else {
            printf("No property owned - nothing closed\n");
        }
        break;
    }
    case StockMarketRise:
        printf("All property values increase by 10%% for 15 rounds\n");
        stockMarketRise_activate(board);
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case EconomicDowntime:
        printf("Property values decrease by 15%% for 15 rounds\n");
        economicDownturn_activate(board);
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case HousingSubsidy_NationalEvent:
        printf("House construction cost reduced by 30%% for 15 rounds\n");
        housingSubsidy_activate(board);
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case InterestRateCut:
        printf("Loan interest reduced by 2%% for 15 rounds\n");
        contextOfTheGame->currentInterestRate -= 2;
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case InterestRateIncrease:
        printf("Loan interest increased by 2%% for 15 rounds\n");
        contextOfTheGame->currentInterestRate += 2;
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case TaxAmnesty: {
        player *all[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
        for (int i = 0; i < 4; i++) {
            if (!all[i]->isBankrupt) {
                all[i]->cash += 2000;
                printf("%s received LKR 2000 tax amnesty\n", all[i]->name);
            }
        }
        break;
    }
    case PowerFailure:
        printf("Utility income halved for 3 rounds\n");
        addNatlEffect(player_x, card, 3, 0, -1);
        break;
    case ForeignFunding:
        printf("Commercial (orange + red) property values increase by 15%% for 15 rounds\n");
        foreignFunding_activate(board);
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case PortExpansion:
        printf("Railway station values increase by 20%% for 15 rounds\n");
        portExpansion_activate(board);
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case FestivalSeason:
        printf("Hotels receive 50%% additional rent for 15 rounds\n");
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case LabourStrike:
        printf("Construction suspended for 2 rounds\n");
        player_x->constructionSuspended = true;
        addNatlEffect(player_x, card, 2, 0, -1);
        break;
    case InsuranceDiscount:
        printf("Insurance premiums reduced by 20%% for 15 rounds\n");
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case PropertyRevaluation: {
        groupType group = propertyRevaluation_activate(board);
        printf("Random property group appreciates by 15%% for 15 rounds\n");
        addNatlEffect(player_x, card, 15, group, -1);
        break;
    }
    case CurrencyDepreciation:
        printf("Construction costs increase by 10%% for 15 rounds\n");
        currencyDepreciation_activate(board);
        addNatlEffect(player_x, card, 15, 0, -1);
        break;
    case GovernmentGrant: {
        player *all[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
        int solvent[4], n = 0;
        for (int i = 0; i < 4; i++) {
            if (!all[i]->isBankrupt) {
                solvent[n++] = i;
            }
        }
        if (n > 0) {
            int idx = solvent[rand() % n];
            all[idx]->cash += 5000;
            printf("%s received LKR 5000 government grant\n", all[idx]->name);
        }
        break;
    }
    case NationalDisaster: {
        int developed[40], n = 0;
        for (int i = 0; i < 40; i++) {
            if (board[i].type == property && board[i].owner != NULL &&
                (board[i].PropertyProperties.noOfHouses > 0 || board[i].PropertyProperties.noOfHotels > 0)) {
                developed[n++] = i;
            }
        }
        if (n > 0) {
            int idx = developed[rand() % n];
            printf("National disaster damages %s\n", board[idx].name);
            damageBuilding(&board[idx]);
        } else {
            printf("No developed property - no damage\n");
        }
        break;
    }
    }
    printf("=========================================================\n");
}

void decayNationalEventEffects(player *player_x, square *board, context *contextOfTheGame) {
    int i = 0;
    while (i < player_x->numActiveNatlEffects) {
        player_x->activeNatlEffects[i].roundsRemaining--;
        if (player_x->activeNatlEffects[i].roundsRemaining > 0) {
            i++;
            continue;
        }

        NationalEventType effect = player_x->activeNatlEffects[i].effect;
        switch (effect) {
        case StockMarketRise:
            stockMarketRise_deactivate(board);
            break;
        case EconomicDowntime:
            economicDownturn_deactivate(board);
            break;
        case HousingSubsidy_NationalEvent:
            housingSubsidy_deactivate(board);
            break;
        case ForeignFunding:
            foreignFunding_deactivate(board);
            break;
        case PortExpansion:
            portExpansion_deactivate(board);
            break;
        case CurrencyDepreciation:
            currencyDepreciation_deactivate(board);
            break;
        case PropertyRevaluation:
            propertyRevaluation_deactivate(board, player_x->activeNatlEffects[i].affectedGroup);
            break;
        case PoliticalRally:
            board[player_x->activeNatlEffects[i].affectedSquare].isClosed = false;
            printf("%s is reopened\n", board[player_x->activeNatlEffects[i].affectedSquare].name);
            break;
        case LabourStrike:
            player_x->constructionSuspended = false;
            break;
        case InterestRateCut:
            contextOfTheGame->currentInterestRate += 2;
            break;
        case InterestRateIncrease:
            contextOfTheGame->currentInterestRate -= 2;
            break;
        default:
            break;
        }
        printf("%s effect expired for %s\n", getNatlEventName(effect), player_x->name);

        for (int j = i; j < player_x->numActiveNatlEffects - 1; j++) {
            player_x->activeNatlEffects[j] = player_x->activeNatlEffects[j + 1];
        }
        player_x->numActiveNatlEffects--;
    }
}

char *getRegionalEventName(regionalDevelopmentType effect) {
    switch (effect) {
    case southernTourismBoom:
        return "Southern Tourism Boom";
    case portCityExpansion:
        return "Port City Expansion";
    case itIndustryGrowth:
        return "IT Industry Growth";
    case nothernDevelopmentProgramme:
        return "Northern Development Programme";
    case teaExportBoom:
        return "Tea Export Boom";
    case airPortExpansion:
        return "Airport Expansion";
    case universityCityGrowth:
        return "University City Growth";
    case beachPollution:
        return "Beach Pollution";
    case floodDamage:
        return "Flood Damage";
    case transportStrike:
        return "Transport Strike";
    case electricityTariffIncrease:
        return "Electricity Tariff Increase";
    case waterShortage:
        return "Water Shortage";
    }
    return "Unknown";
}

void addRegionalEffect(context *contextOfTheGame, regionalDevelopmentType effect, int rounds, groupType group, int squareIdx) {
    if (contextOfTheGame->numActiveRegionalEffects >= 5) {
        return;
    }
    int i = contextOfTheGame->numActiveRegionalEffects++;
    contextOfTheGame->activeRegionalEffects[i].effect = effect;
    contextOfTheGame->activeRegionalEffects[i].roundsRemaining = rounds;
    contextOfTheGame->activeRegionalEffects[i].affectedGroup = group;
    contextOfTheGame->activeRegionalEffects[i].affectedSquare = squareIdx;
}

void southernTourismBoom_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
        }
    }
}
void southernTourismBoom_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
        }
    }
}

void portCityExpansion_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == lightBlue) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.15);
        }
    }
}
void portCityExpansion_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == lightBlue) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.15);
        }
    }
}

void itIndustryGrowth_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == pink) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.15);
        }
    }
}
void itIndustryGrowth_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == pink) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.15);
        }
    }
}

void nothernDevelopmentProgramme_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == green) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
        }
    }
}
void nothernDevelopmentProgramme_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == green) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
        }
    }
}

void airPortExpansion_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == orange) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
        }
    }
}
void airPortExpansion_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == orange) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
        }
    }
}

void universityCityGrowth_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost * 0.85);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost * 0.85);
        }
    }
}
void universityCityGrowth_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost / 0.85);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost / 0.85);
        }
    }
}

void beachPollution_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 0.85);
        }
    }
}
void beachPollution_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 0.85);
        }
    }
}

void transportStrike_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == railway) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 0.75);
        }
    }
}
void transportStrike_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == railway) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 0.75);
        }
    }
}

void waterShortage_activate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.noOfHotels == 1) {
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty * 0.50);
        }
    }
}
void waterShortage_deactivate(square *board) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.noOfHotels == 1) {
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty / 0.50);
        }
    }
}

void regionalDevelopmentActivate(square *board, context *contextOfTheGame, playerPointers *playerObject) {
    // 12-card deck, top card drawn, then returned to the bottom
    regionalDevelopmentType deck[12] = {
        southernTourismBoom, portCityExpansion, itIndustryGrowth,
        nothernDevelopmentProgramme, teaExportBoom, airPortExpansion,
        universityCityGrowth, beachPollution, floodDamage,
        transportStrike, electricityTariffIncrease, waterShortage};

    regionalDevelopmentType card = deck[contextOfTheGame->topRegionalDevelopmentCard];
    contextOfTheGame->topRegionalDevelopmentCard = (contextOfTheGame->topRegionalDevelopmentCard + 1) % 12;
    contextOfTheGame->roundThatRegionalDevelopmentHappened = contextOfTheGame->currentBoardRound;

    printf("\n=========================================================\n");
    printf("Regional Development Card : %s\n", getRegionalEventName(card));
    printf("---------------------------------------------------------\n");

    switch (card) {
    case southernTourismBoom:
        printf("Southern (yellow) property values increase by 20%% for 15 rounds\n");
        southernTourismBoom_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case portCityExpansion:
        printf("Port city (light blue) property values increase by 15%% for 15 rounds\n");
        portCityExpansion_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case itIndustryGrowth:
        printf("IT corridor (pink) property values increase by 15%% for 15 rounds\n");
        itIndustryGrowth_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case nothernDevelopmentProgramme:
        printf("Northern (green) property values increase by 20%% for 15 rounds\n");
        nothernDevelopmentProgramme_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case teaExportBoom: {
        player *all[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
        for (int i = 0; i < 4; i++) {
            if (!all[i]->isBankrupt) {
                all[i]->cash += 2500;
                printf("%s received LKR 2500 tea export dividend\n", all[i]->name);
            }
        }
        break;
    }
    case airPortExpansion:
        printf("Airport corridor (orange) property values increase by 20%% for 15 rounds\n");
        airPortExpansion_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case universityCityGrowth:
        printf("Construction costs reduced by 15%% for 15 rounds\n");
        universityCityGrowth_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case beachPollution:
        printf("Southern (yellow) property values decrease by 15%% for 15 rounds\n");
        beachPollution_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case floodDamage: {
        int coastal[40], n = 0;
        for (int i = 0; i < 40; i++) {
            if (board[i].type == property && board[i].PropertyProperties.propertyGroup == yellow && board[i].owner != NULL) {
                coastal[n++] = i;
            }
        }
        if (n > 0) {
            int idx = coastal[rand() % n];
            printf("Regional floods damage %s\n", board[idx].name);
            damageBuilding(&board[idx]);
        } else {
            printf("No coastal property owned - no damage\n");
        }
        break;
    }
    case transportStrike:
        printf("Railway station values decrease by 25%% for 15 rounds\n");
        transportStrike_activate(board);
        addRegionalEffect(contextOfTheGame, card, 15, 0, -1);
        break;
    case electricityTariffIncrease: {
        player *all[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
        for (int i = 0; i < 4; i++) {
            if (!all[i]->isBankrupt) {
                int levy = all[i]->cash;
                if (all[i]->cash >= 1500) {
                    levy = 1500;
                }
                all[i]->cash -= levy;
                printf("%s paid LKR %d electricity surcharge\n", all[i]->name, levy);
            }
        }
        break;
    }
    case waterShortage:
        printf("Hotel rent halved for 5 rounds\n");
        waterShortage_activate(board);
        addRegionalEffect(contextOfTheGame, card, 5, 0, -1);
        break;
    }
    printf("=========================================================\n");
}

void decayRegionalDevelopmentEffects(context *contextOfTheGame, square *board) {
    int i = 0;
    while (i < contextOfTheGame->numActiveRegionalEffects) {
        contextOfTheGame->activeRegionalEffects[i].roundsRemaining--;
        if (contextOfTheGame->activeRegionalEffects[i].roundsRemaining > 0) {
            i++;
            continue;
        }

        regionalDevelopmentType effect = contextOfTheGame->activeRegionalEffects[i].effect;
        switch (effect) {
        case southernTourismBoom:
            southernTourismBoom_deactivate(board);
            break;
        case portCityExpansion:
            portCityExpansion_deactivate(board);
            break;
        case itIndustryGrowth:
            itIndustryGrowth_deactivate(board);
            break;
        case nothernDevelopmentProgramme:
            nothernDevelopmentProgramme_deactivate(board);
            break;
        case airPortExpansion:
            airPortExpansion_deactivate(board);
            break;
        case universityCityGrowth:
            universityCityGrowth_deactivate(board);
            break;
        case beachPollution:
            beachPollution_deactivate(board);
            break;
        case transportStrike:
            transportStrike_deactivate(board);
            break;
        case waterShortage:
            waterShortage_deactivate(board);
            break;
        default:
            break;
        }
        printf("%s effect expired\n", getRegionalEventName(effect));

        for (int j = i; j < contextOfTheGame->numActiveRegionalEffects - 1; j++) {
            contextOfTheGame->activeRegionalEffects[j] = contextOfTheGame->activeRegionalEffects[j + 1];
        }
        contextOfTheGame->numActiveRegionalEffects--;
    }
}

char *getGroupName(groupType group) {
    switch (group) {
    case brown:
        return "Brown";
    case lightBlue:
        return "Light Blue";
    case pink:
        return "Pink";
    case orange:
        return "Orange";
    case red:
        return "Red";
    case yellow:
        return "Yellow";
    case green:
        return "Green";
    case darkBlue:
        return "Dark Blue";
    }
    return "Unknown";
}

void dynamicPropertyBoom_activate(square *board, groupType group) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == group) {
            board[i].PropertyProperties.initialPrice = doubleToInt(board[i].PropertyProperties.initialPrice * 1.15);
            board[i].mortgageValue = doubleToInt(board[i].mortgageValue * 1.15);
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty * 1.25);
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost * 1.10);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost * 1.10);
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
        }
    }
}
void dynamicPropertyBoom_deactivate(square *board, groupType group) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == group) {
            board[i].PropertyProperties.initialPrice = doubleToInt(board[i].PropertyProperties.initialPrice / 1.15);
            board[i].mortgageValue = doubleToInt(board[i].mortgageValue / 1.15);
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty / 1.25);
            board[i].PropertyProperties.houseConstructionCost = doubleToInt(board[i].PropertyProperties.houseConstructionCost / 1.10);
            board[i].PropertyProperties.hotelConstructionCost = doubleToInt(board[i].PropertyProperties.hotelConstructionCost / 1.10);
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
        }
    }
}

void dynamicPropertyDecline_activate(square *board, groupType group) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == group) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 0.85);
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty * 0.80);
            board[i].mortgageValue = doubleToInt(board[i].mortgageValue * 0.90);
        }
    }
}
void dynamicPropertyDecline_deactivate(square *board, groupType group) {
    for (int i = 0; i < 40; i++) {
        if (board[i].type == property && board[i].PropertyProperties.propertyGroup == group) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 0.85);
            board[i].PropertyProperties.currentRentalofProperty = doubleToInt(board[i].PropertyProperties.currentRentalofProperty / 0.80);
            board[i].mortgageValue = doubleToInt(board[i].mortgageValue / 0.90);
        }
    }
}

void dynamicPropertyEventActivate(square *board, context *contextOfTheGame) {
    // end any leftover effects from a previous review first
    if (contextOfTheGame->dynamicEventRoundsRemaining > 0) {
        if (contextOfTheGame->dynamicBoomGroup != (groupType)-1) {
            dynamicPropertyBoom_deactivate(board, contextOfTheGame->dynamicBoomGroup);
        }
        if (contextOfTheGame->dynamicDeclineGroup != (groupType)-1) {
            dynamicPropertyDecline_deactivate(board, contextOfTheGame->dynamicDeclineGroup);
        }
    }

    // random boom group - same group cannot boom in consecutive reviews
    groupType boomGroup = (groupType)(brown + (rand() % 8));
    while (boomGroup == contextOfTheGame->lastDynamicBoomGroup) {
        boomGroup = (groupType)(brown + (rand() % 8));
    }
    // random decline group - different from the boom group, cannot decline consecutively
    groupType declineGroup = (groupType)(brown + (rand() % 8));
    while (declineGroup == boomGroup || declineGroup == contextOfTheGame->lastDynamicDeclineGroup) {
        declineGroup = (groupType)(brown + (rand() % 8));
    }

    contextOfTheGame->lastDynamicBoomGroup = boomGroup;
    contextOfTheGame->lastDynamicDeclineGroup = declineGroup;
    contextOfTheGame->dynamicBoomGroup = boomGroup;
    contextOfTheGame->dynamicDeclineGroup = declineGroup;
    contextOfTheGame->dynamicEventRoundsRemaining = 10;
    contextOfTheGame->roundThatDynamicPropertyEventHappened = contextOfTheGame->currentBoardRound;

    printf("\n=========================================================\n");
    printf("Property Market Review (Round %d)\n", contextOfTheGame->currentBoardRound);
    printf("---------------------------------------------------------\n");
    printf("Market Boom on %s group for 10 rounds\n", getGroupName(boomGroup));
    printf("Purchase prices +15%%\nmortgage values +15%%\nrental income +25%%\n");
    printf("Construction costs +10%%\nproperty values +20%%\n\n");
    printf("Market Decline on %s group for 10 rounds\n", getGroupName(declineGroup));
    printf("Property values -15%%\nrental income -20%%\nmortgage values -10%%\n");
    printf("Auction starting prices -25%%\n");
    printf("=========================================================\n");

    dynamicPropertyBoom_activate(board, boomGroup);
    dynamicPropertyDecline_activate(board, declineGroup);
}

void decayDynamicPropertyEffects(context *contextOfTheGame, square *board) {
    if (contextOfTheGame->dynamicEventRoundsRemaining <= 0) {
        return;
    }
    contextOfTheGame->dynamicEventRoundsRemaining--;
    if (contextOfTheGame->dynamicEventRoundsRemaining > 0) {
        return;
    }

    if (contextOfTheGame->dynamicBoomGroup != (groupType)-1) {
        dynamicPropertyBoom_deactivate(board, contextOfTheGame->dynamicBoomGroup);
        printf("%s group Market Boom expired\n", getGroupName(contextOfTheGame->dynamicBoomGroup));
    }
    if (contextOfTheGame->dynamicDeclineGroup != (groupType)-1) {
        dynamicPropertyDecline_deactivate(board, contextOfTheGame->dynamicDeclineGroup);
        printf("%s group Market Decline expired\n", getGroupName(contextOfTheGame->dynamicDeclineGroup));
    }
    contextOfTheGame->dynamicBoomGroup = (groupType)-1;
    contextOfTheGame->dynamicDeclineGroup = (groupType)-1;
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

    double multiplier = 1.0000 + (double)contextofgame->currentInflation / 100.0;

    for (int i = 0; i <= 39; i++) {

        board[i].curruntValue = doubleToInt((double)board[i].curruntValue * multiplier);
        board[i].PropertyProperties.currentRentalofProperty = doubleToInt((double)board[i].PropertyProperties.currentRentalofProperty * multiplier);
        board[i].PropertyProperties.initialPrice = doubleToInt((double)board[i].PropertyProperties.initialPrice * multiplier);
        board[i].PropertyProperties.houseConstructionCost = doubleToInt((double)board[i].PropertyProperties.houseConstructionCost * multiplier);
        board[i].PropertyProperties.hotelConstructionCost = doubleToInt((double)board[i].PropertyProperties.hotelConstructionCost * multiplier);
    }
    contextofgame->roundThatInflationHappened = contextofgame->currentBoardRound;
}
