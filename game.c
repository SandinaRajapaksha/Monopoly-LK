#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#define INITIAL_PRICE 30000

void startGame(void) {
    //

    // event counters

    context contextOfTheGame;
    contextOfTheGame.currentActiveEconEvent = -1;
    contextOfTheGame.roundThatEconEventHappened = -1;

    contextOfTheGame.roundThatInflationHappened = -1;
    contextOfTheGame.currentInflation = 0;
    contextOfTheGame.currentInterestRate = INITIAL_INTEREST_RATE;
    contextOfTheGame.currentTaxRate = INITIAL_TAX_RATE;
    contextOfTheGame.rounfThatDisasterHappend = -1;
    contextOfTheGame.currentDisaster = -1;
    contextOfTheGame.topNationalEventCard = 0;
    contextOfTheGame.topRegionalDevelopmentCard = 0;
    contextOfTheGame.roundThatRegionalDevelopmentHappened = -1;
    contextOfTheGame.roundThatDynamicPropertyEventHappened = -1;
    contextOfTheGame.dynamicEventRoundsRemaining = 0;
    contextOfTheGame.dynamicBoomGroup = (groupType)-1;
    contextOfTheGame.dynamicDeclineGroup = (groupType)-1;
    contextOfTheGame.lastDynamicBoomGroup = (groupType)-1;
    contextOfTheGame.lastDynamicDeclineGroup = (groupType)-1;
    contextOfTheGame.currentActiveGovRegulation = (govRegulationsType)-1;
    contextOfTheGame.govRegulationRoundsRemaining = 0;
    contextOfTheGame.roundThatGovRegulationHappened = -1;
    contextOfTheGame.currentBoardRound = 1;

    int noOfBankruptPlayer = 0;
    square board[40];

    srand((unsigned int)time(NULL));

    player aggressiveInvesterPlayer = {.playerID = aggresiveInvester,
                                       .name = "Aggressive Invester",
                                       .currentSquare = 1,
                                       .cash = INITIAL_PRICE,
                                       .Jail = outside,
                                       .hasDebt = false,
                                       .isBankrupt = false};
    player conservativeBankerPlayer = {.playerID = conservativeBanker,
                                       .name = "Conservative Banker",
                                       .currentSquare = 1,
                                       .cash = INITIAL_PRICE,
                                       .Jail = outside,
                                       .hasDebt = false,
                                       .isBankrupt = false};
    player riskTakerPlayer = {.playerID = riskTaker,
                              .name = "Risk Taker",
                              .currentSquare = 1,
                              .cash = INITIAL_PRICE,
                              .Jail = outside,
                              .hasDebt = false,
                              .isBankrupt = false};
    player opportunisticTraderPlayer = {.playerID = opportunisticTrader,
                                        .name = "Oppotunistic Trader",
                                        .currentSquare = 1,
                                        .cash = INITIAL_PRICE,
                                        .Jail = outside,
                                        .hasDebt = false,
                                        .isBankrupt = false};

    player bankOfCeylonInstitution = {.playerID = bankOfCeylon,
                                      .name = "Bank of Ceylon"};

    player player_1;
    player player_2;
    player player_3;
    player player_4;
    player playerBANK = bankOfCeylonInstitution;

    playerPointers playerPointerObject = {
        .player_1 = &player_1,
        .player_2 = &player_2,
        .player_3 = &player_3,
        .player_4 = &player_4,
        .player_BANK = &playerBANK};

    printf("MONOPOLY-LK Simulation\n\n");
    printf("Player 1 : %s\n", aggressiveInvesterPlayer.name);
    printf("Player 2 : %s\n", conservativeBankerPlayer.name);
    printf("Player 3 : %s\n", riskTakerPlayer.name);
    printf("Player 4 : %s\n\n", opportunisticTraderPlayer.name);

    printf("Each player begins with LKR %d.\n\n", INITIAL_PRICE);

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

    initializeBoard(board, &playerPointerObject);

    printf("%s will begin the game.\n\n", player_1.name);
    printf("Turn order : \n");
    printf("%s\n", player_1.name);
    printf("%s\n", player_2.name);
    printf("%s\n", player_3.name);
    printf("%s\n\n", player_4.name);

    // main game loop
    while (true) {
        if (contextOfTheGame.currentBoardRound > 500) {
            break;
        }
        printf("\nCurrunt round is : %d \n\n", contextOfTheGame.currentBoardRound);
        if (player_1.isBankrupt == false) {

            move(&player_1, board, &contextOfTheGame, &playerPointerObject);
            networthEvaluate(&player_1, &player_2, &player_3, &player_4, board);
            bankruptCheck(&playerPointerObject, &noOfBankruptPlayer);
            if (noOfBankruptPlayer == 3) {
                break;
            }
        }
        if (player_2.isBankrupt == false) {

            move(&player_2, board, &contextOfTheGame, &playerPointerObject);
            networthEvaluate(&player_1, &player_2, &player_3, &player_4, board);
            bankruptCheck(&playerPointerObject, &noOfBankruptPlayer);
            if (noOfBankruptPlayer == 3) {
                break;
            }
        }
        if (player_3.isBankrupt == false) {

            move(&player_3, board, &contextOfTheGame, &playerPointerObject);
            networthEvaluate(&player_1, &player_2, &player_3, &player_4, board);
            bankruptCheck(&playerPointerObject, &noOfBankruptPlayer);
            if (noOfBankruptPlayer == 3) {
                break;
            }
        }
        if (player_4.isBankrupt == false) {

            move(&player_4, board, &contextOfTheGame, &playerPointerObject);
            networthEvaluate(&player_1, &player_2, &player_3, &player_4, board);
            bankruptCheck(&playerPointerObject, &noOfBankruptPlayer);
            if (noOfBankruptPlayer == 3) {
                break;
            }
        }

        networthEvaluate(&player_1, &player_2, &player_3, &player_4, board);

        bankruptCheck(&playerPointerObject, &noOfBankruptPlayer);
        if (noOfBankruptPlayer == 3) {
            break;
        }
        int previousRound = contextOfTheGame.currentBoardRound;
        roundCounter(&contextOfTheGame, &player_1, &player_2, &player_3,
                     &player_4);

        // round-based effects tick only when a new round actually starts
        if (contextOfTheGame.currentBoardRound != previousRound) {
            decayRegionalDevelopmentEffects(&contextOfTheGame, board);
            decayDynamicPropertyEffects(&contextOfTheGame, board);
            decayGovRegulationEffects(&contextOfTheGame, board);
        }

        // trigger events after a set number of rounds
        if ((contextOfTheGame.currentBoardRound % 15 == 0) &&
            (contextOfTheGame.currentBoardRound != contextOfTheGame.roundThatEconEventHappened)) {
            econEventActivate(board, &contextOfTheGame);
        }

        if ((contextOfTheGame.currentBoardRound % 10 == 0) &&
            (contextOfTheGame.currentBoardRound != contextOfTheGame.roundThatInflationHappened)) {
            inflationRateRelease(board, &contextOfTheGame);
        }

        if ((contextOfTheGame.currentBoardRound % 10 == 0) &&
            (contextOfTheGame.currentBoardRound != contextOfTheGame.rounfThatDisasterHappend)) {
            disasterAcitivate(board, &contextOfTheGame);
        }

        if ((contextOfTheGame.currentBoardRound % 15 == 0) &&
            (contextOfTheGame.currentBoardRound != contextOfTheGame.roundThatRegionalDevelopmentHappened)) {
            regionalDevelopmentActivate(board, &contextOfTheGame, &playerPointerObject);
        }

        if ((contextOfTheGame.currentBoardRound % 10 == 0) &&
            (contextOfTheGame.currentBoardRound != contextOfTheGame.roundThatDynamicPropertyEventHappened)) {
            dynamicPropertyEventActivate(board, &contextOfTheGame);
        }

        if ((contextOfTheGame.currentBoardRound % 15 == 0) &&
            (contextOfTheGame.currentBoardRound != contextOfTheGame.roundThatGovRegulationHappened)) {
            govRegulationsActivate(board, &contextOfTheGame, &playerPointerObject);
        }
    }

    player *players[4] = {&player_1, &player_2, &player_3, &player_4};
    player *winner = NULL;

    if (noOfBankruptPlayer == 3) {
        for (int i = 0; i < 4; i++) {
            if (!players[i]->isBankrupt) {
                winner = players[i];
                break;
            }
        }
    } else {
        int maxNetWorth = -1;
        for (int i = 0; i < 4; i++) {
            if (players[i]->netWorth > maxNetWorth) {
                maxNetWorth = players[i]->netWorth;
                winner = players[i];
            }
        }
    }

    if (winner) {
        printf("\n\n\n\n====================================================================\n");
        printf("\nWinner: %s with net worth LKR %d\n", winner->name, winner->netWorth);
        printf("\n====================================================================\n");
    }
}
