#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <ncurses.h>
#include "game.h"
#include "cell.h"
#include "floor.h"
#include "chamber.h"
#include "language.h"
#include "itemfactory.h"
#include "enemyfactory.h"
#include "item.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include "player.h"
#include "decoratedplayer.h"
#include "dragon.h"
#include "dragonhoard.h"
#include "staircase.h"
#include "utils.h"
#include "direction.h"
#include "baseplayer.h"
#include "merchant.h"

using namespace std;

Game *Game::gameInstance;

Game *Game::instance() {
    if(gameInstance == NULL) {
        gameInstance = new Game();
        atexit(cleanup);
    }
    
    return gameInstance;
}

void Game::cleanup() {
    delete gameInstance;
}

Game::Game() : gameRunning(false), display(cout), placementsFile(""), placementFileIn(NULL), score(0), currFloor(1), player(NULL),
               itemFactory(new ItemFactory(this)), enemyFactory(new EnemyFactory(this)), stairs(NULL)
{
    // Setup Floors
    for(int i = 0; i < MAX_FLOORS; ++i) {
        floors[i] = new Floor;
    }
}

Game::~Game() {
    endGame();
    
    // Delete Floors
    for(int i = 0; i < MAX_FLOORS; ++i) {
        delete floors[i];
    }
    
    // Delete Factories
    delete itemFactory;
    delete enemyFactory;

    delete placementFileIn;
}

Game::Game(const Game &other) : display(cout) { }           // This should never be called

Game& Game::operator=(const Game &other) {                  // This should never be called
    return *this;
}

