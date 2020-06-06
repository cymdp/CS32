//
//  Dungeon.cpp
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include "Dungeon.h"
#include "utilities.h"
#include "Monsters.h"
#include "Player.h"
#include "GameObjects.h"
#include "Actor.h"
#include "Idol.h"
#include "hfunctions.h"
#include <cstdlib>
#include <iostream>
using namespace std;



Dungeon::Dungeon(int level) //Constructor, creates an array that holds pointers to new objects
    //the pointers are left unitialized until functions are called
{
    if (0 <= level && level <= 4)
        m_level = level;
    else
        exit(5);
    m_maxMonster = 2 + randInt(5 * (level + 1));
    m_maxObject = m_maxMonster + 3; //max of m_maxMonster and 3 objects in dungeon
    m_maxRoom = 20;
    n_Monster = 0;
    n_Object = 0;
    //create the dynamically allocated arrays
    m_monster = new Actor*[m_maxMonster];
    m_object = new GameObjects*[m_maxObject];
    m_room = new Room*[m_maxRoom];
}
    

Dungeon::~Dungeon() //Destructor, deletes everything but Player and Idol
{
    for (int i = 0; i < n_Monster; i++)
        delete m_monster[i];
    for (int i = 0; i < n_Object; i++)
        delete m_object[i];
    for (int i = 0; i < n_Room; i++)
        delete m_room[i];
    delete [] m_object;
    delete [] m_monster;
    delete [] m_room;
    if (m_level == 4)
    {
        delete m_idol;
    }
}


int Dungeon::level() const
{
    return m_level;
}


bool Dungeon::ableToMove(int r, int c) const
{
    char target = m_maze[r][c];
    if (target == ' ' || target == '?' || target == ')' || target == '>' || target == '&')
        return true;
    else
        return false;
}


bool Dungeon::nextLevel(int r, int c) const
{
    if (r == m_stairRow && c == m_stairCol)
        return true;
    else
        return false;
}


Player* Dungeon::player() const
{
    return m_player;
}


Room** Dungeon::room() const
{
    return m_room;
}


int Dungeon::nRoom() const
{
    return n_Room;
}


void Dungeon::setPlayer(Player* player)
{
    m_player = player;
}


string Dungeon::monsterMove(int distance)
{
    string message;
    for (int i = 0; i < n_Monster; i++)
    {
        if (m_monster[i]->sleep()) //if monster is sleeping, decrement sleep by 1 and skip the monster's move
        {
            m_monster[i]->wake();
            continue;
        }
        if (m_monster[i]->icon() == 'D') //if monster is dragon, call selfheal
            m_monster[i]->selfHeal();

        int r = m_monster[i]->row();
        int c = m_monster[i]->col();
        int R = m_player->row();
        int C = m_player->col();
        
        if (canAttack(i)) //if monster is able to attack the player
            message += m_monster[i]->attack(m_player); //attack the player
        
        else if (!m_monster[i]->isSmart()) //if monster is dumb
        {
            
            if (smellBadly(i)) //if monster can smell player
            {
                if (R > r) //when player is below monster, go down
                {
                    if (ableToMove(r + 1, c))
                    {
                        m_monster[i]->move(r + 1, c);
                        continue;
                    }
                }
                
                else if (R < r) //when player is above monster, go up
                {
                    if (ableToMove(r - 1, c))
                    {
                        m_monster[i]->move(r - 1, c);
                        continue;
                    }
                }
                
                if (C > c) //if player is to the right of monster, go right
                {
                    if (ableToMove(r, c + 1))
                    {
                        m_monster[i]->move(r, c + 1);
                        continue;
                    }
                }
                
                else if (C < c) //if player is to the left of monster, go left
                {
                    if (ableToMove(r, c - 1))
                    {
                        m_monster[i]->move(r, c - 1);
                        continue;
                    }
                }
            }
        }
        
        else if (smellBadly(i)) //if monster is smart
        {
            int nextr, nextc;
            int minimum = distance + 1;
            if (smellGood(R, C, r, c, 0, minimum, nextr, nextc))
                m_monster[i]->move(nextr, nextc);
        }
        updateMaze();
    }
    return message;
}


