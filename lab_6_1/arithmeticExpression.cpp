#include "arithmeticExpression.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

void arithmeticExpression::buildTree()
{
    string postFixExpression = infix_to_postfix(); //converts infix expression to post fix
	stack <TreeNode*> s;
	for (unsigned int i = 0; i < postFixExpression.size(); ++i) //traveses post fix string
    {
		TreeNode *newNode = new TreeNode(postFixExpression.at(i), 'a' + i);
		if (priority(postFixExpression.at(i)) == 0) //if char is operand then pushed to stack
        {
			s.push(newNode);
		}
		else if (priority(postFixExpression.at(i)) > 0) //if char is operator then the first two items on top of stack are added as nodes to the operator; both items are replaced with the tree in the stack
        {
			newNode -> right = s.top();
			s.pop();
			newNode -> left = s.top();
			s.pop();
			s.push(newNode);
			root = newNode;
		}
	}
}

void arithmeticExpression::infix() //call recursive infix function
{
    infixRecursive(root);
}

void arithmeticExpression::infixRecursive(TreeNode* node)
{
    if (node -> left == 0 && node -> right == 0) //base case for if node is operand
    {
		cout << node->data;
        return;
	}
    //recursively adds parentheses around all the printed subtrees of the node
    cout << "(";
    infixRecursive(node->left);
    cout << node->data;
    infixRecursive(node->right);
    cout << ")";
}


void arithmeticExpression::prefix() //calls recursive prefix function
{
    prefixRecursive(root);
}

void arithmeticExpression::prefixRecursive(TreeNode* node)
{
    if (node == 0) //base case
    {
		return;
	}
	cout << node -> data; //prints node data and then recursively prints all the data in preOrder fashion
	prefixRecursive(node -> left);
	prefixRecursive(node -> right);
}


void arithmeticExpression::postfix() //calls postfix recursive function
{
    postfixRecursive(root);
}

void arithmeticExpression::postfixRecursive(TreeNode* node)
{
    if (node == 0) // base case when you reach the end of the tree
    {
		return;
	}
	postfixRecursive(node->left); //recursively prints tree in postOrder fashion
	postfixRecursive(node->right);
	cout << node->data;
}

int arithmeticExpression::priority(char op)
{
    int priority = 0; //if char is operand, priority is zero
    if(op == '(') //priority is set for chars based on PEMDAS order of operation rules
    {
        priority =  3;
    }
    else if(op == '*' || op == '/')
    {
        priority = 2;
    }
    else if(op == '+' || op == '-')
    {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix()
{
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i)
    {
        c = infixExpression.at(i);
        if(c == ' ') //ignores white space
        {
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
        { //c is an operator
            if( c == '(')
            {
                s.push(c);
            }
            else if (c == ')') //removes parentheses from the ostream
            {
                while (s.top() != '(')
                {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else //arranged correct order for everything out of parentheses
            {
                while (!s.empty() && priority(c) <= priority(s.top()))
                {
                    if(s.top() == '(')
                    {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else
        { //c is an operand
            oss << c;
        }
    }
    while(!s.empty()) //adds everything from stack onto ostream
    {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::destructorRecursive(TreeNode* node) //recursively removes all nodes in tree from leaves to root
{
    if (node != nullptr) 
    {
        destructorRecursive(node -> left);
        destructorRecursive(node -> right);
        delete node;
    }
}

