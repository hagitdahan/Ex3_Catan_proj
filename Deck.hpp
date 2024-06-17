#ifndef DECK_HPP
#define DECK_HPP
#include <queue>
#include <random>
#include <algorithm>
#include <iostream>
#include "Card.hpp"
/**
 * @class Deck
 * @brief Represents a deck of development cards in the game.
 */
class Deck {
public:
    //Delete copy contructor 
    Deck(const Deck&) = delete;
    Deck &operator=(const Deck&) = delete; 
    ~Deck();
    /**
     * @brief Retrieves the singleton instance of the deck.
     * @return Reference to the singleton instance of the deck.
     */
    static Deck* getInstance();
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
    /**
     * @brief Clean the instance of Deck
     */
    void cleanInstance();
    

private:
    /**
     * @brief private Constructor.
     * Initializes the deck by creating and shuffling the development cards.
     */
    Deck();  
    /**
     * @brief Initializes the development cards in the deck.
     */
    static void initializeDevelopmentCards();
    /**
     * @brief cleans up the deck
     */
    void cleanDeck();
    static std::vector<DevelopmentCard*> developmentCards;
    
    static void shuffleTheDeck();
};
#endif