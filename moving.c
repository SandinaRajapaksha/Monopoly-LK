#include "types.h"
#include <stdio.h>
void move(player *player_x, square *board,
          economicEventCardType *currentEconEvent) {

    diceRollType steps = dice_roller();
    int tempCurrentSquare = player_x->currentSquare;
    if (player_x->Jail == inside) {

        player_x->jailRoundCounter++;
        jailLogic(player_x, steps.doublesRolled);
        return;
    }

    printf("%s rolls %d.\n", player_x->name, steps.rollValue);

    player_x->currentSquare = (player_x->currentSquare + steps.rollValue) % 39;
    player_x->totalsteps = player_x->totalsteps + steps.rollValue;

    printf("%s moves from Square %d to Square %d\n", player_x->name,
           tempCurrentSquare, board[player_x->currentSquare].squareID);
    resolveSquare(player_x, board, currentEconEvent);
    // passed go check

    if ((player_x->currentSquare != 10) && (player_x->currentSquare != 0) &&
        (player_x->currentSquare < tempCurrentSquare)) {
        player_x->cash = player_x->cash + 2000;
        printf("%s received 2000 by passing GO ...\n", player_x->name);
    }
}