string Dungeon::directionFunction(char direction) //to calculate coordinates of player
{
    string result;
    
    int R = m_player->row();
    int C = m_player->col();
    switch (direction)
    {
    case 'h': //left
        C--;
        break;

    case 'j': //down
        R++;
        break;

    case 'k': //up
        R--;
        break;

    case 'l': //right
        C++;
        break;

    default:
        exit(777);
    }
    // check what is in that location
    char destination = m_maze[R][C];
    if (ableToMove(R, C)) //if able to move to that location
    {
        m_player->move(R, C);
    }
    else if (destination == '#') //if #, its a wall so cant move
        ;
    else //if you cant move but its not a wall, its monster
    {
        bool dead = false;
        for (int i = 0; i < n_Monster; i++) //search monster list to find monster
        {
            if (m_monster[i]->row() == R && m_monster[i]->col() == C)
            {
                result = m_player->attack(m_monster[i]); //attack the monster
                dead = m_monster[i]->isDead();
                if (dead) //if monster is dead
                {
                    dropObject(R, C, m_monster[i]->icon());
                    removeMonster(i); //remove monster
                }
            }
        }
    }
    return result;
}


string Dungeon::pickupFunction(bool &success) //returns true if Idol is picked up
{
    string result;
    int R = m_player->row();
    int C = m_player->col();
    
    if (m_level == 4)
    {
        if (R == m_idol->row() && C == m_idol->col()) //if idol is picked up, you've won the game
        {
            result += "You pick up " + m_idol->name() + "\n";
            result += "Congratulations, you won!\n";
            success = true;
            return result;
        }
    }

    for (int i = 0; i < n_Object; i++) //if there's an object at this location, move it to inventory
    {
        if (m_object[i]->row() == R && m_object[i]->col() == C)
        {
            GameObjects* temp = m_object[i];
            if (m_player->addToInventory(temp))
            {
                result += "You pick up " + temp->name() + "\n";
                removeObject(i);
            }
    
            else //if inventory is full
            {
                result += "Your knapsack is full; you can't pick that up.\n";
            }
            success = false;
            return result;
        }
    }
    return "";
}


string Dungeon::inventoryFunction(char command)
{
    string result;
    clearScreen();
    m_player->displayInventory();
    char temp = getCharacter();
    int index = (int)(temp - 97); //convert the characters to integer index
    if (command == 'w')
        result = m_player->wieldWeapon(index);
    else if (command == 'r')
    {
        bool tele = false;
        result = m_player->readScroll(index, tele); //tele is true only if scroll teleports
        if (tele)
            teleportFunction();
    }
    return result;
}


void Dungeon::cheatFunction()
{
    m_player->cheat();
}


void Dungeon::teleportFunction()
{
    int r, c;
    
    do //generate random location that is movable
    {
        int index = randInt(n_Room);
        m_room[index]->randPoint(r, c);
    } while (ableToMove(r, c));
    m_player->move(r, c); //move player to that location
}


int Dungeon::downstairsFunction() //only returns if Player is on Stairs
{
    if (nextLevel(m_player->row(), m_player->col()))
        return m_level;
    else
        return -1;
}


bool Dungeon::canAttack(int pos) //checks if monster can attack
{
    if (pos < 0 || pos >= n_Monster)
        return false;
    Actor* temp = m_monster[pos];
    int distance = abs(temp->row() - m_player->row()) + abs(temp->col() - m_player->col());
    if (distance == 1)
        return true;
    else
        return false;
}


