#include "types.h"

int diceRoll() {

    srand(time(NULL));
    return rand() % (12 - 2 + 1) + 2;
}
//
// void twoPlayeRollEqualResolve(player *plyrA , player *plyrB){
//
// }
void initializeTurnOrder(player *aggr, player *risktkr, player *investbnkr,
                         player *opporttrdr, player *player1, player *player2,
                         player *player3, player *player4) {

    int aggrTurn[100];
    for (int i = 0; i < 99; i++) {
        aggrTurn[i] = diceRoll();
    }

    int risktktTurn[100];
    for (int i = 0; i < 99; i++) {
        risktktTurn[i] = diceRoll();
    }

    int investbnkrTurn[100];
    for (int i = 0; i < 99; i++) {
        risktktTurn[i] = diceRoll();
    }

    int opporttrdrTurn[100];
    for (int i = 0; i < 99; i++) {
        risktktTurn[i] = diceRoll();
    }

    // same roll checker
    int aggr_risk_pivot = 0;
    while (aggrTurn[aggr_risk_pivot] == risktktTurn[aggr_risk_pivot]) {
        aggr_risk_pivot++;
    }

    int aggr_invest_pivot = 0;
    while (aggrTurn[aggr_invest_pivot] == investbnkrTurn[aggr_invest_pivot]) {
        aggr_invest_pivot++;
    }

    int aggr_opport_pivot = 0;
    while (aggrTurn[aggr_opport_pivot] == opporttrdrTurn[aggr_opport_pivot]) {
        aggr_opport_pivot++;
    }

    int risk_invest_pivot = 0;
    while (risktktTurn[risk_invest_pivot] ==
           investbnkrTurn[risk_invest_pivot]) {
        risk_invest_pivot++;
    }

    int risk_opport_pivot = 0;
    while (risktktTurn[risk_opport_pivot] ==
           opporttrdrTurn[risk_opport_pivot]) {
        risk_opport_pivot++;
    }

    int invest_opprt_pivot = 0;
    while (investbnkrTurn[invest_opprt_pivot] ==
           opporttrdrTurn[invest_opprt_pivot]) {
        invest_opprt_pivot++;
    }

    if (aggr_risk_pivot != 0) {
        aggr->initialDiceRollValue = aggrTurn[aggr_risk_pivot];
        risktkr->initialDiceRollValue = risktktTurn[aggr_risk_pivot];
    }
    if (aggr_invest_pivot != 0) {
        investbnkr->initialDiceRollValue = investbnkrTurn[aggr_invest_pivot];
        aggr->initialDiceRollValue = aggrTurn[aggr_invest_pivot];
    }
    if (aggr_opport_pivot != 0) {
        aggr->initialDiceRollValue = aggrTurn[aggr_opport_pivot];
        opporttrdr->initialDiceRollValue = opporttrdrTurn[aggr_opport_pivot];
    }
    if (risk_invest_pivot != 0) {
        investbnkr->initialDiceRollValue = investbnkrTurn[risk_invest_pivot];
        risktkr->initialDiceRollValue = risktktTurn[risk_invest_pivot];
    }
    if (risk_opport_pivot != 0) {
        risktkr->initialDiceRollValue = risktktTurn[risk_opport_pivot];
        opporttrdr->initialDiceRollValue = opporttrdrTurn[risk_opport_pivot];
    }
    if (invest_opprt_pivot != 0) {
        investbnkr->initialDiceRollValue = investbnkrTurn[invest_opprt_pivot];
        opporttrdr->initialDiceRollValue = opporttrdrTurn[invest_opprt_pivot];
    }
}

void initializeBoard(square *board) {
    board[0] = (square){.squareID = 0,
                        .name = "go",
                        .type = go,
                        .owner = noOwnner,
                        .mortgageStatus = cannotMortgage,
                        .mortgageValue = 0,
                        .value = 0};
    board[1] = (square){

        .squareID = 1,
        .name = "Pettah",
        .type = property,
        .mortgageStatus = noMortgage,
        .mortgageValue = 750,
        .value = 1500,
        .PropertyProperties.propertyGroup = brown,
        .PropertyProperties.baseRental = 500};

    board[5] = (square){.squareID = 5,
                        .name = "Colombo Fort Railway Station",
                        .type = railway,
                        .owner = noOwnner,
                        .mortgageStatus = cannotMortgage,
                        .mortgageValue = 0,
                        .value = 0};
}
