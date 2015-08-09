#ifdef DLC

#include "playerclass.h"
#include "player.h"
#include "game.h"
#include <ncurses.h>
#include <string>

using namespace std;

PlayerClass::PlayerClass(Player *component): 
    BasePlayer(Game::instance(), 
        component->getMaxHP(),
        component->getAttack(),
        component->getDefence(),
        component->getAccuracy(),
        component->getEvasion(),
        component->getGoldMultiplier(),
        component->getScoreMultiplier(),
        component->getPositivePotionMultiplier(),
        component->getNegativePotionMultiplier()),
    component(component) {
        window = Game::instance()->getWindow();
    }

PlayerClass::~PlayerClass() {}

#endif
