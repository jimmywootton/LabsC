#include "IntList.h"

IntList::~IntList()
{
    while (dummyHead != nullptr) //traverses list
    {
        IntNode* nodeToDelete = dummyHead; //sets nodeToDelete to head
        dummyHead = dummyHead -> next; //head becomes head's next
        delete nodeToDelete; //delete old head
    }
    delete dummyHead; //delete head
}


void IntList::push_front(int value) 
{
   IntNode* newNode = new IntNode(value);
   IntNode* firstNode = dummyHead -> next; //sets head's next node to firstNode
   dummyHead -> next = newNode; //links newNode with head
   newNode -> prev = dummyHead; //links newNode with head
   newNode -> next = firstNode; //links newNode with firstNode
   firstNode -> prev = newNode; //links newNode with firstNode
}

void IntList::pop_front() //removes first node
{
    IntNode* curNode = dummyHead -> next; //passes first node's reference into remove function
    remove(curNode);
}

void IntList::push_back(int value) 
{
    IntNode* newNode = new IntNode(value);
    IntNode* lastNode = dummyTail -> prev; //sets tail's prev node to last node
    newNode -> next = dummyTail; //links newNode with tail
    dummyTail -> prev = newNode; //links newNode with tail
    lastNode -> next = newNode; //links newNode with lastNode
    newNode -> prev = lastNode; //links newNode with lastNode
}

void IntList::pop_back() //removes last node
{
    IntNode* curNode = dummyTail -> prev; //passes last node's reference into remove function
    remove(curNode);
}

bool IntList::empty() const //checks to see if list there is anything between dummyHead and dummyTail, if not then list is empty
{
    return (dummyHead -> next == dummyTail);
}

ostream & operator<<(ostream &out, const IntList &rhs)
{
    if (rhs.empty()) //stops function if list is empty
    {
        return out;
    }
    IntNode* curr = rhs.dummyHead -> next;
    while (curr -> next -> next != nullptr) //traverses linked list, prints everything except for head, tail, and first node
    {
        out << curr -> data << " ";
        curr = curr -> next;
    }
    out << curr -> data; //prints first node without space
    return out; //return ostream
}

void IntList::printReverse() const
{
    if (empty()) //stops function if list is empty
    {
        return;
    }
    IntNode* curr = dummyTail -> prev; 
    while (curr -> prev -> prev != nullptr) //traverses linked list, prints everything except for head, tail, and last node
    { 
        cout << curr -> data << " ";
        curr = curr -> prev;
    }
    cout << curr -> data; //prints last node without space
}

void IntList::remove(IntNode*& curNode) //removes node passed as a reference
{
    if (empty()) //stops function if list is empty
    {
        return;
    }
    curNode -> prev -> next = curNode -> next; //links currNode's previous with currNode's next
    curNode -> next -> prev = curNode -> prev; //links currNode's previous with currNode's next
    delete curNode; //deletes dynamically allocated memory in curNode
}

