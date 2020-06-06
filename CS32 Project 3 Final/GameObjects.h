//  GameObjects.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef GameObjects_h
#define GameObjects_h

#include <string>

class GameObjects
{
public:
    GameObjects(int row, int col) : m_row(row), m_col(col) //Constructor
    {}
    
    virtual ~GameObjects() = 0; //Destructor (pure virtual)
    
    int row()
    {
        return m_row;
    }
    
    int col()
    {
        return m_col;
    }
    
    virtual std::string name() const = 0;
    virtual char icon() const = 0;

    // Playing the game
    void moveToInventory()
    {
        m_row = -1; //negative values here indicate a game object in the inventory
        m_col = -1;
    }

private:
    int m_row;
    int m_col;
};


inline GameObjects::~GameObjects() {} //due to GameObjects being an abstract virtual class

#endif /* GameObjects_h */