bool Dungeon::smellBadly(int pos)
{
    if (pos < 0 || pos >= n_Monster)
        return false;
    Actor* temp = m_monster[pos];
    int distance = abs(temp->row() - m_player->row()) + abs(temp->col() - m_player->col());
    if (distance <= temp->smellDistance())
        return true;
    else
        return false;
}


bool Dungeon::smellGood(int sr, int sc, int er, int ec, int count, int &min, int &nRow, int &nCol)
    //(sr,sc) is the current searching position, and this function uses the player's position for sc and sr and the monster's positions as ec and er
    //the intial value for count is 0 and the minimun is smellDistance+1
{
    if (count + 1 >= min) //if the steps to get there are more than the current path, return false
        return false;
    
    //only visit a location with the shortest path known, so every time a location is visited, the character is inspected

    //if the int representing the character is smaller than or equal to count, return false bc there's a path with less teps
    if ((int)m_maze[sr][sc] <= count)
        return false;
    else if (unableToMove(sr, sc) && count != 0) //when count is 0, the position is unmoavble because it's occupied by a monster or wall
        return false;
    m_maze[sr][sc] = (char)count; //otherwise, char is set to current count

    //visiting (sr,sc), min represents the shortest path to (ec,er), which is (count+1).
    //if directly next to target, update closest position to current location
    if ((sr - 1 == er) && sc == ec)
    {
        min = count + 1;
        nRow = sr;
        nCol = sc;
        return true;
    }
    else if (sr == er && (sc + 1 == ec))
    {
        min = count + 1;
        nRow = sr;
        nCol = sc;
        return true;
    }
    else if ((sr + 1 == er) && sc == ec)
    {
        min = count + 1;
        nRow = sr;
        nCol = sc;
        return true;
    }
    else if (sr == er && (sc - 1 == ec))
    {
        min = count + 1;
        nRow = sr;
        nCol = sc;
        return true;
    }
    
    //if not close to target, check recursively
    bool coordN = smellGood(sr - 1, sc, er, ec, count + 1, min, nRow, nCol); //check north coord
    bool coordE = smellGood(sr, sc + 1, er, ec, count + 1, min, nRow, nCol); //check east coord
    bool coordS = smellGood(sr + 1, sc, er, ec, count + 1, min, nRow, nCol); //check south coord
    bool coordW = smellGood(sr, sc - 1, er, ec, count + 1, min, nRow, nCol); //check west coord

    //if one of the recursions found to target, return true; otherwise, return false.
    return coordN || coordE || coordS || coordW;
}


bool Dungeon::unableToMove(int r, int c) const //checks to make sure all moves are valid
{
    char target = m_maze[r][c];
    if (target == '#' || target == 'B' || target == 'S' || target == 'D' || target == 'G' || target == '@')
        return true;
    else
        return false;
}

bool Dungeon::initializeDungeon()
{
    buildWall();
    createConnectedRoom();
    if (m_level !=4)
        createStairs();
    else
        createIdol();
    return true;
}


Room* Dungeon::createRoom(int r, int c, int h, int w) //creates a room based on these parameters
{
    if (r < 0 || c < 0 || h <= 0 || w <= 0)
        return nullptr;
    int R = r + randInt(3); //generates a upperleft corner at location (r,c) and a room with that corner
    int C = c + randInt(4);
    int H = 4 + randInt(h - 4); //generates height and width that are smaller than, but close to h and w
    int W = 4 + randInt(w - 4);
    
    if (R + H >= 17 || C + W >= 69) //if room paramaters result in a room that violates the constraints of the dungeon, return null
        return nullptr;
    Room* ptr = new Room(R, C, H, W); //otherwise, create new room and return a pointer
    return ptr;
}


