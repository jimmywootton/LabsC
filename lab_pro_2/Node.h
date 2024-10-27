#ifndef __NODE_H__
#define __NODE_H__
#include <string>
using namespace std;

class Node
{
    private:
        Node* left;
        Node* right;
        string key;
        int count;
    public:
        Node(string key): 
            left(nullptr), //left and right nullptr, meaning all nodes are initialized as leaves of tree
            right(nullptr),
            key(key), //string parameter
            count(1) //count automatically 1 when node is created, only changed in insert and remove function
        {
        }
        Node* getLeft() const;
        Node* getRight() const;
        void setLeft(Node* node);
        void setRight(Node* node);
        string getKey() const;
        void setKey(string key);
        int getCount() const;
        void setCount(int count);
        void incrementCount();
        void decrementCount();
};

#endif
