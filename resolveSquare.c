#include "types.h"
#include <stdio.h>
void resolveSquare(player *player_x, square *board,
                   economicEventCardType *currentEconEvent) {
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
        resolveProperty(player_x, board, currentEconEvent);
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

void resolveProperty(player *player_x, square *board,
                     economicEventCardType *currentEconEvent) {

    // if property owns by bank
    if (board[player_x->currentSquare].owner->playerID == bankOfCeylon) {
        playerType currentPlayer = player_x->playerID;

        switch (currentPlayer) {
        case aggresiveInvester:

            if ((player_x->cash >
                 (1000 + board[player_x->currentSquare]
                             .PropertyProperties.initialPrice)) &&
                (board[player_x->currentSquare].owner->playerID !=
                 aggresiveInvester)) {

                player_x->cash =
                    player_x->cash - board[player_x->currentSquare]
                                         .PropertyProperties.initialPrice;
                board[player_x->currentSquare].owner = player_x;
                printf("%s buys %s\n", player_x->name,
                       board[player_x->currentSquare].name);
            }
            break;

        case conservativeBanker:

            if ((player_x->cash - (board[player_x->currentSquare]
                                       .PropertyProperties.initialPrice) >
                 (player_x->cash / 2)) &&
                (*currentEconEvent != EconomicRecession) &&
                ((board[player_x->currentSquare].owner->playerID !=
                  conservativeBanker))) {

                player_x->cash =
                    player_x->cash - board[player_x->currentSquare]
                                         .PropertyProperties.initialPrice;
                board[player_x->currentSquare].owner = player_x;
                printf("%s buys %s\n", player_x->name,
                       board[player_x->currentSquare].name);
            } else {
                // auction logic to be implemented
            }
            break;
        default:
            break;
            // if property isnt owned yet
        }
    }
    // if property owned by another player
    else if (board[player_x->currentSquare].owner->playerID !=
             player_x->playerID) {

        playerType currentPlayer = player_x->playerID;
        switch (currentPlayer) {
        case aggresiveInvester:

            if ((player_x->cash >
                 board[player_x->currentSquare]
                     .PropertyProperties.currentRentalofProperty) &&
                (board[player_x->currentSquare].mortgageStatus !=
                 mortgagedToBank)) {

                // player pays rent

                player_x->cash =
                    player_x->cash -
                    board[player_x->currentSquare]
                        .PropertyProperties.currentRentalofProperty;

                // owner gets paid

                board[player_x->currentSquare].owner->cash =
                    board[player_x->currentSquare].owner->cash +
                    board[player_x->currentSquare]
                        .PropertyProperties.currentRentalofProperty;

                printf("%s payed %d to %s as the rent of %s\n", player_x->name,
                       board[player_x->currentSquare]
                           .PropertyProperties.currentRentalofProperty,
                       board[player_x->currentSquare].owner->name,
                       board[player_x->currentSquare].name);

            } else {
                //      loan logic to be implemented
                break;

            case conservativeBanker:

                if ((player_x->cash >
                     board[player_x->currentSquare]
                         .PropertyProperties.currentRentalofProperty) &&
                    (board[player_x->currentSquare].mortgageStatus !=
                     mortgagedToBank)) {

                    // player pays rent

                    player_x->cash =
                        player_x->cash -
                        board[player_x->currentSquare]
                            .PropertyProperties.currentRentalofProperty;

                    // owner gets paid

                    board[player_x->currentSquare].owner->cash =
                        board[player_x->currentSquare].owner->cash +
                        board[player_x->currentSquare]
                            .PropertyProperties.currentRentalofProperty;

                    printf("%s payed %d to %s as the rent of %s\n",
                           player_x->name,
                           board[player_x->currentSquare]
                               .PropertyProperties.currentRentalofProperty,
                           board[player_x->currentSquare].owner->name,
                           board[player_x->currentSquare].name);
                } else {
                    // loan logic for rent payment to be implemented
                }

            default:
                break;
            }
        }
    }
}
