/**
 * @file deck.h
 * @author Dominic Gomez
 * @date 11 Oct 2018
 * @brief File containing the interface for a deck of standard playing cards.
 *
 * Constants, data structures, and functions to create, observe, manipulate, and destroy decks of standard playing
 * cards. The playing cards have standard ranks and suits, but the decks are not necessarily standard in that they
 * may be composed of more than one standard deck because casino games (for which these utilities were intended)
 * often use more than one set of standard playing cards in each deck.
 * @see http://www.github.com/dominicgomez
 */

#ifndef deck_h
#define deck_h

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief A playing card.
 *
 * @note Users should not instantiate @c card types. They are returned by some @c deck functions.
 */
typedef struct {
    char *rank; /**< The card's rank (A, K, Q, ..., 3, 2). */
    char *suit; /**< The card's suit (spades, hearts, diamonds, clubs) as an icon. */
} card;

/** * The deck may be composed of one or more standard decks.
 */
typedef struct {
    card *cards;        /**< A collection of the cards in the deck from top to bottom. */
    size_t top;         /**< The index of the next card in the deck to be drawn. */
    size_t stddecks;    /**< The number of standard playing card sets in the deck. */
} deck;

/**
 * @brief Create a deck composed of @p n standard decks.
 *
 * @param n The number of standard decks to include.
 * @return A newly created deck with @p n standard decks.
 * @see deck_prep
 * @see deck_kill
 * @warning The deck is not yet ready for use in play.
 */
deck *
deck_init(size_t n);

/**
 * @brief Destroy a deck.
 *
 * Free the resources used by the deck (i.e. the heap space used to store card objects).
 * @param d The deck to destroy.
 */
void
deck_kill(deck *d);

/**
 * @brief Determine whether a deck is ready for use in play.
 *
 * A deck is ready for use in play if it is full and shuffled.
 * @param d The deck to check.
 * @return Whether a deck is ready for use in play.
 * @see deck_full
 * @see deck_shuffled
 */
bool
deck_good(const deck *const d);

/**
 * @brief Determine whether a deck is full.
 *
 * A deck is full if no cards have been drawn from it.
 * @param d The deck to check.
 * @return Whether the deck is full.
 * @see deck_empty
 */
bool
deck_full(const deck *const d);

/**
 * @brief Determine whether a deck is empty.
 *
 * A deck is empty if all cards have been drawn from it.
 * @param d The deck to check.
 * @return Whether the deck is empty.
 * @see deck_full
 */
bool
deck_empty(const deck *const d);

/**
 * @brief Determine whether a deck is shuffled.
 *
 * @param d The deck to check.
 * @return Whether the deck is shuffled.
 * @see deck_shuffle
 */
bool
deck_shuffled(const deck *const d);

/**
 * @brief Prepare a deck for use in play.
 *
 * A deck is ready for use in play if it is full and shuffled.
 * @param d The deck to prepare.
 * @see deck_full
 * @see deck_shuffled
 */
void
deck_prep(deck *d);

/**
 * @brief Shuffle a deck.
 *
 * @param d The deck to shuffle.
 */
void
deck_shuffle(deck *d);

/**
 * @brief Draw a card from the top of the deck.
 *
 * @param d The deck to draw from.
 * @return A pointer to the drawn card.
 */
card *
deck_draw(deck *d);

/**
 * @brief Print the remaining cards in the deck in order.
 *
 * @param d The deck to print.
 */
void deck_print(const deck *d);

#endif
