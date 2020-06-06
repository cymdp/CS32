//
//  linear.cpp
//  Homework 3
//
//  Created by Cymfenee on 5/5/20.
//  Copyright © 2020 CDP. All rights reserved.
//

    bool somePredicate(string s);

    // Return false if the somePredicate function returns true for at
	  // least one of the array elements; return true otherwise.
    bool allFalse(const string a[], int n)
	{
        if (n<=0)
        {
            return true;
        }
        
        if (somePredicate(a[n-1])==true)
        {
	    return false;
        }
        
        else
        {
            return (allFalse(a+1, n-1));
        }
	}

	  // Return the number of elements in the array for which the
	  // somePredicate function returns false.
	int countFalse(const string a[], int n)
	{
        if (n<=0) //invalid index
        {
            return 0;
        }
        
        if (somePredicate(a[0])==false) //if first element is false, increment and add 1
        {
            return 1+countFalse(a+1,n-1);
        }
        
        else
        {
            return countFalse(a+1,n-1); //if not, keep incrementing
        }
    }

	  // Return the subscript of the first element in the array for which
	  // the somePredicate function returns false.  If there is no such
	  // element, return -1.
	int firstFalse(const string a[], int n)
	{
        if (n<=0) //base case
        {
            return -1;
        }
        
        if (somePredicate(a[0])==false) //if first element is false
        {
            return 0;
        }
        
        else
        {
            if (firstFalse(a+1,n-1) == -1) //if we don't find a false during recur
            {
                return -1;
            }
            
         return 1+(firstFalse(a+1,n-1);
        }
	}

	  // Return the subscript of the greatest string in the array (i.e.,
	  // the smallest subscript m such that a[m] >= a[k] for all
	  // k from 0 to n-1).  If the array has no elements to examine,
	  // return -1.
	int locateMaximum(const string a[], int n)
	{
        if (n<=0) //base case 1
        {
            return -1;
        }
                    
        if (n==1) //base case 2
        {
            return 0;
        }
        
        if (a[locateMaximum(a,n-1)] >= a[n-1])
        {
            return locateMaximum(a,n-1);
        }
                    
        else
        {
            return n-1;
        }
	}

	  // If all n2 elements of a2 appear in the n1 element array a1, in
	  // the same order (though not necessarily consecutively), then
	  // return true; otherwise (i.e., if the array a1 does not contain
	  // a2 as a not-necessarily-contiguous subsequence), return false.
	  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
	  // For example, if a1 is the 7 element array
	  //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
	  // then the function should return true if a2 is
	  //    "kyle" "kenny" "butters"
	  // or
	  //    "kyle" "cartman" "cartman"
	  // and it should return false if a2 is
	  //    "kyle" "butters" "kenny"
	  // or
	  //    "stan" "kenny" "kenny"
	bool contains(const string a1[], int n1, const string a2[], int n2)
	{
        if (n2<=0) //base case 1
        {
            return true;
        }
        
        if (n1<=0 || n1<n2) //base case 2
        {
            return false;
        }
        
        if (a2[0]==a1[0]) //if the first element of a2 matches a1
        {
            return contains(a1+1,n1-1,a2+1,n2-1); //increment both recursively
        }
        
        else //otherwise increment a1 until it matches a2
        {
            return  contains(a1+1,n1-1,a2,n2);
        }
	}
