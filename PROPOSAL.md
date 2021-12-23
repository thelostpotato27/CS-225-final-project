## CS 225 Final Project Proposal
### Leading Question
We are trying to determine the most effective way(s) to get from one city to another. One problem is that finding multiple methods of transportation can be time consuming, and transport (especially flights) can be expensive. We are hoping to produce a search tool that, given two major cities in the US, is able to return multiple possible transport plans based on price, time, or a weighted mix of the two. If time permits, we will add data from multiple types of transportation (trains, buses etc.) and utilize the different types to find even faster/cheaper travel itineraries.

### Dataset Acquisition and Processing
We are going to use the Bureau of Transportation Statistics data on flights to get our data on price and flight time. We will represent each major city by a node, and each flight (or train/bus route) by an edge. Each city will have a few properties like location and list of airports, and each edge will have properties such as transportation type, duration, and cost. We plan on preprocessing our data into the CSV format for nodes and edges using Python. If we add more transport types, we will also need to process the data for those. Multiple airports within the same city will be assigned to the same node. Missing/erroneous entries will be removed/ignored. We may also later use more datasets in order to get more cost data and transport types. The [first public dataset](https://www.transtats.bts.gov/DL_SelectFields.asp?gnoyr_VQ=FHK&QO_fu146_anzr=b4vtv0%20n0q%20Qr56v0n6v10%20f748rB) that we will be using is the from Bureau of Transportation Statistics's website. We will be able to use our data to analyze the cost and time of different trip options. Despite the fact that flights may take a little bit longer in certain directions due to wind, for simplicity we will be using an undirected graph.

### Graph Algorithms
(Note: E and V are the sets of edges and vertices in our graph respectively.)

We expect to implement the following 3 graph algorithms:
1. Breadth First Search with O(|V|+|E|) time complexity. We will use this to implement our traversal/iterator.
2. Dijkstra's Algorithm: Given our graph and a start and end point, as well as how much to weight the different heuristics of time and cost, this function will return which sequence of edges/flights to take in order to minimize our weighted heuristic and reach the destination. The target time complexity for this algorithm is O((|V| + |E|)log|V|). This algorithm will be used to find the shortest path between two points according to a given heuristic.
3. Kruskal's Algorithm: Given our graph and how much to weight the different heuristics of time and cost, this function will find the minimum spanning tree of our graph according to the given heuristic. Our time complexity target for this algorithm is O(|E|log|E|) time.

### Timeline (tentative)
Nov. 14th - **Data Acquisition**: Finalizing the datasets we wish to use for cost, distance, and time for each method of transportation.

Nov. 24th - **Data Preprocessing**: Processing our variety of datasets into the consistent node/edge format described in the "Dataset Acquisition" section.

Nov. 24th - **Graph Implementation and BFS**: The basic implementation of our graph using nodes and edges. We will also hopefully have finished the BFS algorithm and iterator by this time.

Nov. 30th - **Kruskal's Algorithm**: Implementation of Kruskal's algorithm as described above.

Nov. 30th - **Initial Visualization**: A basic way to visualize a set of edges on the graph using some sort of image.

Dec. 5th - **Dijkstra's Algorithm**: Implementation of Dijkstra's algorithm as described above.

Dec. 9th - **Final Visualization**: Final implementation of visualization with support for visualizing the outputs of all of our graph algorithms, as well as a menu system for user interaction and file I/O.

Dec. 12th - **Report and Presentation / Final Deliverables**
