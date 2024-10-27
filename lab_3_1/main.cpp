#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) 
{
   if (vals.size() - 1 == index) //returns the index of the last item in the array if the index parameter is the last item
   {
      return index;
   }
   unsigned int min = index; //sets variable minimum to index
   for (unsigned int i = index + 1; i < vals.size();++i) //sets the variable minimum to the index of the smallest element if parameter index itself is not the smallest
   {
      if (vals.at(i) < vals.at(min))
      {
         min = i;
      }
   }
   return min;
}

template<typename T>
void selection_sort(vector<T> &vals)
{
   if (vals.size() == 0) //stops function is vector is empty
   {
      return;
   }
   for (unsigned int i = 0;i < vals.size() - 1;++i) //goes through all but the last element in vector; doesnt need to go to last element because it will be in the correct spot
   {
      if (vals.at(i) > vals.at(min_index(vals, i+1))) // swaps current element with a smaller element in the remaining portion of the vector if it exists
      {
         swap(vals.at(i), vals.at(min_index(vals, i+1)));
      }
   }
}

template<typename T>
T getElement(vector<T> vals, int index)
{
   return vals.at(index);
}

vector<char> createVector()
{
   int vecSize = rand() % 26;
   char c = 'a';
   vector<char> vals;
   for(int i = 0; i < vecSize; i++)
   {
      vals.push_back(c);
      c++;
   }
   return vals;
}

int main()
{
   { //test selection sort algorithm; creates vector with items in reverse order and prints them before and after selection sort
      vector<int> test;
      for (unsigned int i = 9;i > 0; --i)
      {
         test.push_back(i);
      }
      
      for (unsigned int i = 0;i < test.size();++i)
      {
         cout << test.at(i) << " ";
      }
      cout << endl;
      selection_sort(test);
      for (unsigned int i = 0;i < test.size();++i)
      {
         cout << test.at(i) << " ";
      }
      cout << endl;
   }
   srand(time(0));
   vector<char> vals = createVector();
   char curChar;
   int index;
   int numOfRuns = 10;
   while(--numOfRuns >= 0)
   {
      try
      {
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
      }
      catch (const std::out_of_range& excpt) //throw out of range exception
      {
         cout << excpt.what() << endl;
         cout << "out of range exception occured" << endl;
      }
   }
   return 0;
}