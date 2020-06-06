//
//  Dungeon.h
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//


#ifndef Dungeon_h
#define Dungeon_h

#include "Actor.h"
#include "Player.h"
#include "Room.h"
#include "Idol.h"
#include <string>


class Dungeon {
public:
    Dungeon(int level); //Constructor
    ~Dungeon(); //Destructor
        
    int level() const;
    bool ableToMove(int r, int c) const;
    bool nextLevel(int r, int c) const;
    Player* player() const;
    Room** room() const;
    int nRoom() const;


    void setPlayer(Player* player);
    std::string monsterMove(int distance);
    std::string directionFunction(char direction);
    std::string pickupFunction(bool &success);
    std::string inventoryFunction(char command);
    void cheatFunction();
    void teleportFunction();
    int downstairsFunction();
    bool canAttack(int pos);
    bool smellBadly(int pos);
    bool smellGood(int sr, int sc, int er, int ec, int count, int &min, int &nRow, int &nCol);
    bool unableToMove(int r, int c) const;


    // Dungeon populator
    bool initializeDungeon();
    Room* createRoom(int r, int c, int h, int w);
    void createConnectedRoom();
    bool createStairs();
    bool createIdol();
    bool createObject();
    bool createMonsters();
    bool createPlayer();
    

    //Operators for Monster and GameObjects
    bool addMonster(int r, int c, char id);
    bool removeMonster(int r, int c);
    bool removeMonster(int pos);
    bool addObject(int r, int c, char id);
    bool removeObject(int r, int c);
    bool removeObject(int pos);
    bool dropObject(int r, int c, char icon);


    //Operators for Maze
    void updateMaze();
    void displayMaze() const;


    //Operators to Build Room
    void buildRoom(int index);
    void buildWall();
    
    //To Display Stats at bottom of maze
    void displayStatus() const;


private:
    char m_maze[18][70]; //the dungeon is a maze of characters
    Idol* m_idol;
    Room** m_room;
    int n_Room;
    int m_maxRoom;
    Actor** m_monster; //dynamically allocated array of pointers to rooms in dungeon
    int n_Monster;
    int m_maxMonster;
    Player* m_player; //pointer to the dynamically allocated player
    GameObjects** m_object; //dynamically allocated array of pointers to objects
    int n_Object;
    int m_maxObject;
    int m_level;
    int m_stairRow;
    int m_stairCol;
};


#endif /* Dungeon_h */
