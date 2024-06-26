#include "Catan.hpp"
Catan::Catan(){}
Catan::Catan(Player &p1, Player &p2, Player &p3){
    p1.setOtherPlayers(&p2,&p3);
    p2.setOtherPlayers(&p1,&p3);
    p3.setOtherPlayers(&p1,&p2);
    //init resources to all the players
    p1.initializeResources();
    p2.initializeResources();
    p3.initializeResources();
    
    this->players.push_back(&p1);
    this->players.push_back(&p2);
    this->players.push_back(&p3);
    
    this->board= new Board();
    
    p1.setBoard(this->board);
    p2.setBoard(this->board);
    p3.setBoard(this->board);
    
    this->resoureManage=new ResourceManager();

    p1.setResManage(resoureManage);
    p2.setResManage(resoureManage);
    p3.setResManage(resoureManage);

    this->devManager = new DevCardManager(Deck::getInstance());
    p1.setDevManager(devManager);
    p2.setDevManager(devManager);
    p3.setDevManager(devManager);

    startGame();
}
Catan::~Catan() {
    delete board;
    delete resoureManage;
    delete devManager;
}
void Catan::reorderPlayers() {
    std::rotate(players.begin(), players.begin() + currentPlayerIndex, players.end());
    currentPlayerIndex = 0;
}
void Catan::ChooseStartingPlayer(){
    srand(static_cast<unsigned int>(time(nullptr)));
    currentPlayerIndex = rand() % 3;
    currentPlayer = players[currentPlayerIndex];
    currentPlayer->setTurn(true);
    std::cout << currentPlayer->getName() << " starts the game!" << std::endl;
    reorderPlayers();
    this->board->setTurns(3);
}
void Catan::nextTurn() {
    if (checkVictory(currentPlayer)) {
        std::cout << currentPlayer->getName() << " has won the game!" << std::endl;
        exit(0); // End the game
    }
    currentPlayer->setTurn(false);
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    currentPlayer = players[currentPlayerIndex];
    currentPlayer->setTurn(true);
    std::cout << "It is now " << currentPlayer->getName() << "'s turn." << std::endl;
}
bool Catan::checkVictory(Player* player) {
    return player->getVictoryPoints() >= 10;
}
Player* Catan::getCurrentPlayer() const {
    return currentPlayer;
}
void Catan::startGame(){
    std::cout << "Game started!" << std::endl;
}
Board Catan::getBoard(){
    return *board;
}
