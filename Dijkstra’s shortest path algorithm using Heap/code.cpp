

#include <iostream>
#include <list>
#include <queue>




//Pair is used to combine together two values that may be of different data types.Pair provides a way to store
//two heterogeneous objects as a single unit.It is basically used if we want to store tuples.The pair container
//is a simple container defined in <utility> header consisting of two data elements or objects.
// iPair ==> Integer Pair
using ipair = std::pair<int, int>;



// This class represents a directed graph using
// adjacency list representation
class Graph {
    int V; // No. of vertices

    //std::list is a container that supports constant time insertionand removal of elements from anywhere in the container.
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    std::list< std::pair<int, int> >* adj;

public:
    Graph(int V); // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int w);

    // prints shortest path from s
    void shortestPath(int s);


    void printSolution(std::vector<int> dist, std::vector<int> parent, int V, int src);

    void printPath(int currentNode, std::vector<int> parent, int src);

    int minimumDistance(int src, int tgt);

    void auxPath(int currentNode, std::vector<int> parent, int src, std::vector<int>* path);

    std::vector<int> minimumPath(int src, int tgt);

};


// Allocates memory for adjacency list
Graph::Graph(int V) {
    // About this: We can see that every time we access an attribute or 
    // call a method inside the class we precede it with the this pointer.
    // This pointer stores the memory address where the attributes of the
    // respective object are stored.
    this->V = V;
    adj = new std::list<ipair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
    // Constructs a pair object with its first element set to xand its second element set to y.
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w));
}

// A utility function to print the constructed path array.
void Graph::printPath(int currentNode, std::vector<int> parent, int src) {

    if (currentNode == src) {
        std::cout << src << ' ';
        return;
    }

    printPath(parent[currentNode], parent, src);
    std::cout << currentNode << ' ';
}


// A utility function to print the constructed distance array.
void Graph::printSolution(std::vector<int> dist, std::vector<int> parent, int V, int src) {

    std::cout << "Node \t\t Distance from Source \t\tPath" << '\n';

    for (int i{ 0 }; i < V; i++) {
        std::cout << i << "\t\t\t" << dist[i] << "\t\t\t";
        printPath(i, parent, src);
        std::cout << '\n';
    }

}




// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
    // Create a priority queue to store vertices that
    // are being preprocessed.
    // 
    //// Priority queues are a type of container adapters, specifically designed such that the first
    //// element of the queue is either the greatest or the smallest of all elements in the queue
    //// and elements are in nonincreasing order(hence we can see that each element of the queue has
    //// a priority{ fixed order }).However in C++ STL, by default, the top element is always the
    //// greatest element.We can also change it to the smallest element at the top.Priority queues
    //// are built on the top to the max heapand uses array or vector as an internal structure.

    //// Binary function object class whose call returns whether the its first argument compares greater
    //// than the second(as returned by operator >)
    std::priority_queue< ipair, std::vector<ipair>, std::greater<ipair> > pq;

    // Create a vector for distances and initialize all
    // distances as infinite (INT_MAX)
    std::vector<int> dist(V, INT_MAX);


    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(std::make_pair(0, src));
    dist[src] = 0;


    std::vector<int> parent(V, 0);
    for (int i{ 0 }; i < V; i++) {
        parent[i] = i;
    }


    // Looping till priority queue becomes empty (or all
    // distances are not finalized)
    while (!pq.empty()) {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        //
        //// top(): This function is used to get the highest priority element in the queue without removing
        //// it from the queue.
        //
        //// pop(): This function removes the element with the highest priority from the queue.
        ////////////////std::cout << pq.top().first << "----" << pq.top().second << '\n';
        int u = pq.top().second;
        pq.pop();


        // 'i' is used to get all adjacent vertices of a
        // vertex
        std::list< std::pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            // Get vertex label and weight of current
            // adjacent of u.
            int v = (*i).first;
            int weight = (*i).second;

            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    //Print shortest distances stored in dist[]
    printSolution(dist, parent, V, src);
}







// Prints shortest paths from src to all other vertices
int Graph::minimumDistance(int src, int tgt) {

    std::priority_queue< ipair, std::vector<ipair>, std::greater<ipair> > pq;

    std::vector<int> dist(V, INT_MAX);

    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    std::vector<int> parent(V, 0);
    for (int i{ 0 }; i < V; i++) {
        parent[i] = i;
    }

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        std::list< std::pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {

            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight) {

                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
                parent[v] = u;
            }
            if (u == tgt) {
                break;
            }
        }
        if (u == tgt) {
            break;
        }
    }

    return dist[tgt];
}




// A utility function to construct the path array.
void Graph::auxPath(int currentNode, std::vector<int> parent, int src, std::vector<int>* path) {

    if (currentNode == src) {
        (*path).push_back(currentNode);
        return;
    }
    (*path).push_back(currentNode);
    auxPath(parent[currentNode], parent, src, path);

}


// Prints shortest paths from src to all other vertices
std::vector<int> Graph::minimumPath(int src, int tgt) {

    std::priority_queue< ipair, std::vector<ipair>, std::greater<ipair> > pq;

    std::vector<int> dist(V, INT_MAX);

    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    std::vector<int> parent(V, 0);
    for (int i{ 0 }; i < V; i++) {
        parent[i] = i;
    }

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        std::list< std::pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {

            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight) {

                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
                parent[v] = u;
            }
            if (u == tgt) {
                break;
            }
        }
        if (u == tgt) {
            break;
        }
    }

    std::vector<int> path{};
    std::vector<int>* ptr_path{ &path };

    auxPath(tgt, parent, src, ptr_path);

    std::reverse(path.begin(), path.end());

    return path;

}




