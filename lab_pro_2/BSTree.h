#ifndef __BSTREE_H__
#define __BSTREE_H__
#include "Node.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class BSTree
{
   private:
      Node *root;
   public:
      BSTree(): //initialized binary search tree to root nullptr
         root(nullptr)
      {
      }
      ~BSTree() //destructor; calls private recursive helper function 
      {
         destructorRecursive(root);
      }
      void insert(const string& key);
      void remove(const string& key);
      bool search(const string& key) const;
      string largest() const;
      string smallest() const;
      int height(const string&) const;
      void inOrder() const;
      void preOrder() const;
      void postOrder() const;
   private:
      Node* getParent(Node* node);
      Node* getParentRecursive(Node* parent, Node* node);
      void destructorRecursive(Node* node);
      Node* nodeSearch(string key) const;
      Node* nodeSearchRecursive(Node* node, string key) const;
      void insertRecursive(Node* parent, Node* node);
      void removeRecursive(Node*& parent, Node*& node);
      int heightRecursive(Node* node) const;
      void inOrderRecursive(Node* node) const;
      void preOrderRecursive(Node* node) const;
      void postOrderRecursive(Node* node) const; 
};

#endif