#include "types.h"
#include <stdbool.h>
#include <stdio.h>

diceRollType dice_roller() {
    int roll1 = (rand() % 6) + 1;
    int roll2 = (rand() % 6) + 1;

    diceRollType roll;

    if (roll1 == roll2) {
        roll.doublesRolled = true;
    } else {
        roll.doublesRolled = false;
    }
    roll.rollValue = roll1 + roll2;
    return roll;
}

void ranker(player *player1, player *player2, player *player3,
            player *player4) {

    player *players[4] = {player1, player2, player3, player4};
    for (int i = 0; i < 4; i++) {
        players[i]->diceRoll = dice_roller().rollValue;
        printf("%s rolls %d\n", players[i]->name, players[i]->diceRoll);
    }

    // sort dice values of players
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (players[j + 1]->diceRoll < players[j]->diceRoll) {

                // sort the array
                player *tempPointer = players[j];
                players[j] = players[j + 1];
                players[j + 1] = tempPointer;
            }
        }
    }
    // dupicate resolve --

    for (int i = 0; i < 4;) {
        int j = i;
        while (j + 1 < 4 && players[j + 1]->diceRoll == players[i]->diceRoll) {
            j++;
        }
        if (j > i) {
            // group
            int distinct;
            do {
                distinct = 1;
                for (int a = i; a <= j; a++) {
                    players[a]->diceRoll = dice_roller().rollValue;
                    printf("reroll (tie) %s: %d\n", players[a]->name,
                           players[a]->diceRoll);
                }
                for (int a = i; a <= j && distinct; a++) {
                    for (int b = a + 1; b <= j; b++) {
                        if (players[a]->diceRoll == players[b]->diceRoll) {
                            distinct = 0;
                            break;
                        }
                    }
                }
            } while (!distinct);
            for (int a = i; a < j; a++) {
                for (int b = i; b < j - (a - i); b++) {
                    if (players[b + 1]->diceRoll < players[b]->diceRoll) {
                        player *tempPointer = players[b];
                        players[b] = players[b + 1];
                        players[b + 1] = tempPointer;
                    }
                }
            }
        }
        i = j + 1;
    }
    //--

    // asign ranks
    for (int i = 0; i < 4; i++) {
        players[i]->rank = i + 1;
    }
}

// final player ranker

void finalRankAssign(player *player_X, player *player_1, player *player_2,
                     player *player_3, player *player_4) {

    if (player_X->rank == 1) {
        *player_1 = *player_X;
    }
    if (player_X->rank == 2) {
        *player_2 = *player_X;
    }
    if (player_X->rank == 3) {
        *player_3 = *player_X;
    }
    if (player_X->rank == 4) {
        *player_4 = *player_X;
    }
}

void roundCounter(int *curruntBoardRound, player *player_1, player *player_2,
                  player *player_3, player *player_4) {
    bool Equalitycheck =
        (player_1->totalsteps / 39) && (player_2->totalsteps / 39) &&
        (player_3->totalsteps / 39) && (player_4->totalsteps / 39);

    int tempCurrentRound = *curruntBoardRound;
    if (Equalitycheck == true) {
        *curruntBoardRound = (player_1->totalsteps / 39) + 1;
        if (*curruntBoardRound != tempCurrentRound) {

            printf("==================================================================\n Round %d Summary \n", tempCurrentRound);
            printf("==================================================================\n\n");
            printf("%s\n\n", player_1->name);
            printf("Cash : %d \n\n", player_1->cash);
            printf("Networth : %d \n\n", player_1->netWorth);
            printf("Properties : %d \n\n", player_1->noOfProperties);
            printf("Hotels : %d \n\n", player_1->noOfHotelsOwned);
            printf("Outstanding Loan : %d \n\n", player_1->outStandingLoan);
            printf("------------------------------------------------------------------\n\n");
            printf("%s\n\n", player_2->name);
            printf("Cash : %d \n\n", player_2->cash);
            printf("Networth : %d \n\n", player_2->netWorth);
            printf("Properties : %d \n\n", player_2->noOfProperties);
            printf("Hotels : %d \n\n", player_2->noOfHotelsOwned);
            printf("Outstanding Loan : %d \n\n", player_2->outStandingLoan);
            printf("------------------------------------------------------------------\n\n");
            printf("%s\n\n", player_3->name);
            printf("Cash : %d \n\n", player_3->cash);
            printf("Networth : %d \n\n", player_3->netWorth);
            printf("Properties : %d \n\n", player_3->noOfProperties);
            printf("Hotels : %d \n\n", player_3->noOfHotelsOwned);
            printf("Outstanding Loan : %d \n\n", player_3->outStandingLoan);
            printf("------------------------------------------------------------------\n\n");
            printf("%s\n\n", player_4->name);
            printf("Cash : %d \n\n", player_4->cash);
            printf("Networth : %d \n\n", player_4->netWorth);
            printf("Properties : %d \n\n", player_4->noOfProperties);
            printf("Hotels : %d \n\n", player_4->noOfHotelsOwned);
            printf("Outstanding Loan : %d \n\n", player_4->outStandingLoan);
            printf("------------------------------------------------------------------\n\n");
        }
    }
}
