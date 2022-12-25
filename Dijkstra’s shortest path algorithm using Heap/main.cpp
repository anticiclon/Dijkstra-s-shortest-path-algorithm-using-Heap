// Dijkstra’s shortest path algorithm using Heap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "header.h"


// Driver's code
int main()
{
    // create the graph given in above figure
    int V = 9;
    Graph g(V);

    // making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    // Source
    int source{ 3 };
    // Target
    int target{ 7 };

    // Function call
    g.shortestPath(source);

    std::cout << '\n';
    int distance{ g.minimumDistance(source, target) };
    std::cout << "La distancia minima entre el nodo " << source << " y el nodo " << target << " es " << distance << '\n';

    std::vector<int> camino = g.minimumPath(source, target);

    std::cout << '\n';

    std::cout << "El camino mas corto entre el nodo " << source << " y el nodo " << target << " es ";

    for (int i : camino) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;

}




