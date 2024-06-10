#ifndef DEVCARDMANAGER_HPP
#define DEVCARDMANAGER_HPP
#include "Deck.hpp"
class Player;
/**
 * @class DevCardManager
 * @brief Manages the use, purchase, addition, and removal of development cards for players.
 */
class DevCardManager{
    public:
    DevCardManager(Deck& deck) : deck(deck) {}
       /**
     * @brief Adds a development card to the player's collection.
     * @param card Pointer to the development card to add.
     * @param p Pointer to the player.
     */
    void addDevelopmentCard(DevelopmentCard* card,Player* p);
      /**
     * @brief Removes a development card from the player's collection.
     * @param card Pointer to the development card to remove.
     * @param p Pointer to the player.
     */
    void removeDevelopmentCard(DevelopmentCard* card,Player* p);
    /**
     * @brief Uses a development card's effect for the player.
     * @param card Pointer to the development card to use.
     * @param p Pointer to the player.
     */
    void useDevelopmentCard(DevelopmentCard* card,Player* p);
    /**
     * @brief Allows the player to buy a development card from the deck.
     * @param p Pointer to the player.
     */
    void buyDevelopmentCard(Player* p);
    private:
    Deck& deck;
};
#endif