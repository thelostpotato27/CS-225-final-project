#pragma once
#include <string>
#include "Graph.h"

unsigned short promptForNode(std::string prompt, Graph g); // prompt for a city name from the given graph.

Graph readGraph(std::string node_file, std::string edge_file); // return a graph read from these two files.

std::vector<Graph::Edge> runKruskal(Graph g, int choice = -1); // prompt user to specify how they want to run Kruskal's algorithm.

std::vector<Graph::Edge> runDijkstra(Graph G); //same as above

std::vector<Graph::Edge> runBFS(Graph G); //same as above

void visualizeRoute(Graph G, std::vector<Graph::Edge> edgelist, std::string filename = "");

