#include "AVLTree.h"

void AVLTree::insert(const string& key) 
{
    Node* node = new Node(key); //creates node with key parameter
    if (root == nullptr) //if tree is empty then node becomes root
    {
        root = node;
        return;
    }
    Node* current = root;
    while (current != nullptr) //sets current's next node to the node to insert
    {
        if (current -> key > node -> key) 
        {
            if (current -> left == nullptr) 
            {
                current -> left = node;
                node -> parent = current;
                break;
            }
            else 
            {
                current = current -> left;
            }
        }
        else if ((current -> key < node -> key))
        {
            if (current -> right == nullptr) 
            {
                current -> right = node;
                node -> parent = current;
                break;
            }
            else
            {
                current = current -> right;
            }
        }
        else //if the key already exists in the node
        {
            break;
        }
    }
    node = node -> parent;
    while (node != nullptr) //rebalances tree to meet AVL properties
    {
        rebalance(node);
        node = node -> parent;
    }
}

void AVLTree::rebalance(Node* node) 
{
    if (balance(node) == 2) //balances tree if the node is unbalances
    {
        if (balance(node -> left) == -1) //handles case where left child has right child, turns it to left child has left child
        {
            rotateLeft(node -> left);
        }
        rotateRight(node); //left child has left child
    } 
    else if (balance(node) == -2) //handles case where right child has left chukd, turns it to right child has right child
    {
        if (balance(node -> right) == 1) 
        {
            rotateRight(node -> right);
        }
        rotateLeft(node); //right child has right child
    }       
}

int AVLTree::balance(Node* node) const //returns the difference in height between the left and right nodes
{
    return height(node -> left) - height(node -> right);
}

int AVLTree::height(Node* node) const //calls recursive height function
{
    if (node == nullptr) //base case for if node is not found or the end of the bst has been reached
    {    
        return -1;
    }
    //recursively iterates through the next subtrees
    int leftHeight = height(node ->left);
    int rightHeight = height(node -> right);
    return 1 + max(leftHeight, rightHeight); 
}

void AVLTree::rotateLeft(Node* node) 
{
    Node* rightLeftChild = node -> right -> left; //remembers node that causes unbalancing
    if (node -> parent != nullptr)
    {
        replaceChild(node, node -> right); //sets new parent for all rotating nodes
    }
    else //in the case where rebalancing modifies root
    {
        root = node -> right;
        root -> parent = nullptr;
    }
    setChild(node -> right, "left", node); //sets new children
    setChild(node, "right", rightLeftChild); //sets new children
}

void AVLTree::rotateRight(Node* node) //same as rotate left but in the opposite direction
{
    Node* leftRightChild = node -> left -> right;
    if (node -> parent != nullptr)
    {
        replaceChild(node, node -> left);
    }
    else 
    {
        root = node -> left;
        root -> parent = nullptr;
    }
    setChild(node -> left, "right", node);
    setChild(node, "left", leftRightChild);
}

void AVLTree::replaceChild(Node* currentChild, Node* newChild) //sets parent to left or right child
{
    if (currentChild -> parent -> left == currentChild)
    {
        setChild(currentChild -> parent, "left", newChild);
    }
    else if (currentChild -> parent -> right == currentChild)
    {
        setChild(currentChild -> parent, "right", newChild);
    }
}

void AVLTree::setChild(Node* parentNode, string whichChild, Node* child) 
{
    if (whichChild != "left" && whichChild != "right") //case where whichChild node is not one of two expected values
    {
        return;
    }
    if (whichChild == "left")
    {
        parentNode -> left = child;
    }
    else
    {
        parentNode -> right = child;
    }
    if (child != nullptr)
    {
        child -> parent = parentNode;
    }
}

void AVLTree::printBalanceFactors() const //calls recursive print balance factor
{
    printBalanceFactorsRecursive(root);
    cout << endl;
}

void AVLTree::printBalanceFactorsRecursive(Node* node) const
{
    if (node == nullptr) //base case
    {
        return;
    }
    //recursively traverses list in order of key
    printBalanceFactorsRecursive(node -> left);
    cout << node -> key << "(" << balance(node) << "), ";
    printBalanceFactorsRecursive(node -> right);
}

void AVLTree::destructorRecursive(Node* node) //private helper function used in destructor
{
    if (node != nullptr) //starts at the root and recursively deletes all the nodes from the leaves to the root
    {
        destructorRecursive(node -> left);
        destructorRecursive(node -> right);
        delete node;
    }
}
