/**
 * @file player.h
 * @author Dominic Gomez
 * @date 11 Oct 2018
 * @brief File containing the interface for a blackjack player.
 *
 * @see http://www.github.com/dominicgomez/blackjack
 */

#ifndef player_h
#define player_h

#include "deck.h"

/**
 * @brief A blackjack player.
 */
typedef struct {
    char *name;
    card **hand;
    size_t cards;
} player;

/**
 * @brief Create a blackjack player.
 *
 * @param name The player's name.
 * @return A newly created blackjack player.
 * @see player_kill
 */
player *
player_init(const char *name);

/**
 * @brief Destroy a blackjack player.
 *
 * Free the resources used by the player.
 * @param p The player to destroy.
 */
void
player_kill(player *p);

/**
 * @brief Calculate the value of the player's hand.
 *
 * @param p the player whose hand value to calculate.
 * @return The hand's value.
 */
size_t
player_handvalue(const player *const p);

/**
 * @brief Determine whether the player was dealt a hand whose value totaled 21.
 *
 * @param p The player to check.
 * @return Whether the player's initial hand value totaled 21.
 */
bool
player_blackjack(const player *const p);

/**
 * @brief Determine if the player's hand value has exceeded 21.
 *
 * @param p The player to check.
 * @return Whether the player's hand value has exceeded 21.
 */
bool
player_bust(const player *const p);

/**
 * @brief Take another card from the dealer.
 *
 * @param p The player to hit.
 */
void
player_hit(player *p);

/**
 * @brief Take no more cards.
 *
 * @param p The player to stand.
 */
void
player_stand(player *p);

/**
 * @brief Double the bet amount under the condition that the player receives exactly 1 more card.
 *
 * @param p The player to double down.
 */
void
player_doubledown(player *p);

/**
 * @brief Play two separate hands in the event that the player is dealt cards with equal value.
 *
 * TODO: Explain in detail.
 * @param p The player to split.
 */
void
player_split(player *p);

/**
 * @brief Quit the current hand, surrendering half of the bet to the dealer.
 *
 * @param p The player to surrender.
 */
void
player_surrender(player *p);

#endif
