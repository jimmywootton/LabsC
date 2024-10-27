#include "Playlist.h"

void PlaylistNode::InsertAfter(PlaylistNode* node)
{  
    PlaylistNode* tempNextNode = this -> nextNodePtr; //remember next node with node "tempNextNode"
    this -> nextNodePtr = node; //link this node's next with parameter
    node -> nextNodePtr = tempNextNode; //link parameter's next with "tempNextNode"
}

void PlaylistNode::SetNext(PlaylistNode* node)
{
    this -> nextNodePtr = node; //set this node's next with parameter
}

const string& PlaylistNode::GetID() const 
{
    return uniqueID; 
}

const string& PlaylistNode::GetSongName() const
{
    return songName;
}

const string& PlaylistNode::GetArtistName() const
{
    return artistName;
}

int PlaylistNode::GetSongLength() const
{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const
{
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const
{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: "  << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::~Playlist() 
{ //works by setting head to head's next and then deleting the old head
    while (head != nullptr)
    {
        PlaylistNode* nodeToDelete = head; //sets head to "nodeToDelete"
        head = head -> GetNext(); //sets head to next
        delete nodeToDelete; //deletes old head
    }
    delete head; //deletes head at very end
}

void Playlist::AddNode(string nodeToAddId, string nodeToAddSongName, string nodeToAddArtistName, int nodeToAddLength)
{
    PlaylistNode* node = new PlaylistNode(nodeToAddId, nodeToAddSongName, nodeToAddArtistName, nodeToAddLength); //creates new node with inputed information
    if (head == nullptr) //if linked list is empty, the parameter becomes the only item in the list and the head and tail both point to it
    {
        head = node;
        tail = node;
    }
    else 
    {
        tail -> InsertAfter(node); //parameter inserted after tail
        tail = tail -> GetNext(); //parameter becomes tail
    }
}

void Playlist::RemoveNode(string nodeToRemoveId) 
{
    if (head == nullptr) //stops function if linked list is empty
    {
        return;
    }
    PlaylistNode* current = head;
    PlaylistNode* previous = nullptr;
    while (current!= nullptr && current -> GetID() != nodeToRemoveId) //identifies the node with the same ID as the parameter and sets it to currentand the node before it to prev
    {
        previous = current; 
        current = current -> GetNext();
    }
    if (current == nullptr) //stops function if node not found
    {
        return;
    }
    if (current == head && current == tail) //node to remove is the only item in list
    {
        head = nullptr; 
        tail = nullptr;
    } 
    else if (current == head) //node to remove is the head
    {
        head = head -> GetNext(); //sets head to current's next
    } 
    else if (current == tail) //node to remove is the tail
    {
        tail = previous; //tail is set to tail's previous item
        tail -> SetNext(nullptr); //new tail's next becomes null
    } 
    else //item to remove is found in middle of linked list
    {
        previous -> SetNext(current -> GetNext()); //links current's previous node to current's next node, thus removing current from linked list
    }
    cout << "\"" << current -> GetSongName() << "\" removed." << endl << endl; 
    delete current; //deallocates memory of current, if current was head or tail the memory of old head and tail is also deallocated since they would also be the same as current
}

void Playlist::ChangeNode(int oldPos, int newPos)
{
    if (oldPos == newPos) //ends function if old and new position are identical;ei no movement
    {
        return;
    }
    int numNodes = 0; //number of nodes counter
    int currCount = 1; //position counter
    PlaylistNode* current = head; //node counter
    PlaylistNode* previous = nullptr; //previous node counter
    PlaylistNode* oldNode = nullptr; //node to move
    PlaylistNode* oldPrevNode = nullptr; //node to move's previous
    PlaylistNode* newNode = nullptr; //node in new position
    PlaylistNode* newPrevNode = nullptr; //node in new position's previous
    if (newPos < 1) //if new position is less than 1 then new position equals one (head)
    {
        newPos = 1;
    }
    while (current != nullptr) //finds the node at old position and number of nodes in list
    {
        if (oldPos == currCount) 
        {
            oldNode = current;
            oldPrevNode = previous;
        }
        previous = current;
        current = current -> GetNext();
        currCount++; 
        numNodes++; //counts number of nodes
    }
    if (oldPos > numNodes || oldPos < 1) //ends function is oldPos is out of bounds
    {
        return;
    }
    { //deleting old node
        if (oldNode == head) //if old node is at the head
        {
            head = head -> GetNext();
        }
        else if (oldNode == tail) //if old node is at the tail
        {
            tail = oldPrevNode;
            tail -> SetNext(nullptr);
        }
        else //if old node is in the middle
        {
            oldPrevNode -> SetNext(oldNode -> GetNext());
        }
    }
    --numNodes; //subtract number of nodes since a node was removed
    currCount = 1; //reset for new loop
    current = head; //reset for new loop
    previous = nullptr; //reset for new loop
    while (current != nullptr) //finds node at new position, new loop needed since a node was removed and positions changed
    {
        if (newPos == currCount) 
        {
            newNode = current;
            newPrevNode = previous;
        }
        previous = current;
        current = current -> GetNext();
        currCount++;
    }
    { //inserting old node before new node
        if (newNode == head) // inserts old node at head if new node is head
        {
            oldNode -> SetNext(newNode);
            head = oldNode;
        }
        else if (newPos > numNodes) //inserts old node at tail if new node position is larger than the number of nodes
        {
            tail -> InsertAfter(oldNode);
            tail = tail -> GetNext();
        }
        else //inserts old node before new node somewhere in the middle of list
        {
            newPrevNode -> InsertAfter(oldNode);
        }
    }
    cout << "\"" << oldNode -> GetSongName() << "\" moved to position " << newPos << endl << endl; 
}

void Playlist::PrintArtistList(string artist) const
{
    PlaylistNode* current = head;
    int count = 1;
    while (current != nullptr)
    {
        if (current -> GetArtistName() == artist)
        {
            cout << count << "." << endl; //prints song's number
            current -> PrintPlaylistNode(); //prints song's info
            cout << endl;
        }
        current = current -> GetNext(); //goes to next item in linked list
        ++count; //updates song number
    }
}

int Playlist::TotalTime() const
{
    PlaylistNode* current = head;
    int total = 0;
    while (current != nullptr) 
    {
        total += current -> GetSongLength();
        current = current -> GetNext();
    }
    return total;
}


void Playlist::OutputPlaylist() const
{
    PlaylistNode* current = head;
    int count = 1; 
    while(current != nullptr) //traverses list
    {
        cout << count << "." << endl; //prints song's number
        current -> PrintPlaylistNode(); //prints song's info
        cout << endl;
        current = current -> GetNext(); //goes to next item in linked list
        ++count; //updates song number
    }
    if (count == 1) //if song number never updates then there is no songs in list; print out empty playlist
    {
        cout << "Playlist is empty" << endl << endl;
    }
}
