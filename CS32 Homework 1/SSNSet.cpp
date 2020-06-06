//
//  SSNSet.cpp
//  Homework 1
//
//  Created by Cymfenee on 4/14/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{
    m_SSNsize=0;
}

bool SSNSet::add(unsigned long ssn)
{
    if (m_SSNset.insert(ssn))
    {
        m_SSNsize++;
        return true;
    }
    return false;
}

int SSNSet::size() const
{
    return m_SSNsize;
}

void SSNSet::print() const
{
    unsigned long value=0;
    
    for (int i=0; i< m_SSNsize; i++)
    {
        m_SSNset.get(i,value);
        cout << value << endl;
    }
}
