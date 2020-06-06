//
//  Set.h
//  CS32 Project 2
//
//  Created by Cymfenee on 4/14/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
using ItemType = std::string;

//using ItemType = unsigned long;

class Set
{
  public:
    Set();         // Create an empty set (i.e., one with no items).
    Set(const Set& other); //Copy Constructor
    
    ~Set(); //Destructor
    Set& operator = (const Set& n); //assignment

    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if the value was not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
    
    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
      // If 0 <= pos < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.
    
    
private:
    struct Node
    {
        ItemType m_data;
        Node* prev;
        Node* next;
    };
    
    int m_size;
    Node* front;
    Node* end;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */

