// ChatTracker.cpp

// This is a correct but inefficient implementation of
// the ChatTracker functionality.

#include "ChatTracker.h"
#include <string>
#include <vector>
#include <list>
#include <functional>
using namespace std;

  // This class does the real work of the implementation.

class ChatTrackerImpl
{
  public:
    ChatTrackerImpl(int maxBuckets);
    ~ChatTrackerImpl();
    void join(string user, string chat);
    int terminate(string chat);
    int contribute(string user);
    int leave(string user, string chat);
    int leave(string user);
    
    unsigned int hash_function(const string& hashMe); //Hash Function Declaration
    
  private:
    struct Info
    {
        Info(string u, string c) : user(u), chat(c), count(0) {}
        string user;
        string chat;
        int count;
    };

    vector<list<Info>> hashTable;
    vector<list<Info>> chat_hashTable;
    int hash_buckets;
    
};

//Hash Function Implementation from Nachenberg Slides
unsigned int ChatTrackerImpl::hash_function(const string& hashMe)
{
    hash<string>str_hash;
    size_t hashValue = str_hash(hashMe);
    unsigned int numOfBuckets = hashValue % hash_buckets;
    return numOfBuckets;
}

ChatTrackerImpl::ChatTrackerImpl(int maxBuckets) //Constructor
{
    hash_buckets=maxBuckets;
    hashTable.resize(hash_buckets); //resizes hashTable hold to hash_buckets
    chat_hashTable.resize(hash_buckets); //resizes chat_hashTable hold to hash_buckets
}

void ChatTrackerImpl::join(string user, string chat)
//  The user joins a new or existing chat. Whether or not the user was associated with that chat before, that chat is now the user's current chat. If the user had previously joined that chat and not left it since then, the user's count of contributions to that chat remains the same; otherwise, it becomes 0. If the chat had previously been joined by this or any other user and has not been terminated since then, the chat's count of contributions is unchanged; otherwise, it becomes 0.
{
    unsigned int hash_index=hash_function(user); //intializing index for user hashing
    unsigned int chat_index=hash_function(chat); //intializing index for chat hashing
    while (hashTable[hash_index].size() !=0 && hashTable[hash_index].begin()->user != user) //when size is not zero
    {
        if (hash_index==hash_buckets - 1) //when hash_index is one less than hash_buckets
        {
            hash_index=0; //set it to 0
        }
        
        else
        {
            hash_index++; //increment hash_index
        }
    }
    
    while (chat_hashTable[chat_index].size() !=0 && chat_hashTable[chat_index].back().chat != chat) //when size is not zero
    {
        if (chat_index==hash_buckets - 1) //when chat_index is one less than hash_buckets
        {
            chat_index=0; //set it to 0
        }
        
        else
        {
            chat_index++; //increment chat_index
        }
    }
    
    if (chat_hashTable[chat_index].size()==0) //when size of chat is 0
    {
        chat_hashTable[chat_index].push_back(Info("",chat));
    }
    
    list<Info>::iterator hash_it=hashTable[hash_index].end(); //declaration of hash iterator
    while (hash_it != hashTable[hash_index].begin()) //while hash iterator hasn't reached the beginning
    {
        hash_it--; //decrement hash_it
        
        if (hash_it->chat==chat)
        {
            Info tempPtr = Info(hash_it->user, hash_it->chat);
            tempPtr.count=hash_it->count;
            hashTable[hash_index].push_back(tempPtr);
            return;
        }
    }
    
    hashTable[hash_index].push_back(Info(user, chat));
    chat_hashTable[chat_index].push_back(Info(user,chat));
    return;
}

