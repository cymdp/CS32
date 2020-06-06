//
//  History.h
//  CS32 Project 1
//
//  Created by Cymfenee on 4/4/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
	{
	  public:
	    History(int nRows, int nCols);
	    bool record(int r, int c);
	    void display() const;
    private:
        int m_rows;
        int m_cols;
        char showGrid[MAXROWS][MAXCOLS];
	};

#endif /* History_h */
