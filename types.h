#ifndef TYPES_H
#define TYPES_H
#define NOT_INITIALIZED -99;
#define TRUE 1;
#define FALSE 0;

// player types
typedef struct {

    int playerId;
    int turnOrder;

} player;

// square
typedef enum {
    go,
    special,
    railway,
    utility,
    event,
    insure,
    tax,
    bank,
    property
} squareType;

typedef enum {
    noOwnner,
    bankOfCeylon,
    aggresiveInvester,
    conservativeBanker,
    riskTaker,
    opportunisticTrader
} playerType;

typedef enum { cannotMortgage, mortgagedToBank, noMortgage } mortgageType;

typedef enum {
    brown,
    lightBlue,
    pink,
    orange,
    red,
    yellow,
    green,
    darkBlue
} groupType;

typedef enum { inusured, notInsured } insurance;

typedef struct sq {

    int squareID;
    char *name;
    squareType type;
    playerType owner;
    mortgageType mortgageStatus;
    int mortgageValue;
    int value;

    struct {
        int BaseRentalOfUtility;
        int noOfUtiliesOwnedByOwner;
        int currentRentOfUtility; // based on dice role
    } utilityproperties;

    struct {
        int noOfRailwaysOwnedByOwner;
        int baseRentOfRailway;
        int currentRentOfRailway; // calculated using other two properties
    } railwayProperties;

    struct {
        groupType propertyGroup;
        int baseRental;
        int houseConstructionCost;
        int hotelConstructionCost;
        insurance insuranceStatus;
        int noOfHouses;
        int noOfHotels;
        int currentRentalofProperty;
    } PropertyProperties;

    struct {
        int taxAmount;
    } TaxSquareProperties;

} square;

// event_related types
typedef enum {

    TourismBoom = 1001,
    FuelCrisis,
    HeavyMonsoon,
    EconomicRecession,
    StockMarketBoom,
    GovernmentHousingProgramme,
    ForeignInvestment,
    PoliticalUnrest

} economicEventCardType;

// goverment regulation types
typedef enum {

    IncreasePropertyTax = 2001,
    ReduceLoanInterest,
    HousingSubsidy,
    LuxaryPropertyTax,
    RailwayModernization,
    ElectricityTariffRevision,
    InsuranceRegulation,
    AntiSpeculantAct

} govRegulationsType;

// national event cards

typedef enum {

    TourismHype = 3001,
    FuelShortage,
    PoliticalRally,
    StockMarketRise,
    EconomicDowntime,
    HousingSubsidy_NationalEvent,
    InterestRateCut,
    InterestRateIncrease,
    TaxAmnesty,
    PowerFailure,
    ForeignFunding,
    PortExpansion,
    FestivalSeason,
    LabourStrike,
    InsuranceDiscount,
    PropertyRevaluation,
    CurrencyDepreciation,
    GovernmentGrant,
    NationalDisaster

} NationalEventType;

// regional development type

typedef enum {

    southernTourismBoom = 4001,
    portCityExpansion,
    itIndustryGrowth,
    nothernDevelopmentProgramme,
    teaExportBoom,
    airPortExpansion,
    universityCityGrowth,
    beachPollution,
    floodDamage,
    transportStrike,
    electricityTariffIncrease,
    waterShortage

} regionalDevelopmentType;

typedef enum {

    dynamicPropertyMarketBoom = 5001,
    dynamicPropertyMarketDecline

} dynamicPropertyMarketEventType;

// function Prototypes

void startGame(void);
void initializeBoard(square *);
//  randomly choosen after round count
void econEventActivate(square *);
void govRegulationsActivate(square *);
// card decks and draws
void nationalEventActivate(int *, square *);
void regionalDevelopmentActivate(int *, square *);

#endif
