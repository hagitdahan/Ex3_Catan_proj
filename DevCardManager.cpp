
#include "DevCardManager.hpp"
#include "Player.hpp"
void DevCardManager::addDevelopmentCard(DevelopmentCard* card, Player* p) {
    p->developmentCards.push_back(card);
    if(card->getDevelopmentCardType()==KNIGHT){
        std::cout<<"adding knight card"<<std::endl;
        p->knightNumber++;
        if(p->knightNumber>=3){
            p->victoryPoints+=2;
            p->haveBiggestArmy=true;
        }
    }
}
void DevCardManager::removeDevelopmentCard(DevelopmentCard* card,Player* p){
    auto it = std::find(p->developmentCards.begin(), p->developmentCards.end(), card);
    if (it != p->developmentCards.end()) {
        p->developmentCards.erase(it);
        if(card->getDevelopmentCardType()==KNIGHT){
            std::cout<<"im here"<<std::endl;
            p->knightNumber--;
            if(p->knightNumber<3){
                p->haveBiggestArmy=false;
            }
        }
    } else {
        std::cerr << "Error: Card not found in player's development cards." << std::endl;
    }
}
DevelopmentCard* DevCardManager::getCardFromPlayer(Player* p, DevelopmentCardType type) {
    for (DevelopmentCard* card : p->developmentCards) {
        if (card->getDevelopmentCardType() == type) {
            return card;
        }
    }
    return nullptr;
}
void DevCardManager::useMonopolyCard(ResourceType resource,Player* p){
    DevelopmentCard * monopoly=getCardFromPlayer(p,MONOPOLY);
    if(monopoly==nullptr){
        std::cout<< "You dont have this card"<<std::endl;
    }
    int resourceCount1 = p->otherPlayer1->getResourceCardCount(resource);
    int resourceCount2 = p->otherPlayer2->getResourceCardCount(resource);

    if (resourceCount1 > 0) {
        p->otherPlayer1->removeResourceCard(resource, resourceCount1);
        p->addResourceCard(resource, resourceCount1);
    } else {
        std::cout << "Other Player 1 does not have any " << resource << " cards.\n";
    }

    if (resourceCount2 > 0) {
        p->otherPlayer2->removeResourceCard(resource, resourceCount2);
        p->addResourceCard(resource, resourceCount2);
    } else {
        std::cout << "Other Player 2 does not have any " << resource << " cards.\n";
    }
    removeDevelopmentCard(monopoly,p);
    delete monopoly;
}
void DevCardManager::useRoadBuildingCard(int verindex1, int verindex2, int verindex3, int verindex4,Player* p){
    DevelopmentCard * roadBuild=getCardFromPlayer(p,ROAD_BUILDING);
    if(roadBuild==nullptr){
        std::cout<< "You dont have this card"<<std::endl;
    }
    // Allow the player to build two roads without cost
    p->resourceManagerInstance->addResourcesOfPiece("ROAD",p);
    p->resourceManagerInstance->addResourcesOfPiece("ROAD",p);
    p->buildRoad(verindex1, verindex2); // Build the first road
    p->buildRoad(verindex3, verindex4); // Build the second road
    removeDevelopmentCard(roadBuild,p);
    delete roadBuild;
}
void DevCardManager::useYearOfPlentyCard(ResourceType resource1, ResourceType resource2,Player* p){
    DevelopmentCard * yearsOfPlenty=getCardFromPlayer(p,YEAR_OF_PLENTY);
    if(yearsOfPlenty==nullptr){
        std::cout<< "You dont have this card"<<std::endl;
    }
    p->addResourceCard(resource1, 1);
    p->addResourceCard(resource2, 1);
    removeDevelopmentCard(yearsOfPlenty,p);
    delete yearsOfPlenty;
}
void DevCardManager::buyDevelopmentCard(Player* p) {
    if(p->resourceManagerInstance->canAfford("DEVELOPMENT_CARD",p)){
        DevelopmentCard* newCard = Deck::getInstance()->drawDevelopmentCard();
        if (newCard) {
            addDevelopmentCard(newCard, p);
        }
       // Update the player's knight count or winning points based on the card type
        if (newCard->getDevelopmentCardType() == KNIGHT)
            p->knightNumber++;
        else if (newCard->getDevelopmentCardType() == VICTORY_POINT)
            p->victoryPoints += 1;
        else {
            std::cout << "Cannot buy development card. Deck is empty." << std::endl;
        }
    }
}
bool DevCardManager::tradeDev(Player* player,Player* otherPlayer, DevelopmentCard* myDevCard, DevelopmentCard* theirDevCard){
    DevelopmentCard* dev1=getCardFromPlayer(player,myDevCard->getDevelopmentCardType());
    DevelopmentCard* dev2=getCardFromPlayer(otherPlayer,theirDevCard->getDevelopmentCardType());
    if(dev1 ==nullptr||dev2==nullptr){
        std::cout<<"cant doing this trade"<<std::endl;
        return false;
    }
    removeDevelopmentCard(dev1,player);
    addDevelopmentCard(dev1,otherPlayer);

    removeDevelopmentCard(dev2,otherPlayer);
    addDevelopmentCard(dev2,player);
    if(dev1->getDevelopmentCardType()==KNIGHT){
        otherPlayer->knightNumber++;
        player->knightNumber--;
    }
    if(dev2->getDevelopmentCardType()==KNIGHT){
        otherPlayer->knightNumber--;
        player->knightNumber++;
    }
    std::cout << "Trade successful!" << std::endl;
    return true;


}
