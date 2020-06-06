//
//  newSet.cpp
//  Homework 1
//
//  Created by Cymfenee on 4/14/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include "newSet.h"
#include <iostream>
#include <string>
using namespace std;

Set::Set()
{
    m_size=0;
    m_max=DEFAULT_MAX_ITEMS;
    m_newSet=new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(int max)
{
    m_max=max;
    
    if(max< 0)
    {
        cerr << "Error: Set cannot contain negative items." << endl;
        exit(1);
    }
    
    m_size=0;
    m_newSet=new ItemType[max];
}

Set::Set(const Set& otherSet) //copy constructor implementation
{
    m_size=otherSet.m_size;
    m_newSet=new ItemType[m_max];
    m_max=otherSet.m_max;
    
    for(int i=0; i< m_size; i++)
        m_newSet[i]=otherSet.m_newSet[i];
}


Set& Set::operator=(const Set& n) //assignment operator
{
    if (this !=&n)
    {
        Set temp(n);
        swap(temp);
    }
    return *this;
}

bool Set::empty() const
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType &value)
{
    if (m_size < m_max)
    {
    
    for(int i=0; i< m_size; i++) //checks if array is already present
    {
        if(m_newSet[i] == value)
            return false;
    }
        m_newSet[m_size]=value; //inserts value
        m_size++;
    return true;
}
    return false;
}

bool Set::erase(const ItemType& value)
{
    for(int i=0; i< m_size; i++)
    {
        if(m_newSet[i]==value)
        {
            m_newSet[i]=m_newSet[i+1];
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value)
{
    for (int i=0; i< m_size; i++)
    {
        if(m_newSet[i] == value)
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    ItemType sorted[DEFAULT_MAX_ITEMS];
    int counter = 0;
 
    for(int k=0; k< m_size; k++)
    {
        counter = 0;
        for (int j=0; j< m_size; j++)
        {
            if (m_newSet[k] > m_newSet[j])
                counter++;
    }
        sorted[counter]=m_newSet[k];
}
    if (i>=0 && i< m_size)
    {
        value = sorted[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    int tempSize;
    int tempMax;
    ItemType *tempPtr;
    
    tempSize=m_size;
    m_size=other.m_size;
    other.m_size=tempSize;
    
    tempMax=m_max;
    m_max=other.m_max;
    other.m_max=tempMax;
    
    tempPtr=m_newSet;
    m_newSet=other.m_newSet;
    other.m_newSet=tempPtr;
}

Set::~Set() //destructor implementation
{
    if (m_max !=0)
        delete [] m_newSet;
}
