//
//  Monsters.cpp
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//


#include "Monsters.h"
#include "utilities.h"
using namespace std;

//Monster Implementations

Bogeyman::Bogeyman(int r, int c, Dungeon* dungeon)
    : Actor(2 + randInt(2), 2 + randInt(2), 2, 5 + randInt(6), r, c, "the Bogeyman", new shortSword(-1, -1), dungeon)
{}


Bogeyman::~Bogeyman()
{}


char Bogeyman::icon() const
{
    return 'B';
}


bool Bogeyman::isSmart() const
{
    return false;
}


int Bogeyman::smellDistance() const
{
    return 5;
}


Snakewoman::Snakewoman(int r, int c, Dungeon* dungeon)
    : Actor(2, 3, 3, 3 + randInt(4), r, c, "the Snakewoman", new magicFangs(-1, -1), dungeon)
{}


Snakewoman::~Snakewoman()
{}


char Snakewoman::icon() const
{
    return 'S';
}


bool Snakewoman::isSmart() const
{
    return false;
}


int Snakewoman::smellDistance() const
{
    return 3;
}



Goblin::Goblin(int r, int c, Dungeon* dungeon)
    : Actor(3, 1, 1, 15 + randInt(6), r, c, "the Goblin", new shortSword(-1, -1), dungeon)
{}


Goblin::~Goblin()
{}


char Goblin::icon() const
{
    return 'G';
}


bool Goblin::isSmart() const
{
    return true;
}


int Goblin::smellDistance() const
{
    return 16;
}



Dragon::Dragon(int r, int c, Dungeon* dungeon)
    : Actor(4, 4, 4, 20 + randInt(6), r, c, "the Dragon", new longSword(-1, -1), dungeon)
{}


Dragon::~Dragon()
{}


char Dragon::icon() const
{
    return 'D';
}


void Dragon::selfHeal() //for player and dragon, this function will give a 0.1 chance to regain one hit point
{
    if (trueWithProbability(0.1))
        addHP(1);
}


bool Dragon::isSmart() const
{
    return false;
}


int Dragon::smellDistance() const
{
    return 0;
}
