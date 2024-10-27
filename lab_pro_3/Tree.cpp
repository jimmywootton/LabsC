#include "Tree.h"

bool Tree::comp(Node* a, Node* b) //overload operator for sort algorithm, sorts nodes based on small key size
{
    return (a -> small < b -> small);
}

void Tree::insert(const string& key)
{
    if (root == nullptr)
    {
        root = new Node(key);
    }
    else
    {
        nodeFind(root, key);
    }
}

void Tree::nodeFind(Node*& node, const string& key)
{
    if (key == node -> small || key == node -> large) //stop function if node with key is found; prevents duplicates
    {
        return;
    }
    if (!(node -> isLeaf())) //recursively traverses list to find the correct leaf node for insertion
    {
        if (key < node -> small)
        {
            nodeFind(node -> left, key);
        }
        else if (node -> large.empty() || key < node -> large)
        {
            nodeFind(node -> middle, key);
        }
        else 
        {
            nodeFind(node -> right, key);
        }
    }
    else
    {
        insertRecursive(node, nullptr, key); //calls recursive insert function when correct leaf has been found
    }
}

void Tree::insertRecursive(Node*& node, Node* childNode, const string& key)
{
    if (!(node -> isFull())) //case for if node isnt full
    {
        {//inserts key in right spot
            if (key < node -> small)
            {
                node -> large = node -> small;
                node -> small = key;
            }
            else
            {
            node -> large = key;
            }
        }
        if (!(node -> isLeaf())) //if node isnt full; child pointers updated
        {
            vector<Node*> keys = {node -> left, node -> middle, childNode}; //create vector of node's pointers and the unlinked child pointer
            sort (keys.begin(), keys.end(), comp); //sort them using overloaded comparison operator
            {//assigns childen of node based on small key size
                node -> left = keys.at(0);
                node -> left -> parent = node;
                node -> middle = keys.at(1);
                node -> middle -> parent = node;
                node -> right = keys.at(2);
                node -> right -> parent = node;
            }
        }
    }
    else //case for if node is full
    {
        vector<string> stringKeys = {node -> small, node -> large, key}; //vector node's current keys and the key to insert
        sort(stringKeys.begin(), stringKeys.end()); //sorts keys
            //assigns smallest key to current node and largest key to a new node unlinked child pointer
            node -> small = stringKeys.at(0);
            node -> large = "";
            Node* newNode = new Node(stringKeys.at(2));
        if (!(node -> isLeaf())) //if node isnt a leaf
        {
            vector<Node*> keys = {node -> left, node -> middle, node -> right, childNode}; //create vector of node's child pointers and unlinked child pointer
            sort(keys.begin(), keys.end(), comp); //sort them using overloaded comparisio operator
            {//links all of current node's children and the unlinked child pointer with the current node and new node
                node -> left = keys.at(0);
                node -> left -> parent = node;
                node -> middle = keys.at(1);
                node -> middle -> parent = node;
                node -> right = nullptr;
                newNode -> left = keys.at(2);
                newNode -> left -> parent = newNode;
                newNode -> middle = keys.at(3);
                newNode -> middle -> parent = newNode;
            }
        }
        if (node == root) //if node is the root
        {
            Node* rootNode = new Node(stringKeys.at(1)); //creates new root node
            {//assigns current node and new node with new root node
                rootNode -> left = node;
                node -> parent = rootNode;
                rootNode -> middle = newNode;
                newNode -> parent = rootNode;
            }
            root = rootNode; //sets root to root node
        }
        else
        {
            insertRecursive(node -> parent, newNode, stringKeys.at(1)); //recursively repeats the process with the new created node and the middle string value on the parent
        }
    }
}

Node* Tree::nodeSearch(string key) const //call recursive node search
{
    return nodeSearchRecursive(root, key);
}

Node* Tree::nodeSearchRecursive(Node* node, string key) const
{
    if (node != nullptr)  //recursively traverses the list to find node that contains the key
    {
        if (key == node -> small || key == node -> large) //returns node that contains the key
        {
            return node; 
        }
        else if (key < node -> small) 
        {
            return nodeSearchRecursive(node -> left, key);
        }
        else if ((!node -> isFull()) || key < node -> large)
        {
            return nodeSearchRecursive(node -> middle, key);
        }
        else 
        {
            return nodeSearchRecursive(node -> right, key);
        }
    }
    return nullptr; //returns nullptr if node is not found
}

