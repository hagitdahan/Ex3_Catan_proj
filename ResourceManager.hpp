#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include "Card.hpp"
#include <iostream>
#include <vector>

class Player; // Forward declaration
/**
 * @brief The ResourceManager class manages the resources of players in the game.
 */
class ResourceManager{
public:
    /**
     * @brief Constructs a new ResourceManager object and initializes building costs.
     */
    ResourceManager();
      /**
     * @brief Adds resources of a specified type to a player's inventory.
     * 
     * @param type The type of resource to add.
     * @param amount The amount of the resource to add.
     * @param p Pointer to the player.
     */
    void addResource(ResourceType type, int amount, Player *p);
    /**
     * @brief Removes resources of a specified type from a player's inventory.
     * 
     * @param type The type of resource to remove.
     * @param amount The amount of the resource to remove.
     * @param p Pointer to the player.
     * @throws std::runtime_error if the player does not have enough resources to remove.
     */
    void removeResource(ResourceType type, int amount, Player *p);
     /**
     * @brief Retrieves the count of a specific resource type in a player's inventory.
     * 
     * @param type The type of resource.
     * @param p Pointer to the player.
     * @return The count of the specified resource type.
     */
    int getResourceCount(ResourceType type, Player *p);
    /**
     * @brief Retrieves the count of all Resources of player's inventory.
     * 
     * @param p Pointer to the player.
     * @return The count of all resources.
     */
    int getResourceCountAll(Player* p);
       /**
     * @brief Checks if a player can afford to build a certain type of piece.
     * 
     * @param pieceType The type of piece to build.
     * @param p Pointer to the player.
     * @return true if the player can afford to build the piece, false otherwise.
     */
    bool canAfford(std::string pieceType, Player *player);
    
    /**
     * @brief Initializes resources for a player.
     * 
     * @param player Pointer to the player.
     */
    void initializeResources(Player* p);
       /**
     * @brief Distributes resources to a player based on a given roll value.
     * 
     * @param roll The value rolled on the dice.
     * @param p Pointer to the player.
     */
    void distributeResources(std::vector<ResourceType> resources,Player* p); 
     /**
     * @brief Prints the resources of a player.
     * 
     * @param p Pointer to the player.
     */
    void printResources(Player* p);
    /**
     * @brief Removes half of a player's resources if they have more than 7 resources.
     * 
     * @param p Pointer to the player.
     */
    void removeHalfResources(Player* p);
       /**
     * @brief Removes resources needed to build a specific piece type from a player's inventory.
     * 
     * @param pieceType The type of piece to build.
     * @param p Pointer to the player.
     */
    void removeResourcesOfPiece(std::string pieceType, Player *player);
       /**
     * @brief Adds resources needed to build a specific piece type to a player's inventory.
     * 
     * @param pieceType The type of piece to build.
     * @param p Pointer to the player.
     */
    void addResourcesOfPiece(std::string pieceType, Player *p);
     /**
     * @brief Distributes resources to a player from the lands on the board.
     * 
     * @param resources A vector containing the types of resources distributed.
     * @param p Pointer to the player.
     */
    void distributeResources(int roll, Player* p);
       /**
     * @brief init all the resources of the player to zero.
     * 
     * @param p Pointer to the player.
     */
    void initResources(Player* p);
private:
    std::map<std::string, std::map<ResourceType, int>> buildingCosts;
};

#endif // RESOURCEMANAGER_HPP
