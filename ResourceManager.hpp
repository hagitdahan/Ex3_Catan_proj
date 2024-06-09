#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include "Card.hpp"
#include <iostream>
#include <vector>

class Player; // Forward declaration

class ResourceManager{
public:
    ResourceManager();
    void addResource(ResourceType type, int amount, Player *p);
    void removeResource(ResourceType type, int amount, Player *p);
    int getResourceCount(ResourceType type, Player *p);
    bool canAfford(std::string pieceType, Player *player);
    void initializeResources(Player* p);
    void distributeResources(std::vector<ResourceType> resources,Player* p); 
    void printResources(Player* p);
    void removeHalfResources(Player* p);
    void removeResourcesOfPiece(std::string pieceType, Player *player);
    void distributeResources(int roll, Player* p);
private:
    std::map<std::string, std::map<ResourceType, int>> buildingCosts;
};

#endif // RESOURCEMANAGER_HPP
