#include <stdio.h>      /* input/output */
#include <string.h>
#include "deck.h"       /* provides constants */


/* Functions prototypes */
int compareCards(Card *c1, Card *c2);
void bubbleSort(void *arr[], int size, comparator comp);
char *suitName(cardsuit s);
char *rankName(cardrank r);
void printSpaces(int n);
int numberOfDigits(int n);

/* Functions definitions */

/* 
  Compares two cards according to their ranks. 
  In the case c1 and c2 have the same rank, the order
  is decided according to their suits. The convention
  for suits order is:
  clubs < diamonds < hearts < spades.
  The function returns < 0 if c1 is less than c2, 0 if c1 equals c2,
  > 0 if c1 greater than c2.
*/
int compareCards(Card *c1, Card *c2){
    
    int result;
    if((c1 -> rank) == (c2 -> rank)){
        /* decide using suits */
        result = (c1 -> suit) - (c2 -> suit);
    }
    else{
        /* decide using ranks */
        result = (c1 -> rank) - (c2 -> rank);
    }
    return result;
}

/* Bubble sort algorithm. */
/* Adrian Hernandez */
void bubbleSort(void *arr[], int size, comparator comp){
    
    int sorted;         /* flag to indicate whether arr is sorted or not. */
    int pos = size - 1; /* position to fill. */
    
    /* need to loop over the array at least once. */
    do {
        
        /* ensure the algorithm will stop */
        sorted = TRUE;
        
        /* loop */
        int i;
        for (i = 0; i < pos; i ++) {
            if((*comp)(arr[i], arr[i + 1]) > 0){
                
                /* found not sorted elements */
                sorted = FALSE;
                
                /* sort the elements */
                void *temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        
        /* arr[pos] is filled with the right card so decrease pos */
        pos --;
        
    } while (!sorted);
}

/* Return name of n-th suit */
char *suitName(cardsuit n){
    
    static char *names[] = {
        "Invalid suit",
        "CLUBS",
        "DIAMONDS",
        "HEARTS",
        "SPADES"
    };
    
    return (n < CLUBS || n > SPADES) ? names[0] : names[n];
}

/* Return name of n-th rank */
char *rankName(cardrank n){
    
    static char *names[] = {
        "Invalid rank",
        "ACE", "TWO", "THREE", "FOUR",
        "FIVE", "SIX", "SEVEN", "EIGHT",
        "NINE", "TEN", "JACK", "QUEEN",
        "KING"
    };
    return (n < ACE || n > KING) ? names[0] : names[n];
}

/* Return the number if s represents a positive integer. */
/* Return -1 otherwise. */
int stringToNumber(char *s){
    
    int n = 0;        /* number from string */
    int valid = TRUE; /* flag for valid chars in s */
    
    int i;
    for (i = 0; (s[i] != '\0') && valid; i++) {
        if (s[i] < '0' || s[i] > '9'){
            
            /* s[i] is not a digit */
            valid = FALSE;
            n = -1;
        }
        else{
            n = 10 * n + (s[i] - '0');
        }
    }
    return n;
}

/* Prints n white spaces */
void printSpaces(int n){
    
    int i;
    for (i = 1; i <= n; i++){
        printf(" ");
    }
    
}

/* Copy orig into copy */
void copyHand(Hand orig, Hand *copy, int size){
    
    char handName[MAX_HAND_NAME];
    int i;
    for (i = 0; i < size; i++) {
        copy -> cards[i] = orig.cards[i];
        strcpy(copy -> handName, orig.handName);
    }
}

/* Return the number of digits of n */
int numberOfDigits(int n){
    
    int ndigits = 0;
    do {
        ndigits++;
    } while ((n /= 10) != 0);
    
    return ndigits;
}
