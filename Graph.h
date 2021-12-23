#pragma once
#include <vector>
#include <string>
#include <map>

class Graph{
    public:
        struct Node;
        struct Edge;
        Graph();
        Graph copyNodes(); // returns copy of this graph but with no edges
        void addNode(std::string n, float lat, float lon);  // adds a node with latitude and longitude, the string n represents a city name
        void addEdge(std::string city1, std::string city2, short cost, short distance, short time);          //adds edge between cities, can be done with either city names or 
        void addEdge(unsigned short node1, unsigned short node2, short cost, short distance, short time);    //City IDs  
        const std::map<std::string, unsigned short>& getCityIDs() const;       //gets city IDs
        const std::vector<Node>& getNodes() const;      //returns a vector of all nodes
        const std::vector<Edge>& getEdges() const;      //returns a vector of all edges
        
        struct Node{// node struct 
            Node(std::string s, float lat, float lon): name(s), latitude(lat), longitude(lon), adj_list() {}
            std::string name;// nodes have a name lat and lon, and an adj list
            float latitude;
            float longitude;
            std::vector<unsigned short> adj_list;
            bool operator<(const Node& other) const;
        };

        struct Edge{
            Edge(unsigned short c1, unsigned short c2, short c, short d, short t): node1_id(c1), node2_id(c2), cost(c), dist(d), time(t) {}
            unsigned short node1_id; // node1_id < node2_id
            unsigned short node2_id;// nodes have 2 ids , and wieghts in cost dist and time
            short cost;
            short dist;
            short time;
            bool operator<(const Edge& other) const;
        };

    private:
        std::vector<Node> nodes;    //all nodes
        std::vector<Edge> edges;    //all edges
        std::map<std::string, unsigned short> name_to_node_id;  //city to city id map
};