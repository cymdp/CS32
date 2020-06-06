//
//  Actor.cpp
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//


#include "Actor.h"
#include "utilities.h"
#include "hfunctions.h"
#include <iostream>
using namespace std;


Actor::Actor(int strength, int dex, int armor, int HP, int r, int c, string name, Weapon* weapon, Dungeon* dungeon) //Constructor
    :m_strength(strength), m_dexterity(dex), m_armor(armor), m_hitPoint(HP), m_maxHP(HP), m_row(r), m_col(c), m_name(name), m_weapon(weapon), m_sleepTime(0), m_dungeon(dungeon)
{}


Actor::~Actor() //Destructor
{}


int Actor::strength() const
{
    return m_strength;
}


int Actor::dex() const
{
    return m_dexterity;
}


int Actor::armor() const
{
    return m_armor;
}


int Actor::hp() const
{
    return m_hitPoint;
}


int Actor::sleep() const //return sleepTime
{
    return m_sleepTime;
}


int Actor::row() const
{
    return m_row;
}


int Actor::col() const
{
    return m_col;
}


string Actor::name() const
{
    return m_name;
}


Weapon* Actor::weapon() const
{
    return m_weapon;
}


Dungeon* Actor::dungeon() const
{
    return m_dungeon;
}


bool Actor::isDead() const //return true is actor is dead
{
    return m_hitPoint <= 0;
}


void Actor::addHP(int amt)
{
    m_hitPoint += amt;
    if (m_hitPoint > m_maxHP)
        m_hitPoint = m_maxHP;
}


void Actor::fallAsleep(int time) //updates sleepTime
{
    m_sleepTime = max(time, m_sleepTime);
}


void Actor::wake() //decrements sleepTime
{
    m_sleepTime--;
}


void Actor::move(int r, int c)
{
    m_row = r;
    m_col = c;
}


void Actor::cheat()
{
    m_maxHP = 50;
    m_hitPoint = 50;
    m_strength = 9;
}


void Actor::addMaxHP(int amt)
{
    m_maxHP += amt;
    if (m_maxHP < 0)
        m_maxHP = 0;
    else if (m_maxHP > 99)
        m_maxHP = 99;
}


void Actor::addStrength(int amt)
{
    m_strength += amt;
    if (m_strength < 0)
        m_strength = 0;
    else if (m_strength > 99)
        m_strength = 99;
}


void Actor::addDexterity(int amt)
{
    m_dexterity += amt;
    if (m_dexterity < 0)
        m_dexterity = 0;
    else if (m_dexterity > 99)
        m_dexterity = 99;
}


void Actor::addArmor(int amt)
{
    m_armor += amt;
    if (m_armor < 0)
        m_armor = 0;
    else if (m_armor > 99)
        m_armor = 99;
}


void Actor::changeWeapon(Weapon* nWeapon)
{
    if (nWeapon != nullptr)
        m_weapon = nWeapon;
}


void Actor::changeDungeon(Dungeon* newDungeon)
{
    m_dungeon = newDungeon;
}


string Actor::attack(Actor* victim) //takes a pointer to actor being attacked and updates the status of actor while under attack
{
    string result; //returns a string to be printed
    result += m_name + " " + m_weapon->weaponAction() + " " + m_weapon->name() + " at " + victim->name() + " and ";
    int attackPoint = m_dexterity + m_weapon->dex();
    int defendPoint = victim->m_dexterity + victim->m_weapon->dex();

    if (randInt(attackPoint) < randInt(defendPoint)) //if attack is missed, print string
    {
        result += "misses.";
        return result;
    }

    result += "hits"; //if attack lands, it's a hit and update status
    int damagePoint = randInt(m_strength + m_weapon->damage());
    victim->addHP(-1 * damagePoint);

    if (victim->isDead()) //if victim is dead, print out string stating they died
    {
        result += ", dealing a final blow. ";
        return result;
    }

    int sleep = m_weapon->putToSleep(); //if victim is still alive, check if asleep
    if (sleep) //if alseep, print string
    {
        result += ", putting " + victim->name() + " to sleep";
        victim->fallAsleep(sleep);
    }
    result += ".";
    return result;
}


void Actor::selfHeal() //for player and dragon, this function will give a 0.1 chance to regain one hit point
{}
