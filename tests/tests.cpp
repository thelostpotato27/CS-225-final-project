#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include "../GraphAlgos.h"
#include "../DisjointSets.h"
#include "../Utils.h"
#include <iostream>

Graph makeTestGraph(){
	Graph G;
	G.addNode("Colin", 45.6,49.0);//start of nodes
    G.addNode("JurassicGrill", 45.7,49.7);
    G.addNode("Patrick", 42.3,-93.4);
    G.addNode("Grace", 43.5,46.7);
    G.addNode("ARC",32.4,35.4);
    G.addNode("Yogi",23.5,12.3);
    G.addNode("ECEB",34.5,23.4);
    G.addNode("AMC",26.7,27.8);
	G.addNode("Walgreens", 43.7,68.9);// end of nodes


    G.addEdge("AMC","Colin",13,4,91);//start of edges
	G.addEdge("AMC","JurassicGrill",12,3,105);
	G.addEdge("Colin","JurassicGrill",12,3,5);
	G.addEdge("AMC","ECEB",15,3,102);
    G.addEdge("Yogi","ECEB",15,1,7);
	G.addEdge("Yogi","ARC",5,1,14);
	G.addEdge("Walgreens","ARC",5,1,10);
	G.addEdge("Grace","ARC",1,1,5);
	G.addEdge("Grace","Patrick",3,1,10);
	G.addEdge("Grace","Colin",2,1,7);
	G.addEdge("Patrick","Colin",5,1,12);// end of edges

	return G;
}

TEST_CASE("addElements1", "[weight=1[valgrind]")// these are disjoint set tests, we want to make sure these work and dont lose memeory
{
	DisjointSets disjSets;
	disjSets.addelements(5);
	REQUIRE(3 == disjSets.find(3));
}

TEST_CASE("addElements2", "[weight=1][valgrind]")
{
	DisjointSets disjSets;
	disjSets.addelements(5);
	REQUIRE(0 == disjSets.find(0));
	disjSets.addelements(5);
	REQUIRE(9 == disjSets.find(9));
}

TEST_CASE("testFindAndSetUnion1", "[weight=1][valgrind]")
{
	DisjointSets disjSets;
	disjSets.addelements(4);
	
	disjSets.setunion(1, 2);
	
	REQUIRE(disjSets.find(2) == disjSets.find(1));
}

TEST_CASE("testFindAndSetUnion2", "[weight=1][valgrind]")
{
	DisjointSets disjSets;
	disjSets.addelements(10);

	disjSets.setunion(4, 8);
	disjSets.setunion(1, 3);
	disjSets.setunion(1, 5);
	disjSets.setunion(8, 3);
	disjSets.setunion(6, 7);
	disjSets.setunion(2, 8);
	disjSets.setunion(7, 1);
	//disjSets.printSet();
	int root = disjSets.find(1);
	for (int i = 2; i <= 8; i++)
		REQUIRE(root == disjSets.find(i));
	REQUIRE(disjSets.find(0) != disjSets.find(9));
}

TEST_CASE("testFindAndSetUnion3", "[weight=1][valgrind]")
{
	DisjointSets disjSets;
	disjSets.addelements(8);
	
	disjSets.setunion(1, 2);
	disjSets.setunion(1, 3);
	disjSets.setunion(4, 5);
	disjSets.setunion(4, 6);
	disjSets.setunion(3, 6);
	REQUIRE(disjSets.find(4) == disjSets.find(1));
	REQUIRE(disjSets.find(0) != disjSets.find(4));
}

TEST_CASE("size1", "[weight=1][valgrind]")
{
	DisjointSets disjSets;
	disjSets.addelements(4);
	REQUIRE(1 == disjSets.size(2));
}

TEST_CASE("size2", "[weight=1][valgrind]")
{
	DisjointSets disjSets;
	disjSets.addelements(8);
	
	disjSets.setunion(1, 7);
	disjSets.setunion(2, 6);
	
	disjSets.setunion(3, 5);
	disjSets.setunion(2, 3);
	
	
	REQUIRE(4 == disjSets.size(3));
	disjSets.setunion(1, 3);
	REQUIRE(6 == disjSets.size(6));

}// disjoint set test cases to make sure that works


TEST_CASE("addNode", "[weight=1][valgrind]")// add node make sure it does not add edge 
{
	Graph G;
	G.addNode("Urbana", 20,21);// this test just tests if the add node function works correctly 
    std::vector<Graph::Node> nodeList;
    nodeList=G.getNodes();
    Graph::Node N=nodeList[0];
	REQUIRE(1 == G.getNodes().size());// tests if the node is in the node list 
    REQUIRE(0 == G.getEdges().size());// test if there r no edges
    REQUIRE("Urbana" == N.name);// tests node data
    REQUIRE(20 == N.latitude);
    REQUIRE(21 == N.longitude);
}

