#include "types.h"
#include <stdbool.h>
#include <stdio.h>

void networthEvaluate(player *player_1, player *player_2, player *player_3, player *player_4, square *board) {
    player *players[4] = {player_1, player_2, player_3, player_4};

    for (int i = 0; i <= 3; i++) {
        int totalAssetValue = 0;
        int totalMortgageValuesofPlayer = 0;

        for (int j = 0; j <= 39; j++) {
            if (board[j].owner == players[i]) {
                if (board[j].type == property) {
                    int propertyValue = board[j].curruntValue;
                    if (board[j].mortgageStatus == mortgagedToBank) {
                        propertyValue = board[j].mortgageValue;
                    } else {
                        propertyValue += board[j].PropertyProperties.noOfHouses * board[j].PropertyProperties.houseConstructionCost;
                        propertyValue += board[j].PropertyProperties.noOfHotels * board[j].PropertyProperties.hotelConstructionCost;
                    }
                    totalAssetValue += propertyValue;
                    totalMortgageValuesofPlayer += board[j].mortgageValue;
                } else if (board[j].type == railway || board[j].type == utility) {
                    int assetValue = board[j].curruntValue;
                    if (board[j].mortgageStatus == mortgagedToBank) {
                        assetValue = board[j].mortgageValue;
                    }
                    totalAssetValue += assetValue;
                    totalMortgageValuesofPlayer += board[j].mortgageValue;
                }
            }
        }

        players[i]->netWorth = players[i]->cash + totalAssetValue - players[i]->outStandingLoan;
        players[i]->MaxElegibleLoanAmount = totalMortgageValuesofPlayer * 0.75;
    }
}
void resolveBank(player *player_x, square *board, context *contextOfTheGame) {

    playerType tempPlayer = player_x->playerID;

    // taking loans
    if (player_x->hasDebt == false) {
        switch (tempPlayer) {

        case aggresiveInvester:
            // if player has monopoly and cannot afford buildings in cash , he gest a loan.

            if (playerHasaMonopoly(player_x, board) && player_x->cash <= 5000) {
                player_x->hasDebt = true;
                player_x->cash += player_x->MaxElegibleLoanAmount;
                player_x->outStandingLoan = player_x->MaxElegibleLoanAmount;
                printf("%s borrowed a loan of LKR %d from the Bank of Ceylon\n", player_x->name, player_x->MaxElegibleLoanAmount);
                break;
            }
            break;
        case conservativeBanker:
            if (player_x->netWorth < 5000) {
                player_x->hasDebt = true;
                player_x->cash += player_x->MaxElegibleLoanAmount;
                player_x->outStandingLoan = player_x->MaxElegibleLoanAmount;
                printf("%s borrowed a loan of LKR %d from the Bank of Ceylon\n", player_x->name, player_x->MaxElegibleLoanAmount);
                break;
            }
            break;
        case riskTaker:
            player_x->hasDebt = true;
            player_x->cash += player_x->MaxElegibleLoanAmount;
            player_x->outStandingLoan = player_x->MaxElegibleLoanAmount;
            printf("%s borrowed a loan of LKR %d from the Bank of Ceylon\n", player_x->name, player_x->MaxElegibleLoanAmount);
            break;
        case opportunisticTrader:
            if (contextOfTheGame->currentActiveEconEvent == GovernmentHousingProgramme || contextOfTheGame->currentActiveEconEvent == StockMarketBoom) {
                player_x->hasDebt = true;
                player_x->cash += player_x->MaxElegibleLoanAmount;
                player_x->outStandingLoan = player_x->MaxElegibleLoanAmount;
                printf("%s borrowed a loan of LKR %d from the Bank of Ceylon\n", player_x->name, player_x->MaxElegibleLoanAmount);
                break;
            }
            break;
        default:
            break;
        }
    } else {

        // paying loans
        playerType tempPlayer = player_x->playerID;
        if (player_x->hasDebt == true && player_x->MaxElegibleLoanAmount > player_x->cash) {
            // auction
        }
        switch (tempPlayer) {

        case aggresiveInvester:
            if (player_x->cash > 2 * player_x->outStandingLoan) {
                player_x->cash -= player_x->outStandingLoan;
                player_x->hasDebt = false;
                printf("%s fully repaid the loan of %d to the Bank of Ceylon\n", player_x->name, player_x->outStandingLoan);
                player_x->outStandingLoan = 0;
            }
            break;
        case riskTaker:
            if (player_x->cash > 2 * player_x->outStandingLoan) {
                player_x->cash -= player_x->outStandingLoan;
                player_x->hasDebt = false;
                printf("%s fully repaid the loan of %d to the Bank of Ceylon\n", player_x->name, player_x->outStandingLoan);
                player_x->outStandingLoan = 0;
            }
            break;
        }
    }
}

