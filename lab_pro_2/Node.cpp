#include "Node.h"

Node* Node::getLeft() const
{
    return left;
}

Node* Node::getRight() const
{
    return right;
}

void Node::setLeft(Node* node)
{
    left = node;
}

void Node::setRight(Node* node)
{
    right = node;
}

string Node::getKey() const
{
    return key;
}

void Node::setKey(string keyString)
{
    key = keyString;
}

int Node::getCount() const
{
    return count;
}

void Node::setCount(int countInt)
{
    count = countInt;
}

void Node::incrementCount()
{
    ++count;
}

void Node::decrementCount()
{
    --count;
}