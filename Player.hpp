#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <map>
#include <iostream>
#include "Board.hpp"
#include "ResourceManager.hpp"
// #include "DevelopmentCardManager.hpp"
using namespace std;
class Board;
class Player {
public:
    friend class ResourceManager;
    Player();
    Player(const std::string name,int id);
    void setBoard(Board *board);
    std::string getName();
    int getId();
    bool getTurn();
    void buildSettlement(int vertexIndex);
    void buildRoad(int startVertexIndex, int endVertexIndex);
    void buildCity(int vertexIndex); 
    void setTurn(bool flagTurn);
    void setOtherPlayers(Player* player1, Player* player2);
    void addResourceCard(ResourceType resource, int amount);
    void removeResourceCard(ResourceType resource, int amount);
    int getResourceCardCount(ResourceType type);
    void setResManage(ResourceManager* res);
    //int getDevelopmentCardCount();
    //std::map<DevelopmentCard*, int> getDevelopmentCards();
    // void addDevelopmentCard(DevelopmentCard* card);
    // void removeDevelopmentCard(DevelopmentCard* card);
    // void useDevelopmentCard(DevelopmentCard* card);
    // void buyDevelopmentCard();
    // const std::map<DevelopmentCard*,int>& getDevelopmentCards() const;
    void initializeResources();
    void printResources();
    void removeHalfResources();
    // void trade(Player p,string s1,string s2,int n1,int n2);
    int getVictoryPoints() const; 
    void notifyOthers(int roll);
    void handleRoll(int roll);
    void rollDice();
    void endTurn();
    //void useMonopolyCard(ResourceType resource);
    // void useRoadBuildingCard(int verindex1,int verindex2,int verindex3,int verindex4);
    // void useYearOfPlentyCard(ResourceType resource1, ResourceType resource2);
    // void useKnightCard();
    // void useVictoryPointCard();

private:
    bool isMyTurn;
    std::string name;
    int id;
    int knightNumber;
    std::map<ResourceType, int> resourceCards;
    std::map<DevelopmentCard*, int> developmentCards;
    std::vector<Settlement> settlements;
    std::vector<City>cites;
    std::vector<Road> roads;
    int victoryPoints;
    Board *board;
    Player *otherPlayer1;
    Player *otherPlayer2; 
    ResourceManager* resourceManagerInstance;
};

#endif // PLAYER_H