TEST_CASE("addEdge", "[weight=1][valgrind]")// add edge make sure it does not add node
{
	Graph G;
	G.addNode("Home", 20.5,20.5);// this test tests the add edge function with node ids
	G.addNode("Champaign", 20.6,20.5);// need 2 nodes for an edge 
	G.addEdge(0,1,2,3,4);
    std::vector<Graph::Edge> edgeList;
    edgeList=G.getEdges();
    Graph::Edge E=edgeList[0];
	REQUIRE(1 == G.getEdges().size());// check if edge was added
    REQUIRE(2 == G.getNodes().size());//check if node was added
    REQUIRE(1 == E.node2_id);// test node data
    REQUIRE(0 == E.node1_id);
    REQUIRE(2 == E.cost);// tests if data was enter correctly 
    REQUIRE(3 == E.dist);
    REQUIRE(4 == E.time);
}

TEST_CASE("addEdge2", "[weight=1][valgrind]")// add edge by name bc that is a differernt function than the prevous one 
{
	Graph G;
	G.addNode("Home", 20.5,20.5);// tests add edge with strings 
	G.addNode("Champaign", 20.6,20.5);// indirectly testing the map
	G.addEdge("Home","Champaign",2,3,4);// add edge
    std::vector<Graph::Edge> edgeList;
    Graph::Edge E(0,0,0,0,0);
    edgeList=G.getEdges();
    E=edgeList[0];
	REQUIRE(1 == G.getEdges().size());// test if edge was added
    REQUIRE(2 == G.getNodes().size());// test if node was added
    REQUIRE(0 == E.node1_id);// home should id 1 bc its last alphbetically
    REQUIRE(1 == E.node2_id);//champaign should have id 0 bc its first alphbetically
    REQUIRE(2 == E.cost);// test edge data
    REQUIRE(3 == E.dist);
    REQUIRE(4 == E.time);
}
TEST_CASE("miniGraphKMST", "[weight=1][valgrind]")
{
	Graph G = makeTestGraph();
	REQUIRE(11 == G.getEdges().size());
    REQUIRE(9 == G.getNodes().size());
    std::vector<Graph::Edge> kMST=KruskalMST(G,0,0,1);// make kurskal mst based on time
	REQUIRE(8 == kMST.size());// make sure #edges = #nodes-1
	Graph::Edge E(2,1,0,0,0);// no defult edge consturctor
	std::vector<short> times={5,5,7,7,10,10,14,91};// hand calculated times form smallest to biggest 
	for(size_t i=0;i<kMST.size();i++)
	{
		E=kMST[i];// make sure algorthem matches hand calculted 
		REQUIRE(times[i] == E.time);
	}
	
}
TEST_CASE("miniGraphBFS", "[weight=1][valgrind]")
{
	Graph G = makeTestGraph();// makes the test graph
	REQUIRE(11 == G.getEdges().size());
    REQUIRE(9 == G.getNodes().size());// test test graph
    std::vector<Graph::Edge> bFS=BFS(G,1,7);// make a 1 edge BFS
	REQUIRE(1 == bFS.size());// test if one edge
	Graph::Edge E(2,1,0,0,0);
	E=bFS[0];// get edge
	
	REQUIRE(1 == E.node1_id);// make sure it has the corrent nodes 
	REQUIRE(7 == E.node2_id);
	
	
}
TEST_CASE("smallGraphBFS", "[weight=1][valgrind]")
{
	Graph G = makeTestGraph();// makes the test graph
	REQUIRE(11 == G.getEdges().size());
    REQUIRE(9 == G.getNodes().size());// test test graph
    std::vector<Graph::Edge> bFS=BFS(G,3,1);
	
	REQUIRE(2 == bFS.size());// test if two edges
	Graph::Edge E(2,1,0,0,0);
	REQUIRE(2 == bFS.size());// make sure 2 lay deep bfs is 2 layers 
	E=bFS[0];// get first edge of bfs
	REQUIRE(3 == E.node1_id); //make sure start edge is correct 
	REQUIRE(0 == E.node2_id); // 
	E=bFS[1];
	REQUIRE(0 == E.node1_id); //make sure ending edge correct
	REQUIRE(1 == E.node2_id);
	
}
TEST_CASE("miniDijkstra", "[weight=1][valgrind]"){
	Graph G = makeTestGraph();
	const auto& nodes = G.getNodes();
	std::vector<std::pair<int,int>> dijkstraout = DijkstraSSSP(G, nodes[3], 0,1,0);
	std::vector<std::pair<int,int>> answer;
	answer.push_back(std::pair<int,int>(1,3));
	answer.push_back(std::pair<int,int>(4,0));
	answer.push_back(std::pair<int,int>(1,3));
	answer.push_back(std::pair<int,int>(0,-1));
	answer.push_back(std::pair<int,int>(1,3));
	answer.push_back(std::pair<int,int>(2,4));
	answer.push_back(std::pair<int,int>(3,5));
	answer.push_back(std::pair<int,int>(5,0));
	answer.push_back(std::pair<int,int>(2,4));
	REQUIRE(dijkstraout.size() == 9);
	for(unsigned i = 0; i < 9; ++i){
		REQUIRE(dijkstraout[i].first == answer[i].first);
		REQUIRE(dijkstraout[i].second == answer[i].second);
	}
}

