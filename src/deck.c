#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "deck.h"

const char *STD_RANKS[] = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
const char *STD_SUITS[] = {"♠", "♥", "♦", "♣"};
const size_t NUM_STD_RANKS = sizeof(STD_RANKS) / sizeof(STD_RANKS[0]);
const size_t NUM_STD_SUITS = sizeof(STD_SUITS) / sizeof(STD_SUITS[0]);
const size_t NUM_STD_CARDS = NUM_STD_RANKS * NUM_STD_SUITS;

static card
card_init(const char *rank, const char *suit)
{
    card c;
    c.rank = strndup(rank, strlen(rank));
    c.suit = strndup(suit, strlen(suit));
    return c;
}

static void
card_kill(card *c)
{
    free(c->rank);
    c->rank = NULL;
    free(c->suit);
    c->suit = NULL;
}

static void
card_print(const card *const c)
{
    printf("%s%s", c->rank, c->suit);
}

void
card_println(const card *const c)
{
    card_print(c);
    printf("\n");
}

deck *
deck_init(size_t stddecks)
{
    deck *d = malloc(sizeof(deck));
    if (!d) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    d->cards = malloc(sizeof(card) * stddecks * NUM_STD_CARDS);
    if (!d->cards) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    d->top = 0;
    for (size_t i = 0; i < stddecks; ++i) {
        for (size_t j = 0; j < NUM_STD_RANKS; ++j) {
            for (size_t k = 0; k < NUM_STD_SUITS; ++k) {
                d->cards[d->top] = card_init(STD_RANKS[j], STD_SUITS[k]);
                ++d->top;
            }
        }
    }
    d->top = 0;
    d->stddecks = stddecks;
    d->shuffled = false;
    return d;
}

void
deck_kill(deck *d)
{
    // Avoid dereferencing a null pointer.
    if (!d) {
        return;
    }
    for (size_t i = 0; i < d->stddecks * NUM_STD_CARDS; ++i) {
        card_kill(&d->cards[i]);
    }
    free(d->cards);
    d->cards = NULL;
    free(d);
    d = NULL;
}

bool
deck_good(const deck *const d)
{
    return deck_full(d) && deck_shuffled(d);
}

bool
deck_full(const deck *const d)
{
    return deck_remaining(d) == deck_count(d);
}

bool
deck_empty(const deck *const d)
{
    return deck_remaining(d) == 0;
}

bool
deck_shuffled(const deck *const d)
{
    return d->shuffled;
}

size_t
deck_count(const deck *const d)
{
    return d->stddecks * NUM_STD_CARDS;
}

size_t
deck_remaining(const deck *const d)
{
    return deck_count(d) - d->top;
}

void
deck_prep(deck *d)
{
    d->top = 0;
    deck_shuffle(d);
}

void
deck_shuffle(deck *d)
{
    srand(time(NULL));
    for (size_t i = (d->stddecks * NUM_STD_CARDS) - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        // TODO: Make swap its own function. I can't figure out how to make it persistent.
        card temp = d->cards[i];
        d->cards[i] = d->cards[j];
        d->cards[j] = temp;
    }
    d->top = 0;
    d->shuffled = true;
}

card
deck_draw(deck *d)
{
    if (!deck_empty(d)) {
        ++d->top;
    }
    return d->cards[d->top - 1];
}

void
deck_print(const deck *d)
{
    printf("[");
    for (size_t i = d->top; i < (d->stddecks * NUM_STD_CARDS) - 1; ++i) {
        card_print(&d->cards[i]);
        printf(", ");
    }
    card_print(&d->cards[(d->stddecks * NUM_STD_CARDS) - 1]);
    printf("]\n");
}
