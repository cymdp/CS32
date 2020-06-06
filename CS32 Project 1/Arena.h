//
//  Arena.hpp
//  CS32 Project 1
//
//  Created by Cymfenee on 4/4/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Arena_h
#define Arena_h

#include "History.h" // to use m_history
#include "globals.h"
#include <string>

class Player; //to let compiler know what Player is
class Vampire; //to let compiler know what Vampire is

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     vampireCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfVampiresAt(int r, int c) const;
    void    display(std::string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addVampire(int r, int c);
    bool addPlayer(int r, int c);
    void moveVampires();
    
    History& history();

  private:
    int      m_grid[MAXROWS][MAXCOLS];
    int      m_rows;
    int      m_cols;
    Player*  m_player;
    Vampire* m_vampires[MAXVAMPIRES];
    int      m_nVampires;
    int      m_turns;

      // Helper functions
    void checkPos(int r, int c, std::string functionName) const;
    bool isPosInBounds(int r, int c) const;
    
    History m_history;
};


#endif /* Arena_h */
