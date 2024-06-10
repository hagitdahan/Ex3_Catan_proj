#ifndef DECK_HPP
#define DECK_HPP
#include <queue>
#include <random>
#include <algorithm>
#include "Card.hpp"
/**
 * @class Deck
 * @brief Represents a deck of development cards in the game.
 */
class Deck {
public:
    /**
     * @brief Retrieves the singleton instance of the deck.
     * @return Reference to the singleton instance of the deck.
     */
    static Deck& getInstance();
    /**
     * @brief Initializes the development cards in the deck.
     */
    void initializeDevelopmentCards();
     /**
     * @brief Draws a development card from the deck.
     * @return Pointer to the drawn development card.
     */
    DevelopmentCard* drawDevelopmentCard();
      /**
     * @brief Retrieves the size of the deck.
     * @return The size of the deck.
     */
    int getDeckSize();

private:
    /**
     * @brief Constructor.
     * Initializes the deck by creating and shuffling the development cards.
     */
    Deck(); 
    Deck(const Deck&) = delete; 
    void operator=(const Deck&) = delete; 
    std::vector<DevelopmentCard*> developmentCards;//< Vector containing the development cards in the deck.
    std::mt19937 rng;//< Random number generator for shuffling the deck.
};
#endif