void Game::spawnObjects() {
    Floor *floor = floors[currFloor - 1];

    // If a placements file is provided, trust the input is valid and use it instead of random generation
    if(placementsFile.length() > 0) {
        // We need some way of connecting any spawned Dragon to its Hoard
        vector<Dragon *> dragons;
        vector<DragonHoard *> dragonHoards;
        
        for(int r = 0; r < ROWS; ++r) {
            string line;
            getline(*placementFileIn, line);
            for(int c = 0; c < line.length(); ++c) {
                char ch = line.at(c);
                
                Cell *cell = floor->getCell(r, c);
                if(cell == NULL || cell->getOccupant() != NULL) {
                    continue;
                }
                
                if(ch == '0') {
                    // Spawn RH
                    RestoreHealth *rh = itemFactory->createRestoreHealth();
                    items.push_back(rh);
                    cell->setOccupant(rh);
                    rh->setLocation(cell);
                } else if(ch =='1') {
                    // Spawn BA
                    BoostAttack *ba = itemFactory->createBoostAttack();
                    items.push_back(ba);
                    cell->setOccupant(ba);
                    ba->setLocation(cell);
                } else if(ch =='2') {
                    // Spawn BD
                    BoostDefence *bd = itemFactory->createBoostDefence();
                    items.push_back(bd);
                    cell->setOccupant(bd);
                    bd->setLocation(cell);
                } else if(ch =='3') {
                    // Spawn PH
                    PoisonHealth *ph = itemFactory->createPoisonHealth();
                    items.push_back(ph);
                    cell->setOccupant(ph);
                    ph->setLocation(cell);
                } else if(ch =='4') {
                    // Spawn WA
                    WoundAttack *wa = itemFactory->createWoundAttack();
                    items.push_back(wa);
                    cell->setOccupant(wa);
                    wa->setLocation(cell);
                } else if(ch =='5') {
                    // Spawn WD
                    WoundDefence *wd = itemFactory->createWoundDefence();
                    items.push_back(wd);
                    cell->setOccupant(wd);
                    wd->setLocation(cell);
                } else if(ch =='6') {
                    // Spawn Normal Gold Pile
                    GoldPile *normalPile = itemFactory->createNormalPile();
                    items.push_back(normalPile);
                    cell->setOccupant(normalPile);
                    normalPile->setLocation(cell);
                } else if(ch =='7') {
                    // Spawn Small Hoard
                    GoldPile *smallHoard = itemFactory->createSmallHoard();
                    items.push_back(smallHoard);
                    cell->setOccupant(smallHoard);
                    smallHoard->setLocation(cell);
                } else if(ch =='8') {
                    // Spawn Merchant Hoard
                    GoldPile *merchantHoard = itemFactory->createMerchantHoard();
                    items.push_back(merchantHoard);
                    cell->setOccupant(merchantHoard);
                    merchantHoard->setLocation(cell);
                } else if(ch =='9') {
                    // Spawn Dragon Hoard
                    DragonHoard *hoard = itemFactory->createDragonHoard();
                    items.push_back(hoard);
                    cell->setOccupant(hoard);
                    hoard->setLocation(cell);

                    dragonHoards.push_back(hoard);
                } else if(ch =='V') {
                    // Spawn Vampire
                    Vampire *V = enemyFactory->createVampire();
                    enemies.push_back(V);
                    cell->setOccupant(V);
                    V->setLocation(cell);
                } else if(ch =='W') {
                    // Spawn Werewolf
                    Werewolf *W = enemyFactory->createWerewolf();
                    enemies.push_back(W);
                    cell->setOccupant(W);
                    W->setLocation(cell);
                } else if(ch =='N') {
                    // Spawn Goblin
                    Goblin *N = enemyFactory->createGoblin();
                    enemies.push_back(N);
                    cell->setOccupant(N);
                    N->setLocation(cell);
                } else if(ch =='M') {
                    // Spawn Merchant
                    Merchant *M = enemyFactory->createMerchant();
                    enemies.push_back(M);
                    cell->setOccupant(M);
                    M->setLocation(cell);
                } else if(ch =='X') {
                    // Spawn Phoenix
                    Phoenix *X = enemyFactory->createPhoenix();
                    enemies.push_back(X);
                    cell->setOccupant(X);
                    X->setLocation(cell);
                } else if(ch =='T') {
                    // Spawn Troll
                    Troll *T = enemyFactory->createTroll();
                    enemies.push_back(T);
                    cell->setOccupant(T);
                    T->setLocation(cell);
                } else if(ch =='D') {
                    // Spawn Dragon
                    Dragon *D = enemyFactory->createDragon();
                    enemies.push_back(D);
                    cell->setOccupant(D);
                    D->setLocation(cell);
                    
                    dragons.push_back(D);
                } else if(ch == '@') {
                    cell->setOccupant(player);
                    player->setLocation(cell);
                } else if(ch == DISPLAY_STAIRS) {
                    cell->setOccupant(stairs);
                    stairs->setLocation(cell);
                }
            }
            
            // We now must "connect" Dragons and their Hoards
            while(!dragons.empty()) {
                // Get the next Dragon
                Dragon *D = dragons.back();
                
                // Search for a neighbouring Hoard
                for(vector<DragonHoard *>::iterator i = dragonHoards.begin(); i != dragonHoards.end(); ++i) {
                    DragonHoard *hoard = *i;
                    
                    if(D->isOneCellFrom(*hoard)) {
                        // We have a connection to make!
                        D->setHoard(hoard);
                        hoard->setDragon(D);
                        
                        // This hoard is no longer able to make another connection with a Dragon
                        dragonHoards.erase(i);
                        break;
                    }
                }
                
                // We've now finished connecting this Dragon to its Hoard
                dragons.pop_back();
            }
        }
    } else {
        // Spawn Player
        Chamber *playerChamber = floor->getChamber(randomIntInRange(1, CHAMBERS));
        Cell *playerCell = playerChamber->getNthCell(randomIntInRange(0, playerChamber->chamberSize() - 1));
        playerCell->setOccupant(player);
        player->setLocation(playerCell);
        
        // Spawn Staircase
        Chamber *staircaseChamber;
        // Player and Staircase cannot be spawned in the same Chamber!
        while(true) {
            staircaseChamber = floor->getChamber(randomIntInRange(1, CHAMBERS));
            if(playerChamber != staircaseChamber) {
                break;
            }
        }
        Cell *staircaseCell = staircaseChamber->getNthCell(randomIntInRange(0, staircaseChamber->chamberSize() - 1));
        staircaseCell->setOccupant(stairs);
        stairs->setLocation(staircaseCell);
        
        // Spawn Potions
        for(int i = 0; i < MAX_FLOOR_POTIONS; ++i) {
            Chamber *randomChamber = floor->getChamber(randomIntInRange(1, CHAMBERS));
            Cell *randomCell;
            
            // Make sure the Cell is unoccupied!
            while(true) {
                randomCell = randomChamber->getNthCell(randomIntInRange(0, randomChamber->chamberSize() - 1));
                if(randomCell->getOccupant() == NULL) break;
            }
            
            // Spawn the Potion
            Potion *spawnedPotion = itemFactory->createPotion();
            randomCell->setOccupant(spawnedPotion);
            spawnedPotion->setLocation(randomCell);
            items.push_back(spawnedPotion);
        }
        
        // Spawn Treasures
        for(int i = 0; i < MAX_FLOOR_TREASURES; ++i) {
            Chamber *randomChamber = floor->getChamber(randomIntInRange(1, CHAMBERS));
            Cell *randomCell;
            
            // Make sure the Cell is unoccupied!
            while(true) {
                randomCell = randomChamber->getNthCell(randomIntInRange(0, randomChamber->chamberSize() - 1));
                if(randomCell->getOccupant() == NULL) break;
            }
            
            // Spawn the Treasure
            Treasure *spawnedTreasure = itemFactory->createTreasure();
            randomCell->setOccupant(spawnedTreasure);
            spawnedTreasure->setLocation(randomCell);
            items.push_back(spawnedTreasure);
            
            // If we spawned a DragonHoard, spawn a Dragon too!
            DragonHoard *hoard = dynamic_cast<DragonHoard *>(spawnedTreasure);
            if(hoard != NULL) {
                Dragon *D = enemyFactory->createDragon();
                enemies.push_back(D);
                
                // Find a random neighbouring cell to put the Dragon into
                vector<Cell *> cells = hoard->getLocation()->getNeighbours();
                Cell *cellToSpawnIn;
                while(true) {
                    cellToSpawnIn = cells.at(randomIntInRange(0, cells.size() - 1));
                    if(cellToSpawnIn->getOccupant() == NULL && cellToSpawnIn->getAppearance() == ENEMY_ALLOWED_CELLS[0]) break;
                }
                cellToSpawnIn->setOccupant(D);
                D->setLocation(cellToSpawnIn);
                
                // Make connection
                D->setHoard(hoard);
                hoard->setDragon(D);
            }
        }
        
        // Spawn Enemies (note, we may have already spawned some Dragons, hence the starting index)
        for(int i = (int)enemies.size(); i < MAX_FLOOR_ENEMIES; ++i) {
            // Get a random Chamber, then a random Cell in that Chamber
            Chamber *randomChamber = floor->getChamber(randomIntInRange(1, CHAMBERS));
            Cell *randomCell;
            
            // Make sure the Cell is unoccupied!
            while(true) {
                randomCell = randomChamber->getNthCell(randomIntInRange(0, randomChamber->chamberSize() - 1));
                if(randomCell->getOccupant() == NULL) break;
            }
            
            // Spawn the Enemy
            Enemy *spawnedEnemy = enemyFactory->createMovableEnemy();
            randomCell->setOccupant(spawnedEnemy);
            spawnedEnemy->setLocation(randomCell);
            enemies.push_back(spawnedEnemy);
        }
    }
}

