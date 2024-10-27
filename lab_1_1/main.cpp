#include <iostream>
#include <string>
#include <vector>


using namespace std;

#include "Playlist.h"

void OutputTotalTime(Playlist& p)
{
    cout << "Total time: "<< p.TotalTime() << " seconds" << endl << endl;
}

void OutputArtist(Playlist& p)
{
    string artist;
    cout << "Enter artist's name:" << endl << endl;
    getline(cin, artist);
    //get user input above; take user input and call member function with user information as parameters
    p.PrintArtistList(artist);
}

void ChangePos(Playlist& p)
{
    int currPos;
    int newPos;
    cout << "Enter song's current position:" << endl;
    cin >> currPos;
    cin.ignore();
    cout << "Enter new position for song:" << endl;
    cin >> newPos;
    cin.ignore();
    //get user input above; take user input and call member function with user information as parameters
    p.ChangeNode(currPos, newPos);
}

void RemoveSong(Playlist &p)
{
    string songToRemoveId;
    cout << "Enter song's unique ID:" << endl;
    cin >> songToRemoveId;
    cin.ignore();
    //get user input above; take user input and call member function with user information as parameters
    p.RemoveNode(songToRemoveId);
}

void AddSong(Playlist& p)
{
    string songToAddId;
    string songToAddSongName;
    string songToAddArtistName;
    int songToAddLength;
    cout << "Enter song's unique ID:" << endl;
    cin >> songToAddId;
    cin.ignore();
    cout << "Enter song's name:" << endl;
    getline(cin, songToAddSongName);
    cout << "Enter artist's name:" << endl;
    getline(cin , songToAddArtistName);
    cout << "Enter song's length (in seconds):" << endl << endl;
    cin >> songToAddLength;
    cin.ignore();
    //get user input above; take user input and call member function with user information as parameters
    p.AddNode(songToAddId, songToAddSongName, songToAddArtistName, songToAddLength); //add new node to end of linked list
}

void PrintMenu(string title, Playlist& p)
{
    char choice;
    while (choice != 'q') //continuously prints out menu until 'q' is entered
    {
        cout << title << " PLAYLIST MENU" << endl; //prints menu
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl << endl;
        cout << "Choose an option:" << endl;
        cin >> choice;
        cin.ignore();
        while (choice != 'a' && choice != 'd' &&  choice != 'c' &&  choice != 's' && choice != 't' && choice != 'o' && choice != 'q') //asks again for new option if invalid choice
        {
            cout << "Choose an option:"  << endl;
            cin >> choice;
        }
        if (choice == 'o') 
        {
            cout << title << " - OUTPUT FULL PLAYLIST" << endl;
            p.OutputPlaylist();
        }
        //all functions below work in the same way
        //they are responsible for getting user information and then
        //calling a member function in the playlist class with the user information as parameters
        if (choice == 'a')
        {
            cout << "ADD SONG" << endl;
            AddSong(p);
        }
        if (choice == 'd')
        {
            cout << "REMOVE SONG" << endl;
            RemoveSong(p);
        }
        if (choice == 'c')
        {
            cout << "CHANGE POSITION OF SONG" << endl;
            ChangePos(p);
        }
        if (choice == 's')
        {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            OutputArtist(p); 
        }
        if (choice == 't')
        {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            OutputTotalTime(p);
        }
    }
}

int main()
{
    Playlist p;
    string title;
    cout << "Enter playlist's title:" << endl;
    getline(cin , title);
    cout << endl;
    PrintMenu(title, p);
    return 0;
}