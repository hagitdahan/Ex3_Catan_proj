#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "Card.hpp"
#include "Piece.hpp"

class Edge;
/**
 * @brief Represents a vertex on the game board.
 */
class Vertex {
public:
    int VertexId; /**< The unique identifier of the vertex. */
    int owner; /**< The ID of the player who owns this vertex. */
    Piece *piece; /**< The piece (settlement or city) built on this vertex. */
    std::vector<Edge*> edges; /**< The edges connected to this vertex. */
    std::vector<ResourceType> connectedResources; /**< The types of resources connected to this vertex. */
     /**
     * @brief Default constructor for the Vertex class.
     */
    Vertex():VertexId(0), owner(0), piece(nullptr) {};
    /**
     * @brief Parameterized constructor for the Vertex class.
     * @param index The ID of the vertex.
     */
    Vertex(int index) : VertexId(index) ,owner(0),piece(nullptr){}
     /**
     * @brief Destructor for the Vertex class.
     */
    ~Vertex() {};
    /**
     * @brief Adds an edge to the list of connected edges.
     * @param e The edge to add.
     */
    void addEdge(Edge *edge){
        edges.push_back(edge);
    }
    /**
     * @brief Returns a vector of connected edges.
     * @return A constant reference to the vector of connected edges.
     */
    const std::vector<Edge*>& getConnectedEdges() const {
        return edges;
    }
    /**
     * @brief Adds a connected resource to the vertex.
     * @param resourceType The type of resource to add.
     */
    void addResource(ResourceType resourceType) {
        connectedResources.push_back(resourceType);
    }
    /**
     * @brief Returns a vector of connected resources.
     * @return A vector of connected resource types.
     */
    std::vector<ResourceType> getConnectedResources() const {
        return connectedResources;
    }
    /**
     * @brief Gets the ID of the vertex.
     * @return The ID of the vertex.
     */
    int getVertexId() const {
        return this->VertexId;
    }
    /**
     * @brief Sets the owner of the vertex.
     * @param id The ID of the player who owns the vertex.
     */
    void setOwner(int ownerId){
        this->owner=ownerId;
    }
    /**
     * @brief Gets the ID of the owner of the vertex.
     * @return The ID of the player who owns the vertex.
     */
    int getOwner() const{
        return this->owner;
    }
    /**
     * @brief Sets the piece (settlement or city) on the vertex.
     * @param piece The piece to set on the vertex.
     */
    void setPiece(Piece *piece){
        this->piece = piece;
    }
    /**
     * @brief Gets the piece (settlement or city) on the vertex.
     * @return A pointer to the piece on the vertex.
     */
    Piece * getPiece() const{
        return this->piece;
    }
};


#endif // VERTEX_HPP