void Tree::remove(const string& key)
{
    Node* node = nodeSearch(key); //returns the key with the node
    if (node == nullptr) //ends function if node is not found or tree does not exist
    {
        return;
    }
    if (node == root && (!node -> isFull()) && node -> isLeaf()) //deletes the tree if the node is the sole item in the tree and also only contains a single key
    {
        delete node;
        root = nullptr;
    }
    else
    {
        if (node -> isLeaf()) //if the node is a leaf
        {
            if (node -> isFull()) //if the node is full then remove the key from the node and adjust the remain key
            {
                if (key == node -> small)
                {
                    node -> small = node -> large;
                }
                node -> large = "";  
            }
            else //if the node isnt a leaf
            {
                if ((!node -> parent -> isFull()) && (!node -> parent -> left -> isFull()) && (!node -> parent -> middle -> isFull()) && node -> parent -> right == nullptr) //in the case of when parent of node isnt full and all of parents children arent full, removes all children nodes and sets the other child node as the second key
                {
                    if (node -> parent -> left == node)
                    {
                        node -> parent -> large = node -> parent -> middle -> small;
                    }
                    else if (node -> parent -> middle == node)
                    {
                        node -> parent -> large = node -> parent -> small;
                        node -> parent -> small = node -> parent -> left -> small;
                    }
                    node = node -> parent;
                    delete node -> left;
                    delete node -> middle;
                    node -> left = nullptr;
                    node -> middle = nullptr;
                }
                else //unhandled cases; to be finished
                {
                    throw std::runtime_error("unexpected leaf node case");
                }
            }
        }
        else //if the node isnt a leaf
        {
            if (node == root && (!node -> isFull()) && (!node -> left -> isFull()) && (!node -> middle -> isFull()) && (node -> right == nullptr)) //in the case when the node is a not full root and both of its children are not full leaves
            {
                node -> small = node -> left -> small;
                node -> large = node -> middle -> small;
                delete node -> left;
                delete node -> middle;
                node -> left = nullptr;
                node -> middle = nullptr;
            }
            else //unhandled cases; to be finished
            {
                throw std::runtime_error("unexpected non leaf node case");
            }
        }
    }
}

bool Tree::search (const string& key) const //returns true if the nodeSearch function does not yield a nullptr
{
    return (nodeSearch(key) != nullptr);
}

void Tree::preOrder() const //calls recursive preOrder function
{
    preOrderRecursive(root);
}

void Tree::preOrderRecursive(Node* node) const //recursively prints preOrder
{
    if (node == nullptr) //base case
    {
        return;
    }
    cout << node -> small << ", ";
    preOrderRecursive(node -> left);
    if (node -> isFull()) //only prints second key if it exists
    {
        cout << node -> large << ", ";
    }
    preOrderRecursive(node -> middle);
    preOrderRecursive(node -> right);
}

void Tree::inOrder() const //calls recursive inOrder function
{
    inOrderRecursive(root); 
}

void Tree::inOrderRecursive(Node* node) const //recursively prints inOrder
{
    if (node == nullptr) //base case
    {
        return;
    }
    inOrderRecursive(node -> left);
    cout << node -> small << ", ";
    inOrderRecursive(node -> middle);
    if (!(node -> large.empty())) //only prints second key if it exists
    {
        cout << node -> large << ", ";
    }
    inOrderRecursive(node -> right);
}

void Tree::postOrder() const //calls recursive postOrder function
{
    postOrderRecursive(root);
}

void Tree::postOrderRecursive(Node* node) const //recursively prints postOrder
{
    if (node == nullptr) //base case
    {
        return;
    }
    postOrderRecursive(node -> left);
    postOrderRecursive(node -> middle);
    cout << node -> small << ", ";
    postOrderRecursive(node -> right);
    if (!(node -> large.empty())) //only prints second key if it exists
    {
        cout << node -> large << ", ";
    }
}

void Tree::destructorRecursive(Node* node) //recursive destructor
{
    if (node != nullptr) 
    {
        destructorRecursive(node -> left);
        destructorRecursive(node -> middle);
        destructorRecursive(node -> right);
        delete node;
    }
}
