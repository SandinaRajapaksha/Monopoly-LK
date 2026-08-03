#include "types.h"
#include <stdbool.h>
#include <stdio.h>

void startGame(void) {
    //

    // event counters

    economicEventCardType curruntActiveEconEvent = -1;
    int roundThatEconEventHappened = -1;

    int roundThatInflationHappened = -1;
    int curruntInflation = 0;

    int topNationalEventCard = 0;
    int topreigionaldevelopmentcard = 0;
    int curruntBoardRound = 1;
    square board[40];

    srand((unsigned int)time(NULL));
    player aggressiveInvesterPlayer = {.playerID = aggresiveInvester,
                                       .name = "Aggressive Invester",
                                       .currentSquare = 1,
                                       .cash = 30000,
                                       .Jail = outside,
                                       .hasDebt = false,
                                       .isBankrupt = false};
    player conservativeBankerPlayer = {.playerID = conservativeBanker,
                                       .name = "Conservative Banker",
                                       .currentSquare = 1,
                                       .cash = 30000,
                                       .Jail = outside,
                                       .hasDebt = false,
                                       .isBankrupt = false};
    player riskTakerPlayer = {.playerID = riskTaker,
                              .name = "Risk Taker",
                              .currentSquare = 1,
                              .cash = 30000,
                              .Jail = outside,
                              .hasDebt = false,
                              .isBankrupt = false};
    player opportunisticTraderPlayer = {.playerID = opportunisticTrader,
                                        .name = "Oppotunistic Trader",
                                        .currentSquare = 1,
                                        .cash = 30000,
                                        .Jail = outside,
                                        .hasDebt = false,
                                        .isBankrupt = false};

    player player_1;
    player player_2;
    player player_3;
    player player_4;

    printf("MONOPOLY-LK Simulation\n\n");
    printf("Player 1 : %s\n", aggressiveInvesterPlayer.name);
    printf("Player 2 : %s\n", conservativeBankerPlayer.name);
    printf("Player 3 : %s\n", riskTakerPlayer.name);
    printf("Player 4 : %s\n\n", opportunisticTraderPlayer.name);

    printf("Each player begins with LKR 30,000.\n\n");

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

    printf("%s will begin the game.\n\n", player_1.name);
    printf("Turn order : \n");
    printf("%s\n", player_1.name);
    printf("%s\n", player_2.name);
    printf("%s\n", player_3.name);
    printf("%s\n\n", player_4.name);

    // main game loop
    while (true) {
        if (curruntBoardRound > 500) {
            break;
        }
        printf("\nCurrunt round is : %d \n\n", curruntBoardRound);
        if (player_1.isBankrupt == false) {

            move(&player_1, board, &curruntActiveEconEvent, &curruntInflation);
        }
        if (player_2.isBankrupt == false) {

            move(&player_2, board, &curruntActiveEconEvent, &curruntInflation);
        }
        if (player_3.isBankrupt == false) {

            move(&player_3, board, &curruntActiveEconEvent, &curruntInflation);
        }
        if (player_4.isBankrupt == false) {

            move(&player_4, board, &curruntActiveEconEvent, &curruntInflation);
        }

        networthEvaluate(&player_1, &player_2, &player_3, &player_4, board);

        roundCounter(&curruntBoardRound, &player_1, &player_2, &player_3,
                     &player_4);

        // trigger events after a set number of rounds
        if ((curruntBoardRound % 15 == 0) &&
            (curruntBoardRound != roundThatEconEventHappened)) {
            econEventActivate(board, &roundThatEconEventHappened,
                              &curruntActiveEconEvent, &curruntBoardRound);
        }

        if ((curruntBoardRound % 10 == 0) &&
            (curruntBoardRound != roundThatInflationHappened)) {
            inflationRateRelease(board, &curruntBoardRound,
                                 &roundThatInflationHappened,
                                 &curruntInflation);
            // print markket conditions
            printMarketConditions(&curruntInflation, &curruntActiveEconEvent, &curruntBoardRound);
        }
    }
}
