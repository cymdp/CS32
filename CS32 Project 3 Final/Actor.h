//
//  Actor.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//


#ifndef Actor_h
#define Actor_h


#include "Weapon.h"
#include <string>


class Dungeon;

class Actor {
public:
    Actor(int strength, int dex, int armor, int HP, int r, int c, std::string name, Weapon* weapon, Dungeon* dungeon); //Constructor
    virtual ~Actor(); //Destructor


    int strength() const;
    int dex() const;
    int armor() const;
    int hp() const;
    int sleep() const; //returns sleepTime
    int row() const;
    int col() const;
    std::string name() const;
    Weapon* weapon() const;
    Dungeon* dungeon() const;
    virtual char icon() const = 0; //different actors will have different icons
    bool isDead() const;
    virtual bool isSmart() const = 0; //different actors will have different levels of intelligence
    virtual int smellDistance() const = 0; //different actors will have different smellDistances


    void addHP(int amt);
    void fallAsleep(int time);
    void wake();
    void move(int r, int c);
    
    virtual void cheat();
    virtual void addMaxHP(int amt);
    virtual void addStrength(int amt);
    virtual void addDexterity(int amt);
    virtual void addArmor(int amt);
    virtual void changeWeapon(Weapon* nWeapon);
    void changeDungeon(Dungeon* newDungeon);


    // Playing the game
    virtual std::string attack(Actor* victim); //takes a pointer to actor being attacked and updates the status of actor while under attack
    virtual void selfHeal(); //for player and dragon, this function will give a 0.1 chance to regain one hit point

private:
    int m_strength;
    int m_dexterity;
    int m_armor;
    int m_hitPoint;
    int m_maxHP;
    int m_sleepTime;
    int m_row;
    int m_col;
    std::string m_name;
    Weapon* m_weapon;
    Dungeon* m_dungeon;
};


#endif /* Actor_h */
