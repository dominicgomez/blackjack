#ifndef deck_h
#define deck_h

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char *rank;
    char *suit;
    char *name;
} card;

typedef struct {
    card **cards;
    size_t sets;
    size_t pos;
} deck;

deck *newdeck();
void killdeck(deck *d);
void shuffle(deck *d);
card *draw(deck *d);
void printdeck(const deck *d);

#endif
