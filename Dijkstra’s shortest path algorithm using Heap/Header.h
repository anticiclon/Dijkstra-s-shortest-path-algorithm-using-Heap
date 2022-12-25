#pragma once
#ifndef FUNCTIONS_H //se define una única vez para evitar definimir las mismas funciones dos veces al hacer #include "functions.h"
#define FUNCTIONS_H


#include <iostream>
#include <list>
#include <queue>



class Graph {
    int V; 

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















#endif