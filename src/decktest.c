#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int main()
{
    printf("Creating empty deck...");
    deck *d = deck_init(1);
    assert(d);
    printf("DONE\n");

    printf("Verifying appropriate top position in deck...");
    assert(d->top == 0);
    printf("DONE\n");
    printf("Verifying appropriate number of sets in deck...");
    assert(d->stddecks == 1);
    printf("DONE\n");
    printf("Verifying deck not shuffled...");
    assert(!d->shuffled);
    printf("DONE\n");

    printf("Verifying deck not ready for use in play in a new game...");
    assert(!deck_good(d));
    printf("DONE\n");
    printf("Verifying deck full...");
    assert(deck_full(d));
    printf("DONE\n");
    printf("Verifying deck not empty...");
    assert(!deck_empty(d));
    printf("DONE\n");
    printf("Verifying deck not shuffled...");
    assert(!deck_shuffled(d));
    printf("DONE\n");

    printf("Unshuffled deck: ");
    deck_print(d);

    printf("Preparing deck for use in play in a new game...");
    deck_prep(d);
    printf("DONE\n");
    printf("Verifying deck ready for use in play in a new game...");
    assert(deck_good(d));
    printf("DONE\n");
    printf("Verifying deck full...");
    assert(deck_full(d));
    printf("DONE\n");
    printf("Verifying deck not empty...");
    assert(!deck_empty(d));
    printf("DONE\n");
    printf("Verifying deck shuffled...");
    assert(deck_shuffled(d));
    printf("DONE\n");

    printf("Shuffled deck: ");
    deck_print(d);

    printf("Drawing card from deck...");
    card c = deck_draw(d);
    printf("DONE\n");
    printf("Drawn card: ");
    card_println(&c);
    printf("Deck: ");
    deck_print(d);

    printf("Drawing card from deck...");
    c = deck_draw(d);
    printf("DONE\n");
    printf("Drawn card: ");
    card_println(&c);
    printf("Deck: ");
    deck_print(d);

    printf("Drawing card from deck...");
    c = deck_draw(d);
    printf("DONE\n");
    printf("Drawn card: ");
    card_println(&c);
    printf("Deck: ");
    deck_print(d);

    printf("Counting remaining cards in deck...");
    int r = deck_remaining(d);
    printf("DONE\n");
    printf("Remaining cards: %d\n", r);
    printf("Drawing all remaining cards from deck...");
    for (int i = 0; i < r; ++i) {
        deck_draw(d);
    }
    printf("DONE\n");
    printf("Counting remaining cards in deck...");
    r = deck_remaining(d);
    printf("DONE\n");
    printf("Remaining cards: %d\n", r);

    printf("Verifying deck not ready for use in play in a new game...");
    assert(!deck_good(d));
    printf("DONE\n");
    printf("Verifying deck not full...");
    assert(!deck_full(d));
    printf("DONE\n");
    printf("Verifying deck empty...");
    assert(deck_empty(d));
    printf("DONE\n");

    printf("Killing deck...");
    deck_kill(d);
    printf("DONE\n");
    // TODO: Why is this still a valid memory address if I set it to null in the destructor?
    /* printf("%p\n", (void *)d); */

    return EXIT_SUCCESS;
}
