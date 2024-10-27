#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H
#include <iostream>
#include <cstdlib>

using namespace std;
struct TreeNode
{
    char data;
    char key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char data, char key): //data represents char value(operator or operand), key is for data visualization
        data(data),
        key(key),
        left(0),
        right(0)
    {
    }
};

class arithmeticExpression
{
    private:
        string infixExpression;
        TreeNode* root;
    public:
        arithmeticExpression(const string & infixExpression): //default constructor
            infixExpression(infixExpression),
            root(nullptr)
        {
        }
        ~arithmeticExpression() //destructor calls private helper function
        {
            destructorRecursive(root);
        }
        /* Converts the infixExpression to its equivalent postfix string
        and then generates the tree and assigns the root node to the 
        root data field. The key for the first node is 'a', 'b' for the second node and so on. */
        void buildTree();
        /* Calls the recursive infix function. */
        void infix();
        /* Calls the recursive prefix function. */
        void prefix();
        /* Calls the recursive postfix function. */
        void postfix();
    private:
        /* Helper function that returns an integer according to
        the priority of the given operator. */
        int priority(char);
        /* Helper function that returns the postfix notation equivalent
        to the given infix expression */
        string infix_to_postfix();
        /* Helper function that outputs the infix notation of the arithmetic expression tree
        by performing the inorder traversal of the tree.
        An opening and closing parenthesis must be added at the 
        beginning and ending of each expression. */
        void infixRecursive(TreeNode *);
        /* Helper function that outputs the prefix notation of the arithmetic expression tree
        by performing the preorder traversal of the tree. */
        void prefixRecursive(TreeNode *);
        /* Helper function that outputs the postfix notation of the arithmetic expression tree
        by performing the postorder traversal of the tree. */
        void postfixRecursive(TreeNode *);
        /* Helper function for generating the dotty file. This is a recursive function. */
        //void visualizeTree(ofstream &, TreeNode *);
        void destructorRecursive(TreeNode* );
};
#endif