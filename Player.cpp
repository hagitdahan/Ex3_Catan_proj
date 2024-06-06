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
    resourceCards[resource] += amount;
}
void Player::removeResourceCard(ResourceType resource, int amount){
    resourceCards[resource] -=amount;
}
int Player::getResourceCardCount(ResourceType type) const {
    auto it = resourceCards.find(type);
    if (it != resourceCards.end()) {
        return it->second;
    }
    return 0;
}
void Player::addDevelopmentCard(DevelopmentCardType type) {
    developmentCards[type]++;
}
void Player::removeDevelopmentCard(DevelopmentCardType type) {
    if (developmentCards[type] > 0) {
        developmentCards[type]--;
    }
}
int Player::getDevelopmentCardCount(DevelopmentCardType type) const {
    auto it = developmentCards.find(type);
    if (it != developmentCards.end()) {
        return it->second;
    }
    return 0;
}
bool Player::canBuildSettlement() const {
    return resourceCards.at(WOOD) >= 1 && resourceCards.at(BRICK) >= 1 && resourceCards.at(WOOL) >= 1 && resourceCards.at(WHEAT) >= 1;
}
bool Player::canBuildRoad() const {
    return resourceCards.at(WOOD) >= 1 && resourceCards.at(BRICK) >= 1;
}
bool Player::canBuildCity() const {
    return resourceCards.at(IRON) >= 3 && resourceCards.at(WHEAT) >= 2;
}
void Player::initializeResources() {
    addResourceCard(WOOD, 4); // 2 for roads, 2 for settlements
    addResourceCard(BRICK, 4); // 2 for roads, 2 for settlements
    addResourceCard(WOOL, 2); // 2 for settlements
    addResourceCard(WHEAT, 2); // 2 for settlements
}
void Player::setTurn(bool flag){
    this->isMyTurn=flag;
}
void Player::setOtherPlayers(Player* player1, Player* player2) {
    otherPlayer1 = player1;
    otherPlayer2 = player2;
}
void Player::printResources(){
    std::cout << "Resources for player " << name << ":" << std::endl;
    std::cout << "WOOD: " << resourceCards[WOOD] << std::endl;
    std::cout << "BRICK: " << resourceCards[BRICK] << std::endl;
    std::cout << "WOOL: " << resourceCards[WOOL] << std::endl;
    std::cout << "WHEAT: " << resourceCards[WHEAT] << std::endl;
    std::cout << "IRON: " << resourceCards[IRON] << std::endl;
}
void Player::removeHalfResources() {
    int totalResources = 0;
    for (const auto& pair : resourceCards) {
        totalResources += pair.second;
    }

    if (totalResources > 7) {
        int resourcesToDrop = totalResources / 2;
        std::cout << "Player " << name << " has more than 7 resources and must drop " << resourcesToDrop << " resources." << std::endl;

        for (auto& pair : resourceCards) {
            int dropAmount = std::min(resourcesToDrop, pair.second);
            pair.second -= dropAmount;
            resourcesToDrop -= dropAmount;
        }
    }
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
        board->distributeResources(roll,this);
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
    else if (canBuildSettlement() && isMyTurn) {
        if(board->placeSettlement(this->id,vertexIndex)){
            resourceCards[WOOD]--;
            resourceCards[BRICK]--;
            resourceCards[WOOL]--;
            resourceCards[WHEAT]--;
            this->victoryPoints+=1;
        }
    } 
    else {
        std::cout << "Cannot build settlement. Not enough resources or Not your turn." << std::endl;
    }
}
void Player::buildRoad(int startVertexIndex, int endVertexIndex) {
    if (canBuildRoad() && isMyTurn) {
        if(board->placeRoad(startVertexIndex, endVertexIndex,this->id)){
            resourceCards[WOOD]--;
            resourceCards[BRICK]--;
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
    else if (canBuildCity() && isMyTurn) {
        if(board->placeCity(this->id, vertexIndex)){
            resourceCards[IRON] -= 3;
            resourceCards[WHEAT] -= 2;
            this->victoryPoints+=1;
        }
    } else {
        std::cout << "Cannot build city. Not enough resources or it is not your turn." << std::endl;
    }
}
