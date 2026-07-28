#include "types.h"
void resolveSquare(player *player_x, square *board) {
    squareType squareToResolve = board[player_x->currentSquare].type;
    switch (squareToResolve) {
    case go:
        resolveGO(player_x);
        break;
    case special:
        resolveSpecial(player_x, board);
        break;
    case railway:
        resolveRailway(player_x, board);
        break;
    case utility:
        resolveUtility(player_x, board);
        break;
    case event:
        resolveEvent(player_x, board);
        break;
    case insure:
        resolveInsure(player_x, board);
        break;
    case tax:
        resolveTax(player_x, board);
        break;
    case bank:
        resolveBank(player_x, board);
        break;
    case property:
        resolveProperty(player_x, board);
        break;
    }
}

void resolveGO(player *player_x) { player_x->cash = player_x->cash + 2000; }
