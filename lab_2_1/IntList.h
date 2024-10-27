#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <iostream>
using namespace std;

struct IntNode 
{
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data): 
        data(data), 
        prev(0), 
        next(0) 
    {
    }
};

class IntList
{
    private:
        IntNode* dummyHead;
        IntNode* dummyTail;
    public:
        IntList(): //inline constructor, especially careful that dummyHead and dummyTail are not nullptr
            dummyHead(new IntNode(0)), 
            dummyTail(new IntNode(0))
        {
            //head and tail are linked to each other and head's prev is nullptr and tail's next is nullptr
            dummyHead -> next = dummyTail; 
            dummyHead -> prev = nullptr;
            dummyTail -> prev = dummyHead;
            dummyTail -> next = nullptr;
        }
        ~IntList();
        void push_front(int value);
        void pop_front();
        void push_back(int value);
        void pop_back();
        bool empty() const;
        friend ostream & operator<<(ostream &out, const IntList &rhs);
        void printReverse() const;
        void remove(IntNode*& curNode);
};

#endif