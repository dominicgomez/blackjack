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

deck *newcard(size_t sets);
void killcard(deck *d);
void printcard(const deck *d);
void deck_shuffle(deck *d, size_t n);
deck *deck_draw(deck *d, size_t n);

#endif
