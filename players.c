#include "types.h"
#include <stdbool.h>

bool OpportTraderBuyCondition(int incomePerLanding, int price, int currentLoanInterestRate) {
    double expectedLandings = 1.5; // 3 opponents x 20 rounds x 1/40

    if (price <= 0) {
        return false;
    }

    double projectedIncome = incomePerLanding * expectedLandings;
    double roi20 = (projectedIncome / price) * 100.0;

    return roi20 > (double)currentLoanInterestRate;
}

void AggrNoCashAuction(square *board, player *player_x, playerPointers *playerObject, context *contextOfTheGame) {
    square *currentSquare = &board[player_x->currentSquare];
    int owedRent = 0;

    if (currentSquare->type == property) {
        owedRent = currentSquare->PropertyProperties.currentRentalofProperty;
    } else if (currentSquare->type == railway) {
        int n = currentSquare->owner->noOfRailways;
        if (n == 1)
            owedRent = currentSquare->railwayProperties.baseRentOfRailway;
        else if (n == 2)
            owedRent = currentSquare->railwayProperties.baseRentOfRailway_2_owned;
        else if (n == 3)
            owedRent = currentSquare->railwayProperties.baseRentOfRailway_3_owned;
        else if (n == 4)
            owedRent = currentSquare->railwayProperties.baseRentOfRailway_4_owned;
    } else if (currentSquare->type == utility) {
        owedRent = currentSquare->utilityProperties.currentUtilityRent;
    }

    do {

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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
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
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].type == railway && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
                    return;
                }
            }
        }
        for (int i = 0; i <= 39; i++) {
            if (board[i].type == utility && board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board, contextOfTheGame, &board[i]);
                if (player_x->cash >= owedRent) {
                    player_x->cash -= owedRent;
                    currentSquare->owner->cash += owedRent;
                    printf("%s payed LKR %d to %s as the rent of %s\n", player_x->name, owedRent, currentSquare->owner->name, currentSquare->name);
                    return;
                }
            }
        }
    }

    while (!player_x->isBankrupt && player_x->cash < owedRent &&
           (player_x->noOfProperties > 0 || player_x->noOfRailways > 0 || player_x->noOfUtilities > 0));

    if (player_x->cash < owedRent) {
        printf("\nplayer %s got bankrupt\n", player_x->name);
        player_x->isBankrupt = true;
    }
}

// railway buy behavour
bool aggrRailwayBuyCondition(player *player_x, square *board) {

    if (player_x->cash - board[player_x->currentSquare].curruntValue >= 2000) {
        return true;
    } else {
        return false;
    }
}

bool riskTkrRailwayBuyCondition(player *player_x, square *board) {

    if (player_x->cash >= board[player_x->currentSquare].curruntValue) {
        return true;
    } else {
        return false;
    }
}

bool opprtTrdrRailwayBuyCondition(player *player_x, square *board, context *contextOfTheGame) {

    if (player_x->cash >= board[player_x->currentSquare].curruntValue && contextOfTheGame->currentActiveEconEvent != EconomicRecession) {
        return true;
    } else {
        return false;
    }
}
bool consBankerRailwayBuyCondition(player *player_x, square *board) {

    if (player_x->cash - board[player_x->currentSquare].curruntValue >= player_x->cash * 0.3) {
        return true;
    } else {
        return false;
    }
}
