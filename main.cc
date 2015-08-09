#include <iostream>
#include <string>
#include <cstdlib>
#include <ncurses.h>
#include "game.h"
#include "language.h"
#include "utils.h"
using namespace std;

// Window for ncurses
#ifdef DLC
WINDOW * window;
bool usedMole;
#endif

// Used for playGame input
string gameIn;

// Game State function
// Initially called to start the game
void playGame(Game* game){
    /* GAME STATE
       During the game, the player can use the following commands:
        'q': quit
        'h': play as Human
        'e': play as Elf
        'd': play as Dwarf
        'o': play as Orc
    */
    string direction;
    int dir;
    // Set input for lulz
    cout << "\e[1;35m";
    while(cin >> gameIn) {
        cout << "\e[0m";
        // Quit
        if(gameIn == "q") {
            break;
        }
        // Restart
        else if(gameIn == "r") {
            game->endGame();
            cout << "\e[1;32;40m";
            cout << Language::getText("selectRace") << endl;
            break;
        }
        // Use potion in <direction>
        else if(gameIn == "u"){
            cin >> direction;
            dir = directionToInt(direction);
            
            if (dir != ERROR)
                game->playerUseInDirection(dir);
            else
                cout << Language::getText("invalidDir") << endl;
        }
        // Attack enemy in <direction>
        else if(gameIn == "a"){
            cin >> direction;
            dir = directionToInt(direction);
            
            if (dir != ERROR)
                game->playerAttackInDirection(dir);
            else
                cout << Language::getText("invalidDir") << endl;
        }
        #ifdef DEBUG
        /*
        ||  DEBUGGING COMMANDS
        ||___________________________ */
        else if(gameIn == "s") {
            // Skip player turn (debugging)
            game->skip();
        }
        else if(gameIn == "n") {
            // Go to next floor (debugging)
            game->nextFloor();
        }
        else if(gameIn == "d") {
            // Kill player (debugging)
            game->die();
        }
        else if (gameIn == "spawnPotion"){
            int type;
            cin >> type;
            cin >> direction;
            dir = directionToInt(direction);
            game->dbSpawnPotion(type, dir);
        }
        else if (gameIn == "spawnGold"){
            int type;
            cin >> type;
            cin >> direction;
            dir = directionToInt(direction);
            game->dbSpawnGold(type, dir);
        }
        
        /*||  END OF DEBUGGING COMMANDS
        ||___________________________*/
        #endif
        // Movement
        else {
            dir = directionToInt(gameIn);
            if (dir != ERROR)
                game->playerMoveInDirection(dir);
            else
                cout << "Incorrect input." << endl;
        }
        // Restore colour for input    
        cout << "\e[1;35m";
    }
}

#ifdef DLC
// Printing functions
void print(const char * text){
    wprintw(window, text);
}

void line(){
    waddch(window, '\n');
}

void println(const char * text){
    print(text);
    line();
}

void printIntro(){
    println(Language::getText("selectRace").c_str());
    println("Press 'q' to quit.");
}

string getstring(){
    string text = "";
    char input = getch();
    while (input != '\n'){
        text += input;
        input = getch();
    }
    return string(text);
}

void printControls(){
    println("Controls:");
    println("=Direction=");
    println("QWE  ");
    println("A D  These keys are mapped to the 8 cardinal/sub-cardinal directions.");
    println("ZXC  ");
    line();
    println("Use these keys to move, or to specify a direction following a command.");
    println("If you miss using WASD controls, you can also pretend S is X.");
    line();
    println("Gold will automatically be picked up if you walk over it.");
    line();
    println("=Attacking=");
    println("K    Press K, then specify a direction to attack an enemy in that direction.");
    line();
    println("=Potion Use=");
    println("U    Press U, then specify a direction to use a potion in that direction.");
    line();
    println("=Misc.=");
    println("::help, ::h     Type the command to view this screen again.");
    println("::quit, ::q     Type the command to quit the game.");
    println("::reset, ::r    Type the command to restart the game.");
    line();
    println("Press any key to continue.");
    getch();
    clear();
}

