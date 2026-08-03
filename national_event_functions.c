#include "types.h"

void tourismBoomActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].PropertyProperties.noOfHotels == 1) {
            board[i].PropertyProperties.currentRentalofProperty *= 2;
        }
        if (board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = board[i].curruntValue * (1.15);
        }
    }
}
void tourismBoom_Deactivate(square *board) {}

void FuelCrisisActivate(square *board) {}
void FuelCrisis_Deactivate(square *board) {}

void HeavyMonsoonActivate(square *board) {}
void HeavyMonsoon_deActivate(square *board) {}

void recessionActivate(square *board) {}
void recession_deActivate(square *board) {}

void StockMarketBoomActivate(square *board) {}
void StockMarketBoom_deActivate(square *board) {}

void GovernmentHousingProgrammeActivate(square *board) {}
void GovernmentHousingProgramme_deActivate(square *board) {}

void ForeignInvestmentActivate(square *board) {}
void ForeignInvestment_deActivate(square *board) {}

void PoliticalUnrestActivate(square *board) {}
void PoliticalUnrest_deActivate(square *board) {}
