#include <stdio.h>
#include <string.h>
#include "poker.h"


/* Program defines */


/* Functions prototypes */

/* deckUtils.c */
void printSpaces(int n);
void bubbleSort(void *arr[], int size, comparator comp);

/* deck.c */
void displayCard(Card card);

/* poker.c */
cardrank max(cardrank r1, cardrank r2);
int comparePokerRanks(cardrank r1, cardrank r2);

void displayPokerHand(Hand hand);
void displayRankedHands(Hand hands[], int nhands);

void rankHands(Hand hands[], int nhands);
void rankHand(Hand *hand);

void displayWinners(Hand hands[], int nhands);
char *handRankName(handrank n);
int comparePokerHands(Hand *h1, Hand *h2);

/* Function definitions */


/*****************************************************************/
/* Functions to determine hand rank. */
/*****************************************************************/

/* Adrian Hernandez */
cardrank isStraightFlush(Card *cards[]){
    
    cardrank result           = NIL;
    cardrank isStraightResult = isStraight(cards);
    cardrank isFlushResult    = isFlush(cards);
    
    if ((isStraightResult != NIL) && (isFlushResult != NIL)) {
        result = isStraightResult;
    }
    return result;
}

/* Adrian Hernandez */
cardrank isFourKind(Card *cards[]){
    
    int step        = 3;
    cardrank result = NIL;
    int keepLooking = TRUE;
    
    int i;
    for (i = 0; (i + step < POKER_HAND) && keepLooking; i ++ ) {
        if (cards[i] -> rank == cards[i + step] -> rank) {
            result      = cards[i] -> rank;
            keepLooking = FALSE;
        }
    }
    return result;
}

/* Adrian Hernandez */
cardrank isFullHouse(Card *cards[]){
    
    cardrank result = NIL;
    cardrank threeKindResult = isThreeOfAKind(cards);
    
    if (threeKindResult != NIL) {
        /* check if there are 2 matching cards of a different rank. */
        if (isOnePair(cards, threeKindResult) != NIL){
            result = threeKindResult;
        }
    }
    return result;
}

/**/
/* Camilo Rivera */
//Function that checks for 2 cards of the same rank in a hand.
/*cardrank ignore is an enum type that accepts an enum of that type that the function will ignore (for example NIL which is 0)*/
cardrank isOnePair(Card *pokerHand[], cardrank ignore) 
{
    
    int i;
    cardrank result;
     
    for(i = 0; i+1 < POKER_HAND; i++)               //The For loop cycles through the sorted hand in the 
    {
        if((pokerHand[i]->rank == pokerHand[i+1]->rank)&&(pokerHand[i]->rank != ignore)) //Checks the card and the card after since the hand is sorted by rank
        {
            result = pokerHand[i]->rank;
            return result;                                                             //Returns the rank
        }
        else
        {
            result = NIL;                                                             //If no pair then returns NIL
        }
    }
    
    return result;
}

/* Camilo Rivera */
//Function that checks for two different pair of cards. Each pair is a pair of cards with the same rank.
cardrank isTwoPair(Card *pokerHand[])
{
    
    cardrank firstPair, secondPair, result;
    
    firstPair  = isOnePair(pokerHand, NIL);  //Checks for one pair first
    secondPair = NIL;
    
    if(firstPair != NIL)                      //If there is a first pair then it gets ignored to check for a second pair.
    {
        secondPair = isOnePair(pokerHand, firstPair);
    }
    
    if((firstPair == NIL || secondPair == NIL) || (firstPair == secondPair)) //Return NIL if there is only one pair or no pairs or if both pairs have same rank.
    {
        result = NIL;
    }
    else
    {
        result = max(firstPair,secondPair);                           //Returns the largest ranked pair for tiebreaking
    }
    
    return result;
}


/* Camilo Rivera */
//Function that checks for 3 cards of the same rank in a hand
cardrank isThreeOfAKind(Card *pokerHand[])
{
    int i;
    cardrank result;
    
    for(i = 0; i + 2 < POKER_HAND; i++) //Loops through the hand looking for 2 consecutive cards of the same rank since the hand is sorted
    {
        if((pokerHand[i]->rank == pokerHand[i+1]->rank) && (pokerHand[i+1]->rank  == pokerHand[i+2]->rank))
        {
            result = pokerHand[i+1]->rank;      //Returns in the rank if there is 3 of a kind
            return result;
        }
        else
        {
            result = NIL;
        }
    }
    return result;
}

