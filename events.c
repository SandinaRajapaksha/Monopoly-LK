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
    NationalEventType NationalEventCards[20] = {
        TourismHype, FuelShortage, HeavyFloods, PoliticalRally, StockMarketRise,
        EconomicDowntime, HousingSubsidy_NationalEvent, InterestRateCut,
        InterestRateIncrease, TaxAmnesty, PowerFailure, ForeignFunding,
        PortExpansion, FestivalSeason, LabourStrike, InsuranceDiscount,
        PropertyRevaluation, CurrencyDepreciation, GovernmentGrant,
        NationalDisaster};

    NationalEventType currentNationalEvent =
        NationalEventCards[*topNationalEventcard];
    *topNationalEventcard = (*topNationalEventcard + 1) % 20;
}

static const char *getNatlEventName(NationalEventType card) {
    switch (card) {
    case TourismHype: return "Tourism Hype";
    case FuelShortage: return "Fuel Shortage";
    case HeavyFloods: return "Heavy Floods";
    case PoliticalRally: return "Political Rally";
    case StockMarketRise: return "Stock Market Rise";
    case EconomicDowntime: return "Economic Downturn";
    case HousingSubsidy_NationalEvent: return "Housing Subsidy";
    case InterestRateCut: return "Interest Rate Cut";
    case InterestRateIncrease: return "Interest Rate Increase";
    case TaxAmnesty: return "Tax Amnesty";
    case PowerFailure: return "Power Failure";
    case ForeignFunding: return "Foreign Funding";
    case PortExpansion: return "Port Expansion";
    case FestivalSeason: return "Festival Season";
    case LabourStrike: return "Labour Strike";
    case InsuranceDiscount: return "Insurance Discount";
    case PropertyRevaluation: return "Property Revaluation";
    case CurrencyDepreciation: return "Currency Depreciation";
    case GovernmentGrant: return "Government Grant";
    case NationalDisaster: return "National Disaster";
    default: return "Unknown";
    }
}

static void addPlayerNatlEffect(player *p, NationalEventType card, int rounds,
                               groupType grp, int sq) {
    if (p->numActiveNatlEffects >= 5) return;
    int i = p->numActiveNatlEffects++;
    p->activeNatlEffects[i].effect = card;
    p->activeNatlEffects[i].roundsRemaining = rounds;
    p->activeNatlEffects[i].affectedGroup = grp;
    p->activeNatlEffects[i].affectedSquare = sq;
}

static void addBoardNatlEffect(context *ctx, NationalEventType card, int rounds,
                                groupType grp, int sq) {
    if (ctx->numActiveBoardNatlEffects >= 5) return;
    int i = ctx->numActiveBoardNatlEffects++;
    ctx->boardNatlEffects[i].effect = card;
    ctx->boardNatlEffects[i].roundsRemaining = rounds;
    ctx->boardNatlEffects[i].affectedGroup = grp;
    ctx->boardNatlEffects[i].affectedSquare = sq;
}

static void stockMarketRiseNatl_activate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property)
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.10);
}
static void stockMarketRiseNatl_deactivate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property)
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.10);
}

static void economicDowntimeNatl_activate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 0.85);
            board[i].PropertyProperties.currentRentalofProperty =
                doubleToInt(board[i].PropertyProperties.currentRentalofProperty * 0.9);
        }
    }
}
static void economicDowntimeNatl_deactivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 0.85);
            board[i].PropertyProperties.currentRentalofProperty =
                doubleToInt(board[i].PropertyProperties.currentRentalofProperty / 0.9);
        }
    }
}

static void housingSubsidyNatl_activate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property)
            board[i].PropertyProperties.houseConstructionCost =
                doubleToInt(board[i].PropertyProperties.houseConstructionCost * 0.70);
}
static void housingSubsidyNatl_deactivate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property)
            board[i].PropertyProperties.houseConstructionCost =
                doubleToInt(board[i].PropertyProperties.houseConstructionCost / 0.70);
}

static void foreignFundingNatl_activate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property &&
            (board[i].PropertyProperties.propertyGroup == orange ||
             board[i].PropertyProperties.propertyGroup == red))
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.15);
}
static void foreignFundingNatl_deactivate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property &&
            (board[i].PropertyProperties.propertyGroup == orange ||
             board[i].PropertyProperties.propertyGroup == red))
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.15);
}

