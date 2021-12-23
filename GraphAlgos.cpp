#include "GraphAlgos.h"
#include "Graph.h"
#include "DisjointSets.h"
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <cfloat>
//#include <bits/stdc++.h>
//#include <boost/heap/fibonacci_heap.hpp> //never ended up using these? 

std::vector<Graph::Edge> KruskalMST(Graph G, float costWeight, float distWeight, float timeWeight){
    //comparator llamda function to allow priority queue to sort edges
    auto cmp = [=](Graph::Edge a, Graph::Edge b) { return (a.cost*costWeight+a.dist*distWeight+a.time*timeWeight) > (b.cost*costWeight+b.dist*distWeight+b.time*timeWeight); };
    if(G.getNodes().size() == 0) return std::vector<Graph::Edge>();// above is comparator function this line is if empty we r done
    unsigned retsize = G.getNodes().size()-1;
    DisjointSets nodeSet; //create disjoint set to check if node already in MST
    std::priority_queue<Graph::Edge, std::vector<Graph::Edge>, decltype(cmp)> prio_q(cmp, G.getEdges()); //sort edges into priorty queue
    nodeSet.addelements(prio_q.size()); //create disjoint set with number of sets as the number of edges
    std::vector<Graph::Edge> ret; //list of edges to return
    if(!prio_q.size() || retsize <= 0) return ret;
    ret.reserve(retsize);
    while(prio_q.size() && ret.size()!=retsize){ //run while there edges in priority queue
        auto curedge = prio_q.top(); //pop off smallest edge
        if(nodeSet.find(curedge.node1_id) != nodeSet.find(curedge.node2_id)){ //check if adds new node 
            ret.push_back(curedge); //add edge to return list
            nodeSet.setunion(curedge.node1_id, curedge.node2_id); //add node to union if adding edge
        }
        prio_q.pop(); //remove edge from priority queue
    }
    if(ret.size() < retsize){ //fail safe if edge list does not include number of nodes minus one
        ret.clear();
    }
    return ret;
}

std::vector<std::pair<int,int>> DijkstraSSSP(Graph G, Graph::Node start,  float costWeight, float distWeight, float timeWeight){
    const auto& nodeIDs = G.getCityIDs();
    const auto& nodes = G.getNodes();
    const auto& edges = G.getEdges();
    std::vector<nodeDist> ret; //stores node IDs, weight to start node, predescessor node
    for(unsigned i = 0; i < nodes.size(); ++i){
        ret.push_back(nodeDist(i,INT_MAX,-1));
    }
    ret[nodeIDs.at(start.name)].dist = 0; //this line won't work until the start Node is changed to not a test

    //Just in case I need it again: https://stackoverflow.com/questions/5807735/c-priority-queue-with-lambda-comparator-error
    //nodeDist is nodeID, distance then predecessor
    auto weightedCompare = [=](nodeDist a, nodeDist b){return a.dist > b.dist;};
    std::priority_queue<nodeDist, std::vector<nodeDist>, decltype(weightedCompare)> pqueue(weightedCompare, ret);

    //check if we have used a node
    std::vector<bool> usedNodes(ret.size(), false);

    //cost helper function
    auto cost = [=, &edges](int node, int parent){
        for(Graph::Edge edge : edges) if(edge.node1_id == std::min(node,parent) && edge.node2_id == std::max(node,parent)) return edge.cost*costWeight+edge.dist*distWeight+edge.time*timeWeight;
        return FLT_MAX;};
                                                                                                    
    for(unsigned i = 0; i < nodes.size(); ++i){
        nodeDist minnode = pqueue.top();
        pqueue.pop();
        while (usedNodes[minnode.node]){ //find non duplicate node
            minnode = pqueue.top();
            pqueue.pop();
        }
        usedNodes[minnode.node] = true; //set node to true so we know it's used
        //Get vector of nodes adjacent to minode but not already used
        std::vector<unsigned short> unusedNeighboors;
        const auto& adjedges = nodes[minnode.node].adj_list; //returns vector of unsigned shorts
        for(unsigned short edge : adjedges){
            Graph::Edge edgeobj = edges[edge];
            if(usedNodes[edgeobj.node1_id] == false && usedNodes[edgeobj.node2_id] == false){
                std::cout << "We have a problem here" << std::endl;
            }
            if(usedNodes[edgeobj.node1_id] == false) unusedNeighboors.push_back(edgeobj.node1_id); //check edges to find the unused nodes
            else if(usedNodes[edgeobj.node2_id] == false) unusedNeighboors.push_back(edgeobj.node2_id);
        }
        //Going through each unused node and changing distance as needed
        for(unsigned short node : unusedNeighboors){
            if (cost(node, minnode.node) + ret[minnode.node].dist < ret[node].dist){
                ret[node].dist = cost(node, minnode.node) + ret[minnode.node].dist;
                ret[node].predecessor = minnode.node;
                pqueue.push(ret[node]); //add new distance node to the priority queue
            }
        }
    }
    std::vector<std::pair<int,int>> dijkstraout;
    for(nodeDist node : ret){
        dijkstraout.push_back(std::pair<int,int>(node.dist, node.predecessor)); //create return vector
    }
    return dijkstraout;
}

