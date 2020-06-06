//
//  maze.cpp
//  Homework 3
//
//  Created by Cymfenee on 5/5/20.
//  Copyright © 2020 CDP. All rights reserved.
//


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


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    maze[sr][sc]='#';
    
   if (sr==er && sc==ec)
   {
       return true;
   }

    if (maze[sr+1][sc]=='.') //South
    {
        if (pathExists(maze, sr+1, sc, er, ec))
        {
            return true;
        }
            
    }
    
    if (maze[sr][sc-1]=='.') //West
    {
        if (pathExists(maze, sr, sc-1, er, ec))
        {
            return true;
        }
            
    }
    
    if (maze[sr-1][sc]=='.') //North
    {
        if (pathExists(maze, sr-1, sc, er, ec))
        {
            return true;
        }
            
    }
    
     if (maze[sr][sc+1]=='.') //East
    {
        if (pathExists(maze, sr, sc+1, er, ec))
        {
            return true;
        }
            
    }
    
    return false;
}


