#include "Deck.hpp"
//declare static instance of the deck
Deck* instance=nullptr;
std::vector<DevelopmentCard*> Deck::developmentCards;//< Vector containing the development cards in the deck.

Deck* Deck::getInstance() {
    if(instance==nullptr){
        instance=new Deck();
    }
   return instance;
}

Deck::Deck() {
    initializeDevelopmentCards();
    shuffleTheDeck();
}
Deck::~Deck() {
    cleanDeck();
}
void Deck::cleanDeck(){
    // Clean up dynamically allocated DevelopmentCard objects
    for (auto card : developmentCards) {
        delete card;
    }
    developmentCards.clear();
}
void Deck::cleanInstance(){
    // Clean up the singleton instance
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
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
}
void Deck::shuffleTheDeck(){
    std::random_device rd;                        // Obtain a random number from hardware
    std::mt19937 g(rd());                         // Seed the generator
    std::shuffle(developmentCards.begin(), developmentCards.end(), g);  // Shuffle the cards
    std::cout << "Deck shuffled." << std::endl;
}

DevelopmentCard* Deck::drawDevelopmentCard() {
    if (developmentCards.empty()) {
        return nullptr;
    }
    
    DevelopmentCard* drawnCard = developmentCards.back();
    developmentCards.pop_back();
    return drawnCard;
}

int Deck::getDeckSize() {
    return developmentCards.size();
}
