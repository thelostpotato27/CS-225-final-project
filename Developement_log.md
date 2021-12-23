11/7/21
    Wrote out and committed the Project proposal and Project Contract, which detailed what we would be doing in our
    project and what each person in the group would be doing in the project, respectively. For the project, we decided
    to focus on transportation data, namely the distance, cost and time it took to get from one location to another,
    taking into account multiple modes of transportation. These modes of transportation include, but are not limited
    to, plane and train.

11/23/21
    Started writing our data parser and finished researching plane transportation data, which include the cost, time, 
    and distance to get from one city to another. We will be using Cities as our origin and destination for our data.
    the .csv files for the data has been downloaded, and we plan on completing our DataParser.py to output a .csv file 
    that is easier to use that combines the data we found in a more human-friendly way. We are using the Bereau of 
    Transportation statistics for the data.

12/1/21
    Finished writing the DataParser.py function and successfully generated the Flight_Data.csv file that will be the
    starting data for the project. We found a small bug in the DataParser function that produces duplicate routes as
    some cities have multiple airports. This bug will be fixed by next week. Graph implimentation coding also began
    this week. We discussed the exact structure of the nodes and edges for this graph including how to store them in
    the minumum number of bytes. New files added this week include Edge.cpp and Edge.h.
    
12/2/21
    Wrote code to parse .csv files and turn them into a edge list and node list. We also implemented Kruskal's algorithm, 
    and used different parameters to our cost function to allow the user to change to weight the tree differently. We
    also overhauled our data processing code to handle storing latitude and longitude for each point. Finally, we wrote
    a utility function to allow the user to search for a city.

12/7/2021
    Wrote code for our BFS traversal and our Dijkstra's traversal. Dijkstra's traversal is still in progress, but just 
    needs a priority queue implemented. BFS is finished. The BFS uses a pretty standerd Queue and mark visited process,
    the visited edges are put in a vector in reverse order they are visited in, then the vector is reversed and returned.
    We brainstorming how to implment test cases and how to draw the flight patterns.
  
12/13/201
    This is the final log before the project is due. We added a test suite and the CS225 folder to allow for visualizations.
    A text based input was implemented in main.cpp to allow the user to select between the different data sets and graph algorithms.
    A visualization function was written that allows the outputs from the graph algorithms to be overlaid onto a map of the US

