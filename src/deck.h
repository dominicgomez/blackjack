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
 * @see http://www.github.com/dominicgomez/blackjack
 */

#ifndef deck_h
#define deck_h

#include <stdbool.h>
#include <stddef.h>

/** The ranks in a standard deck (A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2). */
extern const char *STD_RANKS[];
/** The suits in a standard deck (spades, hearts, diamonds, clubs). */
extern const char *STD_SUITS[];
/** The number of ranks in a standard deck (13). */
extern const size_t NUM_STD_RANKS;
/** The number of suits in a standard deck (4). */
extern const size_t NUM_STD_SUITS;
/** The number of cards in a standard deck (52). */
extern const size_t NUM_STD_CARDS;

/**
 * @brief A playing card.
 *
 * @note Users should not instantiate @c card types. They are returned by some @c deck functions.
 */
typedef struct {
    char *rank; /**< The card's rank (A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2). */
    char *suit; /**< The card's suit (spades, hearts, diamonds, clubs) as an icon. */
} card;

/**
 * @brief Determine the card's value.
 *
 * @param c The card to evaluate.
 */
static size_t
card_value(const card *const c);

/**
 * @brief Print a playing card's rank and suit followed by a newline.
 *
 * @param c The card to print.
 */
void
card_println(const card *const c);

/**
 * @brief A deck of standard playing cards.
 */
typedef struct {
    card *cards;        /**< A collection of the cards in the deck from top to bottom. */
    size_t top;         /**< The index of the next card in the deck to be drawn. */
    size_t stddecks;    /**< The number of standard playing card sets in the deck. */
    bool shuffled;      /**< Whether the deck has been shuffled. */
} deck;

/**
 * @brief Create a deck composed of @p n standard decks.
 *
 * @param n The number of standard decks to include.
 * @return A newly created deck with @p n standard decks.
 * @see deck_prep
 * @see deck_kill
 * @warning The deck is not yet ready for use in play in a new game.
 */
deck *
deck_init(size_t n);

/**
 * @brief Destroy a deck.
 *
 * Free the resources used by the deck.
 * @param d The deck to destroy.
 */
void
deck_kill(deck *d);

/**
 * @brief Determine whether a deck is ready for use in play in a new game.
 *
 * A deck is ready for use in play in a new game if it is full and shuffled.
 * @param d The deck to check.
 * @return Whether a deck is ready for use in play in a new game.
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
 * @brief Determine the number of cards initially in the deck.
 *
 * @param d The deck to count.
 * @return The number of cards initially in the deck.
 * @see deck_full
 * @see deck_empty
 */
size_t
deck_count(const deck *const d);

/**
 * @brief Determine the number of cards remaining in the deck.
 *
 * @param d The deck to count.
 * @return The number of cards remaining in the deck.
 * @see deck_full
 * @see deck_empty
 */
size_t
deck_remaining(const deck *const d);

/**
 * @brief Prepare a deck for use in play in a new game.
 *
 * A deck is ready for use in play in a new game if it is full and shuffled.
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
card
deck_draw(deck *d);

/**
 * @brief Print the remaining cards in the deck in order.
 *
 * @param d The deck to print.
 */
void deck_print(const deck *d);

#endif
