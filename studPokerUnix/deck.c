#include <stdio.h>        /* to perform input output */
#include <stdlib.h>       /* to use rand(void) and srand(unsigned int s)*/
#include <time.h>         /* to use time(time_t *) */
#include <string.h>       /* to use strlen() */
#include "deck.h"         /* to provide constants */

/* Program defines */
#define DECK_COLUMNS 4    /* columns to display deck */

/* Functions prototypes */

/* defined in deckUtils.c */
char *suitName(cardsuit s);
char *rankName(cardrank r);
int compareCards(Card *c1, Card *c2);
void bubbleSort(void *arr[], int size, comparator comp);
int stringToNumber(char *s);
void printSpaces(int n);
void copyHand(Hand orig, Hand *copy, int size);
int numberOfDigits(int n);

/* defined in deck.c */
Card createCard(cardsuit suit, cardrank rank);
void createDeck(Card deck[]);
void displayDeck(Card deck[], int size);
void displayCard(Card card);
void shuffleDeck(Card deck[], int size);
void createHands(Card deck[], Hand hands[], int handSize, int nhands);
void displayHands(Hand hands[], Hand sortedHands[], int handSize, int nhands);
void sortHand(Hand *hand, int handSize);
int validInput(int argc, char *argv[], int *handSize, int *nhands);

/* Function definitions */

/* Creates a card. */
Card createCard(cardsuit suit, cardrank rank){
    
    Card temp;
    temp.suit = suit;
    temp.rank = rank;
    return temp;
}

/* Creates a deck of cards. */
void createDeck(Card deck[]){
    
    int i, j, k;
    k = 0;
    for (i = ACE; i <= KING; i++) {
        for (j = CLUBS; j <= SPADES; j++) {
            deck[k] = createCard(j, i);
            k++;
        }
    }
}

/* Displays a deck of cards. */
void displayDeck(Card deck[], int size){
    
    int i;
    for (i = 0; i < size; i++) {
        
        /* alignment */
        printSpaces(DEFAULT_ALIGN);
        displayCard(deck[i]);
        
        if((i % DECK_COLUMNS) == (DECK_COLUMNS - 1)){
            /* start new row */
            printf("\n");
        }
    }
}

/* Display a single card. */
void displayCard(Card card){
    
    int i;
    int nameLength;
    char *suit = suitName(card.suit);
    char *rank = rankName(card.rank);
    
    nameLength = strlen(suit) + strlen(rank) + 4;
    
    /* print spaces to right align */
    printSpaces(MAX_CARD_NAME - nameLength);
    
    /* print card */
    printf("%s OF %s", rank, suit);
}

/* Shuffles a deck of cards. */
void shuffleDeck(Card deck[], int size){
    
    int i;
    time_t t;
    
    /* initialize random number generator */
    srand((unsigned) time(&t));
    
    for (i = 0; i < size; i++) {
        
        /* generate random possiton to swap with position i. */
        int rp = rand()%size;
        
        /* swap cards */
        Card temp = deck[i];
        deck[i] = deck[rp];
        deck[rp] = temp;
    }
    
}

/* Create hands of cards. */
void createHands(Card deck[], Hand hands[], int handSize, int nhands){
    
    int i, j, k;
    
    k = 0;
    for (i = 0; i < handSize; i++) {
        for (j = 0; j < nhands; j ++) {
            hands[j].cards[i] = &deck[k];
            k++;
        }
    }
    
    /* set the hands names */
    for (i = 0; i < nhands; i ++) {
        sprintf(hands[i].handName, "Hand %d", i + 1);
    }
}

/* sort hands */
void sortHands(Hand unsorted[], Hand sorted[], int handSize, int nhands){
    
    int i;
    for (i = 0; i < nhands; i++) {
        copyHand(unsorted[i], &sorted[i], handSize);
        sortHand(&sorted[i], handSize);
    }
}

/* display hands. */
void displayHands(Hand hands[], Hand sortedHands[], int handSize, int nhands){

    
    int i, j;     /* loop variables */

    for (i = 0; i < nhands; i++) {
        
        Hand sorted = sortedHands[i];
        char *unsortedHandName = hands[i].handName;
        char *sortedHandName   = sorted.handName;
        
        /* align and print hands names */
        int handNameLen      = strlen(unsortedHandName);
        int sortedHandNamLen = strlen(sortedHandName);
        
        /* alignment */
        printSpaces(MAX_CARD_NAME + DEFAULT_ALIGN - handNameLen);
        printf("%s", unsortedHandName);
        
        /* alignment */
        printSpaces(MAX_CARD_NAME + DEFAULT_ALIGN - (sortedHandNamLen + 7));
        printf("%s sorted\n\n", sortedHandName);
        
        for (j = 0; j < handSize; j++) {
            
            /* alignment */
            printSpaces(DEFAULT_ALIGN);
            
            /* print original */
            displayCard(*(hands[i].cards[j]));
            
            /* alignment */
            printSpaces(DEFAULT_ALIGN);
            
            /* print sorted */
            displayCard(*(sorted.cards[j]));
            
            printf("\n");
            
        }
        printf("\n\n");
    }
}

/* Sort a hand of cards. */
void sortHand(Hand *hand, int handSize){
    bubbleSort((void **)(hand -> cards), handSize, (int(*)(void *, void *))compareCards);
}

/* validates input and set hand size and number of hands */
int validInput(int argc, char *argv[], int *handSize, int *nhands){
    
    int valid = FALSE;
    
    /* if got right number of arguments, validate their values */
    if (argc == ARGS_COUNT){
        
        int hsize;   /* hand size */
        int numHands;  /* number of hands */
        
        /* check if hand size and number of hands are valid */
        int validHandSize = ((hsize = stringToNumber(argv[1])) <= MAX_HAND ) && hsize >= MIN_HAND;
        int validNumHands = ((numHands = stringToNumber(argv[2])) <= MAX_NUM_HANDS) && numHands >= MIN_NUM_HANDS;
        
        if (validHandSize && validNumHands && (hsize * numHands) <= DECK_SIZE) {
            *handSize = hsize;
            *nhands = numHands;
            valid = TRUE;
        }
        else if (!validHandSize){
            /* feedback on hand size */
            printf("Hand size should be a number between %d and %d\n", MIN_HAND, MAX_HAND);
        }
        else if(!validNumHands){
            /* feedback on number of hands */
            printf("Number of hands should be a number between %d and %d\n", MIN_NUM_HANDS, MAX_NUM_HANDS);
        }
        else{
            /* feedback on number of cards in the deck */
            printf("The deck contains only %d cards\n", DECK_SIZE);
        }
    }
    
    return valid;
}
