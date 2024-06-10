#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <stdexcept>
#include "Land.hpp"
#include "Edge.hpp"
#include "Player.hpp"
class Player;
/**
 * @class Board
 * @brief Represents the game board of the Catan game.
 */
class Board {
public:
    /**
     * @brief Constructs a new Board object.
     */
    Board();
    /**
     * @brief Destroys the Board object and deallocates memory.
     */
    ~Board();
    /**
     * @brief Places a settlement on the board.
     * @param playerId The ID of the player placing the settlement.
     * @param vertexId The ID of the vertex where the settlement is to be placed.
     * @return True if the settlement was successfully placed, false otherwise.
     */
    bool placeSettlement(int playerId, int vertexId);
      /**
     * @brief Places a road on the board.
     * @param startVertexIndex The index of the starting vertex of the road.
     * @param endVertexIndex The index of the ending vertex of the road.
     * @param playerId The ID of the player placing the road.
     * @return True if the road was successfully placed, false otherwise.
     */
    bool placeRoad(int startVertexIndex, int endVertexIndex,int playerId);
      /**
     * @brief Upgrades a settlement to a city on the board.
     * @param playerId The ID of the player upgrading the settlement.
     * @param vertexId The ID of the vertex where the city is to be built.
     * @return True if the city was successfully built, false otherwise.
     */
    bool placeCity(int playerId,int vertexId);
     /**
     * @brief Sets the number of turns in the game.
     * @param turn The number of turns.
     */
    void setTurns(int turn);
      /**
     * @brief Retrieves the resources connected to a vertex.
     * @param vertexIndex The index of the vertex.
     * @return A vector of ResourceType representing the connected resources.
     */
    std::vector<ResourceType> getVertexResources(int indexVertex) const;
       /**
     * @brief Retrieves the lands (tiles) of the board.
     * @return A vector of Land pointers representing the lands of the board.
     */
    std::vector<Land*> getLands();
     /**
     * @brief Retrieves the edges of the board.
     * @return A vector of Edge pointers representing the edges of the board.
     */
    std::vector<Edge*> getEdges();
     /**
     * @brief Retrieves the vertices of the board.
     * @return A vector of Vertex pointers representing the vertices of the board.
     */
    std::vector<Vertex*> getVertices();
private:
    std::vector<Land*> lands; ///< Vector containing pointers to the lands (tiles) of the board.
    std::vector<Edge*> edges; ///< Vector containing pointers to the edges of the board.
    std::vector<Vertex*> vertices; ///< Vector containing pointers to the vertices of the board.
    int turns;
    /**
     * @brief Initializes the vertices of the board.
     */
    void initVertices(); // Method to initialize vertices
    /**
     * @brief Adds an edge to the board between two vertices.
     * @param startIndex The index of the start vertex.
     * @param endIndex The index of the end vertex.
     * @param jump The number of vertices to jump to reach the next start vertex.
     */
    void addEdge(int startIndex,int lastIndex,int jump);
     /**
     * @brief Initializes the edges of the board.
     */
    void initEdges(); // Method to initialize edges
      /**
     * @brief Initializes the tiles (lands) of the board.
     */
    void initTiles(); // Method to initialize tiles
          /**
     * @brief add Vertices to the land
     */
    void addVertices(int startVertexIndex, int endVertexIndex, Land* land);
      /**
     * @brief Connects the tiles (lands) of the board.
     */
    void connectTiles(); // Method to connect neighboring tiles
};


#endif // BOARD_HPP