std::vector<Graph::Edge> BFS(Graph G, unsigned short start , unsigned short end){
    // this our BFS algorthem it finds the min number of flights from one spot to another 
    std::vector<Graph::Edge> pathEdges;// return vector 
    std::vector<unsigned short> visitedNodes(G.getNodes().size(),32767);//using puedo code from the slides 
    std::vector<unsigned short> visitedEdges(G.getEdges().size(),32767);//max short is unvisited
    // only call once on graph because only one connected compontet 
    std::queue<unsigned short> upNext;// up next queue
    if(start<0||start>G.getNodes().size()||end<0||end>G.getNodes().size())
            {
                 // if bad imput give bad output
                return pathEdges;
            }
    visitedNodes[start]=G.getNodes().size();// mark as start beacuse we are going back to find path we will need to know start
    upNext.push(start);// put start first
    
    unsigned short currSpot;// current spot 
    std::vector<Graph::Node> gNodes=G.getNodes();// get the nodes 
    std::vector<Graph::Edge> gEdge=G.getEdges();// get the edges
   
    while(!upNext.empty())
    {
        
            currSpot=upNext.front();// current is front of queue
            upNext.pop();// remove front form queue
            if(currSpot==end)
            {
                break;// if we found the end we are done
            }
            Graph::Node N=gNodes[currSpot];// find the current spot as a node
            size_t i=0;
            //std::cout <<"Node N is of degree " <<N.adj_list.size()<<std::endl;
            while(i<N.adj_list.size())
            {   
                
                unsigned short otherSide;// the other side 
                Graph::Edge currEdge=gEdge[N.adj_list[i]];//get the current edge 
                otherSide=currEdge.node1_id;// get the fist id in the node
                if(currSpot==otherSide)// if current is the other side get the other one
                {
                    otherSide=currEdge.node2_id;// if curr node 1 then otherside is node 2 
                }
                if(visitedNodes[otherSide]<=G.getNodes().size())// if other node visited skip this one 
                {
                    i++;
                    continue;
                }
                
                
                visitedNodes[otherSide]=currSpot;//set parent of other side
                upNext.push(otherSide);// add other side to the queue
                
                i++;// comment later when debugging 
                
            }
            // going backwards though graph to get start
           
    }
    unsigned short prev;// look for prev
    
           
    prev=visitedNodes[currSpot];
    
    while(prev<G.getNodes().size())
    {
            Graph::Node N=gNodes[currSpot];// get current
            
            size_t i=0;// look for prev though adj list
            while(i<N.adj_list.size())
            {   
                
                unsigned short otherSide;// find other side of current edge
                Graph::Edge currEdge=gEdge[N.adj_list[i]];
                otherSide=currEdge.node1_id;
                if(currSpot==otherSide)
                {
                    otherSide=currEdge.node2_id;// if curr node 1 then otherside is node 2 
                }// if other side = current side get the other oth
                if(otherSide==prev)// if we found the prev go back 
                {
                    //pathEdges.push_back(currEdge);
                    pathEdges.push_back(Graph::Edge(otherSide,currSpot,0,0,0)); //I changed this line so the flights read in the correct order, Patrick
                    break; 
                }
                i++;
                
            }
            currSpot=prev;// go backwards in the edge list 
            prev=visitedNodes[prev];




        }
      
    std::reverse(pathEdges.begin(),pathEdges.end());// reverse the way the edges are pushed to the vector 
    return pathEdges;// return the vector of edges
    
}