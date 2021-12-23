#include "Graph.h"
#include <algorithm>

bool Graph::Node::operator<(const Graph::Node& other) const{
    return name < other.name;// returns less alphbetically
}

bool Graph::Edge::operator<(const Graph::Edge& other) const{
    if(node1_id==other.node1_id) return node2_id<other.node2_id;
    return node1_id<other.node1_id;// returns lthe lower node id
}

Graph::Graph(){} // default constructor does nothing

Graph Graph::copyNodes(){ // copy of graph with same IDs
    Graph g;
    g.name_to_node_id = this->name_to_node_id;
    g.nodes = this->nodes;
    return g;
}

void Graph::addNode(std::string n, float lat, float lon){
    name_to_node_id[n] = nodes.size();// constructs and add nodes to the graph
    nodes.emplace_back(n, lat, lon);
}

void Graph::addEdge(std::string city1, std::string city2, short cost, short distance, short time){
    addEdge(name_to_node_id.at(city1), name_to_node_id.at(city2), cost, distance, time);// constructs an edge from a 2 strings  and wieghts in cost, time and distance
}// calls other add edge

void Graph::addEdge(unsigned short node1, unsigned short node2, short cost, short distance, short time){
    if(node1 > node2) std::swap(node1, node2);// adds and edge adding it to adj list of the nodes
    nodes[node1].adj_list.push_back(edges.size());
    nodes[node2].adj_list.push_back(edges.size());
    edges.emplace_back(node1, node2, cost, distance, time);// also adds it to edge list of graph
}

const std::map<std::string, unsigned short>& Graph::getCityIDs() const{
    return name_to_node_id;// map of node id to name
}

const std::vector<Graph::Node>& Graph::getNodes() const{
    return nodes;// returns vector of nodes
}

const std::vector<Graph::Edge>& Graph::getEdges() const{
    return edges;// returns vector of edges
}
