#include "types.h"
#include <stdbool.h>
#include <stdio.h>

void resolveSquare(player *player_x, square *board, context *contextOfGame, playerPointers *playerObject) {
    if (player_x->loantakigLap + 20 < contextOfGame->currentBoardRound && player_x->hasDebt == true) {
        printf("\n%s failed to replay debt. All assets transfered to the Bank...\nAuction starts now ...\n", player_x->name);
        for (int i = 0; i <= 39; i++) {
            if (board[i].owner == player_x) {
                bankruptAuction(player_x, board, contextOfGame, &board[i], playerObject);
            }
        }
        player_x->hasDebt = false;
    }

    decayNationalEventEffects(player_x, board);

    squareType squareToResolve = board[player_x->currentSquare].type;
    switch (squareToResolve) {
    case go:
        resolveGO(player_x);
        break;
    case special:
        resolveSpecial(player_x, board);
        break;
    case railway:
        resolveRailway(player_x, board, playerObject, contextOfGame);
        break;
    case utility:
        resolveUtility(player_x, board, contextOfGame, playerObject);
        break;
    case event:
        resolveEvent(player_x, board, contextOfGame, playerObject);
        break;
    case insure:
        resolveInsure(player_x, board);
        break;
    case tax:
        resolveTax(player_x, board, contextOfGame);
        break;
    case bank:
        resolveBank(player_x, board, contextOfGame);
        break;
    case property:
        resolveProperty(player_x, board, contextOfGame, playerObject);
        break;
    }
}
void jailLogic(player *player_x, bool doublesRolled) {
    playerType tempPlayer = player_x->playerID;

    switch (tempPlayer) {

    case conservativeBanker:
        if (doublesRolled == true) {
            player_x->Jail = outside;
            player_x->jailRoundCounter = 0;
            printf("%s gets out from the jail by rolling doubles\n",
                   player_x->name);
        } else if (player_x->jailRoundCounter > 3) {
            player_x->Jail = outside;
            printf("%s gets out from the jail by staying 3 turns inside jail\n",
                   player_x->name);
            player_x->jailRoundCounter = 0;
        }
        break;
    default:

        if (player_x->cash > 300) {
            player_x->cash -= 300;
            player_x->Jail = outside;
            player_x->jailRoundCounter = 0;
            printf("%s gets out from the jail by paying a bailout of LKR 300\n",
                   player_x->name);
        } else if (player_x->jailRoundCounter > 3) {
            player_x->Jail = outside;
            player_x->jailRoundCounter = 0;
            printf("%s gets out from the jail by staying 3 turns inside jail\n",
                   player_x->name);
        } else if (doublesRolled == true) {
            player_x->Jail = outside;
            player_x->jailRoundCounter = 0;
            printf("%s gets out from the jail by rolling doubles\n", player_x->name);
        }

        break;
    }
}
void resolveGO(player *player_x) {

    player_x->cash = player_x->cash + 2000;
    printf("%s recieved LKR 2000 by landing on GO ...\n", player_x->name);
}
void resolveSpecial(player *player_x, square *board) {

    specialityType specialityOfSquare =
        board[player_x->currentSquare].specialityProperties.specililtyOfSquare;

    switch (specialityOfSquare) {
    case gotoJail:
        player_x->currentSquare = 10; // jail square
        player_x->Jail = inside;
        player_x->jailRoundCounter = 0;
        printf("%s got inside the jail ...\n", player_x->name);
        break;
    default:
        break;
    }
}

