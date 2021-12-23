# pmm6-colincl2-vvrao2-jdchang3
Final project for pmm6-colincl2-vvrao2-jdchang3

All student written code files are located in the main git directory. Our code calls CS225 helper functions which are contained within
the CS225 directory. Our processed data is contained in the directory named data where the post-processed csv files are stored. Within that
directory, the original data sets are located in the directory called datasets. The test suite is stored in the tests directory in the
tests.cpp file. Visual output PNG images are written to the main git directory. 

The code can be compiled with "make". To run the executable, type "./flights". Text prompts will appear in the terminal asking for
input on which data and algorithms to run. Type in either 1, 2, or 3 into the terminal based on the prompts. If visual output was requested, the PNG file will be placed directly into the main directly with the file name provided by the user.

The test suite utilizes the catch2 helper program to run. The test suite can be compiled with "make test". All tests can be run simultanously by typing "./test". The 
tests that are run include tests to ensure the disjoint sets are working, along with the three graph algorithms. A small test graph is
created in the makeTestGraph function. For the test of the three algorithms, each test compares the return value of the algorithm
function to the correct return value. As the graph is small, the correct value for comparision was calculated by hand.

Our Node_Data and Edge_Data files in the data folder contain representations of airports and flights. Further description of the format of these files can be found in data_format.md in the same folder.
We collected our data from a US government website, so every node is a city within the US.
Our flights are not differentiated by their origin and termination cities, so a flight from Boston to Washington is the same
as a flight from Washington to Boston. We treated flights as undirected.
