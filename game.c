#include "types.h"

void startGame(void) {
    //
    int topNationalEventCard = 0;
    int topreigionaldevelopmentcard = 0;
    square board[40];

    player RiskTaker = {riskTaker};
    player AggressiveInvester = {aggresiveInvester};
    player ConservativeBanker = {conservativeBanker};
    player OpportunisticTrader = {opportunisticTrader};

    // order of players
    player player_1;
    player player_2;
    player player_3;
    player player_4;

    initializeTurnOrder(&RiskTaker, &AggressiveInvester, &ConservativeBanker,
                        &OpportunisticTrader, &player_1, &player_2, &player_3,
                        &player_4);

    initializeBoard(board);
}
