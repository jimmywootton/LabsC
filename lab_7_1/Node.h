#ifndef __NODE_H__
#define __NODE_H__
#include <string>
using namespace std;

class Node
{
    friend class AVLTree;
    private:
        Node* parent;
        Node* left;
        Node* right;
        string key;
    public:
        Node(string key): 
            parent(nullptr),
            left(nullptr), //left and right nullptr, meaning all nodes are initialized as leaves of tree
            right(nullptr),
            key(key) //string parameter
        {
        }
};

#endif