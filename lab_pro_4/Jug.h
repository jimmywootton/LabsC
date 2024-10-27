#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <queue>
using namespace std;

struct vertex //vertex class
{
    int A; //jug A amount
    int B;	//jug B amount
    int distance; //cost distance from origin
    int prev; //index of vertex with shortest distance to this vertex
    vector<pair<int, int>> newStateAfterAction; //vector of edges, first is index of edge, second is cost

    vertex(int A, int B): //default constructor
        A(A), 
        B(B), 
        distance(numeric_limits<int>::max()),
        prev(-1)
    {
    }
};

class Jug 
{
    private:
        int cA; 
        int cB; 
        int N; 
        int cfA; 
        int cfB; 
        int ceA; 
        int ceB; 
        int cpAB; 
        int cpBA;
        vector<vertex> graph; //graph
        int findInGraph(int A, int B, vector<int>& unfinishedVertices); //find index of vertex with jug A and jug B, if not found it is added to unfinished vertices vector
        void buildGraph(); //adds to graph vector
        void djikstra(); //set distance and prev to find shortest path
        int findVertex(int A, int B); //returns index of vertex with jug A and jug B
    public:
        Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA): //set parameters
            cA(cA), 
            cB(cB),
            N(N),
            cfA(cfA),
            cfB(cfB),
            ceA(ceA),
            ceB(ceB),
            cpAB(cpAB),
            cpBA(cpBA)
        {
        }
        int solve(string&);
};

#endif