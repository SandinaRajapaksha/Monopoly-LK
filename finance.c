#include "types.h"
#include <stdbool.h>
#include <stdio.h>

void networthEvaluate(player *player_1, player *player_2, player *player_3, player *player_4, square *board) {
    player *players[4] = {player_1, player_2, player_3, player_4};

    for (int i = 0; i <= 3; i++) {
        int totalPropertyValuesofPlayer = 0;

        int totalMortgageValuesofPlayer = 0;
        for (int j = 0; j <= 39; j++) {
            if (board[j].type == property && board[j].owner == players[i]) {
                totalPropertyValuesofPlayer += board[j].curruntValue;
                totalMortgageValuesofPlayer += board[j].mortgageValue;
            }
        }

        players[i]->netWorth = players[i]->cash + totalPropertyValuesofPlayer;
        players[i]->MaxElegibleLoanAmount = totalMortgageValuesofPlayer * 0.75;

        totalMortgageValuesofPlayer = 0;
        totalPropertyValuesofPlayer = 0;
    }
}
void resolveBank(player *player_x, square *board, economicEventCardType *currentEconEvent) {

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
            if (*currentEconEvent == GovernmentHousingProgramme || *currentEconEvent == StockMarketBoom) {
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
        switch (tempPlayer) {

            if ((player_x->laps - player_x->loantakigLap > 20) && (player_x->hasDebt == true)) {

                // properties transfer to bank and auctiones
            }
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
