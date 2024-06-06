#ifndef LAND_HPP
#define LAND_HPP

#include <vector>
#include "Vertex.hpp"

class Land {
private:
    ResourceType resource;
    int number;
    std::vector<Vertex*> vertices;
public:
    Land(ResourceType res, int num) : resource(res), number(num) {}

    ResourceType getResourceType() const {
        return resource;
    }
    int getLandNumber() const {
        return number;
    }
    void addVertex(Vertex &v){
        v.addResource(resource);
        vertices.push_back(&v);
    }
    const std::vector<Vertex*> getVertices(){
        return this->vertices;
    }
    void printCheckLand(){
        std::cout << "land[0]"<<vertices[0]->getOwner() <<std::endl;
    }
};
#endif // LAND_HPP
