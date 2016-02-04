#include <stdio.h>   /* to perform input output */
//#include "deck.h"    /* constants and functions prototypes */
#include "poker.h"

/* Author: Adrian Hernandez, COP4338 - U03, PID: 5048625 */

/* Description: */
/* The program simulates a deck of cards in preparation for a game of cards. */
/* Input will be the number of cards and the number of hands provided via command-line arguments. */
/* Program has 3 source files (main.c, deck.c and deckUtils.c) and 1 user defined header (deck.h). */


/* Specifications: */
/* Program will accept and validate input via the command-line arguments. */
/* Structures were used to represent a card. */
/* It is assumed that the deck has 52 cards, 13 face values and 4 suits. */
/* It is that there will not be more than 13 hands and no more than 13 cards per hand. */
/* The simulation will create a deck of cards, shuffle the cards, display the shuffled deck of cards, */
/* deal the specified number of cards to the specified number of hands and display each of */
/* the hands of cards. Also the hands will be sorted and displayed before and after sorting. */

/* Compilation: gcc main.c deck.c deckUtils.c deck.h -c */
/* Linkage:     gcc main.o deck.o deckUtils.o -o deck.out */
/* Requires user header file in same directory. */
/* Execute with : ./deck.out hand_size number_of_hands */

/* Certification: */
/* I hereby certify that this collective work is my own and none of it is the work of any other person or entity. */
/* Adrian Hernandez - PID: 5048625 */

/* Pseudo code */
/*
 if (valid arguments){
    create deck;
    display deck;
    shuffle deck;
    display shuffled deck;
    
    if (numberOfHands >= MIN_NUM_HANDS && handSize >= MIN_HAND){
       create hands;
       display hands;
       sort hands;
       display hands;
    }
 }
 else {
    terminate with error;
 }
 */

/* program defines */
#define NO_ERRORS 0        /* no errors found */
#define ERRORS 1           /* errors were found */

/* Simulates a deck of cards in preparation for a game of cards. */
/* Usage: deck hand_size number_of_hands */
int main(int argc, char *argv[]) {
    
    /* input */
    int nhands;                   /* stores number of hands from input */
    int handSize;                 /* stores hand size from input */
    int canDisplayHands;          /* flag to indicate if the hands can be displayed */
    
    int foundErrors = NO_ERRORS;  /* indicate whether errors are found */

    /* validate input */
    if (validInput(argc, argv, &handSize, &nhands)){
        
        Card deck[DECK_SIZE];     /* the cards deck */
        Hand hands[nhands];       /* the hands */
        Hand sortedHands[nhands];
        
        canDisplayHands = (handSize && nhands) > 0 ? TRUE : FALSE;
        
        /* create a deck of cards. */
        printf("\n   Create and display the deck.\n\n");
        createDeck(deck);
        displayDeck(deck, DECK_SIZE);
        
        /* shuffle deck of cards */
        printf("\n   Shuffle and display the deck.\n\n");
        shuffleDeck(deck, DECK_SIZE);
        displayDeck(deck, DECK_SIZE);
        
        if (canDisplayHands){
            /* create and display hands */
            printf("\n   Create and display hands.\n\n");
            createHands(deck, hands, handSize, nhands);
            sortHands(hands, sortedHands, handSize, nhands);
            
            displayHands(hands, sortedHands, handSize, nhands);
                        
            /* rank hands */
            printf("\n   Rank and display ranked hands.\n\n");
            displayRankedHands(sortedHands, nhands);
            
            printf("\n   Display winners.\n\n");
            displayWinners(sortedHands, nhands);
        }
        else{
            printf("\nCould not display hands because either the hand size or the number of hands is zero.\n");
        }
    }
    else{
        /* invalid input */
        printf("Usage: deck hand_size number_of_hands\n");
        foundErrors = ERRORS;
    }
    return foundErrors;
}