static void portExpansionNatl_activate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == railway)
            board[i].curruntValue = doubleToInt(board[i].curruntValue * 1.20);
}
static void portExpansionNatl_deactivate(square *board) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == railway)
            board[i].curruntValue = doubleToInt(board[i].curruntValue / 1.20);
}

static void currencyDepreciationNatl_activate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost =
                doubleToInt(board[i].PropertyProperties.houseConstructionCost * 1.10);
            board[i].PropertyProperties.hotelConstructionCost =
                doubleToInt(board[i].PropertyProperties.hotelConstructionCost * 1.10);
        }
    }
}
static void currencyDepreciationNatl_deactivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost =
                doubleToInt(board[i].PropertyProperties.houseConstructionCost / 1.10);
            board[i].PropertyProperties.hotelConstructionCost =
                doubleToInt(board[i].PropertyProperties.hotelConstructionCost / 1.10);
        }
    }
}

static void applyRandomGroupBoost(square *board, double multiplier, groupType *outGroup) {
    groupType allGroups[8] = {brown, lightBlue, pink, orange, red, yellow, green, darkBlue};
    groupType chosen = allGroups[rand() % 8];
    *outGroup = chosen;
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property &&
            board[i].PropertyProperties.propertyGroup == chosen)
            board[i].curruntValue = doubleToInt(board[i].curruntValue * multiplier);
}

static void applyRandomGroupDeboost(square *board, double multiplier, groupType chosen) {
    for (int i = 0; i <= 39; i++)
        if (board[i].type == property &&
            board[i].PropertyProperties.propertyGroup == chosen)
            board[i].curruntValue = doubleToInt(board[i].curruntValue / multiplier);
}

