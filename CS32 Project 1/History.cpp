//
//  History.cpp
//  CS32 Project 1
//
//  Created by Cymfenee on 4/4/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int i=1; i<=m_rows; i++)
    {
        for (int j=1; j<=m_cols; j++)
        {
            showGrid[i-1][j-1] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    if ((r<=m_rows && r>=1 ) && (c<=m_cols && c>=1))
    {
        if (showGrid [r-1][c-1] == '.'){
            showGrid[r-1][c-1] = 'A';
    }
        else if (showGrid [r-1][c-1] < 'Z')
        {
            showGrid [r-1][c-1]++;
        }
        return true;
}
    else{
        return false;
    }
            
}
        

void History::display() const
{
    
    clearScreen();
    for (int i=1; i<=m_rows; i++){
        for (int j=1; j<=m_cols; j++){
            cout << showGrid[i-1][j-1];
        }
        cout << endl;
    }
    cout << endl;
}

