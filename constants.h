#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>

// Various display constants
const char DISPLAY_TREASURE = 'G';
const char DISPLAY_POTION = 'P';
const char DISPLAY_STAIRS = '\\';

/*  General Game Constants 
||  Constants describing hard-valued game constants.
*/
const int ROWS                  = 25;
const int COLMS                 = 79;
const int CHAMBERS              = 5;
const int MAX_FLOORS            = 8;
const int MAX_FLOOR_POTIONS     = 10;
const int MAX_FLOOR_TREASURES   = 10;
const int MAX_FLOOR_ENEMIES     = 20;
const int TOTAL_POTIONS         = 6;
const int TOTAL_DISPLAY_CELLS   = 6;
const int ERROR                 = -1;
const int MAX_LEVEL             = 10;

const int LEVEL_EXP_TO_NEXT[] = {
    10, 20, 30, 40, 50, 60, 70, 80, 90, 100
};
const int LEVEL_STATS_GAIN[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};
const int LEVEL_MAXHP_GAIN[] = {
    10, 12, 12, 14, 14, 16, 16, 18, 18, 20
};

/*  Movement Mappings
||  Constants describing indicies of Directions corresponing to indicies of neighbouring Cells
*/
// Variable names refer to the shorthand for each direction
const int NW = 0;
const int NO = 1;
const int NE = 2;
const int WE = 3;
const int EA = 4;
const int SW = 5;
const int SO = 6;
const int SE = 7;
const std::string DIRECTION[] = {
    "nw", "no", "ne", "we", "ea", "sw", "so", "se"
};

// Mappings to Cell related indicies
const int FLOOR         = 0;
const int VERT_WALL     = 1;
const int HORI_WALL     = 2;
const int DOOR          = 3;
const int PASSAGE       = 4;
const int SPACE         = 5;

// Chars for displaying Cells
const char DISPLAY_CELLS[] =
{
    '.', '|', '-', '+', '#', ' '
};

// Which Cells are Enemies allowed to occupy?
const int ENEMY_NUM_ALLOWED_CELLS = 1;
const char ENEMY_ALLOWED_CELLS[ENEMY_NUM_ALLOWED_CELLS] =
{
    DISPLAY_CELLS[FLOOR]
};

// Which Cells are Players allowed to occupy?
const int PLAYER_NUM_ALLOWED_CELLS = 3;
const char PLAYER_ALLOWED_CELLS[PLAYER_NUM_ALLOWED_CELLS] =
{
    DISPLAY_CELLS[FLOOR], DISPLAY_CELLS[DOOR], DISPLAY_CELLS[PASSAGE]
};

/*  Entity Characteristic Mappings 
||  Constants describing columns of the characteristic tables.
*/
// Field Sizes
const int RACE_FIELDS       = 9;
const int ENEMY_FIELDS      = 6;
const int POTION_FIELDS     = 4;
const int TREASURE_FIELDS   = 2;

// Characters and Enemies
const int HP        = 0;
const int ATK       = 1;
const int DEF       = 2;

// Race Multipliers (in %)
const int ACCURACY                      = 3;
const int EVASION                       = 4;
const int GOLD_MULTIPLIER               = 5;
const int SCORE_MULTIPLIER              = 6;
const int POSITIVE_POTION_MULTIPLIER    = 7;
const int NEGATIVE_POTION_MULTIPLIER    = 8;

// Enemy Stats
const int GOLD          = 3;
const int EXPER         = 4;
const int ENEMY_SPAWN   = 5;

// Items
const int ITEM_SPAWN    = 0;
const int VALUE         = 1;
const int HP_CHANGE     = 1;
const int ATK_CHANGE    = 2;
const int DEF_CHANGE    = 3;

/*  Race Characteristics Table
||  {HP, Atk, Def, Gold Mult., Score Mult., +Potion Mult., -Potion Mult.}
*/

// Race Mappings
const int HUMAN     = 0;
const int DWARF     = 1;
const int ELF       = 2;
const int ORC       = 3;

const int RACE[][RACE_FIELDS] =
{   // Human
    {140, 20, 20, 100, 50, 100, 150, 100, 100},
    // Dwarf
    {100, 20, 30, 100, 50, 200, 100, 100, 100},
    // Elf
    {100, 20, 30, 100, 50, 100, 100, 100, -100},
    // Orc
    {180, 30, 25, 100, 50, 50, 100, 100, 100}
};

// Chars for race selection
const char RACE_SELECTION[] =
{
    'h', 'd', 'e', 'o'
};

// Race Mappings
const int SIMPLETON = 0;
const int MOLE      = 1;
const int PICKPOCKET= 2;
const int GENTLEMAN = 3;

// Chars for class selection
const char CLASS_SELECTION[] =
{
    's', 'm', 'p', 'g'
};

/*  Enemy Characteristics Table
||  {HP, Atk, Def, Gold, Spawn}
*/

// Enemy Mappings
const int WEREWOLF  = 0;
const int VAMPIRE   = 1;
const int GOBLIN    = 2;
const int TROLL     = 3;
const int PHOENIX   = 4;
const int MERCHANT  = 5;
const int DRAGON    = 6;

const int ENEMIES[][ENEMY_FIELDS] =
{   // Werewolf
    {120, 30, 5, 1, 6, 4},
    // Vampire
    {50, 25, 25, 1, 5, 3},
    // Goblin
    {70, 5, 10, 1, 2, 5},
    // Troll
    {120, 25, 15, 1, 4, 2},
    // Phoenix
    {50, 35, 20, 1, 3, 2},
    // Merchant
    {30, 70, 5, 0, 20, 2},
    // Dragon
    {150, 20, 20, 0, 25, 0}
};

// Chars for displaying Enemies
const int DISPLAY_ENEMIES[] =
{
    'W', 'V', 'N', 'T', 'X', 'M', 'D'
};

/*  Treasure Table
||  {Spawn, Value}
*/

// Treasure Mappings
const int NORMAL_PILE       = 0;
const int SMALL_HOARD       = 1;
const int MERCHANT_HOARD    = 2;
const int DRAGON_HOARD      = 3;

const int TREASURES[][TREASURE_FIELDS] =
{   // Size: Normal Pile
    {5, 1},
    // Size: Small Hoard
    {2, 2},
    // Size: Merchant Hoard
    {0, 4},
    // Size: Dragon Hoard
    {1, 6}
};

/*  Potion Table
||  {Spawn, HP Effect, Atk Effect, Def Effect}
*/

// Potion Mappings
const int RH = 0;
const int PH = 1;
const int BA = 2;
const int WA = 3;
const int BD = 4;
const int WD = 5;

const int POTIONS[][POTION_FIELDS] =
{   // Restore HP
    {1, 10, 0, 0},
    // Poison HP
    {1, -10, 0, 0},
    // Boost Attack
    {1, 0, 5, 0},
    // Wound Attack
    {1, 0, -5, 0},
    // Boost Defence
    {1, 0, 0, 5},
    // Wound Defence
    {1, 0, 0, -5}
};

const std::string POTIONS_SHORT[]=
{
    "RH", "PH", "BA", "WA", "BD", "WD"
};

#endif
