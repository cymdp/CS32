//
//  eval.cpp
//  CS32 HW2
//
//  Created by Cymfenee on 4/30/20.
//  Copyright © 2020 CDP. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int priority(char ch) //sets the priority of !, & and ^
{
    switch (ch)
    {
        case '!':       //  ! has the highest priority
            return 2;
        case '&':       //& has higher priority than ^
            return 1;
        case '^':
            return 0;   //^ has lowest priority
    }
    return 0;
}

string convert(string infix, string& postfix) //converts from infix to postfix
{
    postfix="";   //initialize postfix to empty
    stack<char> opStack;  //operator stack for characters characters
    for (int i=0; i<infix.size(); i++)
    {
        char ch=infix[i];
        
        switch (ch)
        {
            case 'T':       //for T or F
            case 'F':
                postfix +=ch; //add to postfix
                break;
            case '(':       //for  '('
                opStack.push(ch); //push on stack
                break;
            case ')':
                while (opStack.top() !='(')  //until we match ( to ), add the characters from stack on postfix
                {
                    postfix +=opStack.top();
                    opStack.pop();
                }
                opStack.pop();    //pop (
                break;
            
            case '!':   //for (!,&,^)
            case '&':
            case '^':
                while (!opStack.empty() && opStack.top() !='(' && priority(ch) <=priority(opStack.top()))
                //when stack is not empty, we don't see ( and the priority of the current char than the priority of whats on the stack
                {
                    postfix +=opStack.top(); //add to postfix
                    opStack.pop();
                }
                opStack.push(ch); //push the operator on the stack
                break;
        }
    }
    while (!opStack.empty())  //operand stack isn't empty, so add whats left to postfix and return postfix
    {
        postfix +=opStack.top();
        opStack.pop();
    }
    return postfix;
}


string deleteSpaces(string infix)  //returns infix string with no spaces
{
    string infix_deleteSpaces="";
    
    for (int i=0; i<infix.size(); i++)
        
        if (infix[i] !=' ')
            infix_deleteSpaces+=infix[i];
    
    return infix_deleteSpaces;
}


bool isValid(string infix) //checks for valid infix
{
    string m_infix = deleteSpaces(infix);    //checks that there are no spaces
    for (int i=0; i < m_infix.size(); i++) //goes through the infix w/o spaces
    {
        if (m_infix[m_infix.size()-1]=='^' || m_infix[m_infix.size()-1]=='&')
            return false;
        
        if (m_infix[i]=='^' || m_infix[i]=='&')   //if ^ or & are present, T F and ) can be present before the operators
                                                            //also can to have T F ! and ( after the operators, else invalid
        {
            if ((m_infix[i-1] !='T' && m_infix[i-1] !='F' && m_infix[i-1] !=')') || ((m_infix[i+1]) !='T' && m_infix[i+1] !='F' && m_infix[i+1] !='!'
                && m_infix[i+1] !='('))
                return false;
        }
        else if (m_infix[i]=='T' || m_infix[i]=='F')  //if  T or F are present, we can't have T,F or ! after the operand
        {
            if (m_infix[i+1]=='T' || m_infix[i+1]=='F' || m_infix[i+1]=='(' || m_infix[i+1]=='!')
                return false;
        }
    }
    return true;
}

int evaluate(string infix, string& postfix, bool& result) //evaluates postfix
{
    if (isValid(infix)) //checks if infix is valid
    {
        postfix=convert(infix, postfix);    //converts infix to postfix, stores in postfix
        
        if (postfix.empty())
            return 1;
       
        stack<bool> opStack;   //a stack of bools that takes in the operands
        
        for (int i=0; i<postfix.length(); i++)
        {
            char ch=postfix[i];
            
            if (ch=='T')
                opStack.push(true); //push T bc T equals true
            
            else if (ch=='F')
                opStack.push(false); //push F bc F equals false
            
            else if (ch=='!')
            {
                bool temp=opStack.top(); //stores top in temp
                opStack.pop(); //pop temp
                opStack.push(!temp); //push opposite of temp
            }
            else
            {
                bool op2=opStack.top();
                opStack.pop();
                
                if (opStack.empty())   //checks for )
                    return 1;
                
                bool op1=opStack.top();
                opStack.pop();
                
                if (postfix[i]=='^')  //if ^ present
                {
                    if (op1 ^ op2)
                        opStack.push(true); //push to opStack
                    else
                        opStack.push(false);
                }
                if (postfix[i]=='&')  //if & present
                {
                    if (op1 && op2)   //makes && equiv to &
                        opStack.push(true); //push to opStack
                    else
                        opStack.push(false);
                }
                
                if (postfix[i] == '|')  //if | present
                {
                    if (op1 || op2)   //evaluate with ||
                        opStack.push(true); //push to opStack
                    else
                        opStack.push(false);
                }
                
                
            }
        }
        result=opStack.top();    //the last and only item in our stack should be our result, and we return 0
        return 0;
    }
    return 1;
}



