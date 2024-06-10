#include "Deck.hpp"

Deck& Deck::getInstance() {
    static Deck instance;
    return instance;
}

Deck::Deck() {
    initializeDevelopmentCards();
}

void Deck::initializeDevelopmentCards() {
    // Clear any existing cards
    developmentCards.clear();

    // Initialize the deck with the appropriate number of each type of card
    for (int i = 0; i < 5; ++i) {
        developmentCards.push_back(new DevelopmentCard(MONOPOLY));
    }
    for (int i = 0; i < 5; ++i) {
        developmentCards.push_back(new DevelopmentCard(ROAD_BUILDING));
    }
    for (int i = 0; i < 5; ++i) {
        developmentCards.push_back(new DevelopmentCard(YEAR_OF_PLENTY));
    }
    for(int i = 0; i < 4; ++i) {
        developmentCards.push_back(new DevelopmentCard(VICTORY_POINT));
    }
    for(int i = 0; i < 6; ++i) {
        developmentCards.push_back(new DevelopmentCard(KNIGHT));
    }
    std::shuffle(developmentCards.begin(), developmentCards.end(), rng);
}

DevelopmentCard* Deck::drawDevelopmentCard() {
    if (developmentCards.empty()) {
        return nullptr;
    }
    
    DevelopmentCard* drawnCard = developmentCards.front();
    developmentCards.pop_back();
    return drawnCard;
}

int Deck::getDeckSize() {
    return developmentCards.size();
}
