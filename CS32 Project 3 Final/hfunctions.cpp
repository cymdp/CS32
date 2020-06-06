//
//  hfunctions.cpp
//  Project 3
//
//  Created by Cymfenee on 5/17/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include "hfunctions.h"

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

int abs(int a)
{
    if (a < 0)
        a = -a;
    return a;
}