void drawAndApplyNatlEventCard(player *player_x, square *board,
                                context *contextOfTheGame,
                                playerPointers *playerObject) {
    NationalEventType deck[20] = {
        TourismHype, FuelShortage, HeavyFloods, PoliticalRally, StockMarketRise,
        EconomicDowntime, HousingSubsidy_NationalEvent, InterestRateCut,
        InterestRateIncrease, TaxAmnesty, PowerFailure, ForeignFunding,
        PortExpansion, FestivalSeason, LabourStrike, InsuranceDiscount,
        PropertyRevaluation, CurrencyDepreciation, GovernmentGrant,
        NationalDisaster};

    NationalEventType card = deck[contextOfTheGame->topNationalEventCard];
    contextOfTheGame->topNationalEventCard =
        (contextOfTheGame->topNationalEventCard + 1) % 20;

    printf("\n============================================================\n");
    printf("  National Event Card Drawn: %s\n", getNatlEventName(card));
    printf("============================================================\n");

    switch (card) {

    case TourismHype:
        printf("Effect: Hotels earn double rent for 5 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 5, 0, -1);
        break;

    case FuelShortage:
        printf("Effect: Railway rent doubles for 5 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 5, 0, -1);
        break;

    case HeavyFloods: {
        printf("Effect: A random coastal property is damaged.\n\n");
        bool foundCoastal = false;
        int coastalID = -1;
        while (!foundCoastal) {
            coastalID = rand() % 40;
            if (board[coastalID].type == property &&
                board[coastalID].PropertyProperties.propertyGroup == yellow) {
                foundCoastal = true;
            }
        }
        if (board[coastalID].PropertyProperties.noOfHotels > 0) {
            board[coastalID].PropertyProperties.noOfHotels = 0;
            player_x->noOfHotelsOwned--;
            printf("  Hotel on %s was destroyed by floods!\n", board[coastalID].name);
        } else if (board[coastalID].PropertyProperties.noOfHouses > 0) {
            board[coastalID].PropertyProperties.noOfHouses--;
            player_x->noOfHousesOwned--;
            board[coastalID].PropertyProperties.currentRentalofProperty =
                board[coastalID].PropertyProperties.baseRental;
            printf("  A house on %s was destroyed by floods!\n", board[coastalID].name);
        } else {
            printf("  %s was flooded but no buildings to damage.\n", board[coastalID].name);
        }
        break;
    }

    case PoliticalRally: {
        printf("Effect: One random owned property closed for 2 rounds.\n\n");
        int attempts = 0;
        int rallySQ = -1;
        while (attempts < 100) {
            int r = rand() % 40;
            if (board[r].type == property && board[r].owner == player_x) {
                rallySQ = r;
                break;
            }
            attempts++;
        }
        if (rallySQ >= 0) {
            board[rallySQ].isClosed = true;
            printf("  %s is closed for 2 rounds due to political rally!\n", board[rallySQ].name);
            addBoardNatlEffect(contextOfTheGame, card, 2, 0, rallySQ);
        } else {
            printf("  No owned property to close.\n");
        }
        break;
    }

    case StockMarketRise:
        printf("Effect: All property values increase by 10%% for 15 rounds.\n\n");
        stockMarketRiseNatl_activate(board);
        addBoardNatlEffect(contextOfTheGame, card, 15, 0, -1);
        break;

    case EconomicDowntime:
        printf("Effect: Property values decrease by 15%% and rents decrease by 10%% for 15 rounds.\n\n");
        economicDowntimeNatl_activate(board);
        addBoardNatlEffect(contextOfTheGame, card, 15, 0, -1);
        break;

    case HousingSubsidy_NationalEvent:
        printf("Effect: House construction cost reduced by 30%% for 15 rounds.\n\n");
        housingSubsidyNatl_activate(board);
        addBoardNatlEffect(contextOfTheGame, card, 15, 0, -1);
        break;

    case InterestRateCut:
        printf("Effect: Loan interest reduced by 2%% for 15 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 15, 0, -1);
        break;

    case InterestRateIncrease:
        printf("Effect: Loan interest increased by 2%% for 15 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 15, 0, -1);
        break;

    case TaxAmnesty: {
        printf("Effect: Each non-bankrupt player receives LKR 2,000.\n\n");
        player *all[4] = {playerObject->player_1, playerObject->player_2,
                          playerObject->player_3, playerObject->player_4};
        for (int i = 0; i < 4; i++) {
            if (!all[i]->isBankrupt) {
                all[i]->cash += 2000;
                printf("  %s receives LKR 2,000 (Balance: LKR %d)\n",
                       all[i]->name, all[i]->cash);
            }
        }
        break;
    }

    case PowerFailure:
        printf("Effect: Utility income halved for 3 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 3, 0, -1);
        break;

    case ForeignFunding:
        printf("Effect: Commercial properties (Orange & Red) values increase by 15%% for 15 rounds.\n\n");
        foreignFundingNatl_activate(board);
        addBoardNatlEffect(contextOfTheGame, card, 15, 0, -1);
        break;

    case PortExpansion:
        printf("Effect: Railway station values increase by 20%% for 15 rounds.\n\n");
        portExpansionNatl_activate(board);
        addBoardNatlEffect(contextOfTheGame, card, 15, 0, -1);
        break;

    case FestivalSeason:
        printf("Effect: Hotels receive 50%% additional rent for 15 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 15, 0, -1);
        break;

    case LabourStrike:
        printf("Effect: Construction suspended for 2 rounds.\n\n");
        player_x->constructionSuspended = true;
        addPlayerNatlEffect(player_x, card, 2, 0, -1);
        break;

    case InsuranceDiscount:
        printf("Effect: Insurance premiums reduced by 20%% for 15 rounds.\n\n");
        addPlayerNatlEffect(player_x, card, 15, 0, -1);
        break;

    case PropertyRevaluation: {
        printf("Effect: A random property group appreciates by 15%% for 15 rounds.\n\n");
        groupType chosen;
        applyRandomGroupBoost(board, 1.15, &chosen);
        printf("  Group boosted: %s\n",
               chosen == brown ? "Brown" : chosen == lightBlue ? "Light Blue" :
               chosen == pink ? "Pink" : chosen == orange ? "Orange" :
               chosen == red ? "Red" : chosen == yellow ? "Yellow" :
               chosen == green ? "Green" : "Dark Blue");
        addBoardNatlEffect(contextOfTheGame, card, 15, chosen, -1);
        break;
    }

    case CurrencyDepreciation:
        printf("Effect: Construction costs increase by 10%% for 15 rounds.\n\n");
        currencyDepreciationNatl_activate(board);
        addBoardNatlEffect(contextOfTheGame, card, 15, 0, -1);
        break;

    case GovernmentGrant: {
        printf("Effect: A random non-bankrupt player receives LKR 5,000.\n\n");
        player *all[4] = {playerObject->player_1, playerObject->player_2,
                          playerObject->player_3, playerObject->player_4};
        int solvent[4], count = 0;
        for (int i = 0; i < 4; i++)
            if (!all[i]->isBankrupt) solvent[count++] = i;
        if (count > 0) {
            int pick = solvent[rand() % count];
            all[pick]->cash += 5000;
            printf("  %s receives LKR 5,000 (Balance: LKR %d)\n",
                   all[pick]->name, all[pick]->cash);
        }
        break;
    }

    case NationalDisaster: {
        printf("Effect: A random developed property is damaged.\n\n");
        int candidates[40], cnt = 0;
        for (int i = 0; i <= 39; i++)
            if (board[i].type == property &&
                (board[i].PropertyProperties.noOfHouses > 0 ||
                 board[i].PropertyProperties.noOfHotels > 0))
                candidates[cnt++] = i;
        if (cnt > 0) {
            int pick = candidates[rand() % cnt];
            if (board[pick].PropertyProperties.noOfHotels > 0) {
                board[pick].PropertyProperties.noOfHotels = 0;
                if (board[pick].owner) board[pick].owner->noOfHotelsOwned--;
                board[pick].PropertyProperties.currentRentalofProperty =
                    board[pick].PropertyProperties.baseRental * 7;
                printf("  Hotel on %s destroyed!\n", board[pick].name);
            } else {
                board[pick].PropertyProperties.noOfHouses--;
                if (board[pick].owner) board[pick].owner->noOfHousesOwned--;
                int h = board[pick].PropertyProperties.noOfHouses;
                int mult = (h == 0) ? 1 : (h == 1) ? 2 : (h == 2) ? 3 : (h == 3) ? 5 : 7;
                board[pick].PropertyProperties.currentRentalofProperty =
                    board[pick].PropertyProperties.baseRental * mult;
                printf("  A house on %s was destroyed!\n", board[pick].name);
            }
        } else {
            printf("  No developed properties exist to damage.\n");
        }
        break;
    }
    }
    printf("============================================================\n\n");
}

void decayPlayerNationalEffects(player *player_x) {
    for (int i = 0; i < player_x->numActiveNatlEffects; i++) {
        player_x->activeNatlEffects[i].roundsRemaining--;

        if (player_x->activeNatlEffects[i].roundsRemaining <= 0) {
            NationalEventType effect = player_x->activeNatlEffects[i].effect;

            printf("\n  [%s] National event card '%s' has expired.\n",
                   player_x->name, getNatlEventName(effect));

            if (effect == LabourStrike)
                player_x->constructionSuspended = false;

            for (int j = i; j < player_x->numActiveNatlEffects - 1; j++)
                player_x->activeNatlEffects[j] = player_x->activeNatlEffects[j + 1];
            player_x->numActiveNatlEffects--;
            i--;
        }
    }
}

void decayBoardNationalEffects(square *board, context *ctx) {
    for (int i = 0; i < ctx->numActiveBoardNatlEffects; i++) {
        ctx->boardNatlEffects[i].roundsRemaining--;

        if (ctx->boardNatlEffects[i].roundsRemaining <= 0) {
            NationalEventType effect = ctx->boardNatlEffects[i].effect;
            int sq = ctx->boardNatlEffects[i].affectedSquare;
            groupType grp = ctx->boardNatlEffects[i].affectedGroup;

            printf("\n  [Board] National event card '%s' has expired.\n",
                   getNatlEventName(effect));

            switch (effect) {
            case PoliticalRally:
                if (sq >= 0 && sq < 40) {
                    board[sq].isClosed = false;
                    printf("    %s is no longer closed.\n", board[sq].name);
                }
                break;
            case StockMarketRise:
                stockMarketRiseNatl_deactivate(board);
                break;
            case EconomicDowntime:
                economicDowntimeNatl_deactivate(board);
                break;
            case HousingSubsidy_NationalEvent:
                housingSubsidyNatl_deactivate(board);
                break;
            case ForeignFunding:
                foreignFundingNatl_deactivate(board);
                break;
            case PortExpansion:
                portExpansionNatl_deactivate(board);
                break;
            case CurrencyDepreciation:
                currencyDepreciationNatl_deactivate(board);
                break;
            case PropertyRevaluation:
                applyRandomGroupDeboost(board, 1.15, grp);
                break;
            default:
                break;
            }

            for (int j = i; j < ctx->numActiveBoardNatlEffects - 1; j++)
                ctx->boardNatlEffects[j] = ctx->boardNatlEffects[j + 1];
            ctx->numActiveBoardNatlEffects--;
            i--;
        }
    }
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
        // other affecting proerties to be added
    }
    contextofgame->roundThatInflationHappened = contextofgame->currentBoardRound;
}
