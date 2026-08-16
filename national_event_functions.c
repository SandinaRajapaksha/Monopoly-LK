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
void tourismBoom_Deactivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].PropertyProperties.noOfHotels == 1) {
            board[i].PropertyProperties.currentRentalofProperty /= 2;
        }
        if (board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = board[i].curruntValue / (1.15);
        }
    }
}

void FuelCrisisActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == railway) {
            board[i].railwayProperties.baseRentOfRailway *= 2;
        }
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost *= 1.2;
            board[i].PropertyProperties.hotelConstructionCost *= 1.2;
        }
    }
}
void FuelCrisis_Deactivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == railway) {
            board[i].railwayProperties.baseRentOfRailway /= 2;
        }
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost /= 1.2;
            board[i].PropertyProperties.hotelConstructionCost /= 1.2;
        }
    }
}

void HeavyMonsoonActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property &&
            board[i].PropertyProperties.propertyGroup == yellow) { // Galle Fort Unawatuna Hikkaduwa
            board[i].curruntValue = board[i].curruntValue * 0.9;
        }
    }
}

void HeavyMonsoon_deActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property &&
            board[i].PropertyProperties.propertyGroup == yellow) {
            board[i].curruntValue = board[i].curruntValue / 0.9;
        }
    }
}

void recessionActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].curruntValue = board[i].curruntValue * 0.85;
            board[i].PropertyProperties.currentRentalofProperty =
                board[i].PropertyProperties.currentRentalofProperty * 0.9;
        }
    }
}
void recession_deActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].curruntValue = board[i].curruntValue / 0.85;
            board[i].PropertyProperties.currentRentalofProperty =
                board[i].PropertyProperties.currentRentalofProperty / 0.9;
        }
    }
}

void StockMarketBoomActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].curruntValue = board[i].curruntValue * 1.1;
        }
    }
}
void StockMarketBoom_deActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].curruntValue = board[i].curruntValue / 1.1;
        }
    }
}

void GovernmentHousingProgrammeActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost *= 0.75;
        }
    }
}
void GovernmentHousingProgramme_deActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property) {
            board[i].PropertyProperties.houseConstructionCost /= 0.75;
        }
    }
}

void ForeignInvestmentActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property &&
            (board[i].PropertyProperties.propertyGroup == orange ||
             board[i].PropertyProperties.propertyGroup == red)) {
            board[i].curruntValue = board[i].curruntValue * 1.2;
        }
    }
}
void ForeignInvestment_deActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property &&
            (board[i].PropertyProperties.propertyGroup == orange ||
             board[i].PropertyProperties.propertyGroup == red)) {
            board[i].curruntValue = board[i].curruntValue / 1.2;
        }
    }
}

void PoliticalUnrestActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property && board[i].PropertyProperties.noOfHotels == 1) {
            board[i].PropertyProperties.currentRentalofProperty *= 0.5;
        }
    }
}
void PoliticalUnrest_deActivate(square *board) {
    for (int i = 0; i <= 39; i++) {
        if (board[i].type == property && board[i].PropertyProperties.noOfHotels == 1) {
            board[i].PropertyProperties.currentRentalofProperty /= 0.5;
        }
    }
}