void resolveUtility(player *player_x, square *board, context *contextOfTheGame, playerPointers *playerObject) {
    if (board[player_x->currentSquare].owner == player_x) {
        return;
    }

    if (board[player_x->currentSquare].owner->playerID == bankOfCeylon) {
        // buy logic and return
        switch (player_x->playerID) {
        case aggresiveInvester:
            if (aggrRailwayBuyCondition(player_x, board)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfUtilities++;
            }
            break;
        case riskTaker:
            if (riskTkrRailwayBuyCondition(player_x, board)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfUtilities++;
            }
            break;
        case conservativeBanker:
            if (consBankerRailwayBuyCondition(player_x, board)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfUtilities++;
            }
            break;
        case opportunisticTrader:
            if (opprtTrdrRailwayBuyCondition(player_x, board, contextOfTheGame)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfUtilities++;
            }
            break;
        default:
            break;
        }
    }

    switch (board[player_x->currentSquare].owner->noOfUtilities) {
    case 1:

        board[player_x->currentSquare].utilityProperties.currentUtilityRent = 4 * player_x->diceRoll;
        if (player_x->cash >= board[player_x->currentSquare].utilityProperties.currentUtilityRent) {
            player_x->cash -= board[player_x->currentSquare].utilityProperties.currentUtilityRent;
            board[player_x->currentSquare].owner->cash += board[player_x->currentSquare].utilityProperties.currentUtilityRent;
            printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, board[player_x->currentSquare].utilityProperties.currentUtilityRent, board[player_x->currentSquare].owner->name, board[player_x->currentSquare].name);
        } else {
            AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
        }
        break;

    case 2:

        board[player_x->currentSquare].utilityProperties.currentUtilityRent = 10 * player_x->diceRoll;
        if (player_x->cash >= board[player_x->currentSquare].utilityProperties.currentUtilityRent) {
            player_x->cash -= board[player_x->currentSquare].utilityProperties.currentUtilityRent;
            board[player_x->currentSquare].owner->cash += board[player_x->currentSquare].utilityProperties.currentUtilityRent;
            printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, board[player_x->currentSquare].utilityProperties.currentUtilityRent, board[player_x->currentSquare].owner->name, board[player_x->currentSquare].name);
        } else {
            AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
        }
        break;

    default:
        break;
    }
}
void resolveEvent(player *player_x, square *board, context *contextOfTheGame, playerPointers *playerObject) {
    nationalEventActivate(player_x, board, contextOfTheGame, playerObject);
}
void resolveInsure(player *player_x, square *board) {}
void resolveTax(player *player_x, square *board, context *contextOfTheGame) {
    int taxAmount = doubleToInt((double)player_x->cash * (double)contextOfTheGame->currentTaxRate / 100.0000);
    player_x->cash -= taxAmount;
    printf("%s played LKR %d as Income tax\n", player_x->name, taxAmount);
}

