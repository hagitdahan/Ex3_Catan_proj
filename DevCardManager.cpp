
#include "DevCardManager.hpp"
#include "Player.hpp"
void DevCardManager::addDevelopmentCard(DevelopmentCard* card, Player* p) {
    p->developmentCards.push_back(card);
}
void DevCardManager::removeDevelopmentCard(DevelopmentCard* card,Player* p){
    auto it = std::find(p->developmentCards.begin(), p->developmentCards.end(), card);
    if (it != p->developmentCards.end()) {
        if(card->getDevelopmentCardType()==KNIGHT){
            p->developmentCards.erase(it);
        }
        p->developmentCards.erase(it);
    } else {
        std::cerr << "Error: Card not found in player's development cards." << std::endl;
    }
}
void DevCardManager::useDevelopmentCard(DevelopmentCard* card, Player* p) {
    switch (card->getDevelopmentCardType()) {
        case MONOPOLY:
        //input prom terminal witch resource the player want
            p->useMonopolyCard(IRON);
            break;
        case ROAD_BUILDING:
        //input from the plyer wich to road to build 4 index
            p->useRoadBuildingCard(30,31,52,53);
            break;
        case YEAR_OF_PLENTY:
            p->useYearOfPlentyCard(WHEAT, WOOL);
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
        DevelopmentCard* newCard = Deck::getInstance()->drawDevelopmentCard();
        if (newCard) {
            addDevelopmentCard(newCard, p);
        }
        else {
            std::cout << "Cannot buy development card. Deck is empty." << std::endl;
        }
    }
}

