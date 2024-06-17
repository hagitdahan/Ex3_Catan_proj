#include "Player.hpp"

Player::Player(){};
Player::Player(const std::string &name,int id) {
    std::cout << "Player constructed: " << name << std::endl;
    this->name=name;
    this->victoryPoints=0;
    this->isMyTurn=false;
    this->id=id;
    this->knightNumber=0;
    this->haveBiggestArmy=false;
}
Player::~Player(){
    for(auto dev:developmentCards){
        if(dev!=nullptr){
            delete dev;
        }   
    }
}

int Player::getResourceCardCountAll(){
    return resourceManagerInstance->getResourceCountAll(this);
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
    } 
    else {
        std::cout << "Cannot build city. Not enough resources or it is not your turn." << std::endl;
    }
}

void Player::useMonopolyCard(ResourceType resource) {
    devMangerInstance->useMonopolyCard(resource,this);
}

void Player::useRoadBuildingCard(int verindex1,int verindex2,int verindex3,int verindex4) {
    devMangerInstance->useRoadBuildingCard(verindex1,verindex2,verindex3,verindex4,this);
}

void Player::useYearOfPlentyCard(ResourceType resource1, ResourceType resource2) {
    // Allow the player to take two resources of their choice from the resource bank
   devMangerInstance->useYearOfPlentyCard(resource1,resource2,this);
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

bool Player::tradeDev(Player& otherPlayer, DevelopmentCard* myDevCard, DevelopmentCard* theirDevCard){
    return devMangerInstance->tradeDev(this,&otherPlayer,myDevCard,theirDevCard);
}

void Player::addVictoryPointsForTest(int num){
    this->victoryPoints+=num;
}

bool Player::getIfhaveBiggestArmy(){
    if(this->knightNumber>=3)return true;
    else return false;
}

