#include "Jug.h"

struct CompareVertices //operator overload for priority to maintain min-heap properties of user defined class objects
{
    bool operator()(const vertex& a, const vertex& b) 
    {
        return a.distance > b.distance;
    }
};

int Jug::findInGraph(int A, int B, vector<int>& unfinishedVertices) 
{
    for(unsigned int i=0; i < graph.size(); ++i) //returns index of vertex with A and B if found
    {
        if (graph[i].A == A && graph[i].B == B) 
        {
            return i;
        }
    }
    //if not found in graph, it is added to graph and unfinished vertex
    int id = graph.size();
    unfinishedVertices.push_back(id); 
    graph.push_back( vertex(A, B) );
    return id;
}

int Jug::findVertex(int A, int B) //same as findInGraph function without unfinishedVertices parameter
{
    for(unsigned int i=0; i < graph.size(); ++i) 
    {
        if (graph[i].A == A && graph[i].B == B) 
        {
            return i;
        }
    }
    return -1;
}

void Jug::buildGraph()
{
    vector<int> unfinishedNodes;
    findInGraph(0, 0, unfinishedNodes); //adds base node
    while(unfinishedNodes.size() > 0) 
    {
        int id = unfinishedNodes.back(); //takes vertex from unfinished node vector
        unfinishedNodes.pop_back(); 
        int A = graph[id].A;
        int B = graph[id].B;
        //add vertices to graph
        int fillA = findInGraph(cA, B, unfinishedNodes);
        int fillB = findInGraph(A, cB, unfinishedNodes);
        int emptyA = findInGraph(0, B, unfinishedNodes);
        int emptyB = findInGraph(A, 0, unfinishedNodes);
        int roomInB = cB - B;
        int poursize = min(A, roomInB);
        int pourAToB = findInGraph(A-poursize, B+poursize, unfinishedNodes);
        int roomInA = cA - A;
        poursize = min(B, roomInA);
        int pourBToA = findInGraph(A+poursize, B-poursize, unfinishedNodes);
        //set edges and cost
        graph[id].newStateAfterAction.push_back(make_pair(fillA, cfA));
        graph[id].newStateAfterAction.push_back(make_pair(fillB, cfB));
        graph[id].newStateAfterAction.push_back(make_pair(emptyA, ceA));
        graph[id].newStateAfterAction.push_back(make_pair(emptyB, ceB));
        graph[id].newStateAfterAction.push_back(make_pair(pourAToB, cpAB));
        graph[id].newStateAfterAction.push_back(make_pair(pourBToA, cpBA));   
    }
}

void Jug::djikstra()
{
    graph.at(0).distance = 0; //origin distance from itself is 0
    priority_queue <vertex, vector<vertex>, CompareVertices> pq; //priority queue
    pq.push(graph.at(0));
    while (!pq.empty())
    {
        int vertexIndex = findVertex(pq.top().A, pq.top().B); //takes item from queue with smallest distance
        pq.pop();  
        for (unsigned int i = 0;i < graph.at(vertexIndex).newStateAfterAction.size();++i) //sets edge prev and distance variables and then adds them to the queue
        {
            int edgeIndex = graph.at(vertexIndex).newStateAfterAction.at(i).first;
            int edgeWeight = graph.at(vertexIndex).newStateAfterAction.at(i).second;
            int alternativeDistance = graph.at(vertexIndex).distance + edgeWeight;
            if (alternativeDistance < graph.at(edgeIndex).distance) 
            {
                graph.at(edgeIndex).distance = alternativeDistance;
                graph.at(edgeIndex).prev = vertexIndex;
                pq.push(graph.at(edgeIndex));
            }
        }
    }
}

int Jug::solve(string &solution)
{
    solution = "";
    if (N <= 0 || cA <= 0 || cB <= 0 || cA > cB || N > cB || cB > 1000) //return -1 when parameters violate graph properties
    {
        return -1;
    }
    buildGraph(); //builds graph
    djikstra(); //sets path distance from origin for all vertices
    if ((findVertex(0,N) == -1)) //if N is invalid or impossible then 0 is returned
    {
        return 0;
    }
    int cost = 0;
    vector <string> steps;
    vector <string> actions = {"fill A", "fill B", "empty A", "empty B", "pour A B", "pour B A"};
    steps.push_back("success ");
    int edgeIndex = findVertex(0,N); 
    int vertexIndex = graph.at(edgeIndex).prev;
    while (edgeIndex != 0) //starts at destination vertex traces through prev variable to get to starting vertex
    {
        for (unsigned int i = 0;i < graph.at(vertexIndex).newStateAfterAction.size();++i)
        {
            if (graph.at(vertexIndex).newStateAfterAction.at(i).first == edgeIndex)
            {
                steps.push_back(actions.at(i)); //adds string of action that led to the previous vertex to a vector of strings
                cost += graph.at(vertexIndex).newStateAfterAction.at(i).second; //tallys the total cost of the path
            }
        }
        edgeIndex = graph.at(edgeIndex).prev;
        vertexIndex = graph.at(vertexIndex).prev;
    }
    steps.at(0) += to_string(cost); //adds the cost to the string of steps
    reverse(steps.begin(), steps.end()); //right now the vector of steps is in reverse order, so this makes it in the right order
    for (unsigned int i = 0;i < steps.size() - 1;++i) //this adds the vector of string instructionst to the string parameter
    {
        solution += steps.at(i);
        solution += "\n";
    }
    solution += steps.back();
    return 1;
}