int ChatTrackerImpl::terminate(string chat)
//  If the chat does not exist, this function returns 0; otherwise, all users associated with the chat are no longer associated with it (as if they left the chat), and the function returns the chat's count of contributions. If that chat was any user's current chat, then the existing chat the user most recently joined and hasn't left since most recenty joining becomes the user's current chat; if there is no such chat, then that user has no current chat.
{
    unsigned int chat_index=hash_function(chat); //intializing index for chat hashing
    int total=0; //to keep track of total contributions
    
    while (chat_hashTable[chat_index].size() !=0 && chat_hashTable[chat_index].back().chat !=chat) //when size is not zero
    {
        if (chat_index==hash_buckets - 1) //when chat_index is one less than hash_buckets
        {
            chat_index=0; //set it to 0
        }
        
        else
        {
            chat_index++; //increment chat_index
        }
    }
    
    if (chat_hashTable[chat_index].size()==0) //when size is 0
    {
        return 0; //if chat does not exist, return 0
    }
    
    else
    {
        list<Info>::iterator chat_it=chat_hashTable[chat_index].end(); //declaration of chat iterator
        total=chat_hashTable[chat_index].begin()->count;
        
        while(chat_it != chat_hashTable[chat_index].begin()) //while chat iterator hasn't reached the beginning
        {
            chat_it--; //decrement chat_it--
            
            string userName=chat_it->user; //have userName point to user
            
            unsigned int user_index=hash_function(userName); //intializing index for userName hashing
            
            while (hashTable[user_index].size() != 0 && hashTable[user_index].back().user != userName) //when size is not zero
            {
                user_index++; //increment user_index
            }
            
            if (hashTable[user_index].size() != 0) //when size is not zero
            {
                list<Info>::iterator user_it=hashTable[user_index].end(); //declaration of user iterator
                while (user_it != hashTable[user_index].begin()) //while user iterator hasn't reached the beginning
                {
                    user_it--; //decrement user_it--
                    if (user_it->chat==chat)
                    {
                        hashTable[user_index].erase(user_it); //user leaves
                        user_it=hashTable[user_index].begin();
                    }
                }
            }
        }
        chat_hashTable[chat_index].erase(chat_it); //leaves chat
        chat_it=chat_hashTable[chat_index].end();
    }
    return total; //return total contributions
}

