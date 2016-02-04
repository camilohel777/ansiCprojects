/* Program defines */
#define MAX_HAND 5         /* max number of cards per hand */
#define MIN_HAND 5         /* min number of cards per hand */
#define MAX_NUM_HANDS 10   /* max number of hands */
#define MIN_NUM_HANDS 0    /* min number of hands */
#define DECK_SIZE 52       /* numbers of cards in the deck */
#define TRUE 1             /* boolean true */
#define FALSE 0            /* boolean false */
#define ARGS_COUNT 3       /* number of expected arguments */
#define MAX_HAND_NAME 20   /* max string length of hand name */
#define DEFAULT_ALIGN 4    /* default white spaces used for alignment */
#define MAX_CARD_NAME 17   /* max string length of card name */

/* Other definitions */

typedef enum { CLUBS = 1, DIAMONDS, HEARTS, SPADES } cardsuit;

typedef enum { NIL = 0, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
                NINE, TEN, JACK, QUEEN, KING } cardrank;

/* Defines the 9 different hand ranks in a game of poker. */
/* Adrian Hernandez */
typedef enum { NONE = 0, HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_KIND,
               STRAIGHT, FLUSH, FULL_HOUSE, FOUR_KIND, STRAIGHT_FLUSH
             } handrank;

/* Structure describing a card */
typedef struct {
    cardsuit suit;
    cardrank rank;
} Card;

/* Define a cards hand.*/
/* cards      : Array of pointers to the cards that form the hand. */
/* handName   : String of characters for a name to identify the hand. */
/* rank       : Defined type that identify the rank of the hand. */
/* tieBreaker : Rank of the 'most important' card in the hand. */
/* Adrian Hernandez */
typedef struct {
    Card *cards[MAX_HAND];
    char handName[MAX_HAND_NAME];
    handrank rank;
    cardrank tieBreaker;
} Hand;

typedef int (*comparator)(void *obj1, void *obj2);

/* Function prototypes */

/* Creates a deck of cards. Structures of type card are stored in the */
/* provided array. */
void createDeck(Card deck[]);

/* Displays a deck of cards with the provided size. */
void displayDeck(Card deck[], int size);

/* Shuffles a deck of cards with the provided size. */
void shuffleDeck(Card deck[], int size);

/* Create hands of cards. */
/* deck     : array of cards. */
/* hands    : array of Hand objects to store the created hands. */
/* handSize : number of cards in a hand. */
/* nhands   : number of hands. */
void createHands(Card deck[], Hand hands[], int handSize, int nhands);

/* Display all hands of cards. */
/* hands    : array of hands to display. */
/* handSize : number of cards in a hand. */
/* nhands   : number of hands. */
//void displayHands(Hand hands[], int handSize, int nhands);
void displayHands(Hand hands[], Hand sortedHands[], int handSize, int nhands);

/* Sort several hands of cards. */
/* hands    : array of hands to sort. */
/* handSize : number of cards in a hand. */
/* nhands   : number of hands. */
void sortHands(Hand unsorted[], Hand sorted[], int handSize, int nhands);

/* Validate input from command-line and sets hand size and number of hands. */
/* Returns 1 if input is valid and 0 if it is invalid. */
/* If invalid prints feedback. */
/* argc     : number of arguments from command-line. */
/* argv     : array of pointers to arguments values from command-line. */
/* handSize : pointer to variable to store the number of cards in a hand. */
/* nhands   : pointer to variable to store the number of hands. */
int validInput(int argc, char *argv[], int *handSize, int *nhands);
