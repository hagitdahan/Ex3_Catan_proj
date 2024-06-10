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
void Player::setDevManager(DevCardManager* dev){
    this->devMangerInstance=dev;
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

int Player::getDevelopmentCardCount(){
    return this->developmentCards.size();
}
std::vector<DevelopmentCard*> Player::getDevelopmentCards()const{
    return developmentCards;
}
void Player::addDevelopmentCard(DevelopmentCard* card) {
    devMangerInstance->addDevelopmentCard(card,this);
}

void Player::setTurn(bool flagTurn){
    this->isMyTurn=flagTurn;
}

void Player::setOtherPlayers(Player* player1, Player* player2){
    this->otherPlayer1=player1;
    this->otherPlayer2=player2;
}

void Player::useDevelopmentCard(DevelopmentCard* card) {
    devMangerInstance->removeDevelopmentCard(card,this);
    devMangerInstance->useDevelopmentCard(card,this);
}

void Player::printResources(){
    this->resourceManagerInstance->printResources(this);
}

void Player::initializeResources(){
    this->resourceManagerInstance->initializeResources(this);
 }

void Player::buyDevelopmentCard() {
    this->devMangerInstance->buyDevelopmentCard(this);
}

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

void Player::useMonopolyCard(ResourceType resource) {
    int resourceCount1 = otherPlayer1->getResourceCardCount(resource);
    int resourceCount2 = otherPlayer2->getResourceCardCount(resource);

    if (resourceCount1 > 0) {
        otherPlayer1->removeResourceCard(resource, resourceCount1);
        addResourceCard(resource, resourceCount1);
    } else {
        std::cout << "Other Player 1 does not have any " << resource << " cards.\n";
    }

    if (resourceCount2 > 0) {
        otherPlayer2->removeResourceCard(resource, resourceCount2);
        addResourceCard(resource, resourceCount2);
    } else {
        std::cout << "Other Player 2 does not have any " << resource << " cards.\n";
    }
}

void Player::useRoadBuildingCard(int verindex1,int verindex2,int verindex3,int verindex4) {
    // Allow the player to build two roads without cost
    this->resourceManagerInstance->addResourcesOfPiece("ROAD",this);
    this->resourceManagerInstance->addResourcesOfPiece("ROAD",this);
    this->buildRoad(verindex1, verindex2); // Build the first road
    this->buildRoad(verindex3, verindex4); // Build the second road
}

void Player::useYearOfPlentyCard(ResourceType resource1, ResourceType resource2) {
    // Allow the player to take two resources of their choice from the resource bank
    addResourceCard(resource1, 1);
    addResourceCard(resource2, 1);
}

void Player::useKnightCard() {
    // ספירת מספר קלפי האבירים
    int knightCount = 0;
    for (auto card : developmentCards) {
        if (card->getDevelopmentCardType() == KNIGHT) {
            knightCount++;
        }
    }

    // בדיקת תנאי לשימוש בקלף אביר
    if (knightCount >= 3) {
        // הסרת שלושת קלפי האבירים מהשחקן
        int removedKnights = 0;
        for (auto it = developmentCards.begin(); it != developmentCards.end() && removedKnights < 3;) {
            if ((*it)->getDevelopmentCardType() == KNIGHT) {
                it = developmentCards.erase(it);
                removedKnights++;
            } else {
                ++it;
            }
        }

        // הוספת נקודות ניצחון לשחקן
        this->victoryPoints += 2;
        std::cout << "You have used 3 Knight cards and gained 2 Victory Points!" << std::endl;
    } else {
        std::cout << "You cannot use this card. You need 3 Knight cards." << std::endl;
    }
}

bool Player::trade(Player& otherPlayer, ResourceType myResource, int myAmount, ResourceType theirResource, int theirAmount) {
    if (getResourceCardCount(myResource) < myAmount) {
        std::cerr << "Not enough resources to trade." << std::endl;
        return false;
    }
    if (otherPlayer.getResourceCardCount(theirResource) < theirAmount) {
        std::cerr << "Other player does not have enough resources to trade." << std::endl;
        return false;
    }

    removeResourceCard(myResource, myAmount);
    otherPlayer.addResourceCard(myResource, myAmount);

    otherPlayer.removeResourceCard(theirResource, theirAmount);
    addResourceCard(theirResource, theirAmount);

    std::cout << "Trade successful!" << std::endl;
    return true;
}

void Player::useVictoryPointCard() {
    this->victoryPoints++;
}

void Player::addVictoryPointsForTest(int num){
    this->victoryPoints+=num;
}