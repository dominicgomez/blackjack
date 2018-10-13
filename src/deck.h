/*!
 * \file deck.h
 * \author Dominic Gomez
 * \date 13 Oct 2018
 * \brief Facilities for creating and manipulating a deck of playing cards.
 *
 * A deck may be initialized with 1 or more standard 52-card decks. If the deck is initialized with 2 standard
 * 52-card decks, for example, it would have 2 aces of spades, 2 aces of hearts, etc.
 */

#ifndef deck_h
#define deck_h

#include <stdbool.h>
#include <stddef.h>

/*! The ranks in a standard deck (A, K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2). */
extern const char *STDDECK_RANKS[];
/*! The suits in a standard deck (♠, ♥, ♦, ♣). */
extern const char *STDDECK_SUITS[];
/*! The number of ranks in a standard deck (13). */
extern const size_t N_STDDECK_RANKS;
/*! The number of suits in a standard deck (4). */
extern const size_t N_STDDECK_SUITS;
/*! The number of cards in a standard deck (52). */
extern const size_t N_STDDECK_CARDS;

/*!
 * \brief A playing card.
 *
 * \note Users shouldn't ever need to instantiate a \c card. They are all instantiated internally, and references
 * to them are returned when necessary. The signature of its constructor function is purposefully omitted.
 */
typedef struct {
    char *rank; //! The card's rank.
    char *suit; //! The card's suit.
} card;

/*!
 * \brief Determine if the card is an ace.
 *
 * \note Outside the context of a card game, an ace has no value, so it doesn't make sense to assign one.
 */
bool
isace(const card *const c);

/*!
 * \brief Determine if the card is a face card.
 *
 * \note Outside the context of a card game, a face card has no value, so it doesn't make sense to assign one.
 */
bool
isface(const card *const c);

/*!
 * \brief Print a playing card to stdout (without a trailing newline).
 *
 * \param c The card to print.
 */
void
printcard(const card *const c);

//! A deck of playing cards.
typedef struct {
    card *cards;    /*!< An ordered collection of every card in the deck, even if it's already been drawn. */
    size_t n_cards; /*!< The number of cards in the deck. */
    size_t top;     /*!< The index of the next card to draw--the "top" of the deck. */
} deck;

/*!
 * \brief Create a deck composed of \p n standard decks.
 *
 * \param n The number of standard decks to include.
 * \return A newly created deck made up of \p n standard 52-card decks.
 * \see prep
 * \see killdeck
 * \warning The deck is not yet ready for use in play in a new game.
 */
deck
initdeck(size_t n);

/*!
 * \brief Destroy a deck.
 *
 * Free the resources used by the deck.
 * \param d The deck to destroy.
 */
void
killdeck(deck *d);

/**
 * \brief Determine whether a deck is full.
 *
 * A deck is full if no cards have been drawn from it.
 * \param d The deck to check.
 * \return Whether the deck is full.
 * \see isempty
 */
bool
isfull(const deck *const d);

/**
 * \brief Determine whether a deck is empty.
 *
 * A deck is empty if all cards have been drawn from it.
 * \param d The deck to check.
 * \return Whether the deck is empty.
 */
bool
isempty(const deck *const d);

/**
 * \brief Determine whether a deck is shuffled.
 *
 * \param d The deck to check.
 * \return Whether the deck is shuffled.
 */
bool
isshuffled(const deck *const d);

/**
 * \brief Determine the number of cards remaining in the deck.
 *
 * \param d The deck to count.
 * \return The number of cards remaining in the deck.
 */
size_t
len(const deck *const d);

/**
 * \brief Shuffle a deck.
 *
 * \param d The deck to shuffle.
 */
void
shuffle(deck *d);

/**
 * \brief Draw a card from the top of the deck.
 *
 * \param d The deck to draw from.
 * \return A pointer to the drawn card.
 */
card
draw(deck *d);

/**
 * \brief Print the remaining cards in the deck in order.
 *
 * \param d The deck to print.
 */
void
printdeck(const deck *d);

#endif