// DLC version of playGame
void playGamePlus(Game* game){
    char input;
    int dir;
    while(true) {
        input = getch();

        // In case of failure
        if (input == ERR)
            break;

        // Command Mode
        if(input == ':') {
            string command = getstring();

            if (command == ":quit" || command == ":q"){
                clear();
                gameIn = "q";
                break;
            }
            else if (command == ":reset" || command == ":r"){
                game->endGame();
                clear();
                printIntro();
                break;
            }
            else if (command == ":help" || command == ":h"){
                clear();
                printControls();
                clear();
                game->showState();
            }
            else if (command == ":wwxxadadku" || command == ":wwxxasasku"){
                game->konami();
            }
            else{
                game->playerClassCommand(command);
            }
        }
        // Use potion in <direction>
        else if(input == 'u'){
            deleteln();
            print("USE: ");
            input = getch();
            dir = directionToInt(input);
            
            if (dir != ERROR)
                game->playerUseInDirection(dir);
            else{
                line();
                println(Language::getText("invalidDir").c_str());
            }
        }
        // Attack enemy in <direction>
        else if(input == 'k'){
            deleteln();
            print("ATTACK: ");
            input = getch();
            dir = directionToInt(input);
            
            if (dir != ERROR)
                game->playerAttackInDirection(dir);
            else{
                line();
                println(Language::getText("invalidDir").c_str());
            }
        }
        else{
            dir = directionToInt(input);
            if (dir != ERROR)
                game->playerMoveInDirection(dir);
            else{
                line();
                println("Incorrect input.");
            }

        }
        // Restore colour for input    
    }
}
#endif

int main(int argc, char *argv[]) {
    srand(time(NULL));  // Random seed
    
    Game * game = Game::instance();

#ifdef DLC
    // Setting up ncurses mode
    window = initscr();
    char input;
    game->setWindow(window);

    // Intro message
    printIntro();
    while(true) {
        input = getch();

        // In case of failure
        if (input == ERR)
            break;

        if(input == 'q') {
            break;
        }
        else{
            // Clear current messages
            clear();

            // Determine race
            char race;
            if (input == RACE_SELECTION[HUMAN] || 
                input == RACE_SELECTION[ELF] || 
                input == RACE_SELECTION[DWARF] || 
                input == RACE_SELECTION[ORC]){
                race = input;
            }
            else{
                race = ERROR;
            }

            if (race != ERROR){
                println(Language::getText("selectClass").c_str());
                char jobClass;
                input = getch();
                if (input == CLASS_SELECTION[SIMPLETON] ||
                    input == CLASS_SELECTION[MOLE] /*||
                    input == CLASS_SELECTION[PICKPOCKET] ||
                    input == CLASS_SELECTION[GENTLEMAN]*/
                    ){
                    jobClass = input;
                    if (jobClass == CLASS_SELECTION[MOLE]){
                        usedMole = true;
                    }
                }
                else{
                    jobClass = ERROR;
                }
                
                if (jobClass != ERROR){
                // Starting game with valid race
                    clear();
                    printControls();
                    // Custom game map detected
                    if (argc == 2){
                        game->startGamePlus(race, jobClass, argv[1]);
                    }
                    // Regular game start
                    else{
                        game->startGamePlus(race, jobClass);
                    }
                    playGamePlus(game);

                    // Detect if the user ended the game intentionally.
                    if (gameIn == "q")
                        break;

                    if (usedMole){
                        usedMole = false;

                    }
                }
                else{
                    clear();
                    printIntro();
                    println("Invalid input.");
                }
            }
            else{
                clear();
                printIntro();
                println("Invalid input.");
            }
        }
        // Restore colour for input    
    }
    // End game and ncurses window
    game->endGame();
    endwin();
#else
    char input;
    cout << "\e[1;32;40m";
    cout << Language::getText("selectRace") << endl;
    
    /* PRE-GAME STATE
       At the start, the player can use the following commands:
        'q': quit
        'h': play as Human
        'e': play as Elf
        'd': play as Dwarf
        'o': play as Orc
    */
    // Purple input for teh lulz
    cout << "\e[1;35m";
    while(cin >> input) {
        // Back to B&W for display
        cout << "\e[0m";
        if(input == 'q') {
            break;
        }
        else{
            // Determine race
            char race;
            if (input == RACE_SELECTION[HUMAN] || input == RACE_SELECTION[ELF]|| input == RACE_SELECTION[DWARF] || input == RACE_SELECTION[ORC]){
                race = input;
            }
            else{
                race = ERROR;
            }

            // Starting game with valid race
            if (race != ERROR){
                // Custom game map detected
                if (argc == 2){
                    game->startGame(race, argv[1]);
                }
                // Regular game start
                else{
                    game->startGame(race);
                }

                playGame(game);

                // Detect if the user ended the game intentionally.
                if (gameIn == "q")
                    break;
            }
        }
        // Restore colour for input    
        cout << "\e[1;35m";
    }
    game->endGame();
#endif
}
