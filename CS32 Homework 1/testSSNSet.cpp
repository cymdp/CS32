//
//  testSSNSet.cpp
//  Homework 1
//
//  Created by Cymfenee on 4/14/20.
//  Copyright © 2020 CDP. All rights reserved.
//
#include "SSNSet.h"
#include <iostream>
#include <string>
#include <cassert>

int main()
{
    SSNSet s;
    assert(s.size()==0);
    s.add(123456789);
    assert(s.size()==1);
    s.add(543217986);
    s.add(421365789);
    assert(s.size()==3);
    s.print();
    std::cout << "Passed all tests." << std::endl;
}
