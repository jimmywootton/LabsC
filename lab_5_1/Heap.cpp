#include <algorithm> 
#include <iostream> 
using namespace std;
#include "Heap.h"

void Heap::enqueue (PrintJob* printJob)
{
	if (numItems < MAX_HEAP_SIZE) 
	{
		arr[numItems] = printJob;
		trickleUp(numItems);
		numItems++;
	}
}

void Heap::dequeue ()
{
	if(numItems == 1) 
	{
		--numItems;
	}
	else if (numItems > 1)
	{
		arr[0] = arr[numItems-1];
		numItems--;
		trickleDown(0);
	}
}

PrintJob* Heap::highest ()
{
	if (numItems > 0)
	{
		return arr[0];
	}
	return nullptr;
}
/*
void Heap::printAll()
{
	for (int i= 0; i < numItems; ++i)
	{
		cout << "Priority: " << arr[i]->getPriority() << ", Job Number: " << arr[i]->getJobNumber() << ", Number of Pages: " << arr[i]->getPages() << endl;
	}
}
*/
void Heap::print ()
{
	if (numItems > 0)
	{
		cout << "Priority: " << highest()->getPriority() << ", Job Number: " << highest()->getJobNumber() << ", Number of Pages: " << highest()->getPages() << endl;
	}
}


void Heap::trickleDown(int index)
{
	for (int i = 0; i < numItems; i++) 
	{
		if(arr[index] -> getPriority() < arr[i] -> getPriority())
        {
            swap(arr[index], arr[i]);
        }
	}	
}

void Heap::trickleUp(int index) 
{
	while (index > 0) 
	{
		int parent = (index - 1) / 2;
		if (arr[index] -> getPriority() <= arr[parent] -> getPriority())
		{
			return;
		}
		else 
		{
			swap (arr[index], arr[parent]);
			index = parent;
		}
	}
}

void enqueue(int parameter)
{
	if (length >= MAX_SIZE)
	{
		throw runtime_error("uh oh");
	}
	arr[(front + length)%MAX_SIZE] = parameter;
	++size;
}