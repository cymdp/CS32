//
//  Weapon.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Weapon_h
#define Weapon_h

#include <string>
#include "GameObjects.h"
#include "utilities.h"


class Weapon : public GameObjects //Weapon is an abstract class
{
public:
    Weapon(int damage, int dex, std::string name, std::string verb, int row, int col) //Constructor
        : m_damage(damage), m_dexterityBonus(dex), m_name(name), m_verb(verb), GameObjects(row, col)
    {}
    virtual ~Weapon() //Destructor
    {}
    
    int damage() const
    {
        return m_damage;
    }
    
    int dex() const
    {
        return m_dexterityBonus;
    }
    
    virtual std::string name() const
    {
        return m_name;
    }
    
    std::string weaponAction() const
    {
        return m_verb;
    }
    virtual char icon() const
    {
        return ')';
    }

    //Pure virtual functions sleepTime
    virtual int putToSleep() const = 0;

private:
    int m_damage;
    int m_dexterityBonus;
    std::string m_name;
    std::string m_verb;
};

//Constructors and Destructors of Weapons

class Mace : public Weapon
{
public:
    Mace(int row, int col) : Weapon(2, 0, "mace", "swings", row, col)
    {}
    
    virtual ~Mace()
    {}

    virtual int putToSleep() const
    {
        return 0;
    }
};


class shortSword : public Weapon
{
public:
    shortSword(int row, int col) : Weapon(2, 0, "short sword", "slashes", row, col)
    {}
    
    virtual ~shortSword()
    {}

    virtual int putToSleep() const
    {
        return 0;
    }
};


class longSword : public Weapon
{
public:
    
    longSword(int row, int col) : Weapon(4, 2, "long sword", "swings", row, col)
    {}
    
    virtual ~longSword()
    {}

    virtual int putToSleep() const
    {
        return 0;
    }
};


class magicAxe : public Weapon
{
public:
    magicAxe(int row, int col) : Weapon(5, 5, "magic axe", "chops", row, col)
    {}
    
    virtual ~magicAxe()
    {}

    virtual int putToSleep() const
    {
        return 0;
    }
};


class magicFangs : public Weapon
{
public:
    magicFangs(int row, int col) : Weapon(2, 3, "magic fangs of sleep", "strikes", row, col)
    {}
    
    virtual ~magicFangs()
    {}

    virtual int putToSleep() const
    {
        if (trueWithProbability(0.2))
            return 2 + randInt(5);
        else
            return 0;
    }
};


#endif /* Weapon_h */