void Game::deleteObjects() {
    Floor *floor = floors[currFloor - 1];

    // Delete all Enemies
    while(!enemies.empty()) {
        delete enemies.back();
        enemies.pop_back();
    }
    
    // Delete all Items
    while(!items.empty()) {
        delete items.back();
        items.pop_back();
    }
    
    floor->clearFloor();
}

void Game::provideNeighbours() {
    Floor *floor = floors[currFloor - 1];

    if (floor->hasConnections()){
        return;
    }
    
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLMS; ++c) {
            Cell *cell = floor->getCell(r, c);
            if(cell != NULL) {
                for(int i = 0; i < maxDirs; ++i) {
                    Direction dir = dirs[i];        // Which direction are we looking for a neighbour in?
                    int neighbourRow = r + dir.northSouth;
                    int neighbourCol = c + dir.eastWest;

                    // Check for a valid neighbour in this direction
                    if(neighbourRow >= 0 && neighbourRow < ROWS && neighbourCol >= 0 && neighbourCol < COLMS) {
                        cell->addNeighbour(floor->getCell(neighbourRow, neighbourCol));
                    } else {
                        cell->addNeighbour(NULL);   // No neighbour in this direction
                    }
                }
            }
        }
    }
    
    // Make the floor know that its cells are self-aware of its surroundings
    floor->connect();
}

