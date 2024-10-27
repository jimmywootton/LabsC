#include "Node.h"

bool Node::isFull() //returns true if the node has a small and large key
{
    return (!large.empty());
}

bool Node::isLeaf() //returns true is the node is a leaf, meaning no children
{
    return (left == nullptr && middle == nullptr && right == nullptr);
}
