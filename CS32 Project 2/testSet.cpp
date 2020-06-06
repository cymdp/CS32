//
//  testSet.cpp
//  CS32 Project 2
//
//  Created by Cymfenee on 4/19/20.
//  Copyright © 2020 CDP. All rights reserved.
//

        
/*#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
        Set s;
        s.insert("Hello");
        assert(s.size() == 1);
        string x;
        assert(s.get(0, x) && x == "Hello");
        cout << "Passed all tests" << endl;
}*/

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

    void test()
    {
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "laobing";
    assert(ss.get(0, x)  &&  x == "pita");
    assert(ss.get(1, x)  &&  x == "roti");
    }

    int main()
    {
        test();
        cout << "Passed all tests" << endl;
    }


/* #include "Set.h"
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Set uls;
            assert(uls.insert(10));
            assert(uls.insert(20));
            assert(uls.size() == 2);
            assert(uls.contains(20));
            ItemType x = 30;
            assert(uls.get(0, x)  &&  x == 10);
            assert(uls.get(1, x)  &&  x == 20);
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }
 */