void Game::win() {
    if(!gameRunning) return;
    
    #ifdef DLC
    ostringstream ncurseText;
    ncurseText << endl << Language::getText("winGame") << endl;
    displayNcurses(ncurseText.str().c_str());
    #else
    display << endl << Language::getText("winGame") << endl;
    #endif
    
    // The Game is now complete
    complete();
}

void Game::lose() {
    if(!gameRunning) return;
    
    #ifdef DLC
    ostringstream ncurseText;
    ncurseText << endl << Language::getText("loseGame") << endl;
    displayNcurses(ncurseText.str().c_str());
    #else
    display << endl << Language::getText("loseGame") << endl;
    #endif
    // The Game is now complete
    complete();
}

void Game::complete() {
    // Since the game is now complete, display final score and additional info
    #ifdef DLC
    ostringstream ncurseText;
    score += BasePlayer::getInstance()->getEXPScoreBonus();
    ncurseText << Language::getText("finalScore") << score << endl;
    ncurseText << Language::getText("restartGame") << endl << Language::getText("quitGame") << endl << endl;
    displayNcurses(ncurseText.str().c_str());
    #else
    display << Language::getText("finalScore") << score << endl << endl;
    display << Language::getText("restartGame") << endl << Language::getText("quitGame") << endl;
    #endif
    endGame();
}

void Game::prepareCurrentFloor() {
    // Delete any old objects (presumably used on the previous Floor), except Player
    deleteObjects();
    
    // Let each Cell know who its neighbours are
    provideNeighbours();
    
    // Spawn objects (including placing Player)
    spawnObjects();
    
    // Show the user all of these changes
    displayState();
}

