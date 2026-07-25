#include "types.h"
void move(player *player_x, square *board) {
    int steps = dice_roller();
    player_x->currentSquare = (player_x->currentSquare + steps) % 39;
    printf("%s moved to square %d : %s\n", player_x->name,
           board[player_x->currentSquare].squareID,
           board[player_x->currentSquare].name);
}
