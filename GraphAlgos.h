#pragma once
#include "Graph.h"
#include <vector>

std::vector<Graph::Edge> KruskalMST(Graph G, float costWeight, float distWeight, float timeWeight);             //returns a vector of edges, which can be used to make a minimum spanning tree
std::vector<std::pair<int,int>> DijkstraSSSP(Graph G, Graph::Node start,  float costWeight, float distWeight, float timeWeight);    //returns vector of pair<int,int>, with the first int being 
std::vector<Graph::Edge> BFS(Graph G, unsigned short start , unsigned short end);// returns vector of edges to find ends from start, simalr to mp mazes solve maze
  struct nodeDist{
      nodeDist(int n, int d, int p) : node(n), dist(d), predecessor(p) {}
      int node;
      int dist; //dist is the weighted average of all three inputs
      int predecessor;
  };