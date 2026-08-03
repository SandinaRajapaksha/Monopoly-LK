#ifndef TYPES_H
#define TYPES_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int rollValue;
    bool doublesRolled;
} diceRollType;
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
    noOwnner = 301,
    bankOfCeylon,
    aggresiveInvester,
    conservativeBanker,
    riskTaker,
    opportunisticTrader
} playerType;

typedef enum { inside = 401,
               outside } jailStatus;
typedef struct {
    playerType playerID;
    char *name;
    int rank;
    int diceRoll;
    int currentSquare;
    int totalsteps;
    int cash;
    int netWorth;
    jailStatus Jail;
    int jailRoundCounter;
    int noOfHousesOwned;
    int noOfHotelsOwned;
    bool hasDebt;
    int noOfProperties;
    int outStandingLoan;
    bool isBankrupt;
    int MaxElegibleLoanAmount;
    int loanRepaymentRoundCount;
} player;

typedef enum { cannotMortgage,
               mortgagedToBank,
               noMortgage } mortgageType;

typedef enum {
    brown = 8001,
    lightBlue,
    pink,
    orange,
    red,
    yellow,
    green,
    darkBlue
} groupType;

typedef enum {
    gotoJail = 6001,
    JailOrVisiting,
    FreeParking

} specialityType;
typedef enum { inusured,
               notInsured } insurance;

typedef struct sq {

    int squareID;
    char *name;
    squareType type;
    player *owner;
    mortgageType mortgageStatus;
    int mortgageValue;
    int curruntValue;

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
        int initialPrice;
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
    struct {
        specialityType specililtyOfSquare;
    } specialityProperties;

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
void econEventActivate(square *, int *, economicEventCardType *, int *);
void govRegulationsActivate(square *);
void dynamicPropertyEventActivate(square *);
// card decks and draws
void nationalEventActivate(int *, square *);
void regionalDevelopmentActivate(int *, square *);

void initializeTurnOrder(player *, player *, player *, player *, player *,
                         player *, player *, player *);
void finalRankAssign(player *player_X, player *player_1, player *player_2,
                     player *player_3, player *player_4);
void ranker(player *player1, player *player2, player *player3, player *player4);
diceRollType dice_roller();
void move(player *player_x, square *board, economicEventCardType *, int *);
void roundCounter(int *curruntBoardRound, player *player_1, player *player_2,
                  player *player_3, player *player_4);
void eventChecker(int *, int *, square *, int *, economicEventCardType *);
void inflationRateRelease(square *board, int *currundBoardRound,
                          int *roundThatInflationHappened,
                          int *curruntInflation);
// resolve square according to types
void resolveSquare(player *player_x, square *board, economicEventCardType *, int *);
void resolveGO(player *player_x);
void resolveSpecial(player *player_x, square *board);
void resolveRailway(player *player_x, square *board);
void resolveUtility(player *player_x, square *board);
void resolveEvent(player *player_x, square *board);
void resolveInsure(player *player_x, square *board);
void resolveTax(player *player_x, square *board);
void resolveBank(player *player_x, square *board);
void resolveProperty(player *player_x, square *board, economicEventCardType *, int *);
void jailLogic(player *, bool);
bool checkForMonopoly(player *player_x, square *board);
void buidBuilding(player *player_x, square *board);
void networthEvaluate(player *player_1, player *player_2, player *player_3, player *player_4, square *board);
#endif
