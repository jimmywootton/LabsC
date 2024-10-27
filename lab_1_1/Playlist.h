#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class PlaylistNode //node class
{
    public:
        PlaylistNode(): //inline function default constructor
            uniqueID("none"),
            songName("none"),
            artistName("none"),
            songLength(0),
            nextNodePtr(nullptr)
        {
        }
        PlaylistNode(string id, string sName, string aName, int length): //inline function default constructor with paramaters
            uniqueID(id),
            songName(sName),
            artistName(aName),
            songLength(length)
        {
        }
        void InsertAfter(PlaylistNode* node);
        void SetNext(PlaylistNode* node);
        const string& GetID() const;
        const string& GetSongName() const;
        const string& GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;
        void PrintPlaylistNode() const;
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
};


class Playlist //playlist linked list class
{
    public:
        Playlist(): //inline default constructor
            head(nullptr),
            tail(nullptr)
        {
        }
        ~Playlist(); //destructor
        void AddNode(string nodeToAddId, string nodeToAddSongName, string nodeToAddArtistName, int nodeToAddLength);
        void RemoveNode(string x);
        void ChangeNode(int oldPos, int newPos);
        void PrintArtistList(string artist) const;
        int TotalTime() const;
        void OutputPlaylist() const;
    private:
        PlaylistNode* head;
        PlaylistNode* tail;
};

#endif