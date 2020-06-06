//
//  Player.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Player_h
#define Player_h


#include "Actor.h"
#include "GameObjects.h"
#include "Weapon.h"
#include "Scroll.h"
#include <string>


class Dungeon;

class Player : public Actor
{
public:
    Player(int r, int c, Dungeon* dungeon); //Constructor
    virtual ~Player(); //Destructor

    GameObjects** inventory();
    int sizeOfInventory() const;
    virtual char icon() const;
    virtual bool isSmart() const;
    virtual int smellDistance() const;

    bool addToInventory(GameObjects* item);
    std::string wieldWeapon(int pos);
    std::string readScroll(int pos, bool &tele);
    bool eraseInventory(int pos);
    void selfHeal(); //for player and dragon, this function will give a 0.1 chance to regain one hit point

    void displayInventory() const; //to display inventory

private:
    GameObjects* m_inventory[25];
    int m_sizeInventory;
    int m_capacityInventory;
};


#endif /* Player_h */
