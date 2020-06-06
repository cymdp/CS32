//
//  Scroll.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Scroll_h
#define Scroll_h

#include <string>
#include "GameObjects.h"


class Scroll : public GameObjects
{
public:
    Scroll(int r, int c, char id); //Constructor
    
    virtual ~Scroll(); //Destructor
    
    // Accessors
    char id();
    virtual std::string name() const;
    std::string effect();
    int amount();
    virtual char icon() const;

private:
    std::string scrollName;
    std::string scrollEffect;
    int amountInc;
    char m_id;
};


#endif /* Scroll_h */
