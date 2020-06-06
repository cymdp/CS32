//
//  Player.cpp
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//


#include "Player.h"
#include <cstdlib>
#include <iostream>
using namespace std;


Player::Player(int r, int c, Dungeon* dungeon) //Constructor
    : Actor(2, 2, 2, 20, r, c, "Player", new shortSword(-1, -1), dungeon), m_sizeInventory(0), m_capacityInventory(25) //Constructor
{
    m_inventory[0] = weapon();
    m_sizeInventory++;
}


Player::~Player() //Destructor
{
    for (int i = 0; i < m_sizeInventory; i++)
    {
        delete m_inventory[i];
    }
}


GameObjects** Player::inventory()
{
    return m_inventory;
}


int Player::sizeOfInventory() const
{
    return m_sizeInventory;
}


char Player::icon() const
{
    return '@'; //Player's icon
}


bool Player::isSmart() const
{
    return false;
}


int Player::smellDistance() const
{
    return 0;
}


void Player::displayInventory() const
{
    cout << "Inventory:" << endl;
    for (int i = 0; i < m_sizeInventory; i++)
        cout << (char)(i + 97) << ". " << m_inventory[i]->name() << endl;
}


bool Player::addToInventory(GameObjects* item)
{
    if (item == nullptr || m_sizeInventory < 0)
        exit(2);
    if (m_sizeInventory >= m_capacityInventory)
        return false;
    m_inventory[m_sizeInventory] = item;
    m_sizeInventory++;
    return true;
}


string Player::wieldWeapon(int pos)
{
    if (pos < 0 || pos >= m_capacityInventory)
        return "";
    if (pos >= m_sizeInventory)
        return "";
    string result;
    // check if the object is indeed a weapon
    GameObjects* newItem = m_inventory[pos];
    Weapon* newWeapon = dynamic_cast<Weapon*>(newItem);
    
    if (newWeapon == nullptr) //if object is not a weapon, return error message
    {
        Scroll* cantWield = dynamic_cast<Scroll*>(newItem);
        result += "You can't wield " + cantWield->name() + "\n";
        return result;
    }
    
    changeWeapon(newWeapon); //if object is a weaponm wield it
    result += "You are wielding " + weapon()->name() + "\n";
    return result;
}


string Player::readScroll(int pos, bool &tele)
{
    if (pos < 0 || pos >= m_capacityInventory)
        return "";
    if (pos >= m_sizeInventory)
        return "";
    string result;
    
    GameObjects* newItem = m_inventory[pos];
    Scroll* newScroll = dynamic_cast<Scroll*>(newItem);
    
    if (newScroll == nullptr) //if object is not a scroll, return error messae
    {
        Weapon* cantRead = dynamic_cast<Weapon*>(newItem);
        result += "You can't read a " + cantRead->name() + "\n";
        return result;
    }
    
    char scrollID = newScroll->id(); //if object is a scroll, read it
    switch (scrollID)
    {
    case 'A':
        addArmor(newScroll->amount());
        break;

    case 'D':
        addDexterity(newScroll->amount());
        break;

    case 'H':
        addMaxHP(newScroll->amount());
        break;

    case 'S':
        addStrength(newScroll->amount());
        break;

    case 'T':
        tele = true;
        break;

    default:
        exit(3);
    }
    
    result += "You read the scroll called " + newScroll->name() + "\n"; //print out what was read
    result += newScroll->effect() + "\n";

    eraseInventory(pos); //Scroll is deleted from inventory after read
    return result;
}


bool Player::eraseInventory(int pos)
{
    if (pos < 0 || pos >= m_sizeInventory)
        return false;
    delete m_inventory[pos];
    
    for (int i = pos; i < m_sizeInventory - 1; i++)
    {
        m_inventory[i] = m_inventory[i + 1];
    }
    m_sizeInventory--;
    return true;
}


void Player::selfHeal() //for player and dragon, this function will give a 0.1 chance to regain one hit point
{
    if (trueWithProbability(0.1))
        addHP(1);
}
