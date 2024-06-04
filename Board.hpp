#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "Land.hpp"
#include "Edge.hpp"
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
    // bool placeCity(int playerId,int vertexId);
    void distributeResourceToPlayer(int playerId, ResourceType resource, int amount);
    void distributeResources(int roll);
};


#endif // BOARD_HPP
