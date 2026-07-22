#ifndef TYPES_H
#define TYPES_H
#define NOT_INITIALIZED -99;
#define TRUE 1;
#define FALSE 0;

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
    none,
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

typedef struct s {
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
        int currentRentOfRailway = noOfRailwaysOwnedByOwner * baseRentOfRailway;
    } railwayProperties;

    struct {
        groupType propertyGroup;
        int baseRental;
        int houseConstructionCost;
        int hotelConstructionCost;
        insurance insuranceStatus;
        int noOfHouses;
        int noOfHotels;
    } PropertyProperties;

} square;

#endif
