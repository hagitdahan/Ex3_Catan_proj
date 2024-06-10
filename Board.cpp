#include "Board.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

Board::Board() {
    vertices.resize(54); // Ensure vertices vector can hold 54 elements
    initVertices();
    initEdges();
    initTiles();
    connectTiles();
    this->turns=0;
}
Board::~Board() {
    for (auto land : lands) {
        if (land != nullptr) {
            delete land;
            land = nullptr; // Optional, to prevent accidental use after deletion
        }
    }
    
    for (auto edge : edges) {
        if (edge != nullptr) {
            delete edge;
            edge = nullptr; // Optional
        }
    }
    
    for (auto vertex : vertices) {
        if (vertex != nullptr) {
            //delete vertex->getPiece(); // If needed
            delete vertex;
            vertex = nullptr; // Optional
        }
    }
}

void Board::initVertices() {
    // Initialize 54 vertices
    for (int i = 0; i < 54; ++i) {
        vertices[i]=new Vertex(i);
    }
}

void Board::addEdge(int startIndex, int endIndex, int jump) {
        for (int i = startIndex; i < endIndex;) {
            bool edgeExists = false;
            for (auto& edge : edges) {
                if (edge->getStartVertexId() == vertices[i]->getVertexId() && edge->getEndVertexId() == vertices[i + jump]->getVertexId()) {
                    edgeExists = true;
                    break;
                }
            }
            if (!edgeExists) {
                Edge* e = new Edge(*vertices[i], *vertices[i + jump]);
                edges.push_back(e);
                vertices[i]->addEdge(*e);
                vertices[i + jump]->addEdge(*e);
            }
            if(jump==1) i=i+1;
            else i=i+2;
        }
        if(jump!=1){
            Edge* e = new Edge(*vertices[endIndex], *vertices[endIndex + jump]);
            edges.push_back(e);
            vertices[endIndex]->addEdge(*e);
            vertices[endIndex + jump]->addEdge(*e);
        }
}
void Board::initEdges() {
    addEdge(0,6,1);
    addEdge(7,15,1);
    addEdge(16,26,1);
    addEdge(27,37,1);
    addEdge(38,46,1);
    addEdge(47,53,1);
    addEdge(0,6,8);
    addEdge(7,15,10);
    addEdge(16,26,11);
    addEdge(28,36,10);
    addEdge(39,45,8);
}
void Board::initTiles() {
    // Initialize resource tiles with numbers manually
    lands.push_back(new Land(IRON,10));
    lands.push_back(new Land(WOOL,2));
    lands.push_back(new Land(WOOD,9)); 
    lands.push_back(new Land(WHEAT,12)); 
    lands.push_back(new Land(BRICK,6)); 
    lands.push_back(new Land(WOOL,4));
    lands.push_back(new Land(BRICK,10));
    lands.push_back(new Land(WHEAT,9));
    lands.push_back(new Land(WOOD,11)); 
    lands.push_back(new Land(DESERT,0)); 
    lands.push_back(new Land(WOOD,3));
    lands.push_back(new Land(IRON,8));
    lands.push_back(new Land(WOOD,8));
    lands.push_back(new Land(IRON,3));
    lands.push_back(new Land(WHEAT,4));
    lands.push_back(new Land(WOOL,5));
    lands.push_back(new Land(BRICK,5));
    lands.push_back(new Land(WHEAT,6));
    lands.push_back(new Land(WOOL,11));
}
void Board::addVertices(int startVertexIndex, int endVertexIndex, Land* land) {
    for (int i = startVertexIndex; i < 3+startVertexIndex; ++i) {
        land->addVertex(*vertices[i]);
    }
    for (int i = endVertexIndex; i < 3+endVertexIndex; ++i) {
        land->addVertex(*vertices[i]);     
    }
}
void Board::connectTiles() {
    // Manually connect neighboring tiles based on your layout
    // This will depend on the specific layout and vertex/edge connections
    // Here is a simple example connecting first few tiles manually:
    if (lands.size() > 1) {
        addVertices(0,8,lands[0]);
        addVertices(2,10,lands[1]);
        addVertices(4,12,lands[2]);
        addVertices(7,17,lands[3]);
        addVertices(9,19,lands[4]);
        addVertices(11,21,lands[5]);
        addVertices(13,23,lands[6]);
        addVertices(16,27,lands[7]);
        addVertices(18,29,lands[8]);
        addVertices(20,31,lands[9]);
        addVertices(22,33,lands[10]);
        addVertices(24,35,lands[11]);
        addVertices(28,38,lands[12]);
        addVertices(30,40,lands[13]);
        addVertices(32,42,lands[14]);
        addVertices(34,44,lands[15]);
        addVertices(39,47,lands[16]);
        addVertices(41,49,lands[17]);
        addVertices(43,51,lands[18]);
    }
}
bool Board::placeSettlement(int playerId, int vertexId) {
    //Check if the vertex is unoccupied and has at least one adjacent road belonging to the player
    Vertex *vertex = vertices[vertexId];
    if (vertex->getOwner() != 0) {
        std::cout << "Vertex already occupied." << std::endl;
        throw std::runtime_error("Vertex already occupied.");
    }

    //The first round
    if (turns <= 2) {
        Settlement* set = new Settlement(playerId); // Create a settlement object on the heap
        vertex->setPiece(set); // Set the settlement on the vertex
        vertex->setOwner(playerId);
        std::cout << "Settlement placed successfully." << std::endl;
        return true;
    }

    // Check if there is an adjacent road owned by the player
    bool adjacentRoadOwnedByPlayer = false;
    const std::vector<Edge>& edgesVer = vertex->getConnectedEdges();
    for (std::size_t i = 0; i < edgesVer.size(); i++) {
        const Edge& edge = edgesVer[i];
        if (edge.getOwnerId() == playerId) {
            adjacentRoadOwnedByPlayer = true;
            break;
        }
    }

    if (!adjacentRoadOwnedByPlayer) {
        throw std::runtime_error("No adjacent road owned by the player.");
    }

    // Place the settlement
    Settlement* settlement = new Settlement(playerId); // Create a settlement object on the heap
    vertex->setPiece(settlement); // Set the settlement on the vertex
    vertex->setOwner(playerId);
    std::cout << "Settlement placed successfully." << std::endl;
    return true;
}
bool Board::placeRoad(int startVertexIndex, int endVertexIndex, int playerId) {
    std::cout << "Attempting to place road for player " << playerId << " between vertices " << startVertexIndex << " and " << endVertexIndex << std::endl;
    
    if (startVertexIndex < 0 || static_cast<std::size_t>(startVertexIndex) >= vertices.size() || endVertexIndex < 0 || static_cast<std::size_t>(endVertexIndex) >= vertices.size()) {
        std::cout << "Invalid vertex id(s)." << std::endl;
        return false;
    }
    
    for (Edge* edge : edges) {
        if ((edge->getStartVertexId() == startVertexIndex && edge->getEndVertexId() == endVertexIndex) ||
            (edge->getStartVertexId() == endVertexIndex && edge->getEndVertexId() == startVertexIndex)) {
            if (edge->getOwnerId() != 0) {
                std::cout << "Road already exists between the vertices." << std::endl;
                return false;
            } else {
                edge->setOwnerId(playerId);
                cout<<vertices[startVertexIndex]->edges[0].getOwnerId()<<endl;
                cout<<vertices[startVertexIndex]->edges[1].getOwnerId()<<endl;
                Road* road = new Road(playerId);
                // Assuming Edge has a setPiece method
                edge->setPiece(road);
                std::cout << "Road placed successfully." << std::endl;
                return true;
            }
        }
    }
    std::cout << "No existing edge found between the vertices." << std::endl;
    return false;
}
bool Board::placeCity(int playerId, int vertexId) {
    Vertex *vertex = vertices[vertexId];
    if (vertex->getOwner() != playerId) {
        std::cout << "You can't build a city here; this vertex is not yours." << std::endl;
        return false;
    }
   
    Piece* currentPiece = vertex->getPiece();
    if (currentPiece == nullptr || currentPiece->getType() != "SETTLEMENT") {
        std::cout << "You can only build a city on an existing settlement." << std::endl;
        return false;
    }
    delete currentPiece;

    City* city = new City(playerId);
    vertex->setPiece(city);
    
    std::cout << "Settlement upgraded to city successfully." << std::endl;
    return true;
}
void Board::setTurns(int turn){
    this->turns=turn;
}
std::vector<ResourceType> Board::getVertexResources(int vertexIndex) const {
    return vertices[vertexIndex]->getConnectedResources();
}
std::vector<Land*> Board::getLands(){
    return lands;
}
std::vector<Edge*> Board::getEdges(){
    return edges;
}
std::vector<Vertex*> Board::getVertices(){
    return vertices;
}