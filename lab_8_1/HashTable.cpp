#include "HashTable.h"
#include "WordEntry.h"

HashTable::HashTable (int s) //initialize list size and size variable to parameter
{
	hashTable = new list<WordEntry>[s];
    size = s;
}

int HashTable::computeHash(const string &s) //compute hash value of string,
{
    return s.size() % size;
}

void HashTable::put(const string &s, int score) 
{
    int hashVal = computeHash(s); //find hash value where string would be
    list<WordEntry>::iterator it;
    if (contains(s)) //if the string is already in the table, num of appearances and total score are updated
    {
        for(it = hashTable[hashVal].begin(); it != hashTable[hashVal].end(); ++it) //iterates through table to find value to modify
        {
            if(it -> getWord() == s)    
            {
                it -> addNewAppearance(score);
            }
        }
    }
    else //if the word doesnt exist it is added into table
    {
        WordEntry word = WordEntry(s,score);
 		hashTable[hashVal].push_back(word);
    }
}

double HashTable::getAverage(const string &s) 
{
    int hashVal = computeHash(s); //find hash value where string would be
    list<WordEntry>::iterator it;
    if (contains(s))
    {
        for(it = hashTable[hashVal].begin(); it != hashTable[hashVal].end(); ++it) //iterate through list to find the hash table val that matches parameter, then returns that string's average
        {
            if(it -> getWord() == s)    
            {
                return it -> getAverage();
            }
        }
    }
    return 2; //neutral review if word not found
}

bool HashTable::contains(const string& s) 
{
    int hashVal = computeHash(s); //find hash value where string would be
    list<WordEntry>::iterator it;
    for(it = hashTable[hashVal].begin(); it != hashTable[hashVal].end(); ++it) //iterates through hash table, if word is found, return true
    {
        if(it -> getWord() == s)    
        {
            return true;
        }
    }
    return false;
}

#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int main() 
{
	string line;    
	int score;
	string message = " ";
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) 
    {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	HashTable table(20071);
	while (!myfile.eof()) 
    {
	    myfile >> score;
	    myfile.get();
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) 
        {
	        string sub;
	        len = line.find(" ");
	        if (len > 0) 
            {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else 
            {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score);
	    }
	}
	while(message.length() > 0) 
    {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	    double sum = 0;
	    int count = 0;
	    double sentiment = 0.0;
	    size_t len = message.size();
	    while(len != string::npos) 
        {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        sum += table.getAverage(sub);
	        ++count;
	    }
	    if (message.size() > 0) 
        {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) 
            {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) 
            {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) 
            {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else 
            {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	return 0;
}
