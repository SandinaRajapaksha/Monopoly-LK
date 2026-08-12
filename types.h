#ifndef TYPES_H
#define TYPES_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INITIAL_TAX_RATE 15

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
    int laps;
    int loantakigLap;
    int noOfRailways;
    int noOfUtilities;
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
        int baseRentOfRailway;
        int baseRentOfRailway_2_owned;
        int baseRentOfRailway_3_owned;
        int baseRentOfRailway_4_owned;
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
    struct {
        int currentUtilityRent;
    } utilityProperties;

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
typedef enum {
    fire = 1,
    flood,
    riot,
    buildingCollapse,
    electricalFailure
} disaster;

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

typedef struct {
    int currentInflation;
    economicEventCardType currentActiveEconEvent;
    int currentBoardRound;
    int currentInterestRate;
    int roundThatInflationHappened;
    int roundThatEconEventHappened;
    int currentTaxRate;
    int rounfThatDisasterHappend;
    disaster currentDisaster;

} context;

typedef struct {
    player *player_1;
    player *player_2;
    player *player_3;
    player *player_4;
    player *player_BANK;

} playerPointers;
// function Prototypes

void startGame(void);
void initializeBoard(square *, playerPointers *);
//  randomly choosen after round count
void econEventActivate(square *, context *);
void govRegulationsActivate(square *);
void dynamicPropertyEventActivate(square *);
// card decks and draws
void nationalEventActivate(int *, square *);
void regionalDevelopmentActivate(int *, square *);

void initializeTurnOrder(player *, player *, player *, player *, player *,
                         player *, player *, player *);
void finalRankAssign(player *, player *, player *, player *, player *);
void ranker(player *, player *, player *, player *);
diceRollType dice_roller();
void move(player *, square *, context *, playerPointers *);
void roundCounter(context *, player *, player *, player *, player *);
void eventChecker(int *, int *, square *, int *, economicEventCardType *);
void inflationRateRelease(square *, context *);
// resolve square according to types

void resolveSquare(player *, square *, context *, playerPointers *);
void resolveGO(player *);
void resolveSpecial(player *, square *);
void resolveRailway(player *, square *, playerPointers *, context *);
bool aggrRailwayBuyCondition(player *, square *);
bool riskTkrRailwayBuyCondition(player *, square *);
bool consBankerRailwayBuyCondition(player *, square *);
bool opprtTrdrRailwayBuyCondition(player *, square *, context *);
void resolveUtility(player *, square *, context *, playerPointers *);
void resolveEvent(player *, square *);
void resolveInsure(player *, square *);
void resolveTax(player *, square *, context *);
void resolveBank(player *, square *, context *);
void resolveProperty(player *, square *, context *, playerPointers *);
void jailLogic(player *, bool);
bool checkForMonopoly(player *, square *);
void buidBuilding(player *, square *);
void networthEvaluate(player *, player *, player *, player *, square *);
bool playerHasaMonopoly(player *, square *);
void printMarketConditions(context *);
// econ event functions
void tourismBoomActivate(square *);
void tourismBoom_Deactivate(square *);
void FuelCrisisActivate(square *);
void FuelCrisis_Deactivate(square *);
void HeavyMonsoonActivate(square *);
void HeavyMonsoon_deActivate(square *);
void recessionActivate(square *);
void recession_deActivate(square *);
void StockMarketBoomActivate(square *);
void StockMarketBoom_deActivate(square *);
void GovernmentHousingProgrammeActivate(square *);
void GovernmentHousingProgramme_deActivate(square *);
void ForeignInvestmentActivate(square *);
void ForeignInvestment_deActivate(square *);
void PoliticalUnrestActivate(square *);
void PoliticalUnrest_deActivate(square *);
void sellingAuction(player *player_x, player *player_1, player *player_2, player *player_3, player *player_4, square *board, context *contextOfGame, square *);
void printWinner(player *winner, int HighestBid, square *auctionedItem);
bool payRent(player *player_x, square *board);
void AggrNoCashAuction(square *board, player *player_x, playerPointers *playerObject, context *contextOfTheGame);
void bankruptCheck(playerPointers *playerObject, int *);
void bankruptAuction(player *player_x, square *board,
                     context *contextOfGame, square *auctionItem, playerPointers *playerPointerObject);
int doubleToInt(double);
void noBuyAuction(player *player_x, playerPointers *playerObject, square *board, context *contextOfGame, square *auctionItem);
#endif
