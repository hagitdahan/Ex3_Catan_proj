#ifndef CATAN_HPP
#define CATAN_HPP
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.hpp"
/**
 * @class Catan
 * @brief Represents the Catan game.
 */
class Catan {
public:
    /**
     * @brief Default constructor.
     */
    Catan();
     /**
     * @brief Constructs a new Catan game with three players.
     * @param p1 The first player.
     * @param p2 The second player.
     * @param p3 The third player.
     * and initialize all the parameters of the players
     */
    Catan(Player &p1, Player &p2, Player &p3);
    /**
     * @brief Destructor.
     */
    ~Catan(); // Destructor to clean up memory
      /**
     * @brief Reorders the players vector based on the current player index.
     */
    void reorderPlayers();
     /**
     * @brief Chooses the starting player randomly.
     */
    void ChooseStartingPlayer(); 
    /**
     * @brief Moves to the next turn.
     */
    void nextTurn();
    /**
     * @brief Retrieves the current player.
     * @return A pointer to the current player.
     */
    Player* getCurrentPlayer() const;
    /**
     * @brief Retrieves the game board.
     * @return The game board.
     */
    Board getBoard();
    /**
     * @brief Starts the game.
     */
    void startGame();
     /**
     * @brief Checks if a player has achieved victory.
     * @param player The player to check.
     * @return True if the player has achieved victory, false otherwise.
     */
    bool checkVictory(Player* player);
    

private:
    Board *board; //< Pointer to the game board.
    std::vector<Player*> players; //< Vector containing pointers to the players.
    Player* currentPlayer; //< Pointer to the current player.
    int currentPlayerIndex; //< Index of the current player.
    ResourceManager* resoureManage; //< Pointer to the resource manager.
    DevCardManager* devManager; //< Pointer to the development card manager.
};

#endif // CATAN_HPP
