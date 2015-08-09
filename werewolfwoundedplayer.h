#ifdef DLC

#ifndef __WEREWOLFWOUNDEDPLAYER_H__
#define __WEREWOLFWOUNDEDPLAYER_H__

#include "decoratedplayer.h"
#include "player.h"

class WerewolfWoundedPlayer : public DecoratedPlayer {
private:
    static int bleeding;                        // Represents duration of bleeding effect
public:
    int getMaxHP();                             // Gets Max HP
    int getCurrentHP();                         // Gets HP
    int getAttack();                            // Gets attack
    int getDefence();                           // Gets defence
    int getGold();                              // Gets gold
    int getAccuracy();                          // Gets accuracy
    int getEvasion();                           // Gets evasion
    int getGoldMultiplier();                    // Gets gold multiplier
    int getPositivePotionMultiplier();          // Gets positive potion effect multiplier
    int getNegativePotionMultiplier();          // Gets negative potion effect multiplier
    int getScoreMultiplier();                   // Gets score multiplier
    bool isBleeding();                          // Tells werewolf whether or not player is bleeding
    #ifdef DLC
    void preAttack(Enemy *enemy);               // Override: Event before attacking an Enemy
    void postAttack(Enemy *enemy);              // Override: Event after attacking an Enemy
    void preAttacked(Enemy *enemy);             // Override: Event before attacking an Enemy
    void postAttacked(Enemy *enemy);            // Override: Event after attacking an Enemy
    void preMove(int dir);                      // Override: Event after moving in direction dir
    void postMove(int dir);                     // Override: BLEEDING/REGEN EFFECT
    #endif
    WerewolfWoundedPlayer(Player * player);
    ~WerewolfWoundedPlayer();
};

#endif

#endif
