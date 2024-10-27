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
	if (myfile.fail()) //file fails to open
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
	        table.put(sub, score); //input strings into table
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
	        if (len != string::npos) 
			{
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else 
			{
	            sub = message;
	        }
	        sum += table.getAverage(sub); //compute total averages of each word
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