#include "types.h"

void econEventActivate(square *board) {
    // random
    economicEventCardType econEvents[8] = {
        TourismBoom,       FuelCrisis,      HeavyMonsoon,
        EconomicRecession, StockMarketBoom, GovernmentHousingProgramme,
        ForeignInvestment, PoliticalUnrest};
}

void govRegulationsActivate(square *board) {
    // random
    govRegulationsType govRegulations[8] = {
        IncreasePropertyTax, ReduceLoanInterest,   HousingSubsidy,
        LuxaryPropertyTax,   RailwayModernization, ElectricityTariffRevision,
        InsuranceRegulation, AntiSpeculantAct};
}

void nationalEventActivate(int *topNationalEventcard, square *board) {
    // deck
    NationalEventType NationalEventCards[19] = {
        TourismHype,         FuelShortage,         PoliticalRally,
        StockMarketRise,     EconomicDowntime,     HousingSubsidy_NationalEvent,
        InterestRateCut,     InterestRateIncrease, TaxAmnesty,
        PowerFailure,        ForeignFunding,       PortExpansion,
        FestivalSeason,      LabourStrike,         InsuranceDiscount,
        PropertyRevaluation, CurrencyDepreciation, GovernmentGrant,
        NationalDisaster};

    NationalEventType currentNationalEvent =
        NationalEventCards[*topNationalEventcard];
    // all the shit happening accoding to event
    *topNationalEventcard = (*topNationalEventcard + 1) % 19;
}
