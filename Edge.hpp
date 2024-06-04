#ifndef EDGE_HPP
#define EDGE_HPP
#include "Vertex.hpp"
class Edge {
public:
    Edge() : ownerId(0),piece(nullptr) {}  // Default constructor
    Edge(Vertex &v1, Vertex &v2) : ownerId(0), vertex1(v1), vertex2(v2),piece(nullptr) {}
    
    Vertex getStartVertex() const { return vertex1; }
    Vertex getEndVertex() const { return vertex2; }
    int getOwnerId() const { return ownerId; }
    void setOwnerId(int id) { ownerId = id; }
    int getStartVertexId()const {return vertex1.getVertexId();}
    int getEndVertexId()const {return vertex2.getVertexId();}
    void setPiece(Piece *piece){
        delete this->piece;
        this->piece = piece;
    }
    Piece * getPiece(){
        return this->piece;
    }
private:
    int ownerId;
    Vertex vertex1;
    Vertex vertex2;
    Piece *piece;
};


#endif // EDGE_HPP