int ChatTrackerImpl::contribute(string user)
//  If the user has no current chat, return 0. Otherwise, both the user's count of contributions to that user's current chat and that current chat's count of contributions are increased by one. Return the resulting user's count of contributions to that current chat
{
    unsigned int user_index=hash_function(user);
    
    while (hashTable[user_index].size() !=0 && hashTable[user_index].begin()->user != user) //when size is not zero
    {
        if (user_index == hash_buckets - 1)
        {
            user_index=0;
        }
        
        else
        {
            user_index++; //increment hash_index
        }
    }
    
    if (hashTable[user_index].size() > 0) //when size is greater than 0
    {
        hashTable[user_index].back().count++;
        int total=hashTable[user_index].back().count;
        string chat=hashTable[user_index].back().chat;
        unsigned int chat_index=hash_function(chat); //intializing index for chat hashing
        
        while (chat_hashTable[chat_index].size() !=0 && chat_hashTable[chat_index].begin()->chat != chat) //when size is not zero and chat_hashTable
        {
            if (chat_index==hash_buckets - 1) //when chat_index is one less than hash_buckets
            {
                chat_index=0; //set it to 0
            }
            
            else
            {
                chat_index++; //increment chat_index
            }
        }
        chat_hashTable[chat_index].begin()->count++; //increment count
        return total; //return total contributions
    }
    return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
//  If the user is not associated wih the indicated chat, return -1. Otherwise, the user is no longer associated with that chat, and the function returns the user's count of contributions to that chat. If that chat was the user's current chat, then the existing chat the user most recently joined and hasn't left since most recenty joining bcomes the user's current chat; if there is no such chat, then that user has no current chat. This function leaves the chat's count of contributions unchanged.
{
    unsigned int hash_index=hash_function(user); //intializing index for user hashing
    unsigned int chat_index=hash_function(chat); //intializing index for chat hashing
    int total=0; //to keep track of total contributions
    while (hashTable[hash_index].size() !=0 && hashTable[hash_index].begin()-> user != user) //when size is not zero
    {
        if (hash_index==hash_buckets - 1) //when hash_index is one less than hash_buckets
        {
            hash_index=0; //set it to 0.
        }
        
        else
        {
            hash_index++; //increment hash_index
        }
    }
    
    while (chat_hashTable[chat_index].size() !=0 && chat_hashTable[chat_index].back().chat != chat) //when size is not zero
    {
        if (chat_index==hash_buckets - 1) //when chat_index is one less than hash_buckets
        {
            chat_index=0; //set it to 0
        }
        
        else
        {
            chat_index++; //increment chat_index
        }
    }
    
    list<Info>::iterator hash_it=hashTable[hash_index].end(); //declaration of hash iterator
    while (hash_it != hashTable[hash_index].begin()) //while hash iterator hasn't reached the beginning
    {
        hash_it--; //decrement hash_it
        if (hash_it->chat==chat)
        {
            total=hash_it->count;
            hashTable[hash_index].erase(hash_it); //leave chat
        
        
            list<Info>::iterator chat_it=chat_hashTable[chat_index].end(); //declaration of chat iterator
            while (chat_it != chat_hashTable[chat_index].begin()) //while chat iterator hasn't reached the beginning
            {
                chat_it--; //decrement chat_it
                if (chat_it->user==user) //if chat_it is equal to user
                {
                    chat_hashTable[chat_index].erase(chat_it); //leave chat
                }
                return total; //return total contributions
            }
        }
    }
    return -1; //when user is not associated with current chat
}

int ChatTrackerImpl::leave(string user)
//  If the user has no current chat, return -1. Otherwise, the user is no longer associated with that user's current chat, and the function returns the user's count of contributions made to that chat. The existing chat the user most recently joined and hasn't left since most recenty joining bcomes the user's current chat; if there is no such chat, then that user has no current chat. This function leaves the chat's count of contributions unchanged.
{
    unsigned int hash_index=hash_function(user); //intializing index for user hashing
    int total=0; //to keep track of total contributions
    while (hashTable[hash_index].size() !=0 && hashTable[hash_index].begin()-> user != user) //when size is not zero
       {
           if (hash_index==hash_buckets - 1) //when hash_index is one less than hash_buckets
           {
               hash_index=0; //set it to 0
           }
           
           else
           {
               hash_index++; //increment hash_index
           }
       }

    string forumName; //to keep track of forumName
    
    list<Info>::iterator hash_it=hashTable[hash_index].end(); //declaration of hash iterator
    if (hash_it != hashTable[hash_index].begin()) //while chat iterator hasn't reached the beginning
    {
        hash_it--; //decrement hash_it
        
        forumName=hash_it->chat; //have forumName pointer to chat
        total=hash_it->count; //have total point to count
        hashTable[hash_index].erase(hash_it); //leave chat
        
        unsigned int forumName_index=hash_function(forumName); //intializing index for forumName hashing
        while (chat_hashTable[forumName_index].size() !=0 && chat_hashTable[forumName_index].begin()-> chat != forumName) //when size is not zero
        {
            if (forumName_index==hash_buckets - 1) //when forumName_index is one less than hash_buckets
            {
                forumName_index=0; //set it to 0
            }
            
            else
            {
                forumName_index++; //increment forumName_index
            }
     
        }
        list<Info>::iterator chat_it=chat_hashTable[forumName_index].end(); //declaration of chat iterator
        while (chat_it !=chat_hashTable[forumName_index].begin()) //while chat iterator hasn't reached the beginning
        {
            chat_it--; //decrement chat_it
            
            if (chat_it->user==user) //if chat_it is equak to user
            {
                chat_hashTable[forumName_index].erase(chat_it); //leave chat
            }
            return total; //return total contributions
        }
    }
    return -1; //when user has no current chat
}

ChatTrackerImpl::~ChatTrackerImpl() //Destructor
{};

//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
    m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
    delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
    m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
    return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
    return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
    return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
    return m_impl->leave(user);
}
