#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum DevelopmentCardType { KNIGHT, VICTORY_POINT, MONOPOLY, ROAD_BUILDING, YEAR_OF_PLENTY };
enum ResourceType { NONE, WOOD, BRICK, WOOL, WHEAT, IRON, DESERT };
class Card {
public:
    virtual ~Card() = default;
};
/**
 * @class ResourceCard
 * @brief Represents a resource card in the game.
 */
class ResourceCard : public Card {
public:
    /**
     * @brief Constructor.
     * @param type The type of resource card.
     */
    ResourceCard(ResourceType type);
    /**
     * @brief Retrieves the type of resource card.
     * @return The type of resource card.
     */
    ResourceType getResourceType() const;

private:
    ResourceType resourceType; //< Type of the resource card.
};
/**
 * @class DevelopmentCard
 * @brief Represents a development card in the game.
 */
class DevelopmentCard : public Card {
public:
    /**
     * @brief Constructor.
     * @param type The type of development card.
     */
    DevelopmentCard(DevelopmentCardType type);

    /**
     * @enum DevelopmentCardType
     * @brief Enumeration representing the types of development cards.
    */
    DevelopmentCardType getDevelopmentCardType() const;

private:
    DevelopmentCardType devCardType;//< Type of the development card.
};

#endif // CARD_H
