#ifndef EDGE_HPP
#define EDGE_HPP
#include "Vertex.hpp"
/**
 * @brief Represents an edge connecting two vertices on the game board.
 */
class Edge {
public:
    /**
     * @brief Default constructor for the Edge class.
     */
    Edge() : ownerId(0),piece(nullptr) {}  // Default constructor
     /**
     * @brief Parameterized constructor for the Edge class.
     * @param v1 The first vertex connected by the edge.
     * @param v2 The second vertex connected by the edge.
     */
    Edge(Vertex *v1, Vertex *v2) : ownerId(0), vertex1(v1), vertex2(v2),piece(nullptr) {}
    /**
     * @brief Destructor for the road on the edge.
     */
    ~Edge(){
        if(piece!=nullptr){
            delete piece;
        }
    }
    /**
     * @brief Gets the starting vertex of the edge.
     * @return The starting vertex of the edge.
     */
    Vertex getStartVertex() const { return *vertex1; }
    /**
     * @brief Gets the ending vertex of the edge.
     * @return The ending vertex of the edge.
     */
    Vertex getEndVertex() const { return *vertex2; }
    /**
     * @brief Gets the ID of the owner of the edge.
     * @return The ID of the owner of the edge.
     */
    int getOwnerId() const { return ownerId; }
    /**
     * @brief Sets the ID of the owner of the edge.
     * @param id The ID of the owner to set.
     */
    void setOwnerId(int id) { ownerId = id; }
    /**
     * @brief Gets the ID of the starting vertex.
     * @return The ID of the starting vertex.
     */
    int getStartVertexId()const {return vertex1->getVertexId();}
      /**
     * @brief Gets the ID of the ending vertex.
     * @return The ID of the ending vertex.
     */
    int getEndVertexId()const {return vertex2->getVertexId();}
      /**
     * @brief Sets the piece (road) on the edge.
     * @param piece The piece (road) to set on the edge.
     */
    void setPiece(Piece *piece){
        delete this->piece;
        this->piece = piece;
    }
    /**
     * @brief Gets the piece (road) on the edge.
     * @return A pointer to the piece (road) on the edge.
     */
    Piece * getPiece(){
        return this->piece;
    }
private:
    int ownerId; /**< The ID of the player who owns the edge. */
    Vertex *vertex1; /**< The first vertex connected by the edge. */
    Vertex *vertex2; /**< The second vertex connected by the edge. */
    Piece *piece; /**< The piece (road) on the edge. */
};


#endif // EDGE_HPP
