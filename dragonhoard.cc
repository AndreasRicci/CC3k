#include <sstream>
#include <string>
#include "dragonhoard.h"
#include "constants.h"
#include "cell.h"
#include "language.h"
#include "baseplayer.h"

using namespace std;

DragonHoard::DragonHoard(Game * game, Dragon * keeper): Treasure(TREASURES[DRAGON_HOARD][VALUE], game), keeper(keeper) {}

DragonHoard::~DragonHoard() {}

Dragon * DragonHoard::getDragon(){
    return keeper;
}

void DragonHoard::setDragon(Dragon * dragon){
    keeper = dragon;
}

Player * DragonHoard::take(Player * player){
    if (!keeper){
        int loot = value * player->getGoldMultiplier()/100;
        BasePlayer::getInstance()->setGold(player->getGold() + loot);
        game->addToScore(loot * player->getScoreMultiplier()/100);
        location->setOccupant(NULL);
        location = NULL;

        ostringstream goldAmount;
        goldAmount << loot;

        game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("dragonHoard") + Language::getText("worth") + goldAmount.str() + " " + Language::getText("Gold") + ".");
    }
    
    return player;
}