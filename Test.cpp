#include "doctest.h"
#include "Player.hpp"
#include "Catan.hpp"

using namespace std;

TEST_CASE("Test class player"){
    //checking adding and remove resources
    Player player("Alice", 1);
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
    
}
TEST_CASE("Test class Edge"){
    
}
TEST_CASE("Test class Land"){
    
}
TEST_CASE("Test class Catan"){
    
} 
TEST_CASE("Test class Board"){
    
}
TEST_CASE("Test class Card"){
    
}
TEST_CASE("Test Roll dice"){
    
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
    CHECK_THROWS_AS(p->buildSettlement(17), std::runtime_error);
    

}
