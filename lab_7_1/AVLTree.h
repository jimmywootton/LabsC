#ifndef __BSTREE_H__
#define __BSTREE_H__
#include "Node.h"
#include <iostream>
#include <string>
#define COUNT 10
using namespace std;

class AVLTree
{
    private:
        Node *root;
    public:
        AVLTree(): //initialized binary search tree to root nullptr
            root(nullptr)
        {
        }
        ~AVLTree() //destructor; calls private recursive helper function 
        {
            destructorRecursive(root);
        }
        void insert(const string& key);
        void printBalanceFactors() const;
    private:
        void rebalance(Node*);
        int balance(Node*) const;
        int height(Node*) const;
        void rotateLeft(Node* node);
        void rotateRight(Node* node);
        void replaceChild(Node* currentChild, Node* newChild);
        void setChild(Node* parentNode,string whichChild, Node* child);
        void printBalanceFactorsRecursive(Node* node) const;
        void destructorRecursive(Node*);
};
#endif