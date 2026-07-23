#include "types.h"

void econEventActivate(square *board) {
    //
    economicEventCardType econEvents[8] = {
        TourismBoom,       FuelCrisis,      HeavyMonsoon,
        EconomicRecession, StockMarketBoom, GovernmentHousingProgramme,
        ForeignInvestment, PoliticalUnrest};
}

void govRegulationsActivate(square *board) {
    //
    govRegulationsType govRegulations[8] = {
        IncreasePropertyTax, ReduceLoanInterest,   HousingSubsidy,
        LuxaryPropertyTax,   RailwayModernization, ElectricityTariffRevision,
        InsuranceRegulation, AntiSpeculantAct};
}
