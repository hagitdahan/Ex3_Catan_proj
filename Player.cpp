#include "Player.hpp"

Player::Player(const std::string name,int id) {
    std::cout << "Player constructed: " << name << std::endl;
    this->name=name;
    this->victoryPoints=0;
    this->isMyTurn=false;
    this->id=id;
    resources[WOOD] = 0;
    resources[BRICK] = 0;
    resources[WOOL] = 0;
    resources[WHEAT] = 0;
    resources[IRON] = 0;
}
void Player::setBoard(Board *board){
    this->board=board;
} 
std::string Player::getName(){
        return this->name;
}
void Player::addResource(ResourceType resource, int amount) {
    resources[resource] += amount;
}
void Player::removeResource(ResourceType resource, int amount){
    resources[resource] -=amount;
}
void Player::setName(std::string name){
    this->name=name;
}
bool Player::canBuildSettlement() const {
    return resources.at(WOOD) >= 1 && resources.at(BRICK) >= 1 && resources.at(WOOL) >= 1 && resources.at(WHEAT) >= 1;
}
bool Player::canBuildRoad() const {
    return resources.at(WOOD) >= 1 && resources.at(BRICK) >= 1;
}
void Player::initializeResources() {
    addResource(WOOD, 2 + 2); // 2 for roads, 2 for settlements
    addResource(BRICK, 2 + 2); // 2 for roads, 2 for settlements
    addResource(WOOL, 2); // 2 for settlements
    addResource(WHEAT, 2); // 2 for settlements
}
void Player::setTurn(bool flag){
    this->isMyTurn=flag;
}
void Player::setOtherPlayers(Player* player1, Player* player2) {
    otherPlayer1 = player1;
    otherPlayer2 = player2;
}
void Player::printReources(){
    std::cout << "Resources for player " << name << ":" << std::endl;
    std::cout << "WOOD: " << resources[WOOD] << std::endl;
    std::cout << "BRICK: " << resources[BRICK] << std::endl;
    std::cout << "WOOL: " << resources[WOOL] << std::endl;
    std::cout << "WHEAT: " << resources[WHEAT] << std::endl;
    std::cout << "IRON: " << resources[IRON] << std::endl;
}
void Player::removeHalfResources() {
    int totalResources = 0;
    for (const auto& resource : resources) {
        totalResources += resource.second;
    }

    if (totalResources > 7) {
        int resourcesToDrop = totalResources / 2;
        std::cout << "Player " << name << " has more than 7 resources and must drop " << resourcesToDrop << " resources." << std::endl;

        for (auto& resource : resources) {
            int dropAmount = std::min(resourcesToDrop / 5, resource.second); // Assuming 5 different resource types
            resource.second -= dropAmount;
            resourcesToDrop -= dropAmount;
        }
    }
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
        this->board->distributeResources(roll);
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
        resources[WOOD]--;
        resources[BRICK]--;
        resources[WOOL]--;
        resources[WHEAT]--;
        board->placeSettlement(this->id,vertexIndex);
    } else {
        std::cout << "Cannot build settlement. Not enough resources or vertex is occupied." << std::endl;
    }
}
void Player::buildRoad(int startVertexIndex, int endVertexIndex) {
    if (canBuildRoad() && isMyTurn) {
        resources[WOOD]--;
        resources[BRICK]--;
        board->placeRoad(startVertexIndex, endVertexIndex,this->id);
    } 
    else {
        std::cout << "Cannot build road. Not enough resources or edge is occupied." << std::endl;
    }
}