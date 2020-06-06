//
//  Idol.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Idol_h
#define Idol_h

#include "GameObjects.h"


class Idol : public GameObjects
{
public:
    Idol(int r, int c) : GameObjects(r, c) //Constructor
    {}
    
    virtual ~Idol() //Destructor
    {}

    virtual std::string name() const
    {
        return "the golden idol";
    }
    
    virtual char icon() const
    {
        return '&';
    }
};


#endif /* Idol_h */
