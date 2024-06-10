#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <map>
#include <iostream>
#include "Board.hpp"
#include "ResourceManager.hpp"
#include "DevCardManager.hpp"
using namespace std;
class Board;
/**
 * @brief The Player class represents a player in the game.
 */
class Player {
public:
    friend class ResourceManager;
    friend class DevCardManager;
    /**
     * @brief Default constructor for the Player class.
     */
    Player();
     /**
     * @brief Constructor for the Player class.
     * 
     * @param name The name of the player.
     * @param id The unique identifier of the player.
     */
    Player(const std::string name,int id);
    /**
     * @brief Sets the game board for the player.
     * 
     * @param board Pointer to the game board.
     */
    void setBoard(Board *board);
    /**
     * @brief Sets the resource manager instance for the player.
     * 
     * @param res Pointer to the resource manager instance.
     */
    void setResManage(ResourceManager* res);
    /**
     * @brief Sets the development card manager instance for the player.
     * 
     * @param dev Pointer to the development card manager instance.
     */
    void setDevManager(DevCardManager* dev);
    /**
     * @brief Gets the name of the player.
     * 
     * @return The name of the player.
     */
    std::string getName();
    /**
     * @brief Gets the unique identifier of the player.
     * 
     * @return The unique identifier of the player.
     */
    int getId();

    /**
     * @brief Checks if it's the player's turn.
     * 
     * @return true if it's the player's turn, false otherwise.
     */
    bool getTurn();

    /**
     * @brief Adds a resource card to the player's inventory.
     * 
     * @param resource The type of resource to add.
     * @param amount The amount of the resource to add.
     */
    void addResourceCard(ResourceType resource, int amount);
        /**
     * @brief Removes a resource card from the player's inventory.
     * 
     * @param resource The type of resource to remove.
     * @param amount The amount of the resource to remove.
     */
    void removeResourceCard(ResourceType resource, int amount);

    /**
     * @brief Retrieves the count of a specific resource type in the player's inventory.
     * 
     * @param type The type of resource.
     * @return The count of the specified resource type.
     */
    int getResourceCardCount(ResourceType type);

    /**
     * @brief Gets the count of development cards owned by the player.
     * 
     * @return The count of development cards.
     */
    int getDevelopmentCardCount();
    /**
     * @brief Gets the development cards owned by the player.
     * 
     * @return A vector containing pointers to the development cards.
     */
    std::vector<DevelopmentCard*> getDevelopmentCards() const;

    /**
     * @brief Adds a development card to the player's collection.
     * 
     * @param card Pointer to the development card to add.
     */
    void addDevelopmentCard(DevelopmentCard* card);

    /**
     * @brief Sets whether it's the player's turn.
     * 
     * @param flagTurn true if it's the player's turn, false otherwise.
     */
    void setTurn(bool flagTurn);
       /**
     * @brief Sets the other players in the game.
     * 
     * @param player1 Pointer to the first other player.
     * @param player2 Pointer to the second other player.
     */
    void setOtherPlayers(Player* player1, Player* player2);

    /**
     * @brief Rolls the dice and handles the consequences of the roll.
     */
    void rollDice();

    /**
     * @brief Handles the consequences of a roll for the player.
     * 
     * @param roll The value rolled on the dice.
     */
    void handleRoll(int roll);

    /**
     * @brief Notifies other players about a roll.
     * 
     * @param roll The value rolled on the dice.
     */
    void notifyOthers(int roll);
    /**
     * @brief Ends the player's turn.
     */
    void endTurn();

    /**
     * @brief Builds a settlement on a specified vertex index.
     * 
     * @param vertexIndex The index of the vertex on which to build the settlement.
     */
    void buildSettlement(int vertexIndex);

    /**
     * @brief Builds a road between two specified vertex indices.
     * 
     * @param startVertexIndex The index of the starting vertex.
     * @param endVertexIndex The index of the ending vertex.
     */
    void buildRoad(int startVertexIndex, int endVertexIndex);

    /**
     * @brief Builds a city on a specified vertex index.
     * 
     * @param vertexIndex The index of the vertex on which to build the city.
     */
    void buildCity(int vertexIndex);
    /**
     * @brief Uses a development card.
     * 
     * @param card Pointer to the development card to use.
     */
    void useDevelopmentCard(DevelopmentCard* card);
    
    /**
     * @brief Buys a development card.
     */
    void buyDevelopmentCard();
    
    /**
     * @brief Initializes the player's resources.
     */
    void initializeResources();
    
    /**
     * @brief Prints the player's resources.
     */
    void printResources();
    
    /**
     * @brief Removes half of the player's resources.
     */
    void removeHalfResources();
    
    /**
     * @brief Trades resources with another player.
     * 
     * @param otherPlayer Reference to the other player.
     * @param myResource The type of resource the player is giving.
     * @param myAmount The amount of the resource the player is giving.
     * @param theirResource The type of resource the player is receiving.
     * @param theirAmount The amount of the resource the player is receiving.
     * @return true if the trade was successful, false otherwise.
     */
    bool trade(Player& otherPlayer, ResourceType myResource, int myAmount, ResourceType theirResource, int theirAmount);
    
    /**
     * @brief Gets the number of victory points the player has earned.
     * 
     * @return The number of victory points.
     */
    int getVictoryPoints() const;
    /**
     * @brief Uses a Monopoly development card.
     * 
     * @param resource The type of resource to monopolize.
     */
    void useMonopolyCard(ResourceType resource);
    
    /**
     * @brief Uses a Road Building development card.
     * 
     * @param verindex1 The index of the first vertex for the first road.
     * @param verindex2 The index of the second vertex for the first road.
     * @param verindex3 The index of the first vertex for the second road.
     * @param verindex4 The index of the second vertex for the second road.
     */
    void useRoadBuildingCard(int verindex1, int verindex2, int verindex3, int verindex4);
    
    /**
     * @brief Uses a Year of Plenty development card.
     * 
     * @param resource1 The first type of resource to receive.
     * @param resource2 The second type of resource to receive.
     */
    void useYearOfPlentyCard(ResourceType resource1, ResourceType resource2);
    
    /**
     * @brief Uses a Knight development card.
     */
    void useKnightCard();
    
    /**
     * @brief Uses a Victory Point development card.
     */
    void useVictoryPointCard();
    
    /**
     * @brief Adds victory points to the player for testing purposes.
     * 
     * @param num The number of victory points to add.
     */
    void addVictoryPointsForTest(int num);
private:
    bool isMyTurn; /**< Flag indicating whether it's the player's turn. */
    std::string name; /**< The name of the player. */
    int id;/**< The unique identifier of the player. */
    int knightNumber;
    std::map<ResourceType, int> resourceCards;/*vector of all the resources of the player*/
    std::vector<DevelopmentCard*> developmentCards;/*vector of all the development card of the player*/
    std::vector<Settlement> settlements;
    std::vector<City>cites;
    std::vector<Road> roads;
    int victoryPoints;/**< The number of victory points earned by the player. */
    Board *board;/**< Pointer to the game board. */
    Player *otherPlayer1;/**< Pointer to the first other player. */
    Player *otherPlayer2; /**< Pointer to the second other player. */
    ResourceManager* resourceManagerInstance;/**< Pointer to the resource manager inst*/
    DevCardManager* devMangerInstance;/**< Pointer to the development card manager instance. */  
};

#endif // PLAYER_H
