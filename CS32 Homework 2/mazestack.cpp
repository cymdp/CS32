//
//  main.cpp
//  CS32 HW2
//
//  Created by Cymfenee on 4/29/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

//Prototype

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
          // Return true if there is a path from (sr,sc) to (er,ec)
          // through the maze; return false otherwise

//Coord Class

class Coord
        {
          public:
            Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
            int r() const { return m_row; }
            int c() const { return m_col; }
          private:
            int m_row;
            int m_col;
        };

//Path Exists Implementation
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    Coord startCoord(sr,sc);
    coordStack.push(startCoord); //pushes startCoord
    maze[sr][sc]='#'; //maze not '.'
    
    int cRow=sr;
    int cCol=sc;
    
    while(!coordStack.empty())
    {
        startCoord=coordStack.top(); //pops top coordinate to top
        cRow=startCoord.r();
        cCol=startCoord.c();
        coordStack.pop();
        
        if (cRow==er && cCol==ec) //checks if the top coords are the end coords
            return true;
        
        //0 is first row/col and 9 is last row/col
    
        if (cRow<9 && maze[cRow+1][cCol]=='.') //South
        {
            Coord move(cRow+1,cCol);
            coordStack.push(move);
            maze[cRow+1][cCol]='#';
        }
        
        if (cCol>0 && maze[cRow][cCol-1]=='.') //West
        {
            Coord move(cRow,cCol-1);
            coordStack.push(move);
            maze[cRow][cCol-1]='#';
        }
        
        if (cRow>0 && maze[cRow-1][cCol]=='.') //North
        {
            Coord move(cRow-1,cCol);
            coordStack.push(move);
            maze[cRow-1][cCol]='#';
        }
        
        if (cCol<9 && maze[cRow][cCol+1]=='.') //East
        {
            Coord move(cRow,cCol+1);
            coordStack.push(move);
            maze[cRow][cCol+1]='#';
        }
    
    }
    return false;
}

