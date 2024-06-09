#include "doctest.h"
#include "Player.hpp"
#include "Catan.hpp"
using namespace std;

TEST_CASE("Test class player"){
    //checking adding and remove resources
    ResourceManager *res=new ResourceManager();
    Player player("Alice", 1);
    player.setResManage(res);
    player.addResourceCard(WOOD, 3);
    player.addResourceCard(BRICK, 2);
    CHECK(player.getResourceCardCount(WOOD) == 3);
    CHECK(player.getResourceCardCount(BRICK) == 2);
    CHECK(player.getResourceCardCount(WOOL) == 0); // No wool added yet
    player.removeResourceCard(WOOD, 1);
    player.removeResourceCard(BRICK, 1);
    CHECK(player.getResourceCardCount(WOOD) == 2);
    CHECK(player.getResourceCardCount(BRICK) == 1);
    CHECK(player.getResourceCardCount(WOOL) == 0); // No wool removed yet
    
    //Building settlement with enough resources
    Player player2("Bob", 2);
    player2.setResManage(res);
    Board *b=new Board();
    player2.setBoard(b);
    player2.setTurn(true);

    player2.addResourceCard(WOOD, 1);
    player2.addResourceCard(BRICK, 1);
    player2.addResourceCard(WOOL, 1);
    player2.addResourceCard(WHEAT, 1);
    player2.buildSettlement(0); // Assuming vertex index 0 is available

    CHECK(player2.getResourceCardCount(WOOD) == 0);
    CHECK(player2.getResourceCardCount(BRICK) == 0);
    CHECK(player2.getResourceCardCount(WOOL) == 0);
    CHECK(player2.getResourceCardCount(WHEAT) == 0);
    //Assuming building a settlement gives the player 1 victory point
    CHECK(player2.getVictoryPoints() == 1);
}
TEST_CASE("Test class Vertex"){
    Board *b=new Board();
    CHECK_EQ(b->getVertices().size(),54);
}
TEST_CASE("Test class Edge"){
    Board* b=new Board();
    CHECK_EQ(b->getEdges().size(),72);
}
TEST_CASE("Test class Land"){
    
}
TEST_CASE("Test class Catan"){
    
} 
TEST_CASE("Test class Board"){
    
}
TEST_CASE("Test class DevelopentCardManage"){
    
}
TEST_CASE("Test Roll dice"){
    Player p1("mit",10);
    Player p2("Yoss",20);
    Player p3("Dan",30);
    Catan catan(p1, p2, p3);

    p1.setTurn(true);
    p1.buildSettlement(0);
    p1.buildSettlement(3);
    p1.buildRoad(0,1);
    p1.buildRoad(5,6);
    p1.setTurn(false);
    p1.printResources();

    p2.setTurn(true);
    p2.buildSettlement(2);
    p2.buildSettlement(6);
    p2.buildRoad(2,10);
    p2.buildRoad(19,20);
    p2.addResourceCard(IRON,4);
    p2.printResources();
    //p2 need to remove 3 resorces
    p2.handleRoll(7);
    CHECK(p2.getResourceCardCount(IRON)==4);
    p2.setTurn(false);

    p3.setTurn(true);
    p3.buildSettlement(50);
    p3.buildSettlement(43);
    p3.buildRoad(22,23);
    p3.buildRoad(14,15);
    p3.addResourceCard(WHEAT,4);
    p3.setTurn(false);

    p2.setTurn(true);
    p2.addResourceCard(IRON,4);
    p1.addResourceCard(IRON,4);
    //p2 and p1 neet to remove half resources
    p2.notifyOthers(7);
    p2.handleRoll(7);
    p2.printResources();
    p1.printResources();
    p2.setTurn(false);
    CHECK(p2.getResourceCardCount(IRON)==4);
    CHECK(p1.getResourceCardCount(IRON)==5);
    CHECK(p1.getResourceCardCount(WOOL)==1);

}
TEST_CASE("Testing turn order in Catan game") {

    Player player1("Alice", 1);
    Player player2("Bob", 2);
    Player player3("Charlie", 3);
    Catan game(player1,player2,player3);

    game.ChooseStartingPlayer();
    Player* startingPlayer = game.getCurrentPlayer();
    CHECK(startingPlayer->getTurn() == true);
    startingPlayer->endTurn();
    CHECK(startingPlayer->getTurn() == false);
    startingPlayer->setTurn(true);
    int numTurns = 6;

    for (int i = 0; i < numTurns; ++i) {
        Player* currentPlayer = game.getCurrentPlayer();
        CHECK(currentPlayer->getTurn() == true);
        game.nextTurn();
        CHECK(currentPlayer->getTurn() == false);
        Player* nextPlayer = game.getCurrentPlayer();
        CHECK(nextPlayer->getTurn() == true);
        CHECK(nextPlayer != currentPlayer); // לוודא שהשחקן הנוכחי שונה מהשחקן הבא
    }
}
TEST_CASE("number of victory point"){
    Player p1("Amit",10);
    Player p2("Yossi",20);
    Player p3("Dana",30);
    Catan catan(p1, p2, p3);
    
    p1.setTurn(true);
    p1.buildSettlement(0);
    p1.buildSettlement(3);
    p1.buildRoad(0,1);
    p1.buildRoad(5,6);
    CHECK(p1.getVictoryPoints()==2);
    p1.setTurn(false);

    p2.setTurn(true);
    p2.buildSettlement(2);
    p2.buildSettlement(6);
    p2.buildRoad(2,10);
    p2.buildRoad(19,20);
    p2.setTurn(false);

    p3.setTurn(true);
    p3.buildSettlement(50);
    p3.buildSettlement(43);
    p3.buildRoad(22,23);
    p3.buildRoad(14,15);
    

    // p3.addResourceCard(IRON,3);
    // p3.addResourceCard(WHEAT,2);
    // p3.buildCity(50);
    // CHECK(p3.getVictoryPoints()==3);
    // p3.setTurn(false);

}
TEST_CASE("can built settelment"){
    Player p1("Amit",10);
    Player p2("Yossi",20);
    Player p3("Dana",30);
    Catan catan(p1, p2, p3);
    
    p1.setTurn(true);
    p1.buildSettlement(0);
    p1.buildSettlement(3);
    p1.buildRoad(0,1);
    p1.buildRoad(5,6);
    p1.setTurn(false);

    p2.setTurn(true);
    p2.buildSettlement(2);
    p2.buildSettlement(6);
    p2.buildRoad(2,10);
    p2.buildRoad(19,20);
    p2.setTurn(false);

    p3.setTurn(true);
    p3.buildSettlement(50);
    p3.buildSettlement(43);
    p3.buildRoad(22,23);
    p3.buildRoad(14,15);
    p3.setTurn(false);

    p1.initializeResources();
    p2.initializeResources();
    p3.initializeResources();
    catan.ChooseStartingPlayer();
    Player * p=catan.getCurrentPlayer();
    p->rollDice();
    //CHECK_THROWS_AS(p->buildSettlement(17), std::runtime_error);
}

