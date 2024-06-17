#include "doctest.h"
#include "Player.hpp"
#include "Catan.hpp"
#include "Deck.hpp"
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
    int woodNum=player2.getResourceCardCount(WOOD);
    int brickNum=player2.getResourceCardCount(BRICK);
    int woolNum=player2.getResourceCardCount(WOOL);
    int wheatNum=player2.getResourceCardCount(WHEAT);
    player2.buildSettlement(0); // Assuming vertex index 0 is available
    
    CHECK(player2.getResourceCardCount(WOOD) == woodNum-1);
    CHECK(player2.getResourceCardCount(BRICK) == brickNum-1);
    CHECK(player2.getResourceCardCount(WOOL) == woolNum-1);
    CHECK(player2.getResourceCardCount(WHEAT) == wheatNum-1);
    //Assuming building a settlement gives the player 1 victory point
    CHECK(player2.getVictoryPoints() == 1);
    delete res;
    delete b;
}

TEST_CASE("Test class Vertex"){
    Board *b=new Board();
    CHECK_EQ(b->getVertices().size(),54);
    delete b;

}

TEST_CASE("Test class Edge"){
    Board* b=new Board();
    CHECK_EQ(b->getEdges().size(),72);
    delete b;
}

TEST_CASE("Test class Land"){
    Board* b=new Board();
    CHECK_EQ(b->getLands().size(),19);
    delete b;
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

    p2.setTurn(true);
    p2.buildSettlement(2);
    p2.buildSettlement(6);
    p2.buildRoad(2,10);
    p2.buildRoad(19,20);
    p2.addResourceCard(IRON,5);
    int sumRes=p2.getResourceCardCountAll();
    //p2 need to remove 3 resorces
    p2.handleRoll(7);
    CHECK_EQ(p2.getResourceCardCountAll(),sumRes/2);
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
    p1.addResourceCard(IRON,6);
    int sumResourceP2=p2.getResourceCardCountAll();
    int sumResourceP1=p1.getResourceCardCountAll();
    //p2 and p1 neet to remove half resources
    p2.notifyOthers(7);
    p2.handleRoll(7);
    p2.setTurn(false);
    CHECK_EQ(p2.getResourceCardCountAll(),sumResourceP2/2);
    CHECK_EQ(p1.getResourceCardCountAll(),sumResourceP1/2);

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
    
    p3.addResourceCard(IRON,3);
    p3.addResourceCard(WHEAT,2);
    p3.buildCity(50);
    CHECK(p3.getVictoryPoints()==3);
    p3.setTurn(false);

}

// TEST_CASE("can built settelment"){
//     Player p1("Amit",10);
//     Player p2("Yossi",20);
//     Player p3("Dana",30);
//     Catan catan(p1, p2, p3);
    
//     p1.setTurn(true);
//     p1.buildSettlement(0);
//     p1.buildSettlement(3);
//     p1.buildRoad(0,1);
//     p1.buildRoad(5,6);
//     p1.setTurn(false);

//     p2.setTurn(true);
//     p2.buildSettlement(2);
//     p2.buildSettlement(6);
//     p2.buildRoad(2,10);
//     p2.buildRoad(19,20);
//     p2.setTurn(false);

//     p3.setTurn(true);
//     p3.buildSettlement(50);
//     p3.buildSettlement(43);
//     p3.buildRoad(22,23);
//     p3.buildRoad(14,15);
//     p3.setTurn(false);

//     p1.initializeResources();
//     p2.initializeResources();
//     p3.initializeResources();
//     catan.ChooseStartingPlayer();
//     CHECK_THROWS_AS(catan.getCurrentPlayer()->buildSettlement(17), std::runtime_error);
// }

// TEST_CASE("Deck") {
//     ResourceManager *res=new ResourceManager();
//     Board* b=new Board();
//     Player p("hagit",10);
//     p.setResManage(res);
//     p.setBoard(b);
//     // Initialize the deck
//     Deck* deck = Deck::getInstance();
//     DevCardManager * dev=new DevCardManager(deck);
//     p.setDevManager(dev);
//     //Check that the deck is not empty after initialization
//     REQUIRE(deck->getDeckSize() > 0);
//     p.addResourceCard(IRON,1);
//     p.addResourceCard(WOOL,1);
//     p.addResourceCard(WHEAT,1);
//     //Player buys a development card
//     p.buyDevelopmentCard();
//     p.
//     // //Check that the deck size decreases after drawing a card
//     REQUIRE(deck->getDeckSize() == 24); // Assuming 25 cards were initially in the deck
//     delete res;
//     delete b;
//     delete dev;
//     deck->cleanInstance();
// }

TEST_CASE("Deck Singleton") {
    Deck* d1= Deck::getInstance();
    Deck* d2=Deck::getInstance();
    REQUIRE(d1 == d2); // Check that both references are the same instance
    d1->cleanInstance();
}

