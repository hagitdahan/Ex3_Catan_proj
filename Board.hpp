#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <stdexcept>
#include "Land.hpp"
#include "Edge.hpp"
#include "Card.hpp"
#include "Player.hpp"

class Player;

class Board {
private:
    std::vector<Land*> lands;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    std::map<ResourceType, std::vector<ResourceCard>> resourceCardsMap;
    std::map<DevelopmentCardType, std::vector<DevelopmentCard>> developmentCardsMap;
    int turns;
    void initVertices(); // Method to initialize vertices
    void addEdge(int startIndex,int lastIndex,int jump);
    void initEdges(); // Method to initialize edges
    void initTiles(); // Method to initialize tiles
    void addVertices(int startVertexIndex, int endVertexIndex, Land* land);
    void connectTiles(); // Method to connect neighboring tiles
    void initCards();

    
public:
    Board();
    ~Board();
    void printCheck();
    bool placeSettlement(int playerId, int vertexId);
    bool placeRoad(int startVertexIndex, int endVertexIndex,int playerId);
    bool placeCity(int playerId,int vertexId);
    void distributeResources(int roll,Player* player);
    void setTurns(int turn);
};


#endif // BOARD_HPP
