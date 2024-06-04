#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <map>
#include <iostream>
#include "Card.hpp"
#include "Board.hpp"
using namespace std;

class Player {
public:
    Player(const std::string name,int id);
    void setBoard(Board *board);
    std::string getName();
    void setName(std::string name);
    bool canBuildSettlement() const;
    bool canBuildRoad() const;
    bool canBuildCity() const;
    //checing if this is my turn and if i have resiurces.
    void buildSettlement(int vertexIndex);
    void buildRoad(int startVertexIndex, int endVertexIndex);
    void buildCity(int vertexIndex); 
    void setTurn(bool flagTurn);
    void setOtherPlayers(Player* player1, Player* player2);
    void addResource(ResourceType resource, int amount);
    void removeResource(ResourceType resource, int amount);
    void initializeResources();
    void printReources();
    void removeHalfResources();
    // void buyDevelopmentCard();
    // void useDevelopmentCard(DevelopmentCardType type);
    // void trade(Player p,string s1,string s2,int n1,int n2);
    int getVictoryPoints() const; 
    void notifyOthers(int roll);
    void handleRoll(int roll);
    void rollDice();
    void endTurn();

private:
    bool isMyTurn;
    std::string name;
    int id;
    std::map<ResourceType, int> resources;
    std::vector<Settlement> settlements;
    std::vector<City>cites;
    std::vector<Road> roads;
    int victoryPoints;
    std::vector<DevelopmentCard> developmentCards;
    Board *board;
    Player *otherPlayer1;
    Player *otherPlayer2; 
    void incrementVictoryPoints(int points);
    void decrementVictoryPoints(int points);
};

#endif // PLAYER_H
