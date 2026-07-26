#include "types.h"
void move(player *player_x, square *board) {
    int steps = dice_roller();
    int tempCurrentSquare = player_x->currentSquare;

    printf("%s rolls %d.\n", player_x->name, steps);

    player_x->currentSquare = (player_x->currentSquare + steps) % 39;
    player_x->totalsteps = player_x->totalsteps + steps;

    printf("%s moves from Square %d to Square %d\n", player_x->name,
           tempCurrentSquare, board[player_x->currentSquare].squareID);
}