// TEST_CASE("DevelopmentCardManager Singleton AND [DevelopmentCardManager]") {
//     DevelopmentCardManager& manager1 = DevelopmentCardManager::getInstance();
//     DevelopmentCardManager& manager2 = DevelopmentCardManager::getInstance();

//     REQUIRE(&manager1 == &manager2); // Check that both references are the same instance
// }

// TEST_CASE("Initialize and Draw Development Cards AND [DevelopmentCardManager]") {
//     DevelopmentCardManager& manager = DevelopmentCardManager::getInstance();
//     manager.initializeDevCards();

//     // Ensure the deck is initialized with the correct number of cards
//     int expectedTotalCards = 25; // Adjust based on your initialization logic
//     REQUIRE(manager.getDeckSize() == expectedTotalCards);

//     // Draw a card and check the deck size
//     DevelopmentCard& card = manager.drawDevelopmentCard();
//     REQUIRE(manager.getDeckSize() == expectedTotalCards - 1);
// }

// TEST_CASE("Player buys and uses Development Cards") {
//     ResourceManager resourceManager;
//     Player player ("Player1", 1);
//     player.setResManage( &resourceManager);
//     DevelopmentCardManager& manager = DevelopmentCardManager::getInstance();
//     manager.initializeDevCards();

//     // Add resources needed for buying a development card
//     player.addResourceCard(IRON,1);
//     player.addResourceCard(WOOL,1);
//     player.addResourceCard(WHEAT,1);
//     // Player buys a development card
//     player.buyDevelopmentCard();
//     REQUIRE(player.getDevelopmentCardCount() == 1);

//     const std::map<DevelopmentCard*, int>& devCards = player.getDevelopmentCards();
//     REQUIRE_FALSE(devCards.empty()); // Make sure the player has at least one development card
//     DevelopmentCard* card = devCards.begin()->first;
//     player.useDevelopmentCard(card);
//     REQUIRE(player.getDevelopmentCardCount() == 0);
// }

// TEST_CASE("Development Card effects", "[Player][DevelopmentCardManager]") {
//     ResourceManager resourceManager;
//     Player player1 = createPlayer("Player1", 1, &resourceManager);
//     Player player2 = createPlayer("Player2", 2, &resourceManager);
//     Player player3 = createPlayer("Player3", 3, &resourceManager);
    
//     DevelopmentCardManager& manager = DevelopmentCardManager::getInstance();
//     manager.initializeDevCards();

//     // Add resources needed for buying a development card
//     addResourcesForDevelopmentCard(player1);
//     player1.buyDevelopmentCard();

//     // Get the drawn card and simulate its use
//     DevelopmentCard& card = player1.getDevelopmentCards().front();
//     DevelopmentCardType cardType = card.getDevelopmentCardType();

//     if (cardType == MONOPOLY) {
//         // Simulate using the Monopoly card
//         player1.playDevelopmentCard(card);
//         // Check the effect, e.g., player1 receives all of one resource type from other players
//     } else if (cardType == ROAD_BUILDING) {
//         // Simulate using the Road Building card
//         player1.playDevelopmentCard(card);
//         // Check the effect, e.g., player1 can build two roads for free
//     } else if (cardType == YEAR_OF_PLENTY) {
//         // Simulate using the Year of Plenty card
//         player1.playDevelopmentCard(card);
//         // Check the effect, e.g., player1 receives two resource cards of choice
//     }
// }

// TEST_CASE("Knight Card and Largest Army", "[Player][DevelopmentCardManager]") {
//     ResourceManager resourceManager;
//     Player player1 = createPlayer("Player1", 1, &resourceManager);
//     Player player2 = createPlayer("Player2", 2, &resourceManager);
    
//     DevelopmentCardManager& manager = DevelopmentCardManager::getInstance();
//     manager.initializeDevCards();

//     // Add resources needed for buying development cards
//     for (int i = 0; i < 3; ++i) {
//         addResourcesForDevelopmentCard(player1);
//         player1.buyDevelopmentCard();
//     }

//     // Check if player1 gets the Largest Army card after using 3 Knights
//     for (int i = 0; i < 3; ++i) {
//         DevelopmentCard& card = player1.getDevelopmentCards().front();
//         if (card.getDevelopmentCardType() == KNIGHT) {
//             player1.playDevelopmentCard(card);
//         }
//     }
//     REQUIRE(player1.hasLargestArmy());
//     REQUIRE(player1.getVictoryPoints() == 2); // 2 points for the Largest Army
// }