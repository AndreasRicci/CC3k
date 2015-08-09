#include "goldpile.h"
#include "cell.h"
#include "language.h"
#include "baseplayer.h"
#include <sstream>
#include <string>

using namespace std;

GoldPile::GoldPile(Game * game, int value): Treasure(value, game) {}

GoldPile::~GoldPile() {}

Player * GoldPile::take(Player * player){
    int loot = value * player->getGoldMultiplier()/100;
    BasePlayer::getInstance()->setGold(player->getGold() + loot);
    game->addToScore(loot * player->getScoreMultiplier()/100);
    location->setOccupant(NULL);
    location = NULL;

    ostringstream goldAmount;
    goldAmount << loot;

    game->addAction(Language::getText("pc") + Language::getText("picksUp") + Language::getText("goldPile") + Language::getText("worth") + goldAmount.str() + " " + Language::getText("Gold") + ".");
    
    return player;
}