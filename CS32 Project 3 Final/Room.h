//
//  Room.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Room_h
#define Room_h

#include "utilities.h"

class Room
{
public:
    Room(int r, int c, int height, int width) : roomRow(r), roomCol(c), roomHeight(height), roomWidth(width) //Constructor
    {}
    
    ~Room() //Destructor
    {}

    int row() const
    {
        return roomRow;
    }
    
    int col() const
    {
        return roomCol;
    }
    
    int width() const
    {
        return roomWidth;
    }
    
    int height() const
    {
        return roomHeight;
    }
    
    void randPoint(int &r, int &c) const
    {
        r = roomRow + randInt(roomHeight);
        c = roomCol + randInt(roomWidth);
    }

private:
    int roomRow;
    int roomCol;
    int roomHeight;
    int roomWidth;
};


#endif /* Room_h */
