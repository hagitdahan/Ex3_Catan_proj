#include "Player.hpp"

Player::Player(){};
Player::Player(const std::string name,int id) {
    std::cout << "Player constructed: " << name << std::endl;
    this->name=name;
    this->victoryPoints=0;
    this->isMyTurn=false;
    this->id=id;
    resourceCards[WOOD] = 0;
    resourceCards[BRICK] = 0;
    resourceCards[WOOL] = 0;
    resourceCards[WHEAT] = 0;
    resourceCards[IRON] = 0;
}
void Player::setBoard(Board *board){
    this->board=board;
} 
void Player::setResManage(ResourceManager* res){
    this->resourceManagerInstance=res;
}
std::string Player::getName(){
        return this->name;
}
int Player::getId(){
    return this->id;
}
bool Player::getTurn(){
    return isMyTurn;
}
void Player::addResourceCard(ResourceType resource, int amount) {
    resourceManagerInstance->addResource(resource,amount,this);
}
void Player::removeResourceCard(ResourceType resource, int amount){
    resourceManagerInstance->removeResource(resource,amount,this);
}
int Player::getResourceCardCount(ResourceType type){
    return resourceManagerInstance->getResourceCount(type,this);
}

// void Player::addDevelopmentCard(DevelopmentCard* card) {
//     developmentCards[card]++;
// }
// void Player::addDevelopmentCard(DevelopmentCard* card) {
//     developmentCards.insert({card, 1});
// }

// void Player::removeDevelopmentCard(DevelopmentCard* card) {
//     if (developmentCards[card] > 0) {
//         developmentCards[card]--;
//         if (developmentCards[card] == 0) {
//             developmentCards.erase(card);
//         }
//     } else {
//         throw std::runtime_error("Development card not found.");
//     }
// }
void Player::setTurn(bool flagTurn){
    this->isMyTurn=flagTurn;
}
void Player::setOtherPlayers(Player* player1, Player* player2){
    this->otherPlayer1=player1;
    this->otherPlayer2=player2;
}
// void Player::useDevelopmentCard(DevelopmentCard* card) {
//     removeDevelopmentCard(card);
//     DevelopmentCardManager::getInstance().useDevelopmentCard(this, card);
// }
void Player::printResources(){
    this->resourceManagerInstance->printResources(this);
}
void Player::initializeResources(){
    this->resourceManagerInstance->initializeResources(this);
 }
// void Player::buyDevelopmentCard() {
//     if (resourceManagerInstance->canAfford("DEVELOPMENT_CARD", this)) {
//         resourceManagerInstance->removeResourcesOfPiece("DEVELOPMENT_CARD", this);
//         DevelopmentCard* newCard = DevelopmentCardManager::getInstance().drawDevelopmentCard();
//         addDevelopmentCard(newCard);
//     } else {
//         std::cout << "Cannot buy development card. Not enough resources." << std::endl;
//     }
// }
// int Player::getDevelopmentCardCount(){
//    return developmentCards.size();
// }
// const std::map<DevelopmentCard*,int>& Player::getDevelopmentCards() const{
//     return developmentCards;
// }
void Player::removeHalfResources() {
    resourceManagerInstance->removeHalfResources(this);
}
int Player::getVictoryPoints() const{
    return this->victoryPoints;
}
void Player::notifyOthers(int roll){
    otherPlayer1->handleRoll(roll);
    otherPlayer2->handleRoll(roll);
}
void Player::handleRoll(int roll){
    if(roll == 7){
        this->removeHalfResources();
    }
    else{

        this->resourceManagerInstance->distributeResources(roll,this);
    }
}
void Player::rollDice() {
    int roll = (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
    std::cout << "Player " << this->name << " rolled " << roll << std::endl; 

    //notify the other players 
    this->notifyOthers(roll);

    //handle the roll for me
    this->handleRoll(roll);
}
void Player::endTurn() {
    if (isMyTurn) {
        isMyTurn = false;
        if (!otherPlayer1->isMyTurn) {
            otherPlayer1->setTurn(true);
        } else {
            otherPlayer2->setTurn(true);
        }
    }
}

void Player::buildSettlement(int vertexIndex) {
    if(vertexIndex<0 || vertexIndex>53 ){
         throw std::runtime_error("Vertex not exsist.");
    }
    else if (resourceManagerInstance->canAfford("SETTLEMENT",this) && isMyTurn) {
        if(board->placeSettlement(this->id,vertexIndex)){
            resourceManagerInstance->removeResourcesOfPiece("SETTLEMENT",this);
            this->victoryPoints+=1;
            if(settlements.size()<=2){
                std::vector<ResourceType> res=board->getVertexResources(vertexIndex);
                this->resourceManagerInstance->distributeResources(res,this);
            }
        }
    } 
    else {
        std::cout << "Cannot build settlement. Not enough resources or Not your turn." << std::endl;
    }
}
void Player::buildRoad(int startVertexIndex, int endVertexIndex) {
    if (resourceManagerInstance->canAfford("ROAD",this) && isMyTurn) {
        if(board->placeRoad(startVertexIndex, endVertexIndex,this->id)){
            resourceManagerInstance->removeResourcesOfPiece("ROAD",this);
        }
    } 
    else {
        std::cout << "Cannot build road. Not enough resources or Not your turn." << std::endl;
    }
}
void Player::buildCity(int vertexIndex) {
    if(vertexIndex < 0 || vertexIndex > 53) {
        throw std::runtime_error("Vertex not exist.");
    }
    else if ((resourceManagerInstance->canAfford("CITY",this)) && isMyTurn) {
        if(board->placeCity(this->id, vertexIndex)){
            resourceManagerInstance->removeResourcesOfPiece("CITY",this);
            this->victoryPoints+=1;
        }
    } else {
        std::cout << "Cannot build city. Not enough resources or it is not your turn." << std::endl;
    }
}

// void Player::useMonopolyCard(ResourceType resource) {
//     int resourceCount1 = otherPlayer1->getResourceCardCount(resource);
//     int resourceCount2 = otherPlayer2->getResourceCardCount(resource);
//     if (resourceCount1 > 0) {
//         otherPlayer1->removeResourceCard(resource, resourceCount1);
//         addResourceCard(resource, resourceCount1);
//     }
//     if (resourceCount2 > 0) {
//         otherPlayer2->removeResourceCard(resource, resourceCount2);
//         addResourceCard(resource, resourceCount2);
//     }
    
// }

// void Player::useRoadBuildingCard(int verindex1,int verindex2,int verindex3,int verindex4) {
//     // Allow the player to build two roads without cost
//     this->buildRoad(verindex1, verindex2); // Build the first road
//     this->buildRoad(verindex3, verindex4); // Build the second road
// }

// void Player::useYearOfPlentyCard(ResourceType resource1, ResourceType resource2) {
//     // Allow the player to take two resources of their choice from the resource bank
//     addResourceCard(resource1, 1);
//     addResourceCard(resource2, 1);
// }

// void Player::useKnightCard() {
//     //Add a knight to the player's knight count
//     this->knightNumber++;
//     if(knightNumber==3){
//         this->victoryPoints+=2;
//         this->knightNumber=0;
//     }
// }

// void Player::useVictoryPointCard() {
//     this->victoryPoints++;
// }