void Game::takeTurn() {
    if(!gameRunning) return;
    
    Floor *floor = floors[currFloor - 1];
    
    // Take Enemy actions
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLMS; ++c) {
            Cell *cell = floor->getCell(r, c);
            if(cell != NULL) {
                GameObject *occupant = cell->getOccupant();
                if(occupant != NULL) {
                    Enemy *enemy = dynamic_cast<Enemy *>(occupant);     // Be sure we have an Enemy
                    if(enemy != NULL && enemy->canTakeTurn()) {
                        // Attacking takes priority
                        if(enemy->getCanAttack()) {
                            if(player != NULL && enemy->isOneCellFrom(*player)) {
                                enemy->attackPlayer(player);
                                continue; // We attacked, so this Enemy is finished taking an action
                            }
                        }
                        
                        if(enemy->getIsMovable()) {
                            while(true) {
                                int dir = randomIntInRange(0, 7);
                                if(enemy->canMoveInDirection(dir)) {
                                    enemy->moveInDirection(dir);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Turn is over, allows enemies to take a turn next round and display the state of the Game
    for(vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
        Enemy *enemy = *i;
        enemy->allowTurn();
    }
    
    displayState();
    
    action = "";    // Reset the action string for the next turn
}

void Game::displayFloor() {
    #ifdef DLC
    ostringstream ncurseText;
    ncurseText << *floors[currFloor - 1];
    displayNcurses(ncurseText.str().c_str());
    #else
    display << *floors[currFloor - 1];
    #endif
}

void Game::displayHUD() {
    #ifdef DLC
    ostringstream ncurseText;
    ostringstream ncurseText2;
    // Printing Start of character info
    ncurseText << "LV " << BasePlayer::getInstance()->getLevel() << " " << race << " "  << jobClass << " " << Language::getText("gold:") << " " << player->getGold();
    ncurseText << right << setw(COLMS - 34) << Language::getText("floor") << " " << currFloor << endl;
    displayNcurses(ncurseText.str().c_str());
    // Creating HP Bartition
    ostringstream HP;
    HP << Language::getText("hp:") << " " << player->getCurrentHP() << "/" << player->getMaxHP();
    displayBartition(player->getCurrentHP(), player->getMaxHP(), 20, HP.str(), 1, 2);
    // Creating Other Bartitions
    addch('\n');
    BasePlayer::getInstance()->getSpecialBar();
    addch('\n');
    BasePlayer::getInstance()->getEXPBar();

    // Resuming
    ncurseText2 << endl << Language::getText("atk:") << " " << player->getAttack() << endl;
    ncurseText2 << Language::getText("def:") << " " << player->getDefence() << endl;
    ncurseText2 << Language::getText("action:") << " " << action << endl;
    displayNcurses(ncurseText2.str().c_str());
    #else
    display << Language::getText("race:") << " " << race << " " << Language::getText("gold:") << " " << player->getGold();
    display << right << setw(COLMS - 24) << Language::getText("floor") << " " << currFloor << endl;
    display << Language::getText("hp:") << " " << player->getCurrentHP() << endl;
    display << Language::getText("atk:") << " " << player->getAttack() << endl;
    display << Language::getText("def:") << " " << player->getDefence() << endl;
    display << Language::getText("action:") << " " << action << endl;
    #endif
}

void Game::displayState() {
    if(!gameRunning) return;
    #ifdef DLC
    clear();
    #else
    display << endl;
    #endif
    
    displayFloor();
    displayHUD();
}

void Game::notifyStairUse() {
    if(!gameRunning) return;
    
    if(currFloor == MAX_FLOORS) {
        // The player has won in this case!
        win();
    } else {
        // The Game is still in progress, so we prepare the next Floor
        player = BasePlayer::getInstance();
        ++currFloor;
        prepareCurrentFloor();
    }
}

void Game::notifyPlayerDied() {
    if(!gameRunning) return;
    
    displayState();
    #ifdef DLC
    ostringstream ncurseText;
    ncurseText << endl << Language::getText("pc") << Language::getText("hasBeenSlain") << endl;
    displayNcurses(ncurseText.str().c_str());
    #else
    display << endl << Language::getText("pc") << Language::getText("hasBeenSlain") << endl;
    #endif
    lose();
}

void Game::notifyEnemyDied(Enemy *enemy) {
    if(!gameRunning) return;
    
    if(enemy == NULL) {
        return;
    }
    
    // Remove the Enemy from the list of Enemies currently in the Game, and delete it
    for(vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
        Enemy *e = *i;
        
        if(e == enemy) {
            enemies.erase(i);
            break;
        }
    }

    delete enemy;
}

void Game::notifyMerchantDied(Merchant *m) {
    if(!gameRunning) return;
    
    if(m == NULL || m->getLocation() == NULL) {
        return;
    }
    
    // Take the Merchant off it's location and replace it with the Merchant hoard
    Cell *location = m->getLocation();
    m->setLocation(NULL);
    GoldPile *merchantHoard = itemFactory->createMerchantHoard();
    location->setOccupant(merchantHoard);
    merchantHoard->setLocation(location);
    items.push_back(merchantHoard);
}

void Game::addToScore(int scoreToAdd) {
    score += scoreToAdd;
}

void Game::playerMoveInDirection(int dir) {
    if(!gameRunning) return;
    
    if(player == NULL || player->getLocation() == NULL) {
        displayState();
        return;
    }
    
    Cell *location = player->getLocation()->getNeighbours()[dir];       // Get location in direction
    if(location == NULL) {
        displayState();
        return;
    }
    
    Treasure *goldAtDirection = dynamic_cast<Treasure *>(location->getOccupant());    // Check for treasure
    Staircase *stairsAtDirection = dynamic_cast<Staircase *>(location->getOccupant());    // Check for staircase
    
    if (goldAtDirection != NULL){
        // Safe even if DragonHoard, but will simply waste a turn if protected by a Dragon
        player = goldAtDirection->take(player);

        // Only move if the gold has been picked up
        if (location->getOccupant() == NULL)
            player->moveInDirection(dir);
        
        takeTurn();
        return;
    }
    else if (stairsAtDirection != NULL){
        stairsAtDirection->takeStairs();
    }
    else if(player->canMoveInDirection(dir)) {
        player->moveInDirection(dir);
        takeTurn();
    }
    else{
        // Display again if action failed.
        displayState();
    }
}

void Game::updatePlayer(Player * newPlayer){
    Cell * plocation = player->getLocation();
    player->setLocation(NULL);
    player = newPlayer;
    plocation->setOccupant(player);
    player->setLocation(plocation);
}

#ifdef DLC
void Game::konami(){
    player->notifyIncreasedEXP(50);
    displayState();
    
    action = "";    // Reset the action string for the next turn
}
void Game::showState(){
    displayState();
}

void Game::undoPlayer(){
    // Check if the current player is decorated
    if(player == BasePlayer::getInstance()) return;

    DecoratedPlayer *oldPlayer = dynamic_cast<DecoratedPlayer *>(player);
    if(oldPlayer == NULL) return;
    
    // Deletion procedure: undo() makes it safe to delete
    Player * revertedPlayer = oldPlayer->undo();
    updatePlayer(revertedPlayer);
    delete oldPlayer;
}

void Game::displayNcurses(const char * text){
    waddstr(window, text);
    refresh();
}

void Game::setWindow(WINDOW * window){
    this->window = window;
}

WINDOW * Game::getWindow(){
    return window;
}

void Game::playerClassCommand(string text){
    BasePlayer::getInstance()->specialAction(text);
    displayState();
    
    action = "";    // Reset the action string for the next turn
}

void Game::displayBartition(int numer, int denom, int width, std::string text, int colourFull, int colourEmpty, bool special){

    if (special)
        attron(A_STANDOUT);

    // Bartition = Bar Partition
    string bartition = "";

    int fillWidth;
    if (numer >= denom){
        fillWidth = width;
    }
    else if (numer <= 0){
        fillWidth = 0;
    }
    else{
        fillWidth = width * (numer - 1 ) / denom + 1;
    }

    // Writing first section (Full)
    int index;
    int textIndex = 0;
    attron(COLOR_PAIR(colourFull));
    for (index = 0; index < fillWidth && index < width; index++){
        if (textIndex == text.length()){
            addch(' ');
        }
        else{
            addch(text.at(textIndex));
            textIndex++;
        }
    }
    attroff(COLOR_PAIR(colourFull));
    // Writing second section (Empty)
    attron(COLOR_PAIR(colourEmpty));
    for (; index < width; index++){
        if (textIndex == text.length()){
            addch(' ');
        }
        else{
            addch(text.at(textIndex));
            textIndex++;
        }
    }
    attroff(COLOR_PAIR(colourEmpty));
    if (special)
        attroff(A_STANDOUT);
}

#endif

void Game::playerUseInDirection(int dir) {
    if(!gameRunning) return;
    
    if(player == NULL || player->getLocation() == NULL) {
        displayState();
        return;
    }
    
    Cell *location = player->getLocation()->getNeighbours()[dir];       // Get location in direction
    if(location == NULL) {
        displayState();
        return;
    }
    
    GameObject *objectAtDirection = location->getOccupant();            // Get occupant in direction
    if(objectAtDirection == NULL) {
        displayState();
        return;
    }
    
    // An item can be used in direction if it is in the list of items currently in the game
    for(vector<Item *>::iterator i = items.begin(); i != items.end(); ++i) {
        Item *item = *i;
        if(item == objectAtDirection) {
            updatePlayer(item->take(player));
            
            takeTurn();
            return;
        }
    }
    
    // Display again if action failed.
    displayState();
}

void Game::playerAttackInDirection(int dir) {
    if(!gameRunning) return;
    
    if(player == NULL || player->getLocation() == NULL) {
        displayState();
        return;
    }
    
    Cell *location = player->getLocation()->getNeighbours()[dir];       // Get location in direction
    if(location == NULL) {
        displayState();
        return;
    }
    
    GameObject *objectAtDirection = location->getOccupant();            // Get occupant in direction
    if(objectAtDirection == NULL) {
        displayState();
        return;
    }
    
    // An enemy can be attacked in direction if it is in the list of enemies currently in the game
    for(vector<Enemy *>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
        Enemy *enemy = *i;
        if(enemy == objectAtDirection) {
            player->attackEnemy(enemy);
            
            takeTurn();
            return;
        }
    }
    
    // Display again if action failed.
    displayState();
}

Player *Game::getPlayer() {
    return player;
}

void Game::addAction(string action) {
    this->action = this->action.length() == 0 ? action : this->action + " " + action;
}

void Game::startGame(char race, string placementFile) {
    gameRunning = true;
    
    // Reset the placement file to read from the top
    if(placementFileIn != NULL) {
        placementFileIn->clear();
        placementFileIn->seekg(0, ios::beg);
    }
    
    this->placementsFile = placementFile;
    if(placementsFile.length() > 0 && placementFileIn == NULL) {
        placementFileIn = new ifstream(placementFile.c_str());
    }
    
    // Set values to defaults
    currFloor = 1;
    score = 0;
    Merchant::setIsHostile(false);

    // Delete the Stairs
    delete stairs;
    stairs = NULL;
    
    deleteObjects();
    
    // Delete the Player
    BasePlayer::deleteInstance();
    player = NULL;
    
    if(race == RACE_SELECTION[HUMAN]) {
        BasePlayer::createHumanInstance();
        this->race = "Human";
    } else if(race == RACE_SELECTION[DWARF]) {
        BasePlayer::createDwarfInstance();
        this->race = "Dwarf";
    } else if(race == RACE_SELECTION[ELF]) {
        BasePlayer::createElfInstance();
        this->race = "Elf";
    } else if(race == RACE_SELECTION[ORC]) {
        BasePlayer::createOrcInstance();
        this->race = "Orc";
    }
    player = BasePlayer::getInstance();
    stairs = new Staircase(this);
    
    prepareCurrentFloor();
    display << endl << Language::getText("pcFull") << Language::getText("hasSpawned") << endl;
}

#ifdef DLC
void Game::startGamePlus(char race, char jobClass, string placementFile) {
    gameRunning = true;
    
    // Reset the placement file to read from the top
    if(placementFileIn != NULL) {
        placementFileIn->clear();
        placementFileIn->seekg(0, ios::beg);
    }
    
    this->placementsFile = placementFile;
    if(placementsFile.length() > 0 && placementFileIn == NULL) {
        placementFileIn = new ifstream(placementFile.c_str());
    }
    
    // Set values to defaults
    currFloor = 1;
    score = 0;
    Merchant::setIsHostile(false);
    
    // HP Bartition Colour Pairs
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_CYAN, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);

    // Delete the Stairs
    delete stairs;
    stairs = NULL;
    
    deleteObjects();
    
    // Delete the Player
    BasePlayer::deleteInstance();
    player = NULL;
    
    if(race == RACE_SELECTION[HUMAN]) {
        BasePlayer::createHumanInstance();
        this->race = "Human";
    } else if(race == RACE_SELECTION[DWARF]) {
        BasePlayer::createDwarfInstance();
        this->race = "Dwarf";
    } else if(race == RACE_SELECTION[ELF]) {
        BasePlayer::createElfInstance();
        this->race = "Elf";
    } else if(race == RACE_SELECTION[ORC]) {
        BasePlayer::createOrcInstance();
        this->race = "Orc";
    }

    if(jobClass == CLASS_SELECTION[SIMPLETON]) {
        BasePlayer::selectSimpleton();
        this->jobClass = "Simpleton";
    } else if(jobClass == CLASS_SELECTION[MOLE]) {
        BasePlayer::selectMole();
        this->jobClass = "Mole";
    } else {
        BasePlayer::selectSimpleton();
        this->jobClass = "Simpleton";
    }

    player = BasePlayer::getInstance();
    stairs = new Staircase(this);
    
    prepareCurrentFloor();
    ostringstream ncurseText;
    ncurseText << Language::getText("pcFull") << Language::getText("hasSpawned") << "\n";
    displayNcurses(ncurseText.str().c_str());
}
#endif

void Game::endGame() {
    gameRunning = false;
}

#ifdef DEBUG
/////////////////////////////
// DEBUGGING
/////////////////////////////

void Game::skip() {
    takeTurn();
}

void Game::die() {
    notifyPlayerDied();
}

void Game::nextFloor() {
    notifyStairUse();
}

void Game::dbSpawnPotion(int type, int dir){
    if (type < 0 || type > 5){
        return;
    }

    if(player == NULL || player->getLocation() == NULL) {
        return;
    }
    
    Cell *location = player->getLocation()->getNeighbours()[dir];       // Get location in direction
    if(location == NULL) {
        return;
    }
    
    // Check occupied
    GameObject *objectAtDirection = location->getOccupant();
    if(objectAtDirection != NULL) {
        return;
    }

    Potion * spawnedPotion;
    if (type == RH){
        spawnedPotion = new RestoreHealth(this);
    }
    else if (type == PH){
        spawnedPotion = new PoisonHealth(this);
    }
    else if (type == BA){
        spawnedPotion = new BoostAttack(this);
    }
    else if (type == WA){
        spawnedPotion = new WoundAttack(this);
    }
    else if (type == BD){
        spawnedPotion = new BoostDefence(this);
    }
    else if (type == WD){
        spawnedPotion = new WoundDefence(this);
    }
    location->setOccupant(spawnedPotion);
    spawnedPotion->setLocation(location);
    items.push_back(spawnedPotion);
    displayState();
}

void Game::dbSpawnGold(int value, int dir){
    if (value < 0){
        return;
    }

    if(player == NULL || player->getLocation() == NULL) {
        return;
    }
    
    Cell *location = player->getLocation()->getNeighbours()[dir];       // Get location in direction
    if(location == NULL) {
        return;
    }
    
    // Check occupied
    GameObject *objectAtDirection = location->getOccupant();
    if(objectAtDirection != NULL) {
        return;
    }

    GoldPile * spawnedGold = new GoldPile(this, value);

    location->setOccupant(spawnedGold);
    spawnedGold->setLocation(location);
    items.push_back(spawnedGold);
    displayState();
}
#endif
