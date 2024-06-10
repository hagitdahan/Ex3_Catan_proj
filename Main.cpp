// /**
//  * Demo file for Ex3.
//  *
//  */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
using namespace std;

int main()
{
    Player p1("Amit",10);
    Player p2("Yossi",20);
    Player p3("Dana",30);
    Catan catan(p1, p2, p3);
    Board board = catan.getBoard(); // get the board of the game.

    p1.setTurn(true);
    p1.buildSettlement(9);
    p1.buildSettlement(8);
    p1.buildRoad(0,1);
    p1.buildRoad(5,6);
    p1.setTurn(false);

    p2.setTurn(true);
    p2.buildSettlement(19);
    p2.buildSettlement(12);
    p2.buildRoad(2,10);
    p2.buildRoad(19,20);
    p2.setTurn(false);

    p3.setTurn(true);
    try
    {
        p3.buildSettlement(0); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
     try
    {
        p3.buildRoad(19,20); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    p3.buildSettlement(15);
    p3.buildSettlement(22);
    p3.buildRoad(22,23);
    p3.buildRoad(14,15);
    p3.setTurn(false);
    
    catan.ChooseStartingPlayer();
    //simulate game 
    while (catan.getCurrentPlayer()->getId()!=10) {
        catan.ChooseStartingPlayer();
    }
    //now when player1 is the first lets start the game
    //amit built city in vertex 8
    catan.getCurrentPlayer()->rollDice();
    catan.getCurrentPlayer()->addResourceCard(IRON,1);
    catan.getCurrentPlayer()->buildCity(8);
    catan.getCurrentPlayer()->endTurn();
    catan.nextTurn();
    catan.getCurrentPlayer()->rollDice();
    //yossi build road in (12,13)
    //if(amit will roll 7 i need to add yossi resources to build road)
    catan.getCurrentPlayer()->addResourceCard(WOOD,1);
    catan.getCurrentPlayer()->addResourceCard(BRICK,1);
    catan.getCurrentPlayer()->buildRoad(12,13);
    catan.getCurrentPlayer()->endTurn();
    catan.nextTurn();
    //dana build settelment in vertex14 she need wheat
    //if(yossi / amit roll 7 i need to add data resource)
    catan.getCurrentPlayer()->rollDice();
    catan.getCurrentPlayer()->addResourceCard(WHEAT,1);
    catan.getCurrentPlayer()->addResourceCard(WOOD,1);
    catan.getCurrentPlayer()->addResourceCard(BRICK,1);
    catan.getCurrentPlayer()->addResourceCard(WOOL,1);
    catan.getCurrentPlayer()->buildSettlement(14);
    catan.getCurrentPlayer()->endTurn();
    catan.nextTurn();
    //now simulate trade between amit and yossi amit give yossi WHEAT and yossi give amit IRON
    catan.getCurrentPlayer()->rollDice();
    catan.getCurrentPlayer()->addResourceCard(WHEAT,1);
    p2.addResourceCard(IRON,1);
    catan.getCurrentPlayer()->trade(p2,IRON,1,WHEAT,1);
    catan.getCurrentPlayer()->endTurn();
    catan.nextTurn();
    //now simulate buy development card
    catan.getCurrentPlayer()->rollDice();
    try{
        catan.getCurrentPlayer()->buyDevelopmentCard();
        if(catan.getCurrentPlayer()->getDevelopmentCardCount()>0){
            DevelopmentCard* c=catan.getCurrentPlayer()->getDevelopmentCards().at(0);
            catan.getCurrentPlayer()->useDevelopmentCard(c);
        }
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    
        

    return 0;
}





