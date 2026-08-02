#include "types.h"

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
