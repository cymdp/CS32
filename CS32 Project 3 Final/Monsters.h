//
//  Monsters.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Monsters_h
#define Monsters_h

#include "Actor.h"
class Dungeon;

//Monster Declarations

class Bogeyman : public Actor
{
public:
    Bogeyman(int r, int c, Dungeon* dungeon); //Constructor
    virtual ~Bogeyman(); //Destructor
    
    virtual char icon() const;
    virtual bool isSmart() const;
    virtual int smellDistance() const;
};


class Snakewoman : public Actor
{
public:
    Snakewoman(int r, int c, Dungeon* dungeon); //Constructor
    virtual ~Snakewoman(); //Destructor
    
    virtual char icon() const;
    virtual bool isSmart() const;
    virtual int smellDistance() const;
};


class Goblin : public Actor
{
public:
    Goblin(int r, int c, Dungeon* dungeon); //Constructor
    virtual ~Goblin(); //Destructor
    
    virtual char icon() const;
    virtual bool isSmart() const;
    virtual int smellDistance() const;
};


class Dragon : public Actor
{
public:
    Dragon(int r, int c, Dungeon* dungeon); //Constructor
    virtual ~Dragon(); //Destructor
    
    virtual char icon() const;
    virtual bool isSmart() const;
    virtual int smellDistance() const;
    virtual void selfHeal(); //for player and dragon, this function will give a 0.1 chance to regain one hit point
};


#endif /* Monsters_h */
