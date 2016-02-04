#include "deck.h" /* to provide constants */


/* Constants and functions declarations specific to a game of poker. */

/* Program defines */
#define POKER_HAND MAX_HAND

/* Function prototypes */

/* Determines if the cards represent a straight flush. */
/* Returns rank of highest card if it is a straight flush. Returns 0 otherwise. */
/* cards      : Cards to inspect. */
/* Adrian Hernandez */
cardrank isStraightFlush(Card *cards[]);

/* Determines if the cards represent a hand four of a kind. */
/* Returns the rank of the cards if it is a four of a kind. Returns 0 otherwise. */
/* cards      : Cards to inspect. */
/* Adrian Hernandez */
cardrank isFourKind(Card *cards[]);

/* Determines if the cards represent a full hause. */
/* Returns rank of the 3 matching cards if it is a full hause. Returns 0 otherwise. */
/* cards      : Cards to inspect. */
/* Adrian Hernandez */
cardrank isFullHouse(Card *cards[]);


//TODO: Remove comment for production
/* I think we could use these functions prototypes.  */
cardrank isFlush(Card *cards[]);
cardrank isStraight(Card *cards[]);
cardrank isThreeOfAKind(Card *cards[]);
cardrank isOnePair(Card *cards[], cardrank ignore);
cardrank isTwoPair(Card *pokerHand[]);

void displayRankedHands(Hand hands[], int nhands);
void displayWinners(Hand hands[], int nhands);
