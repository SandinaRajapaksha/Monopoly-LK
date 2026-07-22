#ifndef TYPES_H
#define TYPES_H

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

typedef enum { mortgagedToBank, noMortgage } mortgageType;

typedef struct {
    char *name;
    squareType type;
    playerType owner;

    struct {
        int rental;
    } utilityProperties;

    struct {
        mortgageType mortgageStatus;
    } railwayProperties;
} square;

#endif
