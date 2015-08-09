#ifndef __GAME_H__
#define __GAME_H__

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "constants.h"

class Player;
class Enemy;
class Item;
class Staircase;
class ItemFactory;
class EnemyFactory;
class Floor;
class Merchant;

class Game {
private:
    Game();
    ~Game();
    
    Game(const Game &other);                // Prevent copying
    Game &operator=(const Game &other);     // Prevent copying
    
    static Game *gameInstance;              // Game is a singleton
    
    bool gameRunning;                       // Is a game currently in play?
    std::ostream &display;                  // Where should we output the display?
    std::string placementsFile;             // For predetermined spawning
    int score;                              // Current score of the game
    int currFloor;                          // What floor is the player currently on
    std::string race;                       // What Race is the Player?
    std::string jobClass;                   // What Class is the Player?
    std::string action;                     // Action(s) to display after a turn
    Player *player;                         // The star of the show!
    ItemFactory *itemFactory;               // We need to spawn Items
    EnemyFactory *enemyFactory;             // We need to spawn Enemies
    Staircase *stairs;                      // To progress through the game
    std::vector<Enemy *> enemies;           // All enemies currently in the game
    std::vector<Item *> items;              // All items currently in the game
    Floor *floors[MAX_FLOORS];              // Floors for the player to progress through
    std::ifstream *placementFileIn;         // Where to get specific placements from
    
    #ifdef DLC
    WINDOW * window;                        // Stores window for Game class to print via ncurses
    #endif

    void spawnObjects();                    // Spawn GameObjects for current Floor
    void deleteObjects();                   // Delete old GameObjects (except Player)
    void provideNeighbours();               // Setup all Cells with their neighbours
    void win();                             // Win the Game!
    void lose();                            // Lose the Game!
    void complete();                        // When a Game is fully completed (I.E. not quit mid-game) call this
    void prepareCurrentFloor();             // Prepares the current Floor for use (spawning, etc.)
    void takeTurn();                        // After a player takes an action, play one turn of the game
    void displayFloor();                    // Displays the game's floor with all GameObjects shown
    void displayHUD();                      // Displays the HUD (i.e. health, atk, etc.)
    void displayState();                    // Displays the Game's current state (including the Floor)

    static void cleanup();                  // Singleton cleanup
public:
    static Game *instance();                // Main can control when to create a Game
    void notifyStairUse();                  // Call this when the player uses the stairs
    void notifyPlayerDied();                // Call this when the player is slain
    void notifyEnemyDied(Enemy *enemy);     // Call this when an Enemy dies
    void notifyMerchantDied(Merchant *m);   // Call this when an Enemy dies
    void addToScore(int scoreToAdd);        // Add the given amount to current game score
    void playerMoveInDirection(int dir);    // Dir = 0..7, only moves if possible
    void playerUseInDirection(int dir);     // Dir = 0..7, only uses if possible
    void playerAttackInDirection(int dir);  // Dir = 0..7, only attacks if possible
    void addAction(std::string action);     // Tell the Game to add an action to display
    Player *getPlayer();                    // Get the Player of the Game
    // Starts the Game as specific race. Pass in a placement filename if desired.
    void startGame(char race = RACE_SELECTION[HUMAN], std::string placementFile = "");
    void endGame();                         // Ends the current Game (if one is currently in play)
    void updatePlayer(Player *player);      // Tell the Game to update the game in response to player decoration
    #ifdef DLC
    // Starts the Game in DLC mode
    void startGamePlus(char race = RACE_SELECTION[HUMAN], char jobClass = CLASS_SELECTION[SIMPLETON], std::string placementFile = "");
    void konami();                          // :)
    // Prints off bartition
    void displayBartition(int numer, int denom, int width, std::string text, int colourFull, int colourEmpty, bool special = false);
    void setWindow(WINDOW * window);        // Sets window for Game class to print via ncurses
    void showState();                       // A public clone of displayState. Only useful for DLC.
    WINDOW * getWindow();                   // Gets Window for other classes that require it
    void undoPlayer();                      // Tell the Game to undo a player decoration
    //void displayNcurses(std::string text);  // Displays text to ncurses window
    void displayNcurses(const char * text);  // Displays text to ncurses window
    void playerClassCommand(std::string text);  // Attempt user command
    #endif

    #ifdef DEBUG
    //DEBUGGING
    void die();
    void nextFloor();
    void skip();
    void dbSpawnPotion(int type, int dir);
    void dbSpawnGold(int value, int dir);
    #endif
};

#endif