/* Camilo Riviere */
cardrank isFlush(Card *hand[]){
    
    int i;
    cardrank result = NIL;
    int counter = 1;
    
    for(i = 0; i < POKER_HAND - 1; i++){
        if(hand[i] -> suit == hand[i+1] -> suit)
            counter++;
    }
    
    if(counter == POKER_HAND){
        result = hand[POKER_HAND - 1] -> rank;
    }
    return result;
}

/* Camilo Riviere */
//cardrank isStraight(Card *hand[]){
//    
//    int i;
//    int counter = 0;
//    cardrank temp;
//    
//    if ((hand[POKER_HAND - 1]->rank == KING) && (hand[POKER_HAND - 2]->rank == QUEEN) && (hand[POKER_HAND - 3]->rank == JACK) && (hand[MAX_HAND-4]->rank == TEN) && (hand[MAX_HAND-5]->rank == ACE))
//        return (temp = (hand[MAX_HAND-1]->rank + 1));
//    
//    for(i = POKER_HAND - 1; i > 0; i--){
//        if((hand[i] -> rank - hand[i-1] -> rank) == 1)
//            counter++;
//    }
//    
//    if(counter == 4){
//        return (temp = hand[MAX_HAND - 1]->rank);
//    }
//    else{
//        return NIL;
//    }
//}

/* Camilo Riviere */
cardrank isStraight(Card *hand[]){
    
    cardrank result = NIL;
    cardrank onePairTest = isOnePair(hand, NIL);

    /* check that there are not two cards with matching ranks */
    if (onePairTest == NIL) {
        
        cardrank first = hand[0] -> rank;
        cardrank second = hand[1] -> rank;
        cardrank last = hand[POKER_HAND - 1] -> rank;

        if ((last - first) == (POKER_HAND - 1)) {
            /* cards are in sequence */
            result = last;
        }
        else if ((first == ACE) && (last == KING) && ((last - second) == POKER_HAND - 2)){
            /* royal straight */
            result = ACE;
        }
    }
    return result;
}

/*****************************************************************/
/* End of functions to determine hand rank. */
/*****************************************************************/


/* Camilo Rivera */
//Compares 2 different cardrank types and returns the one of higher rank
//Calls the comparePokerRanks function
cardrank max(cardrank r1, cardrank r2)
{
    return (comparePokerRanks(r1, r2) <= 0) ? r2 : r1;
}

/* Camilo Rivera */
//Compares the ranks through an arithmetic calculation.
int comparePokerRanks(cardrank r1, cardrank r2){
    
    int result;
    
    if (r1 == ACE || r2 == ACE){
        result = (-1)*(r1 - r2);        // Takes care of the situation where Ace maybe have a higher value such as a Straight
    }
    else{
        result = r1 - r2;
    }
    return result;
}

/* Adrian Hernandez */
int comparePokerHands(Hand *h1, Hand *h2){
    
    int result;

    if ((h1 -> rank) == (h2 -> rank)) {
        /* use tiebreaker to define */
        result =  comparePokerRanks(h1 -> tieBreaker, h2 -> tieBreaker);
    }
    else {
        result = (h1 -> rank) - (h2 -> rank);
    }
    return result;
}


/*****************************************************************/
/* Functions to control program flow. */
/*****************************************************************/

/* Adrian Hernandez */
void rankHands(Hand hands[], int nhands){
    
    int i;
    for (i = 0; i < nhands; i++) {
        rankHand(&hands[i]);
    }
}

/* Finds the rank of the provided hand. */
/* Adrian Hernandez */
void rankHand(Hand *hand){
    
    cardrank tieBreaker;
    handrank hrank = HIGH_CARD;
    
    if ((tieBreaker = isStraightFlush(hand -> cards)) != NIL) {
        hrank = STRAIGHT_FLUSH;
    }
    else if ((tieBreaker = isFourKind(hand -> cards)) != NIL){
        hrank = FOUR_KIND;
    }
    else if((tieBreaker = isFullHouse(hand -> cards)) != NIL){
        hrank = FULL_HOUSE;
    }
    else if((tieBreaker = isFlush(hand -> cards)) != NIL){
        hrank = FLUSH;
    }
    else if((tieBreaker = isStraight(hand -> cards)) != NIL){
        hrank = STRAIGHT;
    }
    else if((tieBreaker = isThreeOfAKind(hand -> cards)) != NIL){
        hrank = THREE_KIND;
    }
    else if((tieBreaker = isTwoPair(hand -> cards)) != NIL){
        hrank = TWO_PAIR;
    }
    else if((tieBreaker = isOnePair(hand -> cards, NIL)) != NIL){
        hrank = ONE_PAIR;
    }
    else {
        /* high card */
        cardrank lowCard  = (hand -> cards[0]) -> rank;
        cardrank highCard = (hand -> cards[POKER_HAND - 1]) -> rank;
        
        /* since ACE could be at the beginning */
        tieBreaker = max(lowCard, highCard);
    }
    
    hand -> rank       = hrank;
    hand -> tieBreaker = tieBreaker;
}

