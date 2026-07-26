#include "types.h"
void move(player *player_x, square *board) {
    int steps = dice_roller();
    printf("%s rolled %d\n", player_x->name, steps);
    player_x->currentSquare = (player_x->currentSquare + steps) % 39;
    player_x->totalsteps = player_x->totalsteps + steps;
    printf("%s moved to square %d : %s\n", player_x->name,
           board[player_x->currentSquare].squareID,
           board[player_x->currentSquare].name);
}
