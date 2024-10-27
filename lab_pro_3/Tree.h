#ifndef __TREE_H
#define __TREE_H
#include "Node.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Tree 
{
    private:
        Node* root;

    public:
        Tree():
            root(nullptr)
        {
        }
        ~Tree() //calls private helper destructor function
        {
            destructorRecursive(root); 
        }
        void insert(const string&);
        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        void remove(const string &);
        bool search (const string &) const;
    private:
        void nodeFind(Node*&, const string&); 
        void insertRecursive(Node*&, Node*, const string&);
        static bool comp(Node* a, Node* b);
        Node* nodeSearch(string key) const;
        Node* nodeSearchRecursive(Node* node, string key) const;
        void preOrderRecursive(Node* node) const;
        void inOrderRecursive(Node* node) const;
        void postOrderRecursive(Node* node) const;
        void destructorRecursive(Node* node);
};

#endif