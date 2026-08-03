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
void resolveBank(player *player_x, square *board) {

    playerType tempPlayer = player_x->playerID;

    // taking loans
    if (player_x->hasDebt == false) {
        switch (tempPlayer) {

        case aggresiveInvester:
            break;
        case conservativeBanker:
            break;
        case riskTaker:
            player_x->hasDebt = true;
            player_x->cash += player_x->MaxElegibleLoanAmount;
            printf("%s borrowed a loan of LKR %d from the Bank of Ceylon\n", player_x->name, player_x->MaxElegibleLoanAmount);
            break;
        case opportunisticTrader:
            break;
        default:
            break;
        }
    } else {
        // paying loans
    }
}
