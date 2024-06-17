#ifndef DEVCARDMANAGER_HPP
#define DEVCARDMANAGER_HPP
#include "Deck.hpp"
#include <iostream>
class Player;
/**
 * @class DevCardManager
 * @brief Manages the use, purchase, addition, and removal of development cards for players.
 */
class DevCardManager{
    public:
    DevCardManager(Deck* deck) : deck(deck) {}
    ~DevCardManager(){
      if(deck!=nullptr){
        this->deck->cleanInstance();
      }
        
    };
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
    // /**
    //  * @brief Uses a development card's effect for the player.
    //  * @param card Pointer to the development card to use.
    //  * @param p Pointer to the player.
    //  */
    DevelopmentCard* getCardFromPlayer(Player *p,DevelopmentCardType type);

    /**
     * @brief Uses a Monopoly development card.
     * 
     * @param resource The type of resource to monopolize.
     * @param p player that want to use
     */
    void useMonopolyCard(ResourceType resource,Player* p);
    
    /**
     * @brief Uses a Road Building development card.
     * 
     * @param verindex1 The index of the first vertex for the first road.
     * @param verindex2 The index of the second vertex for the first road.
     * @param verindex3 The index of the first vertex for the second road.
     * @param verindex4 The index of the second vertex for the second road.
     * @param p player that want to use
     */
    void useRoadBuildingCard(int verindex1, int verindex2, int verindex3, int verindex4,Player* p);
    
    /**
     * @brief Uses a Year of Plenty development card.
     * 
     * @param resource1 The first type of resource to receive.
     * @param resource2 The second type of resource to receive.
     * @param p player that want to use
     */
    void useYearOfPlentyCard(ResourceType resource1, ResourceType resource2,Player* p);
    /**
     * @brief Trades Development Card with another player.
     * @param player pointer to the first player.
     * @param otherPlayer pointer to the other player.
     * @param myDevCard The Card that the player is giving.
     * @param theirDevCard The Card that the player is receiving.
     * @return true if the trade was successful, false otherwise.
     */
    bool tradeDev(Player* player,Player* otherPlayer, DevelopmentCard* myDevCard, DevelopmentCard* theirDevCard);
    
    /**
     * @brief Allows the player to buy a development card from the deck.
     * @param p Pointer to the player.
     */
    void buyDevelopmentCard(Player* p);
    private:
    Deck* deck;
};
#endif