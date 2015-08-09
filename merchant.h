#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "movableenemy.h"

class Merchant : public MovableEnemy {
private:
    static bool isHostile;                       // Are Merchants hostile to the Player?
protected:
    void preAttacked(Player *player);            // Merchants need to become hostile
    void preDeath();                             // Need to drop the merchant hoard
public:
    Merchant(Game *game);
    ~Merchant();
    
    bool getIsHostile();                         // Returns true iff the Merchant is hostile to the Player
    bool getCanAttack();
    static void setIsHostile(bool isHostile);
};

#endif
