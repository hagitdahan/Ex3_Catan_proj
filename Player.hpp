#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <map>
#include <iostream>
#include "Board.hpp"
using namespace std;
class Board;
class Player {
public:
    Player();
    Player(const std::string name,int id);
    void setBoard(Board *board);
    std::string getName();
    int getId();
    bool getTurn();
    bool canBuildSettlement() const;
    bool canBuildRoad() const;
    bool canBuildCity() const;
    std::string ResourceTypeToString(ResourceType type);
    //checing if this is my turn and if i have resiurces.
    void buildSettlement(int vertexIndex);
    void buildRoad(int startVertexIndex, int endVertexIndex);
    void buildCity(int vertexIndex); 
    void setTurn(bool flagTurn);
    void setOtherPlayers(Player* player1, Player* player2);
    void addResourceCard(ResourceType resource, int amount);
    void removeResourceCard(ResourceType resource, int amount);
    int getResourceCardCount(ResourceType type) const;

    void addDevelopmentCard(DevelopmentCardType type);
    void removeDevelopmentCard(DevelopmentCardType type);
    int getDevelopmentCardCount(DevelopmentCardType type) const;
    void initializeResources();
    void printResources();
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
    std::map<ResourceType, int> resourceCards;
    std::map<DevelopmentCardType, int> developmentCards;
    std::vector<Settlement> settlements;
    std::vector<City>cites;
    std::vector<Road> roads;
    int victoryPoints;
    Board *board;
    Player *otherPlayer1;
    Player *otherPlayer2; 
};

#endif // PLAYER_H
