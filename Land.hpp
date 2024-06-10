#ifndef LAND_HPP
#define LAND_HPP

#include <vector>
#include "Vertex.hpp"
/**
 * @class Land
 * @brief Represents a land tile on the board.
 */
class Land {
private:
    ResourceType resource;/**< The type of resource produced by the land. */
    int number;/**< The number associated with the land tile. */
    std::vector<Vertex*> vertices;/**< The vertices connected to the land tile. */
public:
    /**
     * @brief Constructor for Land class.
     * @param res The type of resource produced by the land.
     * @param num The number associated with the land tile.
     */
    Land(ResourceType res, int num) : resource(res), number(num) {}
     /**
     * @brief Get the resource type of the land.
     * @return The ResourceType enum value representing the resource type.
     */
    ResourceType getResourceType() const {
        return resource;
    }
      /**
     * @brief Get the number associated with the land tile.
     * @return The number associated with the land tile.
     */
    int getLandNumber() const {
        return number;
    }
      /**
     * @brief Add a vertex connected to the land.
     * @param v Reference to the Vertex object to add.
     */
    void addVertex(Vertex &v){
        v.addResource(resource);
        vertices.push_back(&v);
    }
       /**
     * @brief Get the vertices connected to the land.
     * @return A vector containing pointers to the connected vertices.
     */
    const std::vector<Vertex*> getVertices(){
        return this->vertices;
    }
      /**
     * @brief A function to check the properties of the land (for testing purposes).
     */
    void printCheckLand(){
        std::cout << "land[0]"<<vertices[0]->getOwner() <<std::endl;
    }
};
#endif // LAND_HPP