void Dungeon::createConnectedRoom() //uses createRoom's function to make rooms that are connected
{
    //the dungeon is divided into 3 vertical sections, the first containing column numbers 0 through 20, the second containing columns 21 through 50, the third containing columns 51 through 69
    //the following calls will create a series of rooms, and each section is equally likely to have one or two rooms
    if (trueWithProbability(0.5)) //probability of one room in section 1
    {
        m_room[n_Room] = createRoom(2, 2, 12, 15);
        if (m_room[n_Room] != nullptr)
            n_Room++;
    }
    else //probability of two rooms in section 1
    {
        m_room[n_Room] = createRoom(1, 1, 6, 15);
        if (m_room[n_Room] != nullptr)
            n_Room++;
        m_room[n_Room] = createRoom(11, 1, 6, 15);
        if (m_room[n_Room] != nullptr)
            n_Room++;
    }
    if (trueWithProbability(0.5)) //probability of one room in section 2
    {
        m_room[n_Room] = createRoom(2, 22, 12, 24);
        if (m_room[n_Room] != nullptr)
            n_Room++;
    }
    else //probability of two rooms in section 2
    {
        m_room[n_Room] = createRoom(1, 21, 6, 24);
        if (m_room[n_Room] != nullptr)
            n_Room++;
        m_room[n_Room] = createRoom(11, 21, 6, 24);
        if (m_room[n_Room] != nullptr)
            n_Room++;
    }
    if (trueWithProbability(0.5)) //probability of one room in section 3
    {
        m_room[n_Room] = createRoom(2, 52, 12, 15);
        if (m_room[n_Room] != nullptr)
            n_Room++;
    }
    else //probability of two rooms in section 3
    {
        m_room[n_Room] = createRoom(1, 51, 6, 15);
        if (m_room[n_Room] != nullptr)
            n_Room++;
        m_room[n_Room] = createRoom(11, 51, 6, 15);
        if (m_room[n_Room] != nullptr)
            n_Room++;
    }
    
    //to set up corridors to make sure all rooms in the dungeon are connected
    int roomnumber = n_Room;
    for (int i = 0; i < roomnumber - 1; i++)
    {
        int r1, c1;
        m_room[i]->randPoint(r1, c1); //for every time there's two rooms, pick a random point in each room
        int r2, c2;
        m_room[i + 1]->randPoint(r2, c2);
        
        if (r1 == r2) //connect (r1,c1) and (r2,c2)
        {
            m_room[n_Room] = new Room(r1, min(c1, c2), 1, abs(c1 - c2) + 1);
            n_Room++;
        }
        else if (c1 == c2) //connect (r1,c1) and (r2,c2)
        {
            m_room[n_Room] = new Room(min(r1, r2), c1, abs(r1 - r2) + 1, 1);
            n_Room++;
        }
        else
            //connect (r1, c1) and (r2,c1)
        {
            m_room[n_Room] = new Room(min(r1, r2), c1, abs(r1 - r2) + 1, 1); //connect the corridor from r1 to r2
            n_Room++;
        
            //connect (r2,c1) and (r2,c2)
            
            m_room[n_Room] = new Room(r2, min(c1, c2), 1, abs(c1 - c2) + 1); //connect the corridor from c1 to c2
            n_Room++;
        }
    }
    for (int k = 0; k < n_Room; k++) //reflect all rooms in array
        buildRoom(k);
}


bool Dungeon::createStairs()
{
    int index = randInt(n_Room);
    m_room[index]->randPoint(m_stairRow, m_stairCol);
    m_maze[m_stairRow][m_stairCol] = '>';
    return true;
}


bool Dungeon::createIdol()
{
    int r, c;
    int index = randInt(n_Room);
    m_room[index]->randPoint(r, c);
    m_idol = new Idol(r, c);
    m_maze[r][c] = m_idol->icon();
    return true;
}


