#include "WordEntry.h"

WordEntry::WordEntry(const string &text, int score): 
    word(text), 
    numAppearances(1), 
    totalScore(score) 
{	 
}

void WordEntry::addNewAppearance(int s) //when this function is called that means the number of appeaances of the word increments, also the score is updated to parameter
{
	totalScore += s;
	++numAppearances;
}

const string & WordEntry::getWord() //return word
{
    return word;
}

double WordEntry::getAverage() //get average
{
    return static_cast<double>(totalScore) / numAppearances; 
}