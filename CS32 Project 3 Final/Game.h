// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data memebers and other member functions to this class.

#include "Dungeon.h"
#include "Player.h"


class Game
{
public:
    Game(int goblinSmellDistance); //Constructor
    ~Game(); //Destructor
    
    void play();
    void createNewDungeon(int level);
    

private:
    int m_smellDistance;
    Dungeon* m_dungeon;
    Player* m_player;
};

#endif // GAME_INCLUDED