bool Dungeon::createObject()
{
    int n = trueWithProbability(0.5) + 2;
    for (int i = 0; i < n; i++)
    {
        int r, c;
        int index = randInt(n_Room);
        m_room[index]->randPoint(r, c);
        if (trueWithProbability(1.0 / 7))
            addObject(r, c, 'A');
        else if (trueWithProbability(1.0 / 7))
            addObject(r, c, 'D');
        else if (trueWithProbability(1.0 / 7))
            addObject(r, c, 'H');
        else if (trueWithProbability(1.0 / 7))
            addObject(r, c, 'S');
        else if (trueWithProbability(1.0 / 7))
            addObject(r, c, 'l');
        else if (trueWithProbability(1.0 / 7))
            addObject(r, c, 's');
        else
            addObject(r, c, 'm');
    }
    return true;
}


bool Dungeon::createMonsters()
{
    for (int i = 0; i < m_maxMonster; i++)
    {
        int r, c;
        int index = randInt(n_Room);
        m_room[index]->randPoint(r, c); //generates a random coord (r,c in a random room)
        int prob = randInt(4);
        switch (prob)
        {
        case 1: //if level is at least 2, case 1 will create Bogeymen
            if (m_level >= 2)
            {
                addMonster(r, c, 'B');
                break;
            }
            
        case 2: //otherwise, will create Goblin
            addMonster(r, c, 'G');
            break;

        case 3:
            if (m_level >= 3) //if level is at least 3, case 3 will create Dragon
            {
                addMonster(r, c, 'D');
                break;
            }

        case 4: //otherwise, will create Snakewomen
            addMonster(r, c, 'S');
            break;

        default:
            exit(999);
        }
    }
    return true;
}


bool Dungeon::createPlayer()
{
    int r, c; //get coord for Player
    do //initialize a rand coord in a random room
    {
        
        int index = randInt(n_Room);
        m_room[index]->randPoint(r, c);
    } while (!ableToMove(r, c));
    m_player = new Player(r, c, this);
    m_maze[r][c] = m_player->icon();
    return true;
}


bool Dungeon::addMonster(int r, int c, char id) //Adding monsters
{
    if (n_Monster >= m_maxMonster)
        return false;
    if (!ableToMove(r, c))
        return false;
    switch (id)
    {
    case 'B': //Add Bogeymen
        m_monster[n_Monster] = new Bogeyman(r, c, this);
        break;

    case 'D': //Add Dragons
        m_monster[n_Monster] = new Dragon(r, c, this);
        break;

    case 'G': //Add Goblins
        m_monster[n_Monster] = new Goblin(r, c, this);
        break;

    case 'S': //Add Snakewomen
        m_monster[n_Monster] = new Snakewoman(r, c, this);
        break;
        
    default:
        exit(6);
    }
    m_maze[r][c] = m_monster[n_Monster]->icon();
    n_Monster++;
    return true;
}


bool Dungeon::removeMonster(int pos) //Remove monsters
{
    if (pos < 0 || pos >= n_Monster)
        return false;
    
    delete m_monster[pos];
    for (int i = pos; i < n_Monster - 1; i++)
    {
        m_monster[i] = m_monster[i + 1];
    }
    n_Monster--;
    return true;
}


bool Dungeon::addObject(int r, int c, char id)
{
    if (n_Object >= m_maxObject)
        return false;
    char destination = m_maze[r][c];
    if (destination == '#' || destination == '>' || destination == '&' || destination == ')' || destination == '?')
        return false;
    switch (id)
        
    {
            //Scrolls
    case 'A':
    case 'D':
    case 'H':
    case 'S':
    case 'T':
        m_object[n_Object] = new Scroll(r, c, id);
        break;

            //Weapons
    case 'a':
        m_object[n_Object] = new magicAxe(r, c);
        break;

    case 'f':
        m_object[n_Object] = new magicFangs(r, c);
        break;

    case 'l':
        m_object[n_Object] = new longSword(r, c);
        break;

    case 'm':
        m_object[n_Object] = new Mace(r, c);
        break;

    case 's':
        m_object[n_Object] = new shortSword(r, c);
        break;

    default:
        exit(7);
    }
    m_maze[r][c] = m_object[n_Object]->icon();
    n_Object++;
    return true;
}


