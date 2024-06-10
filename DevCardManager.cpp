
#include "DevCardManager.hpp"
#include "Player.hpp"
void DevCardManager::addDevelopmentCard(DevelopmentCard* card, Player* p) {
    p->developmentCards.push_back(card);
}
void DevCardManager::removeDevelopmentCard(DevelopmentCard* card,Player* p){
    auto it = std::find(p->developmentCards.begin(), p->developmentCards.end(), card);
    if (it != p->developmentCards.end()) {
        // אם נמצא, מחק אותו מהרשימה
        p->developmentCards.erase(it);
    } else {
        // אם לא נמצא, תדפיס הודעת שגיאה
        std::cerr << "Error: Card not found in player's development cards." << std::endl;
    }
}
void DevCardManager::useDevelopmentCard(DevelopmentCard* card, Player* p) {
    std::string resourceTypeStr, resource1Str, resource2Str;
    ResourceType resourceType, resource1, resource2;
    int verindex1, verindex2, verindex3, verindex4;
    switch (card->getDevelopmentCardType()) {
        case MONOPOLY:
        //input prom terminal witch resource the player want
            std::cout << "Enter the resource type for Monopoly (IRON, WOOL, WHEAT, WOOD, BRICK): ";
            if (resourceTypeStr == "IRON") resourceType = IRON;
            else if (resourceTypeStr == "WOOL") resourceType = WOOL;
            else if (resourceTypeStr == "WHEAT") resourceType = WHEAT;
            else if (resourceTypeStr == "WOOD") resourceType = WOOD;
            else if (resourceTypeStr == "BRICK") resourceType = BRICK;
            else throw std::runtime_error("Unknown resource type.");

            p->useMonopolyCard(resourceType);
            break;
            break;
        case ROAD_BUILDING:
        //input from the plyer wich to road to build 4 index
            std::cout << "Enter the four vertex indices for Road Building (verindex1 verindex2 verindex3 verindex4): ";
            std::cin >> verindex1 >> verindex2 >> verindex3 >> verindex4;

            p->useRoadBuildingCard(verindex1, verindex2, verindex3, verindex4);
            break;
        case YEAR_OF_PLENTY:
        //input from the terminal with resources the player want
            std::cout << "Enter the two resource types for Year of Plenty (resource1 resource2): ";
            std::cin >> resource1Str >> resource2Str;

            if (resource1Str == "IRON") resource1 = IRON;
            else if (resource1Str == "WOOL") resource1 = WOOL;
            else if (resource1Str == "WHEAT") resource1 = WHEAT;
            else if (resource1Str == "WOOD") resource1 = WOOD;
            else if (resource1Str == "BRICK") resource1 = BRICK;
            else throw std::runtime_error("Unknown resource type.");

            if (resource2Str == "IRON") resource2 = IRON;
            else if (resource2Str == "WOOL") resource2 = WOOL;
            else if (resource2Str == "WHEAT") resource2 = WHEAT;
            else if (resource2Str == "WOOD") resource2 = WOOD;
            else if (resource2Str == "BRICK") resource2 = BRICK;
            else throw std::runtime_error("Unknown resource type.");

            p->useYearOfPlentyCard(resource1, resource2);
            break;
        case KNIGHT:
        // Handle KNIGHT card effect
            p->useKnightCard();
            break;
        case VICTORY_POINT:
        // Handle VICTORY_POINT card effect
            p->useVictoryPointCard();
            break;
        default:
            throw std::runtime_error("Unknown development card type.");
        }
}

void DevCardManager::buyDevelopmentCard(Player* p) {
    if(p->resourceManagerInstance->canAfford("DEVELOPMENT_CARD",p)){
        DevelopmentCard* newCard = Deck::getInstance().drawDevelopmentCard();
        if (newCard) {
            addDevelopmentCard(newCard, p);
        }
        else {
            std::cout << "Cannot buy development card. Deck is empty." << std::endl;
        }
    }
}

