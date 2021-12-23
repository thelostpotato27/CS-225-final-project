#include <iostream>
#include <limits>
#include "Graph.h"
#include "Utils.h"
#include "GraphAlgos.h"

int main(void){
    
    while(1){//entire program while loop
        int choice;
        while(1){//while loop to ask for flight or test data
            std::cout << "\nWould you like to use flight data or test data?" << std::endl;
            std::cout << "1 for flight data, 2 for test data, -1 to quit" << std::endl;
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear cin buffer
            if(choice == 2 || choice == 1 || choice==-1) break;
            std::cout << "Invalid input, please enter either 1 or 2" << std::endl; 
        }
        Graph g;
        if(choice==-1) break;
        else if(choice==1) g = readGraph("data/Node_Data_New.csv","data/Edge_Data_New.csv");
        else g = readGraph("data/Node_Data_Test.csv","data/Edge_Data_Test.csv");
        int algochoice;
        while(1){
            std::cout << "What graph algorithm would you like to use?" << std::endl;
            std::cout << "1 for Kruskal, 2 for Dijkstra, 3 for BFS, -1 to quit" << std::endl;
            std::cin >> algochoice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear cin buffer
            if(algochoice == 2 || algochoice == 1 || algochoice == 3 || algochoice==-1) break;
            std::cout << "Invalid input, please enter 1, 2, or 3" << std::endl; 
        }
        if(algochoice==-1)break;
        int vischoice;
        if(choice == 1){
                while(1){
                std::cout << "Would you like text or visual output?" << std::endl;
                std::cout << "1 for text output, 2 for visual output, -1 to quit" << std::endl;
                std::cin >> vischoice;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear cin buffer
                if(vischoice == 2 || vischoice == 1 || vischoice==-1) break;
                std::cout << "Invalid input, please enter either 1 or 2" << std::endl; 
            }
        }
        else{
            vischoice = 1;
        }
        if(vischoice==-1)break;
        std::string output_file;
        if(vischoice==2){   //ask for filename as output
            while(1){
                std::cout << "What would you like the output file to be called" << std::endl;
                std::cin >> output_file;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear cin buffer
                if(output_file != "") break;
            }
        }
        std::vector<Graph::Edge> edgelist;
        if(algochoice==1) edgelist = runKruskal(g);
        else if(algochoice==2) edgelist = runDijkstra(g);
        else edgelist = runBFS(g);
        

        const auto& nodes = g.getNodes();
        if(vischoice == 1){
            if(algochoice==1) std::cout << "Here is the MST following Kruskal's algorithm" << std::endl;
            else if(algochoice==2) std::cout << "Here is the minimum weight path following Dijkstra's algorithm" << std::endl;
            else std::cout << "Here is the route with the minimum number of flights" << std::endl;
            for(auto e : edgelist) std::cout << nodes[e.node1_id].name << ", " << nodes[e.node2_id].name << std::endl;
        }
        else {

            std::cout << "Your output has been stored in " << output_file << std::endl;
            std::string filename = output_file;
            visualizeRoute(g, edgelist, output_file);
        }

    }
    return 0;
}