bool Dungeon::removeObject(int pos) //Removes object from m_object
{
    if (pos < 0 || pos >= n_Object)
        return false;
    for (int i = pos; i < n_Object - 1; i++)
    {
        m_object[i] = m_object[i + 1];
    }
    n_Object--; //decrements n_Object
    return true;
}


bool Dungeon::dropObject(int r, int c, char icon)
{
    for (int i = 0; i < n_Object; i++) //if there's already an object here, return false
    {
        if (m_object[i]->row() == r && m_object[i]->col() == c)
            return false;
    }
    
    if (m_level == 4) //if there is a golden idol there, return false
    {
        if (m_idol->row() == r && m_idol->col() == c)
            return false;
    }
    else //if there is a stair there, return false
    {
        if (m_stairRow == r && m_stairCol == c)
            return false;
    }
    
    int result;
    switch (icon) //determine which object will be added to the dungeon and call addObject
    {
    case 'B':
        if (trueWithProbability(0.1))
        {
            return addObject(r, c, 'a');
        }
        return false;

    case 'S':
        if (trueWithProbability(1.0 / 3))
        {
            return addObject(r, c, 'f');
        }
        return false;

    case 'D':
        result = randInt(5);
        switch (result)
        {
        case 0:
            return addObject(r, c, 'A');

        case 1:
            return addObject(r, c, 'D');

        case 2:
            return addObject(r, c, 'H');

        case 3:
            return addObject(r, c, 'S');

        default:
            return addObject(r, c, 'T');
        }

    case 'G':
        if (trueWithProbability(1.0 / 3))
        {
            if (trueWithProbability(0.5))
                return addObject(r, c, 'a');
            else
                return addObject(r, c, 'f');
        }
        return false;

    default:
        exit(1123);
    }
}

void Dungeon::updateMaze() //updates m_maze to show the current layer of the dungeon
{
    
    for (int i = 0; i < n_Room; i++) //to show all rooms
    {
        buildRoom(i);
    }
    
    if (m_level != 4) //to update stairs
        m_maze[m_stairRow][m_stairCol] = '>';
    else //to update golfen idol
        m_maze[m_idol->row()][m_idol->col()] = m_idol->icon();
    
    for (int i = 0; i < n_Object; i++) //to update objects
    {
        int r = m_object[i]->row();
        int c = m_object[i]->col();
        m_maze[r][c] = m_object[i]->icon();
    }
    
    for (int i = 0; i < n_Monster; i++) //to update Monsters
    {
        int r = m_monster[i]->row();
        int c = m_monster[i]->col();
        m_maze[r][c] = m_monster[i]->icon();
    }
    // put in the player
    m_maze[m_player->row()][m_player->col()] = m_player->icon(); //place player in maze
}


void Dungeon::displayMaze() const //to display the maze
{
    for (int i = 0; i < 18; i++)
    {
        for (int k = 0; k < 70; k++)
        {
            cout << m_maze[i][k];
        }
        cout << endl;
    }
}


void Dungeon::buildWall() //to fill maze with walls
{
    for (int i = 0; i < 18; i++)
    {
        for (int k = 0; k < 70; k++)
        {
            m_maze[i][k] = '#';
        }
    }
}


void Dungeon::buildRoom(int index) //to build room
{
    int h = m_room[index]->height();
    int w = m_room[index]->width();
    int r = m_room[index]->row();
    int c = m_room[index]->col();
    for (int i = r; i < r + h; i++)
    {
        for (int k = c; k < c + w; k++)
        {
            m_maze[i][k] = ' ';
        }
    }
}


void Dungeon::displayStatus() const //to display status at bottom of maze
{
    cout << "Dungeon Level: " << m_level << ", Hit points: " << m_player->hp() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dex() << endl << endl;
}

