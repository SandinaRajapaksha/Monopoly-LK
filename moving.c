#include "types.h"
#include <stdbool.h>
#include <stdio.h>
void move(player *player_x, square *board, context *contextOfTheGame, playerPointers *playerObject) {

    processInsurancePayments(player_x, board, contextOfTheGame);

    diceRollType steps = dice_roller();
    player_x->diceRoll = steps.rollValue;
    int tempCurrentSquare = player_x->currentSquare;
    if (player_x->Jail == inside) {

        player_x->jailRoundCounter++;
        jailLogic(player_x, steps.doublesRolled);
        return;
    }

    printf("%s rolls %d.\n", player_x->name, steps.rollValue);

    player_x->currentSquare = (player_x->currentSquare + steps.rollValue) % 40;
    player_x->totalsteps = player_x->totalsteps + steps.rollValue;

    printf("%s moves from Square %d to Square %d\n", player_x->name,
           tempCurrentSquare, board[player_x->currentSquare].squareID);
    resolveSquare(player_x, board, contextOfTheGame, playerObject);

    // never end a move with negative cash
    // auction assets or declare bankruptcy
    if (player_x->cash < 0 && !player_x->isBankrupt) {
        for (int i = 0; i <= 39 && player_x->cash < 0 && !player_x->isBankrupt; i++) {
            if (board[i].owner == player_x) {
                sellingAuction(player_x, playerObject->player_1,
                               playerObject->player_2,
                               playerObject->player_3,
                               playerObject->player_4, board,
                               contextOfTheGame, &board[i],
                               playerObject->player_BANK);
            }
        }
        if (player_x->cash < 0) {
            printf("\n%s went bankrupt\n", player_x->name);
            player_x->isBankrupt = true;
        }
    }

    // did he pass go

    if ((player_x->currentSquare != 10) && (player_x->currentSquare != 0) &&
        (player_x->currentSquare < tempCurrentSquare) && (player_x->hasDebt == false) && (player_x->isBankrupt == false)) {
        player_x->cash = player_x->cash + 2000;
        printf("%s received LKR 2000 by passing GO ...\n", player_x->name);
    }

    player_x->laps = player_x->totalsteps / 40;
}
