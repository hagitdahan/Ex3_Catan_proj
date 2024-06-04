#ifndef CATAN_HPP
#define CATAN_HPP
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.hpp"

class Catan {
public:
    Catan();
    Catan(Player &p1, Player &p2, Player &p3);
    ~Catan(); // Destructor to clean up memory
    void reorderPlayers();
    void ChooseStartingPlayer(); 
    void nextTurn();
    Player* getCurrentPlayer() const;
    Board getBoard();
    void startGame();
    // void trade(Player& player);
    // void build(Player& player);
    // std::vector<Player > getPlayers();
    // void printWinner();
    // void distributeResources(int roll);
    

private:
    Board *board;
    std::vector<Player> players;
    Player* currentPlayer;
    int currentPlayerIndex;
};

#endif // CATAN_HPP
