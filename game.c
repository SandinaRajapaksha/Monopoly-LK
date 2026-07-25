#include "types.h"
#include <stdbool.h>

void startGame(void) {
    //
    int topNationalEventCard = 0;
    int topreigionaldevelopmentcard = 0;
    square board[40];

    srand((unsigned int)time(NULL));
    player aggressiveInvesterPlayer = {1001, .name = "Aggressive Invester",
                                       .currentSquare = 1};
    player conservativeBankerPlayer = {1002, .name = "Conservative Banker",
                                       .currentSquare = 1};
    player riskTakerPlayer = {1003, .name = "Risk Taker", .currentSquare = 1};
    player opportunisticTraderPlayer = {1004, .name = "Oppotunistic Trader",
                                        .currentSquare = 1};

    player player_1;
    player player_2;
    player player_3;
    player player_4;

    ranker(&aggressiveInvesterPlayer, &conservativeBankerPlayer,
           &riskTakerPlayer, &opportunisticTraderPlayer);

    finalRankAssign(&aggressiveInvesterPlayer, &player_1, &player_2, &player_3,
                    &player_4);
    finalRankAssign(&conservativeBankerPlayer, &player_1, &player_2, &player_3,
                    &player_4);
    finalRankAssign(&riskTakerPlayer, &player_1, &player_2, &player_3,
                    &player_4);
    finalRankAssign(&opportunisticTraderPlayer, &player_1, &player_2, &player_3,
                    &player_4);

    initializeBoard(board);

    // main game loop
    int i = 0;
    while (true) {
        move(&player_1, board);
        move(&player_2, board);
        move(&player_3, board);
        move(&player_4, board);
        i++;
        if (i == 500) {
            break;
        }
    }
}
