#include "types.h"
#include <stdbool.h>

void AggrNoCashAuction(square *board, player *player_x, playerPointers *playerObject, context *contextOfTheGame) {
    do {
        if (player_x->noOfProperties == 0) {
            player_x->isBankrupt = true;
            return;
        }

        networthEvaluate(playerObject->player_1,
                         playerObject->player_2,
                         playerObject->player_3,
                         playerObject->player_4,
                         board);
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == brown && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == lightBlue && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == pink && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == orange && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == red && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == yellow && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == green && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].PropertyProperties.propertyGroup == darkBlue && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                bool payed = payRent(player_x, board);
                if (payed == true) {
                    return;
                }
            }
        }
    }

    while (player_x->netWorth >
           board[player_x->currentSquare].PropertyProperties.currentRentalofProperty);

    player_x->isBankrupt = true;
}