TEST_CASE("Player buys and uses Development Cards") {
    Player p1("Hagit", 1);
    Player p2("romi",2);
    Player p3("mai",3);
    Catan c(p1,p2,p3);
    
    // Add resources needed for buying a development card
    p1.addResourceCard(IRON,1);
    p1.addResourceCard(WOOL,1);
    p1.addResourceCard(WHEAT,1);
    //Player buys a development card
    p1.buyDevelopmentCard();
    REQUIRE(p1.getDevelopmentCardCount() == 1);

    std::vector<DevelopmentCard*> devCards = p1.getDevelopmentCards();
    REQUIRE_FALSE(devCards.empty()); // Make sure the player has at least one development card
}

 TEST_CASE("Development Card effects Player") {
    Player player1 ("Player1", 1);
    Player player2 ("Player2", 2);
    Player player3 ("Player3", 3);
    Catan catan(player1,player2,player3);
   
    //test YEAR_OF_PLENTY card
    player1.addDevelopmentCard(new DevelopmentCard(YEAR_OF_PLENTY));
    CHECK_EQ(player1.getDevelopmentCardCount(),1);
    player1.useDevelopmentCard(player1.getDevelopmentCards().at(0));

    //add iron to player 2 and 3 for checking
    player2.addResourceCard(IRON,1);
    player3.addResourceCard(IRON,1);
    CHECK_EQ(player2.getResourceCardCount(IRON),1);
    CHECK_EQ(player3.getResourceCardCount(IRON),1);
    
    CHECK_EQ(player1.getDevelopmentCardCount(),0);
    //test MONOPOLY card
    player1.addDevelopmentCard(new DevelopmentCard(MONOPOLY));
    player1.useDevelopmentCard(player1.getDevelopmentCards().at(0));
    CHECK_EQ(player2.getResourceCardCount(IRON),0);
    CHECK_EQ(player3.getResourceCardCount(IRON),0);
    CHECK_EQ(player1.getDevelopmentCardCount(),0);
    
    //test ROAD_BUILDING card
    player1.addDevelopmentCard(new DevelopmentCard(ROAD_BUILDING));
    player1.setTurn(true);
    player1.useDevelopmentCard(player1.getDevelopmentCards().at(0));
    CHECK_EQ(player1.getDevelopmentCardCount(),0);

    //test YEAR_OF_PLENTY card
    CHECK_EQ(player1.getVictoryPoints(),0);
    player1.addDevelopmentCard(new DevelopmentCard(YEAR_OF_PLENTY));
    player1.useDevelopmentCard(player1.getDevelopmentCards().at(0));
    CHECK_EQ(player1.getDevelopmentCardCount(),0);
    
    //test Knight card
    player1.addDevelopmentCard(new DevelopmentCard(KNIGHT));
    player1.addDevelopmentCard(new DevelopmentCard(KNIGHT));
    player1.addDevelopmentCard(new DevelopmentCard(KNIGHT));
    player1.useKnightCard();
    CHECK_EQ(player1.getVictoryPoints(),2);
 }

TEST_CASE("trade"){
    Player player1("Player1", 1);
    Player player2("Player2", 2);

    player1.addResourceCard(IRON, 5);
    player1.addResourceCard(WOOL, 3);

    player2.addResourceCard(WHEAT, 4);
    player2.addResourceCard(IRON, 2);

    REQUIRE(player1.trade(player2, IRON, 2, WHEAT, 2) == true);
    REQUIRE(player1.getResourceCardCount(IRON) == 3);
    REQUIRE(player1.getResourceCardCount(WHEAT) == 2);
    REQUIRE(player2.getResourceCardCount(IRON) == 4);
    REQUIRE(player2.getResourceCardCount(WHEAT) == 2);

    REQUIRE(player1.trade(player2, WOOL, 4, WHEAT, 1) == false);
    REQUIRE(player1.getResourceCardCount(WOOL) == 3);

    REQUIRE(player2.trade(player1, IRON, 5, WOOL, 1) == false);
    REQUIRE(player2.getResourceCardCount(IRON) == 4);
}

TEST_CASE("Player wins the game") {
    Player player1("Alice", 1);
    Player player2("Bob", 2);
    Player player3("Charlie", 3);

    Catan game(player1, player2, player3);

    // Simulate a game where player1 reaches 10 victory points
    player1.addVictoryPointsForTest(10);

    // Check if the game detects the win
    REQUIRE(game.checkVictory(&player1) == true);
}

// TEST_CASE("Simulate a game of Catan") {
//     Player player1("Alice", 1);
//     Player player2("Bob", 2);
//     Player player3("Charlie", 3);

//     Catan game(player1, player2, player3);

//     // Initialize resources for testing
//     player1.addResourceCard(WOOD, 3);
//     player1.addResourceCard(BRICK, 2);
//     player1.addResourceCard(WHEAT, 2);
//     player1.addResourceCard(WOOL, 2);
//     player1.addResourceCard(IRON, 1);

