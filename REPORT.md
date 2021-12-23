Our final project works as described in our goals document. Upon program start, the user is able to choose from one of two data sets to load. The first data set has original data from the website linked and generated using a python script.

https://www.transtats.bts.gov/DL_SelectFields.asp?gnoyr_VQ=FHK&QO_fu146_anzr=b4vtv0%20n0q%20Qr56v0n6v10%20f748rB

The second data set is representation of a graph used in lecture. (Depicted below) As this graph only contains one weight per edge, the distance, cost, and time weight for each edge in our test graph is the same as the corresponding edge in this graph.

![alt text](images/TestGraph.png)

Each graph is represented by two csv files - one for nodes and one for edges. The Node_Data files contain three columns and each row representing a node. The first column is the city name, the second column is the latitude, and the third column is the longitude. We collected our data from a US government website, so every node is a city within the US.  The Edge_Data file contains five columns with each row representing an edge. The first and second column contain the two cities for that flight. The third, fourth, and fifth columns contain the distance in miles, time in minutes, and cost in dollars for that flight respectively. Flights are not differentiated by their origin and termination cities, so a flight from Boston to Washington is the same as a flight from Washington to Boston.


The three graph algorithms that we stated for our goals are Kruskal’s, Dijkstra’s, and BFS. All three work according to their specific specifications and have been tested for correctness with a test suite. 

The output of our project is either a list of edge nodes that is printed out as text in the console or a PNG image that contains the included nodes and shows the route produced by the graph algorithms. The visual output for Kruskal’s is a minimum spanning tree depicting the minimum weight required to span every city based on either distance, time, or cost. The nodes in the MST are overlaid on a map of the US so each node is located at the correct location for that city. The visual output for Dijkstra’s are lines corresponding to flights that start from a specific starting airport and end at the specified ending airport. The specific list of flights is dependent on if the algorithm is minimizing distance, cost, or time. For BFS, the visual output is similar to Dijkstra’s where a series of lines connecting the start and end cities depict the route with the minimum number of flights.

In order to verify that our coded algorithms work correctly we made a test graph in our test suite, we tested the disjoint sets because they are used in the graph, the test we used are from mp_mazes. Then we wrote our own test cases for building a graph, a kruskal's MST, a BFS and a dijkstra, to run these test cases use make test then ./test, you will see that it passes all test cases

Here is the link to our video presentation:
https://illinois.zoom.us/rec/play/v_7HGRopQAE0qej1ia86tvCp-V3ht-_cQWXr12gWEQAH2KWvp2_qiUVnLVTKbTfD9RjDsnyXI3a3Y0U.vo3WKksc5x-LOoI7?_x_zm_rhtaid=882&_x_zm_rtaid=jkm5j5hzRNSu9pkgR4yWpg.1639461541688.3745fd7e9522a7a6f1c45ff52727e3d4&autoplay=true&continueMode=true&startTime=1639460657000
