#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "deck.h"

/** The ranks in a standard deck. */
const char *RANKS[] = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
/** The suits in a standard deck. */
const char *SUITS[] = {"♠", "♥", "♦", "♣"};
/** The number of ranks in a standard deck (13). */
const size_t NUMRANKS = sizeof(RANKS) / sizeof(RANKS[0]);
/** The number of suits in a standard deck (4). */
const size_t NUMSUITS = sizeof(SUITS) / sizeof(SUITS[0]);
/** The number of cards in a standard deck (52). */
const size_t NUMCARDS = NUMRANKS * NUMSUITS;

static card *
card_init(const char *rank, const char *suit)
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
card_kill(card *c)
{
    free(c->rank);
    free(c->suit);
    free(c);
}

static void
card_print(const card *c)
{
    printf("%s%s", c->rank, c->suit);
}

deck *
deck_init(size_t sets)
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
                d->cards[d->top] = card_init(RANKS[j], SUITS[k]);
                ++d->top;
            }
        }
    }
    d->sets = sets;
    d->top = 0;
    return d;
}

void
deck_kill(deck *d)
{
    // Avoid dereferencing a null pointer.
    if (!d) {
        return;
    }
    for (size_t i = 0; i < d->sets * NUMCARDS; ++i) {
        card_kill(d->cards[i]);
    }
    // Free the pointer? Free the pointer to the pointer? I don't even know anymore.
    free(d->cards);
    free(d);
}

bool
deck_isready(const deck *const d)
{
    return deck_isfull(d) && deck_isshuffled(d);
}

bool
deck_isfull(const deck *const d)
{
    return d->top == 0;
}

bool
deck_isempty(const deck *const d)
{
    return d->top == d->sets * NUMCARDS;
}

bool
deck_isordered(const deck *const d)
{
    return true;
}

bool
deck_isshuffled(const deck *const d)
{
    return d->shuffled;
}

void
deck_prepare(deck *d)
{
    d->top = 0;
    deck_shuffle(d);
}

void
deck_shuffle(deck *d)
{
    srand(time(NULL));
    for (size_t i = (d->sets * NUMCARDS) - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        card *temp = d->cards[i];
        d->cards[i] = d->cards[j];
        d->cards[j] = temp;
    }
    d->shuffled = true;
}

card *
deck_draw(deck *d)
{
    if (!deck_isempty(d)) {
        --d->top;
    }
    return d->cards[d->top + 1];
}

void
deck_print(const deck *d)
{
    printf("[");
    for (size_t i = d->top; i < (d->sets * NUMCARDS) - 1; ++i) {
        card_print(d->cards[i]);
        printf(", ");
    }
    card_print(d->cards[(d->sets * NUMCARDS) - 1]);
    printf("]\n");
}
