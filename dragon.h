#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "enemy.h"

class DragonHoard;

class Dragon : public Enemy {
private:
    DragonHoard *hoard;                  // The hoard this Dragon is guarding (NULL means no hoard to guard)
protected:
    void preDeath();                     // Hoard needs to know the Dragon died (so it can be picked up)
public:
    Dragon(Game *game, DragonHoard *hoard = NULL);
    ~Dragon();
    
    DragonHoard *getHoard();             // Get the hoard to guard (NULL means no hoard to guard)
    void setHoard(DragonHoard *hoard);   // Set the hoard this Dragon guards
    
    bool getCanAttack();
};

#endif
