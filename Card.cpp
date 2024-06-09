#include "Card.hpp"

ResourceCard::ResourceCard(ResourceType type) : resourceType(type) {}

ResourceType ResourceCard::getResourceType() const {
    return resourceType;
}

DevelopmentCard::DevelopmentCard(DevelopmentCardType type) : devCardType(type) {}

DevelopmentCardType DevelopmentCard::getDevelopmentCardType() const {
    return devCardType;
}
DevelopmentCard DevelopmentCard::getType(){
    return devCardType;
}

