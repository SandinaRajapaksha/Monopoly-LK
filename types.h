#ifndef TYPES_H
#define TYPES_H
#define notInitialized -99;

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
    aggresiveInvester,
    conservativeBanker,
    riskTaker,
    opportunisticTrader,
    none
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

typedef enum { inusured, notInsurd } insurance;

typedef struct s {
    int squareID;
    char *name;
    squareType type;
    playerType owner;
    mortgageType mortgageStatus;
    int mortgageValue;
    int value;

    struct {
        int rental;
    } utilityproperties;

    struct {
        int noOfRailwaysOwnedByOwner;
        int baseRentOfRailway;
        int currentRent = noOfRailwaysOwnedByOwner * baseRentOfRailway;
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
