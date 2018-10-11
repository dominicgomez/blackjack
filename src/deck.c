#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "deck.h"

static card *
newcard(const char *rank, const char *suit)
{
    card *c = malloc(sizeof(card));
    if (!c) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    c->rank = strndup(rank, strlen(rank));
    if (!c->rank) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    c->suit = strndup(suit, strlen(suit));
    if (!c->suit) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return c;
}

static void
killcard(card *c)
{
    free(c->rank);
    free(c->suit);
    free(c);
}

static void
printcard(const card *c)
{
    printf("%s%s", c->rank, c->suit);
}

static void
swapcards(const card *x, const card *y)
{
    const card *z = x;
    x = y;
    y = z;
}

deck *
newdeck(size_t sets)
{
    deck *d = malloc(sizeof(deck));
    if (!d) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    d->cards = malloc(sizeof(card *) * NUMCARDS * sets);
    if (!d->cards) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    d->top = 0;
    for (size_t i = 0; i < sets; ++i) {
        for (size_t j = 0; j < NUMRANKS; ++j) {
            for (size_t k = 0; k < NUMSUITS; ++k) {
                d->cards[d->top] = newcard(RANKS[j], SUITS[k]);
                ++d->top;
            }
        }
    }
    d->n = NUMCARDS * sets;
    d->shuffled = false;
    return d;
}

void
killdeck(deck *d)
{
    // Avoid dereferencing a null pointer.
    if (!d) {
        return;
    }
    for (size_t i = 0; i < d->n; ++i) {
        killcard(d->cards[i]);
    }
    // Free the pointer? Free the pointer to the pointer? I don't even know anymore.
    free(d->cards);
    free(d);
}

bool
deckisready(const deck *const d)
{
    return deckisfull(d) && d->shuffled;
}

bool
deckisfull(const deck *const d)
{
    return d->top == 0;
}

bool
deckisempty(const deck *const d)
{
    return d->top == d->n;
}

bool
deckisshuffled(const deck *const d)
{
    return d->shuffled;
}

void
preparedeck(deck *d)
{
    d->top = 0;
    shuffledeck(d);
}

void
shuffledeck(deck *d)
{
    srand(time(NULL));
    for (size_t i = d->n - 1; i > 0; --i) {
        int j = rand() % i + 1;
        swapcards(d->cards[j], d->cards[i]);
    }
    d->shuffled = true;
}

const card *const
drawfromdeck(deck *d)
{
    if (!deckisempty(d)) {
        --d->top;
    }
    return d->cards[d->top + 1];
}

void
printdeck(const deck *d)
{
    printf("[");

    printf("]\n");
}
