#include "BSTree.h"

Node* BSTree::getParentRecursive(Node* subtreeRoot, Node* node) //subtreeroot represents the parent we are trying to find and "node" is the parameter
{
   if (subtreeRoot == nullptr) //base case for if BST is empty or if the target node is the root, in these instances nullptr is returned
   {
      return nullptr;
   }
   if (subtreeRoot -> getLeft() == node || subtreeRoot -> getRight() == node) //base case that returns the subtreeroot when it's children are equal to the targetNode, meaning it is the parent
   {
      return subtreeRoot;
   }
   if (node -> getKey() < subtreeRoot -> getKey()) //recursively traverses binary search tree until subtreeroot base case is met
   {
      return getParentRecursive(subtreeRoot -> getLeft(), node);
   }
   else
   {
      return getParentRecursive(subtreeRoot -> getRight(), node);
   }
}

Node* BSTree::getParent(Node* node) //calls getParent recursive function
{
   return getParentRecursive(root, node);
}

void BSTree::destructorRecursive(Node* node) //private helper function used in destructor
{
   if (node != nullptr) //starts at the root and recursively deletes all the nodes from the leaves to the root
   {
      destructorRecursive(node -> getLeft());
      destructorRecursive(node -> getRight());
      delete node;
   }
}

Node* BSTree::nodeSearchRecursive(Node* node, string key) const
{
   if (node != nullptr) 
   {
      if (key == node -> getKey()) //base case for when the node with the same key word has been found
      {
         return node; 
      }
      else if (key < node -> getKey()) //recursively traverse binary search tree until the key string equals a node or it doesnt
      {
         return nodeSearchRecursive(node -> getLeft(), key);
      }
      else
      {
         return nodeSearchRecursive(node -> getRight(), key);
      }
   }
   return nullptr; //base case for when the node with the keyString has not been found
}

Node* BSTree::nodeSearch(string key) const //cases the recursive node search
{
   return nodeSearchRecursive(root, key);
}

void BSTree::insertRecursive(Node* parent, Node* node) 
{
   if (node -> getKey() < parent -> getKey()) //recursively traverses binary search tree until it finds the correct location to insert the node
   {
      if (parent -> getLeft() == nullptr) //base case for when the node becomes the parent's left child
      {
         parent -> setLeft(node);
      }
      else
      {
         insertRecursive(parent -> getLeft(), node);
      }
   }
   else if (node -> getKey() > parent -> getKey())
   {
      if (parent -> getRight() == nullptr) //base case for when the node becomes the parent right child
      {
         parent -> setRight(node);
      }
      else
      {
         insertRecursive(parent -> getRight(), node);
      }
   }
   else
   {
      parent -> incrementCount(); //base case for when inserted node has already been found, increments the count
   }
}

void BSTree::removeRecursive(Node*& parent, Node*& node) 
{
   if (node -> getLeft() == nullptr && node -> getRight() == nullptr) //base case for when the node is a leaf
   {
      if (parent == nullptr) // base case for when the node to delete is a leaf and also the root, in which case the root becomes nullptr(empty tree)
      {
         root = nullptr;
      }
      else if (parent -> getLeft() == node) //sets the node's parent's child to nullptr
      {
         parent -> setLeft(nullptr);
      }
      else
      {
         parent -> setRight(nullptr);
      }
      delete node; //deallocate node memory
   }
   else
   {
      Node* succNode; //recursively sets the next lowest node equal to the node to delete until the leaf to delete is found
      Node* succParent = node;
      if (node -> getLeft() == nullptr) //if the left child doesnt exist then the next smallest node is found and copied to node
      {
         succNode = node -> getRight();
         while (succNode -> getLeft() != nullptr) 
         {
            succParent = succNode;
            succNode = succNode -> getLeft();
         }    
      }
      else //if both children exist then the node of smaller adjacent value is copied and assigned to node
      {
         succNode = node -> getLeft();
         while (succNode -> getRight() != nullptr) 
         {
            succParent = succNode;
            succNode = succNode -> getRight();
         }    
      }
      node -> setKey(succNode -> getKey()); //copy node key information
      node -> setCount(succNode -> getCount()); //copy node count information
      removeRecursive(succParent, succNode); //calls function with new node
   }
}

