#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum DevelopmentCardType { KNIGHT, VICTORY_POINT, MONOPOLY, ROAD_BUILDING, YEAR_OF_PLENTY };
enum ResourceType { NONE, WOOD, BRICK, WOOL, WHEAT, IRON, DESERT };
class Card {
public:
    virtual ~Card() = default;
};

class ResourceCard : public Card {
public:
    ResourceCard(ResourceType type);
    ResourceType getResourceType() const;

private:
    ResourceType resourceType;
};

class DevelopmentCard : public Card {
public:
    DevelopmentCard(DevelopmentCardType type);
    DevelopmentCardType getDevelopmentCardType() const;
    DevelopmentCard getType();

private:
    DevelopmentCardType devCardType;
};

#endif // CARD_H
