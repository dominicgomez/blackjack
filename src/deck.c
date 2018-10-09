#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

static const char *RANKS[] = {"A","K","Q","J","10","9","8","7","6","5","4","3","2"};
static const char *SUITS[] = {"♠","♥","♦","♣"};
static const size_t NUMRANKS = sizeof(RANKS) / sizeof(RANKS[0]);
static const size_t NUMSUITS = sizeof(SUITS) / sizeof(SUITS[0]);
static const size_t NUMCARDS = NUMRANKS * NUMSUITS;

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
    d->sets = sets;
    d->pos = 0;
    for (size_t i = 0; i < sets; ++i) {
        for (size_t j = 0; j < NUMRANKS; ++j) {
            for (size_t k = 0; k < NUMSUITS; ++k) {
                d->cards[d->pos] = newcard(RANKS[j], SUITS[k]);
                ++d->pos;
            }
        }
    }
    return d;
}

void
killdeck(deck *d)
{
    for (size_t i = 0; i < NUMCARDS * d->sets; ++i) {
        killcard(d->cards[i]);
    }
    // Free the pointer? Free the pointer to the pointer? I don't even know anymore.
    free(d->cards);
    free(d);
}

void
shuffle(deck *d, size_t n)
{
    d->pos = 0;
}

deck *
draw(deck *d, size_t n)
{
}

void
printdeck(const deck *d)
{
}
