#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <stdexcept>
#include "Land.hpp"
#include "Edge.hpp"
#include "Player.hpp"

class Player;

class Board {
private:
    std::vector<Land*> lands;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;
    int turns;
    void initVertices(); // Method to initialize vertices
    void addEdge(int startIndex,int lastIndex,int jump);
    void initEdges(); // Method to initialize edges
    void initTiles(); // Method to initialize tiles
    void addVertices(int startVertexIndex, int endVertexIndex, Land* land);
    void connectTiles(); // Method to connect neighboring tiles
public:
    Board();
    ~Board();
    void printCheck();
    bool placeSettlement(int playerId, int vertexId);
    bool placeRoad(int startVertexIndex, int endVertexIndex,int playerId);
    bool placeCity(int playerId,int vertexId);
    void setTurns(int turn);
    std::vector<ResourceType> getVertexResources(int indexVertex) const;
    std::vector<Land*> getLands();
    std::vector<Edge*> getEdges();
    std::vector<Vertex*> getVertices();

};


#endif // BOARD_HPP