bool playerHasaMonopoly(player *player_x, square *board) {

    bool hasMonopolyOnBrown = true;
    bool hasMonopolyOnLightBlue = true;
    bool hasMonopolyOnPink = true;
    bool hasMonopolyOnOrange = true;
    bool hasMonopolyOnRed = true;
    bool hasMonopolyOnYellow = true;
    bool hasMonopolyOnGreen = true;
    bool hasMonopolyOnDarkBlue = true;

    for (int i = 0; i <= 39; i++) {

        if (board[i].PropertyProperties.propertyGroup == brown) {
            if (board[i].owner != player_x) {
                hasMonopolyOnBrown = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == lightBlue) {
            if (board[i].owner != player_x) {
                hasMonopolyOnLightBlue = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == pink) {
            if (board[i].owner != player_x) {
                hasMonopolyOnPink = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == orange) {
            if (board[i].owner != player_x) {
                hasMonopolyOnOrange = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == red) {
            if (board[i].owner != player_x) {
                hasMonopolyOnRed = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == yellow) {
            if (board[i].owner != player_x) {
                hasMonopolyOnYellow = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == green) {
            if (board[i].owner != player_x) {
                hasMonopolyOnGreen = false;
            }
        }
        if (board[i].PropertyProperties.propertyGroup == darkBlue) {
            if (board[i].owner != player_x) {
                hasMonopolyOnDarkBlue = false;
            }
        }
    }
    bool returnBool = hasMonopolyOnBrown ||
                      hasMonopolyOnLightBlue ||
                      hasMonopolyOnPink ||
                      hasMonopolyOnOrange ||
                      hasMonopolyOnRed ||
                      hasMonopolyOnYellow ||
                      hasMonopolyOnGreen ||
                      hasMonopolyOnDarkBlue;

    return returnBool;
}
void printWinner(player *winner, int HighestBid, square *auctionedItem) {

    printf("%s Won the auction !\n", winner->name);
    printf("Bought %s for %d\n\n", winner->name, HighestBid);
    printf("============================================================\n\n");
};
void sellingAuction(player *player_x, player *player_1, player *player_2, player *player_3, player *player_4, square *board, context *contextOfGame, square *auctionItem) {

    printf("============================================================\n\n");
    printf("Auction\n\n");
    printf("============================================================\n\n");

    printf("Auctioned item : %s\n", auctionItem->name);
    printf("Current Owner : %s\n\n", player_x->name);

    player *candidates[4] = {player_1, player_2, player_3, player_4};
    player *bidders[3];
    for (int i = 0, j = 0; i <= 3; i++) {
        if (player_x != candidates[i]) {
            bidders[j] = candidates[i];
            j++;
        }
    }

    int startingPrice = auctionItem->curruntValue / 2;
    int HighestBid = startingPrice;

    int aggrHighestBid;
    int riskTakerHighestBid;
    int conserBankerHighestBid;
    int opportTraderHighestBid;

    player *HighestBidder = player_x;

    while (true) {
        if (player_x->noOfProperties == 0) {
            printf("\n%s went Bankrupt\n", player_x->name);
            player_x->isBankrupt = true;
            return;
        }
        // placing bids
        for (int i = 0; i <= 2; i++) {
            switch (bidders[i]->playerID) {

            case aggresiveInvester:
                if (HighestBidder->playerID == aggresiveInvester) {
                    // buys and win
                    auctionItem->PropertyProperties.noOfHouses = 0;
                    auctionItem->PropertyProperties.noOfHotels = 0;
                    // transfer funds to the owner
                    auctionItem->owner->cash += HighestBid;
                    auctionItem->owner->noOfProperties--;

                    // pay the bid and get ownership
                    auctionItem->owner = bidders[i];
                    bidders[i]->cash -= HighestBid;
                    bidders[i]->noOfProperties++;

                    printWinner(bidders[i], HighestBid, auctionItem);
                    return;
                }
                bool conditionAggr = (bidders[i]->cash >= HighestBid + 250) && (HighestBid < auctionItem->curruntValue * 1.2);
                if (conditionAggr) {
                    bidders[i]->cash -= 250;
                    aggrHighestBid = HighestBid + 250;
                    HighestBid = aggrHighestBid;
                    HighestBidder = bidders[i];
                }
                break;

            case riskTaker:
                if (HighestBidder->playerID == riskTaker) {
                    // buys and win
                    auctionItem->PropertyProperties.noOfHouses = 0;
                    auctionItem->PropertyProperties.noOfHotels = 0;
                    // transfer funds to the owner
                    auctionItem->owner->cash += HighestBid;
                    auctionItem->owner->noOfProperties--;

                    // pay the bid and get ownership
                    auctionItem->owner = bidders[i];
                    bidders[i]->cash -= HighestBid;
                    bidders[i]->noOfProperties++;

                    printWinner(bidders[i], HighestBid, auctionItem);
                    return;
                }
                bool conditionRiskTkr = bidders[i]->cash >= HighestBid + 250;
                if (conditionRiskTkr) {
                    riskTakerHighestBid = HighestBid + 250;
                    HighestBid = riskTakerHighestBid;
                    HighestBidder = bidders[i];
                }
                break;

            case conservativeBanker:
                if (HighestBidder->playerID == conservativeBanker) {
                    // buys and win
                    auctionItem->PropertyProperties.noOfHouses = 0;
                    auctionItem->PropertyProperties.noOfHotels = 0;
                    // transfer funds to the owner
                    auctionItem->owner->cash += HighestBid;
                    auctionItem->owner->noOfProperties--;

                    // pay the bid and get ownership
                    auctionItem->owner = bidders[i];
                    bidders[i]->cash -= HighestBid;
                    bidders[i]->noOfProperties++;

                    printWinner(bidders[i], HighestBid, auctionItem);
                    return;
                }
                bool conditionConserBanker = ((bidders[i]->cash - HighestBid + 250) > bidders[i]->cash / 2) && (HighestBid < auctionItem->curruntValue / (0.75));
                if (conditionConserBanker) {
                    conserBankerHighestBid = HighestBid + 250;
                    HighestBid = conserBankerHighestBid;
                    HighestBidder = bidders[i];
                }
                break;

            case opportunisticTrader:
                if (HighestBidder->playerID == opportunisticTrader) {
                    // buys and win
                    auctionItem->PropertyProperties.noOfHouses = 0;
                    auctionItem->PropertyProperties.noOfHotels = 0;
                    // transfer funds to the owner
                    auctionItem->owner->cash += HighestBid;
                    auctionItem->owner->noOfProperties--;

                    // pay the bid and get ownership
                    auctionItem->owner = bidders[i];
                    bidders[i]->cash -= HighestBid;
                    bidders[i]->noOfProperties++;

                    printWinner(bidders[i], HighestBid, auctionItem);
                    return;
                }
                bool conditionOppotTrader = ((bidders[i]->cash > HighestBid + 250) && (HighestBid < 4000)); // to be implemented
                if (conditionOppotTrader) {
                    opportTraderHighestBid = HighestBid + 250;
                    HighestBid = opportTraderHighestBid;
                    HighestBidder = bidders[i];
                }
                break;
            default:
                break;
            }
        }
        if (HighestBidder == player_x) {
            // sell to the bank at mortgage price

            player_x->cash += auctionItem->mortgageValue;
            auctionItem->owner = NULL;
            player_x->noOfProperties--;
            printf("No one bought item in the auction.\n");
            printf("Sold to the bank for LKR %d\n\n", auctionItem->mortgageValue);
            printf("============================================================\n\n");
            return;
        }
    }
};
bool payRent(player *player_x, square *board) {

    // player pays rent
    if (player_x->cash < board[player_x->currentSquare].PropertyProperties.currentRentalofProperty) {
        return false;
    }

    player_x->cash =
        player_x->cash -
        board[player_x->currentSquare]
            .PropertyProperties.currentRentalofProperty;

    // owner gets paid

    board[player_x->currentSquare].owner->cash =
        board[player_x->currentSquare].owner->cash +
        board[player_x->currentSquare]
            .PropertyProperties.currentRentalofProperty;

    printf("%s payed %d to %s as the rent of %s\n", player_x->name,
           board[player_x->currentSquare]
               .PropertyProperties.currentRentalofProperty,
           board[player_x->currentSquare].owner->name,
           board[player_x->currentSquare].name);

    return true;
}
void bankruptCheck(playerPointers *playerObject, int *noOfBankruptPlayers) {
    *noOfBankruptPlayers = 0;
    player *players[4] = {playerObject->player_1, playerObject->player_2, playerObject->player_3, playerObject->player_4};
    *noOfBankruptPlayers = 0;
    for (int i = 0; i <= 3; i++) {
        if (players[i]->netWorth <= 0) {
            if (!players[i]->isBankrupt) {
                printf("\n%s went Bankrupt\n", players[i]->name);
            }
            players[i]->isBankrupt = true;
        }
        if (players[i]->isBankrupt) {
            (*noOfBankruptPlayers)++;
        }
    }
}