int BSTree::heightRecursive(Node* node) const
{
   if (node == nullptr) //base case for if node is not found or the end of the bst has been reached
   {    
      return -1;
   }
   //recursively iterates through the next subtrees
   int leftHeight = heightRecursive(node -> getLeft());
   int rightHeight = heightRecursive(node -> getRight());
   return 1 + max(leftHeight, rightHeight); //returns the largest of the left and right subtree, +1 is added to allow for the offset of base case returning -1 (in the instance the node is not found)
}

void BSTree::inOrderRecursive(Node* node) const
{
   if (node == nullptr) //base case
   {
      return;
   }
   //recursively traverses list in order of key
   inOrderRecursive(node -> getLeft());
   cout << node -> getKey() << "(" << node -> getCount() << "), ";
   inOrderRecursive(node -> getRight());
}

void BSTree::preOrderRecursive(Node* node) const
{
   if (node == nullptr) //base case
   {
      return;
   }
   //recursively traverses list in order of all leftmost nodes first
   cout << node -> getKey() << "(" << node -> getCount() << "), ";
   preOrderRecursive(node -> getLeft());
   preOrderRecursive(node -> getRight());
}

void BSTree::postOrderRecursive(Node* node) const
{
   if (node == nullptr) //base case 
   {
      return;
   }
   //recursively traverses list in order of height with all leftmost nodes first
   postOrderRecursive(node -> getLeft());
   postOrderRecursive(node -> getRight());
   cout << node -> getKey() << "(" << node -> getCount() << "), ";
}

void BSTree::insert(const string& key) 
{
   Node* node = new Node(key); //creates new node from string
   if (root == nullptr) //if the tree is empty then its root is the new node
   {
      root = node;
   }
   else
   {
      insertRecursive(root, node); //calls recursive insert private helper function
   }
}

void BSTree::remove(const string& key) 
{
   Node* nodeToFind = nodeSearch(key); //finds the node with the string parameter
   if (nodeToFind == nullptr) //if it doesnt exist then the function ends
   {
      return;
   }
   if (nodeToFind -> getCount() > 1) //if the node to remove has a count greater than one then the count is decremented
   {
      nodeToFind -> decrementCount();
      return;
   }
   Node* parent = getParent(nodeToFind); //parent is found for the recursive remove function
   removeRecursive(parent, nodeToFind); //recursive remove node helper function called
}

bool BSTree::search(const string& key) const
{
   return (nodeSearch(key) != nullptr); //returns true if private helper nodeSearch function yields an actual node
}

string BSTree::largest() const
{
   if (root == nullptr) //returns empty string if tree is empty
   {
      return {};
   }
   Node* node = root;
   while (node -> getRight() != nullptr) //traverses through all right children 
   {
      node = node -> getRight();
   }
   return node -> getKey(); //returns the key of the rightmost child
}

string BSTree::smallest() const
{
   if (root == nullptr) //returns empty string if tree is empty
   {
      return {};
   }
   Node* node = root;
   while (node -> getLeft() != nullptr) //traverses through all left children
   {
      node = node -> getLeft();
   }
   return node -> getKey(); //returns the leftmost child
}

int BSTree::height(const string& key) const //calls recursive height function
{
   Node* node = nodeSearch(key); //finds the node with string parameter, passes into recurisve height function
   return heightRecursive(node);
}

void BSTree::inOrder() const
{
   inOrderRecursive(root); //calls recursive inorder function
}

void BSTree::preOrder() const
{
   preOrderRecursive(root); //calls recursive preorder function
}

void BSTree::postOrder() const
{
   postOrderRecursive(root); //calls recursive postOrderfunction
}