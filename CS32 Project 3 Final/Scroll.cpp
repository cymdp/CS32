//
//  Scroll.cpp
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//


#include "Scroll.h"
#include "utilities.h"
#include <cstdlib>


Scroll::Scroll(int r, int c, char id) : GameObjects(r, c), m_id(id) //Constructor
{
    switch (id)
    {
    //Scroll of Enhanced Armor
    case 'A':
        scrollName = "scroll of enhance armor";
        scrollEffect = "Your armor glows blue.";
        amountInc = randInt(3) + 1;
        break;

    //Scroll of Enhanced Dexterity
    case 'D':
        scrollName = "scroll of enhance dexterity";
        scrollEffect = "You feel like less of a klutz.";
        amountInc = 1;
        break;

    //Scroll of Enhanced Health
    case 'H':
        scrollName = "scroll of enhance health";
        scrollEffect = "You feel your heart beating stronger.";
        amountInc = randInt(6) + 3;
        break;

    //Scroll of Strength
    case 'S':
        scrollName = "scroll of strength";
        scrollEffect = "Your muscles bulge.";
        amountInc = randInt(3) + 1;
        break;

    //Scroll of Teleportation
    case 'T':
        scrollName = "scroll of teleportation";
        scrollEffect = "You feel your body wrenched in space and time.";
        amountInc = 0;
        break;

    default:
        exit(1);
    }
}


Scroll::~Scroll() //Destructor
{}

char Scroll::id()
{
    return m_id;
}


std::string Scroll::name() const
{
    return scrollName;
}


std::string Scroll::effect()
{
    return scrollEffect;
}


int Scroll::amount()
{
    return amountInc;
}


char Scroll::icon() const
{
    return '?';
}
