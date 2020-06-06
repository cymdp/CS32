//
//  Set.cpp
//  CS32 Project 2
//
//  Created by Cymfenee on 4/14/20.
//  Copyright © 2020 CDP. All rights reserved.
//
 
#include <iostream>
#include <string>
#include <utility>
#include "Set.h"
using namespace std;

Set::Set() //creates an empty set
{
    m_size=0;
    front=nullptr;
    end=nullptr;
}

Set::~Set() //Destructor
{
    if (front == nullptr) //no memory to clear if set is empty
        return;
    
    Node* p=front; //clears allocated memory
    Node* nextNode;
    
    while (p != nullptr)
    {
        nextNode=p->next;
        delete p;
        p=nextNode;
    }
}

Set::Set(const Set& other) //Copy Constructor
{
    m_size=other.m_size;
    
    if (other.m_size == 0) //if other is empty, empty it and return
    {
        front=nullptr;
        end=nullptr;
        return;
    }
    
    front=new Node; //creates a new linked list
    front->prev=nullptr;
    
    Node* m_node=front;
    
    for (Node* p=other.front; p->next != nullptr; p=p->next) //dynamically alloc. new nodes
    {
        Node* newNode=new Node;
        
        m_node->m_data=p->m_data;
        m_node->next=newNode;
        newNode->prev=m_node;
        
        m_node=newNode;
    }
    
    m_node->m_data=other.end->m_data; //copies to last node
    m_node->next=nullptr; //sets to nullptr
    
    end=m_node; //tail pointer
}

Set& Set::operator=(const Set& n) //Assignment Op., temp is destroyed at end of this loop
{
    if (this != &n)
    {
        Set temp(n); //creates temp copy of n
        swap(temp); //swaps contents
    }
    return *this;
}

bool Set::empty() const //returns true if set is empty
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Set::size() const
{
    return m_size; //returns size of set
}

bool Set::insert(const ItemType &value)
{
  if (contains(value)) //checks if value is already in set
      return false;
  
  if (m_size == 0) //case is set for first node bc no dummy node
  {
      Node* newNode=new Node; //creation of new node
      newNode->m_data=value;
      newNode->prev=nullptr;
      newNode->next=nullptr;
      
      front=newNode; //set of fields for node
      end=newNode;
      
      m_size++; //increments size of node
      return true;
  }
      Node* newNode=new Node; //creation of new nodes
      newNode->m_data=value;
      newNode->prev=end;
      newNode->next=nullptr;
    
    end->next=newNode; //set of fields for node
    end=newNode;
    
    m_size++; //increments size of node
    return true;
}



bool Set::erase(const ItemType &value)
{
    if (!contains(value)) //checks if value is already present in set
        return false;
    
    Node* p=front;
    
    for (; p != nullptr; p=p->next) //goes through list to find the node equiv. to value
    {
        if (p->m_data==value)
            break;
    }
        if (p->prev != nullptr) //links node above value to the one below
        {
            p->prev->next=p->next;
        }
        else
        {
            front=p->next; //points front to next
        }
        
        if (p->next != nullptr)
        {
            p->next->prev=p->prev; //links node below value to the one above
        }
        else
        {
            end=p->prev; //points end to prev
        }
        
        m_size--; //decrements size of node
        delete p; //deletes node that was removed
        return true;
}


    
bool Set::contains(const ItemType& value) const //goes through linked list
{
    for (Node* p=front; p !=nullptr; p=p->next)
    {
        if (p->m_data==value)
            return true; //if found, value is returned
    }
    return false;
}

bool Set::get(int i, ItemType &value) const
{
    if (i>=m_size || i<0)
        return false;
    
    Set tempSet(*this);
    
    for (int j=0; j<i; j++)
    {
        ItemType m_min=tempSet.front->m_data;
        for (Node* p=tempSet.front; p !=nullptr; p=p->next)
        {
            m_min=(p->m_data<m_min) ? p->m_data : m_min;
        }
        tempSet.erase(m_min);
    }
    ItemType m_min=tempSet.front->m_data;
     for (Node* p=tempSet.front; p !=nullptr; p=p->next)
        {
            m_min=(p->m_data<m_min) ? p->m_data : m_min;
        }
    
    value=m_min; //sets value to min
    return true;
}

void Set::swap(Set& other) //Exchanges set with another set
{
 
    int tempSize=m_size;
    m_size=other.m_size;
    other.m_size=tempSize;
    //to switch sizes
 
    Node* tempFront=front;
    front=other.front;
    other.front=tempFront;
    //to swap fronts
    
    Node* tempEnd=end;
    end=other.end;
    other.end=tempEnd;
    //to swap ends
}

void unite(const Set& s1, const Set& s2, Set& result)
    {
        result = s1; //s1 is copied into result
        
        for (int j=0; j<s2.size(); j++) //s2 is put into s1
        {
            ItemType enter;
            s2.get(j,enter);
            result.insert(enter);
        }
}
    
void subtract(const Set& s1, const Set& s2, Set& result)
    {
        if (&s1==&s2) //subtracting set from itself
        {
            Set blank;
            result=blank; //set result to blank set
            return;
        }
        
         for (int j=0; j<s2.size(); j++) //remove s2 from s1
        {
            ItemType remove;
            s2.get(j,remove);
            result.erase(remove); //erase takes out remove only if present
        }
}
    



 
 
