#include "ResourceManager.hpp"
#include "Player.hpp"
#include <stdexcept>

ResourceManager::ResourceManager() {
    //Initialize building costs
    buildingCosts["SETTLEMENT"] = {{WOOD, 1}, {BRICK, 1}, {WOOL, 1}, {WHEAT, 1}};
    buildingCosts["ROAD"] = {{WOOD, 1}, {BRICK, 1}};
    buildingCosts["CITY"] = {{IRON, 3}, {WHEAT, 2}};
    buildingCosts["DEVELOPMENT_CARD"]={{IRON,1},{WOOL,1},{WHEAT,1}};
}

void ResourceManager::addResource(ResourceType type, int amount, Player* p) {
    p->resourceCards[type]+=amount;
}

void ResourceManager::removeResource(ResourceType type, int amount, Player* p) {
     if (p->resourceCards[type] >= amount) {
        p->resourceCards[type] -= amount;
    } else {
        throw std::runtime_error("Not enough resources to remove.");
    }
}

int ResourceManager::getResourceCount(ResourceType type, Player* p){
    auto it = p->resourceCards.find(type);
    if (it != p->resourceCards.end()) {
        return it->second;
    }
    return 0;
}
int ResourceManager::getResourceCountAll(Player* p){
    int totalCount = 0;
    for (const auto& resource : p->resourceCards) {
        totalCount += resource.second;
    }
    return totalCount;
}

bool ResourceManager::canAfford(std::string pieceType, Player *p) {
    const auto &costs = buildingCosts.at(pieceType);
    for (const auto &cost : costs) {
        if (p->resourceCards.at(cost.first) < cost.second) {
            return false;
        }
    }
    return true;
}

void ResourceManager::initializeResources(Player * player){
    addResource(WOOD, 4,player); // 2 for roads, 2 for settlements
    addResource(BRICK, 4,player); // 2 for roads, 2 for settlements
    addResource(WOOL, 2,player); // 2 for settlements
    addResource(WHEAT, 2,player); // 2 for settlements
}

void ResourceManager::distributeResources(std::vector<ResourceType> resources,Player* p){
    for(size_t i=0;i<resources.size();i++){
        addResource(resources[i],1,p);
    }
}

void ResourceManager::printResources(Player* p){
    std::cout << "Resources for player " << p->name << ":" << std::endl;
    std::cout << "WOOD: " << p->resourceCards[WOOD] << std::endl;
    std::cout << "BRICK: " << p->resourceCards[BRICK] << std::endl;
    std::cout << "WOOL: " << p->resourceCards[WOOL] << std::endl;
    std::cout << "WHEAT: " << p->resourceCards[WHEAT] << std::endl;
    std::cout << "IRON: " << p->resourceCards[IRON] << std::endl;
}

void ResourceManager::removeHalfResources(Player* p) {
    int totalResources = 0;
    for (const auto& pair : p->resourceCards) {
        totalResources += pair.second;
    }

    if (totalResources >= 7) {
        int resourcesToDrop = totalResources / 2;
        std::cout << "Player " << p->name << " has more than 7 resources and must drop " << resourcesToDrop << " resources." << std::endl;

        for (auto& pair : p->resourceCards) {
            int dropAmount = std::min(resourcesToDrop, pair.second);
            removeResource(pair.first,dropAmount,p);
            resourcesToDrop -= dropAmount;
        }
    }
}

void ResourceManager::removeResourcesOfPiece(std::string pieceType, Player *p){
    const auto& costs = buildingCosts.at(pieceType);
    for (const auto& cost : costs) {
        removeResource(cost.first, cost.second, p);
    }
}

void ResourceManager::addResourcesOfPiece(std::string pieceType, Player *p){
    const auto& costs = buildingCosts.at(pieceType);
    for (const auto& cost : costs) {
        addResource(cost.first, cost.second, p);
    }
}

void ResourceManager::distributeResources(int roll, Player* p) {
    Board* board = p->board;
    std::vector<Land*> lands=board->getLands();
    for (size_t i = 0; i < lands.size(); ++i) {
        Land* currentLand = lands[i];
        if (currentLand->getLandNumber() == roll) {
            std::vector<Vertex*> landVertices = currentLand->getVertices();
            for (Vertex* vertex : landVertices) {
                if (vertex->getOwner() == p->getId()) {
                    std::vector<ResourceType> resourceVer = vertex->getConnectedResources();
                    // Add resources
                    if (vertex->getPiece()->getType() == "SETTLEMENT") {
                        for (size_t j = 0; j < resourceVer.size(); j++) {
                            addResource(resourceVer.at(j), 1, p);
                            std::cout << p->getName() << " received 1 resource of type " << resourceVer.at(j) << std::endl;
                        }
                    } else if (vertex->getPiece()->getType() == "CITY") {
                        for (size_t j = 0; j < resourceVer.size(); j++) {
                            addResource(resourceVer.at(j), 2, p);
                            std::cout << p->getName() << " received 2 resources of type " << resourceVer.at(j) << std::endl;
                        }
                    }
                }
            }
        }
    }
}