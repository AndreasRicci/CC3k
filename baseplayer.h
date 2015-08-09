#ifndef __BASEPLAYER_H__
#define __BASEPLAYER_H__

#include "player.h"

class BasePlayer : public Player {
private:
    static BasePlayer *playerInstance;
protected:
    BasePlayer(Game *game, int maxHP, int attack, int defence, int accuracy, int evasion, int goldMultiplier, int scoreMultiplier, int positivePotionMultiplier, int negativePotionMultiplier);
public:
    ~BasePlayer();
    static BasePlayer * getInstance();
    static void deleteInstance();
    static void createHumanInstance();
    static void createDwarfInstance();
    static void createElfInstance();
    static void createOrcInstance();
    #ifdef DLC
    static void selectSimpleton();
    static void selectMole();
    #endif
};

#endif