//     player2.addResourceCard(WOOD, 2);
//     player2.addResourceCard(BRICK, 2);
//     player2.addResourceCard(WHEAT, 2);
//     player2.addResourceCard(WOOL, 3);
//     player2.addResourceCard(IRON, 1);

//     player3.addResourceCard(WOOD, 2);
//     player3.addResourceCard(BRICK, 3);
//     player3.addResourceCard(WHEAT, 2);
//     player3.addResourceCard(WOOL, 2);
//     player3.addResourceCard(IRON, 2);

//     // Simulate player1 building a settlement and a road
//     player1.buildSettlement(1);
//     player1.buildRoad(1, 2);

//     // Simulate player2 building a settlement and a road
//     player2.buildSettlement(2);
//     player2.buildRoad(2, 3);

//     // Simulate player3 building a settlement and a road
//     player3.buildSettlement(3);
//     player3.buildRoad(3, 4);

//     // Simulate a trade between player1 and player2
//     player1.trade(player2, WOOD, 1,WHEAT, 1);
//     // Simulate player1 buying and using a development card
//     player1.addResourceCard(IRON, 1);
//     player1.addResourceCard(WOOL, 1);
//     player1.addResourceCard(WHEAT, 1);
//     player1.buyDevelopmentCard();

//     // Simulate multiple turns and actions
//     for (int i = 0; i < 10; ++i) {
//         // Player1's turn
//         player1.rollDice();
//         player1.buildSettlement(5);
//         player1.buildRoad(5, 6);
//         player1.endTurn();

//         // Player2's turn
//         player2.rollDice();
//         player2.buildSettlement(6);
//         player2.buildRoad(6, 7);
//         player2.endTurn();

//         // Player3's turn
//         player3.rollDice();
//         player3.buildSettlement(7);
//         player3.buildRoad(7, 8);
//         player3.endTurn();

//         // Check victory condition
//         if (game.checkVictory(&player1)) {
//             REQUIRE(player1.getVictoryPoints() >= 10);
//             break;
//         }
//         if (game.checkVictory(&player2)) {
//             REQUIRE(player2.getVictoryPoints() >= 10);
//             break;
//         }
//         if (game.checkVictory(&player3)) {
//             REQUIRE(player3.getVictoryPoints() >= 10);
//             break;
//         }
//     }
// }

TEST_CASE("Build Road,Settelment and City by the rulls"){
    Player p1("Amit",10);
    Player p2("Yossi",20);
    Player p3("Dana",30);
    Catan catan(p1, p2, p3);

    p1.setTurn(true);
    p1.buildSettlement(9);
    p1.buildSettlement(8);
    p1.buildRoad(0,1);
    p1.buildRoad(5,6);
    p1.addResourceCard(BRICK,1);
    p1.addResourceCard(WOOD,1);
    p1.setTurn(false);

    p2.setTurn(true);
    p2.buildSettlement(19);
    p2.buildSettlement(12);
    p2.buildRoad(2,10);
    p2.buildRoad(19,20);
    p2.addResourceCard(BRICK,1);
    p2.addResourceCard(WOOD,1);
    p2.setTurn(false);

    p3.setTurn(true);
    p3.buildSettlement(15);
    p3.buildSettlement(22);
    p3.buildRoad(22,23);
    p3.buildRoad(14,15);
    p3.addResourceCard(BRICK,1);
    p3.addResourceCard(WOOD,1);
    p3.setTurn(false);
    catan.startGame();
    catan.ChooseStartingPlayer();
    CHECK_THROWS(catan.getCurrentPlayer()->buildRoad(52,53));

    
}

TEST_CASE("connection between edges and vertex"){
    Board * b=new Board();
    vector<Edge*>edges=b->getEdges();
    vector<Vertex*>vertices=b->getVertices();
    edges[0]->setOwnerId(10);
    CHECK_EQ(vertices[0]->getConnectedEdges().at(0)->getOwnerId(),10);
    delete b;

}

// TEST_CASE("Trade with dev cards"){
//     Player p1("Amit",10);
//     Player p2("Yossi",20);
//     Player p3("Dana",30);
//     Catan catan(p1, p2, p3);
//     Board board = catan.getBoard(); // get the board of the game.

//     p1.addDevelopmentCard(new DevelopmentCard(YEAR_OF_PLENTY));
//     CHECK_EQ(p1.getDevelopmentCardCount(),1);
//     p2.addDevelopmentCard(new DevelopmentCard(KNIGHT));
//     DevelopmentCard* dev1=p1.getDevelopmentCards().at(0);
//     DevelopmentCard* dev2=p2.getDevelopmentCards().at(0);
//     p1.tradeDev(p2,dev1,dev2);
//     CHECK_EQ(p1.getDevelopmentCardCount(),1);
//     CHECK_EQ(p2.getDevelopmentCardCount(),1);

// }