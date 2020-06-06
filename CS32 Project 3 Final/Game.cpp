// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    m_smellDistance = goblinSmellDistance;
    m_dungeon = new Dungeon(0);

    m_dungeon->initializeDungeon(); //Initialize Dungeon
    m_dungeon->createObject(); //Create objects
    m_dungeon->createMonsters(); //Create Monsters
    m_dungeon->createPlayer(); //Place player in dungeon
    m_player = m_dungeon->player(); //m_player points to player in dungeon
    m_dungeon->updateMaze(); //update maze to current layout
    m_dungeon->displayMaze();
    m_dungeon->displayStatus();
}


Game::~Game()
{
    delete m_dungeon;
    delete m_player;
}


void Game::createNewDungeon(int level)
{
    clearScreen(); //delete the current dungeon, create a new one at new level
    delete m_dungeon;
    m_dungeon = new Dungeon(level); //initialize new dungeon the same way
    m_dungeon->initializeDungeon();
    m_dungeon->createObject();
    m_dungeon->createMonsters();
    m_player->changeDungeon(m_dungeon); //link original player with new dungeon, place player in the new dungeon as m_player.
    m_dungeon->setPlayer(m_player);

    int r, c; //generates random coord for Player
    do //generates random coord in random room
    {
        int index = randInt(m_dungeon->nRoom());
        m_dungeon->room()[index]->randPoint(r, c);
    }
    
    while (!m_dungeon->ableToMove(r, c));
    m_player->move(r, c);
    // Update m_maze[18][70] to reflect the current layout of the dungeon.
    m_dungeon->updateMaze();
    m_dungeon->displayMaze();
    m_dungeon->displayStatus();
}


void Game::play()
{
    char input = getCharacter();
    bool success = false;
    while (input != 'q' && !success && !m_player->isDead()) //as long as player isn't dead and q isn't typed, keep asking for input
    {
        string pMessage; //message about Player
        string mMessage; //messages about the monsters
        // If player is asleep, reduce its sleepiness by 1 and skip the player's round.
        if (m_player->sleep())
        {
            m_player->wake();
        }
        else
        {
            switch (input) //to determine which command the user inputs and call the member function in dungeon
            {
            case 'h':
            case 'j':
            case 'k':
            case 'l':
                pMessage = m_dungeon->directionFunction(input);
                break;

            case 'g':
                pMessage = m_dungeon->pickupFunction(success); //success will return true if idol is the item picekd up
                break;

            case 'i':
            case 'r':
            case 'w':
                pMessage = m_dungeon->inventoryFunction(input);
                break;

            case 'c':
                m_dungeon->cheatFunction(); //cheat command for testing
                break;

            case '>':
                int result = m_dungeon->downstairsFunction(); //returns the current level if player is on staircase
                if (result > -1) //otherwise, return -1
                {
                    createNewDungeon(result + 1);
                    input = getCharacter();
                    continue;
                }
                break;
            }
        }
        m_player->selfHeal(); //restores player's HP
        m_dungeon->updateMaze();
        mMessage = m_dungeon->monsterMove(m_smellDistance); //performs appropriate action for each monster and stores message later
        clearScreen();
        m_dungeon->updateMaze();
        m_dungeon->displayMaze();
        m_dungeon->displayStatus();
        if (pMessage != "")
            cout << pMessage;
        if (mMessage != "")
            cout << mMessage;
        if (!success)
            input = getCharacter();
    }
    
    cout << "Press q to exit game." << endl; //
    while (getCharacter() != 'q')
    {
        getCharacter();
    }
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObjects.h,
// etc.
