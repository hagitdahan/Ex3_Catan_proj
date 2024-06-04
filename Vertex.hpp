#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "ResourceType.hpp"
#include "Piece.hpp"

class Edge;
class Vertex {
public:
    int id;
    int owner;
    Piece *piece;
    std::vector<Edge> edges;
    std::vector<ResourceType> connectedResources;
    Vertex():id(0), owner(0), piece(nullptr) {};
    Vertex(int i) : id(i) ,owner(0),piece(nullptr){}
    ~Vertex() {};
    void addEdge(const Edge &e){
        edges.push_back(e);
    }
    const std::vector<Edge>& getConnectedEdges() const {
        return edges;
    }
    void addResource(ResourceType resourceType) {
        connectedResources.push_back(resourceType);
    }
    std::vector<ResourceType> getConnectedResources() const {
        return connectedResources;
    }
    int getVertexId() const {
        return this->id;
    }
    void setOwner(int id){
        this->owner=id;
    }
    int getOwner(){
        return this->owner;
    }
    void setPiece(Piece *piece){
        delete this->piece;
        this->piece = piece;
    }
    Piece * getPiece(){
        return this->piece;
    }
};


#endif // VERTEX_HPP
