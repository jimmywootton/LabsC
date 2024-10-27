#include "BSTree.h"
#include <iostream>
#include <limits>
using namespace std;

void printOrders(BSTree *tree) //print tree in all orders
{
	cout << "Preorder = ";
	tree->preOrder();
	cout << endl;
	cout << "Inorder = ";
	tree->inOrder();
	cout << endl;
	cout << "Postorder = ";
	tree->postOrder();
	cout << endl;
}

int menu() 
{
	int choice = 0;
	cout << endl;
	cout << "Enter menu choice: " << endl;
	cout
	<< "1. Insert" << endl
	<< "2. Remove" << endl
	<< "3. Print" << endl
	<< "4. Search" << endl
	<< "5. Smallest" << endl
	<< "6. Largest" << endl
	<< "7. Height" << endl
	<< "8. Quit" << endl;
	cin >> choice;
	cin.clear(); //remove cin stream if choice has spaces
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return choice;
}

int main() 
{
	BSTree tree;
	int choice = menu(); //get choice from menu prompt
	string entry;
	while (choice != 8) //terminate when quit is entered
	{
		if (choice == 1) 
		{
			cout << "Enter string to insert: ";
			getline(cin,entry);
			cout << endl;
			tree.insert(entry);
		} 
		else if (choice == 2) 
		{
			cout << "Enter string to remove: ";
			getline(cin,entry);
			cout << endl;
			tree.remove(entry);
		} 
		else if (choice == 3) //prints from printOrder function in main
		{
			printOrders(&tree);
		} 
		else if (choice == 4) 
		{
			cout << "Enter string to search for: ";
			getline(cin,entry);
			cout << endl;
			if (tree.search(entry))
			{
				cout << "Found" << endl;
			}
			else
			{
				cout << "Not Found" << endl;
			}
		} 
		else if (choice == 5) 
		{
			cout << "Smallest: ";
			cout << tree.smallest() << endl;
		} 
		else if (choice == 6) 
		{
			cout << "Largest: ";
			cout << tree.largest() << endl;;
		} 
		else if (choice == 7) 
		{
			cout << "Enter string: ";
			getline(cin,entry);
			cout << endl;
			cout << "Height of subtree rooted at " << entry << ": ";
			cout << tree.height(entry) << endl;
		}
		choice = menu();
	}
	return 0;
}

