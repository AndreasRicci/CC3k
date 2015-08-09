#include "language.h"

using namespace std;

bool Language::languageInitialized = false;
map<string, map<string, string>* > Language::languageToDictionary;
map<string, string> Language::englishDictionary;

void Language::initLanguage() {
    // Init the mapping from language to dictionary
    languageToDictionary[english] = &englishDictionary;
    
    // Init each individual language dictionary
    englishDictionary["pc"]                 = "PC";
    englishDictionary["pcFull"]             = "Player character";
    englishDictionary["hasSpawned"]         = " has spawned.";
    englishDictionary["hasBeenSlain"]       = " has been slain!";
    englishDictionary["hasSlain"]           = " has slain ";
    
    englishDictionary["winGame"]            = "You won!";
    englishDictionary["loseGame"]           = "You lost!";
    englishDictionary["finalScore"]         = "Your final score is: ";
    #ifdef DLC
    englishDictionary["restartGame"]        = "Enter ::r to restart the game.";
    englishDictionary["quitGame"]           = "Enter ::q to quit the game.";
    #else
    englishDictionary["restartGame"]        = "Enter r to restart the game.";
    englishDictionary["quitGame"]           = "Enter q to quit the game.";
    #endif
    englishDictionary["selectRace"]         = "Please select a race: (h)uman, (e)lf, (d)warf, or (o)rc";
    englishDictionary["selectClass"]        = "Please select a class: (s)impleton.\n(Hint: Choose (s)impleton.)";
    //englishDictionary["selectClass"]        = "Please select a class: (s)impleton, (m)ole, (p)ickpocket, or (g)entleman";
    englishDictionary["invalidDir"]         = "That's not a valid direction!";
    
    englishDictionary["human"]              = "Human";
    englishDictionary["dwarf"]              = "Dwarf";
    englishDictionary["elf"]                = "Elf";
    englishDictionary["orc"]                = "Orc";
    
    englishDictionary["HP"]                 = "HP";
    englishDictionary["Gold"]               = "Gold";
    englishDictionary["Atk"]                = "Atk";
    englishDictionary["Def"]                = "Def";
    englishDictionary["race:"]              = "Race:";
    englishDictionary["gold:"]              = englishDictionary["Gold"] + ": ";
    englishDictionary["floor"]              = "Floor ";
    englishDictionary["hp:"]                = englishDictionary["HP"] + ": ";
    englishDictionary["atk:"]               = englishDictionary["Atk"] + ": ";
    englishDictionary["def:"]               = englishDictionary["Def"] + ": ";
    englishDictionary["action:"]            = "Action: ";
    
    englishDictionary["deals"]              = " deals ";
    englishDictionary["steals"]             = " steals ";
    englishDictionary["absorbs"]            = " absorbs ";
    englishDictionary["uses"]               = " uses ";
    englishDictionary["moves"]              = " moves ";
    englishDictionary["damageTo"]           = " damage to ";
    englishDictionary["and"]                = " and ";
    englishDictionary["and-"]               = "and";
    englishDictionary["sees"]               = " sees ";
    englishDictionary["seesA(n)"]           = " sees a(n) ";
    englishDictionary["picksUp"]            = " picks up ";
    englishDictionary["worth"]              = " worth ";
    englishDictionary["misses"]             = "misses";
    englishDictionary["attackButMiss"]      = " attacks but " + englishDictionary["misses"] + " ";
    
    englishDictionary["no"]                 = "North";
    englishDictionary["so"]                 = "South";
    englishDictionary["ea"]                 = "East";
    englishDictionary["we"]                 = "West";
    englishDictionary["ne"]                 = englishDictionary["no"] + "-" + englishDictionary["ea"];
    englishDictionary["nw"]                 = englishDictionary["no"] + "-" + englishDictionary["we"];
    englishDictionary["se"]                 = englishDictionary["so"] + "-" + englishDictionary["ea"];
    englishDictionary["sw"]                 = englishDictionary["so"] + "-" + englishDictionary["we"];
    
    englishDictionary["potion"]             = "potion";
    englishDictionary["potions"]            = "potions";
    englishDictionary["goldPile"]           = "pile of gold";
    englishDictionary["goldPiles"]          = "piles of gold";
    englishDictionary["dragonHoard"]        = "dragon's hoard";
    englishDictionary["dragonHoards"]       = "dragon's hoards";
    englishDictionary["unknown"]            = "unknown";
    englishDictionary["Wound"]              = "Wound";
    englishDictionary["Boost"]              = "Boost";
    englishDictionary["unknownP"]           = englishDictionary["unknown"] + " " + englishDictionary["potion"];
    englishDictionary["unknownPs"]          = englishDictionary["unknown"] + " " + englishDictionary["potions"];
    englishDictionary["RH"]                 = "Restore " + englishDictionary["HP"] + " " + englishDictionary["potion"];
    englishDictionary["PH"]                 = "Poison " + englishDictionary["HP"] + " " + englishDictionary["potion"];
    englishDictionary["BA"]                 = englishDictionary["Boost"] + " " + englishDictionary["Atk"] + " " + englishDictionary["potion"];
    englishDictionary["WA"]                 = englishDictionary["Wound"] + " " + englishDictionary["Atk"] + " " + englishDictionary["potion"];
    englishDictionary["BD"]                 = englishDictionary["Boost"] + " " + englishDictionary["Def"] + " " + englishDictionary["potion"];
    englishDictionary["WD"]                 = englishDictionary["Wound"] + " " + englishDictionary["Def"] + " " + englishDictionary["potion"];
}

string Language::getText(string shorthand, string language) {
    // Make sure our languages are initialized
    if (!languageInitialized) {
        initLanguage();
        languageInitialized = true;
    }

    return (*languageToDictionary[language])[shorthand];
}
