/**
 * @file deck.h
 * @author Dominic Gomez
 * @date 11 Oct 2018
 * @brief File containing the interface for a deck of playing cards.
 *
 * Constants, data structures, and functions to create, observe, manipulate, and destroy decks of playing cards.
 * The playing cards have standard ranks and suits, but the decks are not necessarily standard in that they may be
 * composed of more than one standard deck because casino games (for which these utilities were intended) often use
 * more than one set of standard playing cards.
 * @see http://www.github.com/dominicgomez
 */

#ifndef deck_h
#define deck_h

/** @file */

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief A playing card.
 */
typedef struct {
    char *rank; /**< The card's rank (A, K, Q, ..., 3, 2). */
    char *suit; /**< The card's suit icon (spades, hearts, diamonds, clubs). */
} card;

/**
 * @brief A standard 52-card deck of cards.
 */
typedef struct {
    card **cards;   /**< An ordered (top to bottom) collection of the cards in the deck. */
    size_t sets;    /**< The number of sets in the deck. */
    size_t top;     /**< The index of the next card in the deck to be drawn. */
} deck;

/**
 * @brief Create a (multi)deck with @p n standard decks.
 *
 * @param sets The number of standard decks to include.
 * @return A newly created deck with @p n standard decks.
 * @see getready
 * @warning The deck is not ready to draw from.
 */
deck *deck_init(size_t sets);

/**
 * @brief Destroy a deck.
 *
 * @param d The deck to destroy.
 */
void deck_kill(deck *d);

/**
 * @brief Determine whether a deck is ready to draw from.
 *
 * @param d The deck to check.
 */
bool deck_isready(const deck *const d);

/**
 * @brief Determine whether a deck has not been drawn from.
 *
 * @param d The deck to check.
 */
bool deck_isfull(const deck *const d);

/**
 * @brief Determine whether all the cards in a deck have been drawn.
 *
 * @param d The deck to check.
 */
bool deck_isempty(const deck *const d);

/**
 * @brief Determine whether a deck is ordered.
 *
 * @param d The deck to check.
 */
bool deck_isordered(const deck *const d);

/**
 * @brief Determine whether a deck is shuffled.

 * @param d The deck to check.
 */
bool deck_isshuffled(const deck *const d);

/**
 * @brief Get a deck ready to draw from.
 *
 * @param d The deck to prepare.
 */
void deck_prepare(deck *d);

/**
 * @brief Shuffle a deck.
 *
 * @param d The deck to shuffle.
 */
void deck_shuffle(deck *d);

/**
 * @brief Draw @p n cards from the top of the deck.
 *
 * @param d The deck to draw from.
 */
card *deck_draw(deck *d);

/**
 * @brief Print the deck's cards from top to bottom to stdout.
 *
 * @param d The deck to print.
 */
void deck_print(const deck *d);

#endif
