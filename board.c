#include "types.h"

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
