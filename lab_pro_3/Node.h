#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node 
{
    friend class Tree;
    private:
        string small;
        string large;
        Node* left;
        Node* middle;
        Node* right;
        Node* parent;
    public:
        friend class Tree;
        Node(string small): //initializes nodes to only have small key
            small(small),
            large(""),
            left(nullptr),
            middle(nullptr),
            right(nullptr),
            parent(nullptr)
        {
        }
        bool isFull();
        bool isLeaf();
};

#endif

