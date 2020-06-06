//
//  Game.hpp
//  CS32 Project 1
//
//  Created by Cymfenee on 4/4/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <string>

class Arena; //to let compiler know what Arena is

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};


#endif /* Game_h */