/* Camilo Riviere */
void displayRankedHands(Hand hands[], int nhands){
    
    rankHands(hands, nhands);
    
    int i;
    for (i = 0; i < nhands; i++) {
        displayPokerHand(hands[i]);
    }
    
}

/* Display a poker hand. */
/* Adrian Hernandez */
void displayPokerHand(Hand hand){
    
    char *handName = hand.handName;
    char *handRank = handRankName(hand.rank);
    
    int handNameLength = strlen(handName);
    int handRankLength = strlen(handRank);
    
    printf("\n");
    printSpaces(DEFAULT_ALIGN + MAX_CARD_NAME - handNameLength);
    printf("%s\n", handName);
    
    printSpaces(DEFAULT_ALIGN + MAX_CARD_NAME - handRankLength);
    printf("%s\n\n", handRank);
    
    int i;
    for (i = 0; i < POKER_HAND ; i++) {
        
        /* alignment */
        printSpaces(DEFAULT_ALIGN);
        
        displayCard(*(hand.cards[i]));
        printf("\n");
    }
    printf("\n");
}

/* Adrian Hernandez */
void displayWinners(Hand hands[], int nhands){
    
//    void sortPokerHands(Hand *arr[], int size);
//    void bubbleSort1(void *arr[], int size, comparatorFuncPointer comparator);
    
    Hand *hpointers [nhands];
    int i;
    for (i = 0; i < nhands; i++) {
        hpointers[i] = &hands[i];
    }
    
//    sortPokerHands(hpointers, nhands);
    bubbleSort((void **)hpointers, nhands, (int(*)(void *, void *)) comparePokerHands);
    
    int winnerIndex = nhands - 1;
    Hand *winner = hpointers[winnerIndex];
   
    int done = FALSE;
    for (; winnerIndex >= 0 && !done; winnerIndex --) {
        if (comparePokerHands(winner, hpointers[winnerIndex]) == 0) {
            /* there is a tie. */
            winner = hpointers[winnerIndex];
            displayPokerHand(*winner);
        }
    }
    
}

/* Return name of n-th hand rank */
/* Camilo Riviere */
char *handRankName(handrank n){
    
    static char *names[] = {
        "NONE",
        "HIGH CARD", "ONE PAIR", "TWO PAIRS" , "THREE OF A KIND",
        "STRAIGHT" , "FLUSH"   , "FULL HOUSE", "FOUR OF A KIND",
        "STRAIGHT FLUSH"
    };
    return (n < HIGH_CARD || n > STRAIGHT_FLUSH) ? names[0] : names[n];
}


//void bubbleSort1(void *arr[], int size, comparatorFuncPointer comparator){
//    
//    int sorted;         /* flag to indicate whether arr is sorted or not. */
//    int pos = size - 1; /* position to fill. */
//    
//    /* need to loop over the array at least once. */
//    do {
//        
//        /* ensure the algorithm will stop */
//        sorted = TRUE;
//        
//        /* loop */
//        int i;
//        for (i = 0; i < pos; i ++) {
//            if((*comparator)(arr[i], arr[i + 1]) > 0){
//                
//                /* found not sorted elements */
//                sorted = FALSE;
//                
//                /* sort the elements */
//                void *temp = arr[i];
//                arr[i] = arr[i + 1];
//                arr[i + 1] = temp;
//            }
//        }
//        
//        /* arr[pos] is filled with the right card so decrease pos */
//        pos --;
//        
//    } while (!sorted);
//}


/* Bubble sort algorithm for poker hands. */
//void sortPokerHands(Hand *arr[], int size){
//    
//    int sorted;         /* flag to indicate whether arr is sorted or not. */
//    int pos = size - 1; /* position to fill. */
//    
//    /* need to loop over the array at least once. */
//    do {
//        
//        /* ensure the algorithm will stop */
//        sorted = TRUE;
//        
//        /* loop */
//        int i;
//        for (i = 0; i < pos; i ++) {
//            if(comparePokerHands(*arr[i], *arr[i + 1]) > 0){
//                
//                /* found not sorted elements */
//                sorted = FALSE;
//                
//                /* sort the elements */
//                Hand *temp = arr[i];
//                arr[i] = arr[i + 1];
//                arr[i + 1] = temp;
//            }
//        }
//        
//        /* arr[pos] is filled with the right card so decrease pos */
//        pos --;
//        
//    } while (!sorted);
//}
