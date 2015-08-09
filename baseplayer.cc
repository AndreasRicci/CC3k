#include "baseplayer.h"
#include "human.h"
#include "game.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "simpleton.h"
#include "mole.h"

BasePlayer *BasePlayer::playerInstance = NULL;

BasePlayer::BasePlayer(Game *game, int maxHP, int attack, int defence, int accuracy, int evasion, int goldMultiplier, int scoreMultiplier, int positivePotionMultiplier, int negativePotionMultiplier):
    Player(game, maxHP, attack, defence, accuracy, evasion, goldMultiplier, scoreMultiplier, positivePotionMultiplier, negativePotionMultiplier) { };

BasePlayer::~BasePlayer() { }


BasePlayer * BasePlayer::getInstance() {
    return playerInstance;
}

void BasePlayer::deleteInstance() {
    delete playerInstance;
    playerInstance = NULL;
}

void BasePlayer::createHumanInstance(){
    if(playerInstance != NULL) {
        deleteInstance();
    }

    playerInstance = new Human(Game::instance());
}

void BasePlayer::createDwarfInstance(){
    if(playerInstance != NULL) {
        deleteInstance();
    }

    playerInstance = new Dwarf(Game::instance());
}

void BasePlayer::createElfInstance(){
    if(playerInstance != NULL) {
        deleteInstance();
    }

    playerInstance = new Elf(Game::instance());
}

void BasePlayer::createOrcInstance(){
    if (playerInstance != NULL) {
        deleteInstance();
    }

    playerInstance = new Orc(Game::instance());
}

#ifdef DLC
void BasePlayer::selectSimpleton(){
    playerInstance = new Simpleton(playerInstance);
}

void BasePlayer::selectMole(){
    playerInstance = new Mole(playerInstance);
}
#endif