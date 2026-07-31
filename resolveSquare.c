#include "types.h"
#include <stdio.h>
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

void resolveGO(player *player_x) {

    player_x->cash = player_x->cash + 2000;
    printf("%s recieved LKR 2000 by landing on GO ...\n", player_x->name);
}
void resolveSpecial(player *player_x, square *board) {

    specialityType specialityOfSquare =
        board[player_x->currentSquare].specialityProperties.specililtyOfSquare;

    switch (specialityOfSquare) {
    case gotoJail:
        player_x->currentSquare = 10; // jail square
        player_x->Jail = inside;
        printf("%s got inside the jail ...\n", player_x->name);
        break;
    default:
        break;
    }
}

void resolveRailway(player *player_x, square *board) {}
void resolveUtility(player *player_x, square *board) {}
void resolveEvent(player *player_x, square *board) {}
void resolveInsure(player *player_x, square *board) {}
void resolveTax(player *player_x, square *board) {}
void resolveBank(player *player_x, square *board) {}
void resolveProperty(player *player_x, square *board) {}