void resolveRailway(player *player_x, square *board, playerPointers *playerObject, context *contextOfTheGame) {
    // if ownwed by bank
    if (board[player_x->currentSquare].owner->playerID == bankOfCeylon) {
        switch (player_x->playerID) {
        case aggresiveInvester:
            if (aggrRailwayBuyCondition(player_x, board)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfRailways++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
            }
            break;
        case riskTaker:
            if (riskTkrRailwayBuyCondition(player_x, board)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfRailways++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
            }
            break;
        case conservativeBanker:
            if (consBankerRailwayBuyCondition(player_x, board)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfRailways++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
            }
            break;
        case opportunisticTrader:
            if (opprtTrdrRailwayBuyCondition(player_x, board, contextOfTheGame)) {
                board[player_x->currentSquare].owner = player_x;
                player_x->noOfRailways++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
            }
            break;
        default:
            break;
        }

    } else if (board[player_x->currentSquare].owner->playerID != player_x->playerID) {
        switch (board[player_x->currentSquare].owner->noOfRailways) {
        case 1: {
            int railRent = board[player_x->currentSquare].railwayProperties.baseRentOfRailway;
            if (player_x->cash >= railRent) {
                player_x->cash -= railRent;
                board[player_x->currentSquare].owner->cash += railRent;
                printf("%s payed LKR %d as the rent of %s\n", player_x->name, railRent, board[player_x->currentSquare].name);
            } else {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
            }
            break;
        }
        case 2: {
            int railRent = board[player_x->currentSquare].railwayProperties.baseRentOfRailway_2_owned;
            if (player_x->cash >= railRent) {
                player_x->cash -= railRent;
                board[player_x->currentSquare].owner->cash += railRent;
                printf("%s payed LKR %d as the rent of %s\n", player_x->name, railRent, board[player_x->currentSquare].name);
            } else {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
            }
            break;
        }
        case 3: {
            int railRent = board[player_x->currentSquare].railwayProperties.baseRentOfRailway_3_owned;
            if (player_x->cash >= railRent) {
                player_x->cash -= railRent;
                board[player_x->currentSquare].owner->cash += railRent;
                printf("%s   payed LKR %d as the rent of %s\n", player_x->name, railRent, board[player_x->currentSquare].name);
            } else {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
            }
            break;
        }
        case 4: {
            int railRent = board[player_x->currentSquare].railwayProperties.baseRentOfRailway_4_owned;
            if (player_x->cash >= railRent) {
                player_x->cash -= railRent;
                board[player_x->currentSquare].owner->cash += railRent;
                printf("%s payed LKR %d as the rent of %s\n", player_x->name, railRent, board[player_x->currentSquare].name);
            } else {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
            }
            break;
        }
        default:
            break;
        }
    }
    // if owne
}
void resolveProperty(player *player_x, square *board,
                     context *contextOfTheGame, playerPointers *playerObject) {

    // if property owns by bank
    if (board[player_x->currentSquare].owner->playerID == bankOfCeylon) {
        playerType currentPlayer = player_x->playerID;

        switch (currentPlayer) {
        case aggresiveInvester:

            if ((player_x->cash >
                 (1000 + board[player_x->currentSquare]
                             .PropertyProperties.initialPrice)) &&
                (board[player_x->currentSquare].owner->playerID !=
                 aggresiveInvester)) {

                player_x->cash =
                    player_x->cash - board[player_x->currentSquare]
                                         .PropertyProperties.initialPrice;
                board[player_x->currentSquare].owner = player_x;
                printf("%s buys %s\n", player_x->name,
                       board[player_x->currentSquare].name);
                player_x->noOfProperties++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
            }
            break;

        case conservativeBanker:

            if ((player_x->cash - (board[player_x->currentSquare].PropertyProperties.initialPrice) >
                 (player_x->cash / 2)) &&
                (contextOfTheGame->currentActiveEconEvent != EconomicRecession)) {

                player_x->cash =
                    player_x->cash - board[player_x->currentSquare]
                                         .PropertyProperties.initialPrice;
                board[player_x->currentSquare].owner = player_x;
                printf("%s buys %s\n", player_x->name,
                       board[player_x->currentSquare].name);

                player_x->noOfProperties++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
                // auction logic to be implemented
            }
            break;

        case riskTaker:

            if (player_x->cash > board[player_x->currentSquare].PropertyProperties.initialPrice) {
                player_x->cash -= board[player_x->currentSquare].PropertyProperties.initialPrice;
                board[player_x->currentSquare].owner = player_x;
                printf("%s buys %s\n", player_x->name,
                       board[player_x->currentSquare].name);

                player_x->noOfProperties++;
            } else {
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
                // auction logic
            }
            break;

        case opportunisticTrader:
            if ((player_x->cash > board[player_x->currentSquare].PropertyProperties.initialPrice) && (contextOfTheGame->currentActiveEconEvent != EconomicRecession) && (contextOfTheGame->currentInflation > 0)) {

                player_x->cash -= board[player_x->currentSquare].PropertyProperties.initialPrice;
                board[player_x->currentSquare].owner = player_x;
                printf("%s buys %s\n", player_x->name,
                       board[player_x->currentSquare].name);

                player_x->noOfProperties++;
            } else {
                // auction logic
                noBuyAuction(player_x, playerObject, board, contextOfTheGame, &board[player_x->currentSquare]);
            }
            break;

        default:
            break;
        }
    }
    // if property owned by another player
    else if (board[player_x->currentSquare].owner->playerID !=
             player_x->playerID) {

        playerType currentPlayer = player_x->playerID;
        switch (currentPlayer) {
        case aggresiveInvester:

            if ((player_x->cash >
                 board[player_x->currentSquare]
                     .PropertyProperties.currentRentalofProperty) &&
                (board[player_x->currentSquare].mortgageStatus !=
                 mortgagedToBank)) {

                payRent(player_x, board);

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty && player_x->noOfProperties == 0) {
                printf("\n%s went Bankrupt \n", player_x->name);
                player_x->isBankrupt = true;
                return;

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty) {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
                return;
            }
            break;

        case conservativeBanker:

            if ((player_x->cash >
                 board[player_x->currentSquare]
                     .PropertyProperties.currentRentalofProperty) &&
                (board[player_x->currentSquare].mortgageStatus !=
                 mortgagedToBank)) {

                payRent(player_x, board);

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty && player_x->noOfProperties == 0) {
                printf("\n%s went Bankrupt \n", player_x->name);
                player_x->isBankrupt = true;
                return;

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty) {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
                return;
            }
            break;
        case riskTaker:

            if ((player_x->cash >
                 board[player_x->currentSquare]
                     .PropertyProperties.currentRentalofProperty) &&
                (board[player_x->currentSquare].mortgageStatus !=
                 mortgagedToBank)) {

                payRent(player_x, board);

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty && player_x->noOfProperties == 0) {
                printf("\n%s went Bankrupt \n", player_x->name);
                player_x->isBankrupt = true;
                return;

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty) {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
                return;
            }
            break;

        case opportunisticTrader:

            if ((player_x->cash >
                 board[player_x->currentSquare]
                     .PropertyProperties.currentRentalofProperty) &&
                (board[player_x->currentSquare].mortgageStatus !=
                 mortgagedToBank)) {

                payRent(player_x, board);

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty && player_x->noOfProperties == 0) {
                printf("\n%s went Bankrupt \n", player_x->name);
                player_x->isBankrupt = true;
                return;

            } else if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty) {
                AggrNoCashAuction(board, player_x, playerObject, contextOfTheGame);
                return;
            }
            break;

        default:
            break;
        }
    }

    // if property owned by the player
    else if (board[player_x->currentSquare].owner == player_x) {

        if (player_x->constructionSuspended == true) {
            printf("%s cannot construct buildings (Labour Strike) ...\n", player_x->name);
            return;
        }

        bool eligibleForHouse = checkForMonopoly(player_x, board);

        playerType currentPlayer = player_x->playerID;

        switch (currentPlayer) {

        case aggresiveInvester:
            // test case

            // sellingAuction(player_x, playerObject->player_1, playerObject->player_2,
            //                playerObject->player_3, playerObject->player_4, board, contextOfTheGame, &board[player_x->currentSquare]);

            if (eligibleForHouse && (board[player_x->currentSquare].PropertyProperties.houseConstructionCost <= player_x->cash)) {
                // build house
                if (board[player_x->currentSquare].PropertyProperties.noOfHouses >= 4 && player_x->cash >= board[player_x->currentSquare].PropertyProperties.hotelConstructionCost) {

                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.hotelConstructionCost;
                    board[player_x->currentSquare].PropertyProperties.noOfHotels = 1;

                    player_x->noOfHotelsOwned = 1;
                    player_x->noOfHousesOwned -= 4;
                    board[player_x->currentSquare].PropertyProperties.noOfHouses = 0;
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 10 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    printf("%s constructed a hotel at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.hotelConstructionCost);
                }

                if (board[player_x->currentSquare].PropertyProperties.noOfHouses < 4 && board[player_x->currentSquare].PropertyProperties.noOfHotels == 0) {

                    board[player_x->currentSquare].PropertyProperties.noOfHouses++;
                    player_x->noOfHousesOwned++;
                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.houseConstructionCost;
                    printf("%s constructed a house at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.houseConstructionCost);
                }

                switch (board[player_x->currentSquare].PropertyProperties.noOfHouses) {
                case 1:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 2 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 2:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 3 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 3:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 5 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 4:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 7 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                default:
                    break;
                }
            }
            break;

        case conservativeBanker:

            if (eligibleForHouse && ((player_x->cash - board[player_x->currentSquare].PropertyProperties.houseConstructionCost) > player_x->cash / 2) &&
                (contextOfTheGame->currentActiveEconEvent != EconomicRecession)) {
                // build house
                if (board[player_x->currentSquare].PropertyProperties.noOfHouses >= 4 &&
                    ((player_x->cash - board[player_x->currentSquare].PropertyProperties.hotelConstructionCost) > player_x->cash / 2) &&
                    (player_x->hasDebt == false)) {

                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.hotelConstructionCost;
                    board[player_x->currentSquare].PropertyProperties.noOfHotels = 1;

                    player_x->noOfHotelsOwned = 1;
                    board[player_x->currentSquare].PropertyProperties.noOfHouses = 0;
                    player_x->noOfHousesOwned -= 4;
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 10 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    printf("%s constructed a hotel at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.hotelConstructionCost);
                }

                if (board[player_x->currentSquare].PropertyProperties.noOfHouses < 4 && board[player_x->currentSquare].PropertyProperties.noOfHotels == 0) {

                    board[player_x->currentSquare].PropertyProperties.noOfHouses++;
                    player_x->noOfHousesOwned++;
                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.houseConstructionCost;
                    printf("%s constructed a house at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.houseConstructionCost);
                }

                switch (board[player_x->currentSquare].PropertyProperties.noOfHouses) {
                case 1:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 2 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 2:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 3 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 3:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 5 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 4:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 7 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                default:
                    break;
                }
            }
            break;

        case riskTaker:
            if (eligibleForHouse && (board[player_x->currentSquare].PropertyProperties.houseConstructionCost <= player_x->cash)) {
                // build house
                if (board[player_x->currentSquare].PropertyProperties.noOfHouses >= 4 &&
                    ((player_x->cash - board[player_x->currentSquare].PropertyProperties.hotelConstructionCost) > player_x->cash / 2)) {

                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.hotelConstructionCost;
                    board[player_x->currentSquare].PropertyProperties.noOfHotels = 1;

                    player_x->noOfHotelsOwned = 1;
                    board[player_x->currentSquare].PropertyProperties.noOfHouses = 0;
                    player_x->noOfHousesOwned -= 4;
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 10 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    printf("%s constructed a hotel at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.hotelConstructionCost);
                }

                if (board[player_x->currentSquare].PropertyProperties.noOfHouses < 4 && board[player_x->currentSquare].PropertyProperties.noOfHotels == 0) {

                    board[player_x->currentSquare].PropertyProperties.noOfHouses++;
                    player_x->noOfHousesOwned++;
                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.houseConstructionCost;
                    printf("%s constructed a house at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.houseConstructionCost);
                }

                switch (board[player_x->currentSquare].PropertyProperties.noOfHouses) {
                case 1:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 2 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 2:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 3 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 3:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 5 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 4:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 7 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                default:
                    break;
                }
            }
            break;
        case opportunisticTrader:
            if (eligibleForHouse && (board[player_x->currentSquare].PropertyProperties.houseConstructionCost <= player_x->cash) && (contextOfTheGame->currentInflation <= 0)) {
                // build house
                if (board[player_x->currentSquare].PropertyProperties.noOfHouses >= 4 &&
                    ((player_x->cash - board[player_x->currentSquare].PropertyProperties.hotelConstructionCost) > player_x->cash / 2)) {

                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.hotelConstructionCost;
                    board[player_x->currentSquare].PropertyProperties.noOfHotels = 1;

                    player_x->noOfHotelsOwned = 1;
                    board[player_x->currentSquare].PropertyProperties.noOfHouses = 0;
                    player_x->noOfHousesOwned -= 4;
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 10 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    printf("%s constructed a hotel at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.hotelConstructionCost);
                }

                if (board[player_x->currentSquare].PropertyProperties.noOfHouses < 4 && board[player_x->currentSquare].PropertyProperties.noOfHotels == 0) {

                    board[player_x->currentSquare].PropertyProperties.noOfHouses++;
                    player_x->noOfHousesOwned++;
                    player_x->cash -= board[player_x->currentSquare].PropertyProperties.houseConstructionCost;
                    printf("%s constructed a house at %s for %d\n", player_x->name, board[player_x->currentSquare].name, board[player_x->currentSquare].PropertyProperties.houseConstructionCost);
                }

                switch (board[player_x->currentSquare].PropertyProperties.noOfHouses) {
                case 1:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 2 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 2:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 3 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 3:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 5 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                case 4:
                    board[player_x->currentSquare].PropertyProperties.currentRentalofProperty = 7 * board[player_x->currentSquare].PropertyProperties.baseRental;
                    break;
                default:
                    break;
                }
            }
            break;

        default:
            break;
        }
    }
}

bool checkForMonopoly(player *player_x, square *board) {

    // does the player own the full group?
    groupType CurrentGroup = board[player_x->currentSquare].PropertyProperties.propertyGroup;
    bool ownsAMonopoly = true;
    for (int i = 0; i < 40; i++) {
        bool check1 = (board[i].PropertyProperties.propertyGroup == CurrentGroup) && (board[i].owner != player_x);
        if (check1) {
            ownsAMonopoly = false;
        }
    }

    // houses must be evenly spread before the next build
    int currentNoOfHouses;
    if (board[player_x->currentSquare].PropertyProperties.noOfHotels == 1) {
        currentNoOfHouses = 5;
    } else {
        currentNoOfHouses = board[player_x->currentSquare].PropertyProperties.noOfHouses;
    }

    bool HouseEligiblePerBuildingCount = true;
    for (int i = 0; i < 40; i++) {
        if (board[i].PropertyProperties.propertyGroup != CurrentGroup) {
            continue;
        }
        int otherEffective;
        if (board[i].PropertyProperties.noOfHotels == 1) {
            otherEffective = 5;
        } else {
            otherEffective = board[i].PropertyProperties.noOfHouses;
        }
        if (otherEffective < currentNoOfHouses) {
            HouseEligiblePerBuildingCount = false;
            break;
        }
    }

    bool groupHasMortgage = false;
    for (int i = 0; i < 40; i++) {
        if (board[i].PropertyProperties.propertyGroup == CurrentGroup &&
            board[i].mortgageStatus == mortgagedToBank) {
            groupHasMortgage = true;
            break;
        }
    }
    return ownsAMonopoly && HouseEligiblePerBuildingCount && !groupHasMortgage;
}
