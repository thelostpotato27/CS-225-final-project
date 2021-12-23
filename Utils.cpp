#include "Utils.h"
#include "Graph.h"
#include "GraphAlgos.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

static std::string toLower(std::string orig){
    std::string data = orig;
    std::transform(data.begin(), data.end(), data.begin(),[](unsigned char c){ return std::tolower(c); }); // from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
    return data;
}

static std::string titleCase(std::string orig){ // capitalize only first letter
    std::string data = toLower(orig);
    *data.begin() = std::toupper(*data.begin());
    return data;
}

unsigned short promptForNode(std::string prompt, Graph g){ // prompt for a city name from the given graph.
    unsigned short ret;
    std::string lower, title;
    const auto& citymap = g.getCityIDs();
    while(1){
        std::cout << prompt << std::endl;
        std::getline(std::cin, lower); //read in line from user
        lower = toLower(lower);
        title = lower;
        *title.begin() = std::toupper(*title.begin());
        if(citymap.count(title)) return citymap.at(title);
        std::string suggestions[5];
        int matches = 0;
        for(auto p : citymap){
            std::string plower = toLower(p.first); //checks if string input contains the city and vice versa.
            if(plower.find(lower) != std::string::npos || plower.find(title) != std::string::npos || lower.find(plower) != std::string::npos){ // check 3 forms of city name
                suggestions[matches++] = p.first;
                if(matches == 5) break;
            }
        }
        if(matches == 0){
            std::cout << "No city matches found! Please try a different city." << std::endl;
            continue;
        }
        else if(matches == 1) return citymap.at(suggestions[0]); //one city to be used
        else{
            std::cout << "Possible matches found:" << std::endl;
            for(int i = 0; i<matches; i++){
                std::cout << i+1 << ". \"" << suggestions[i] << "\"" << std::endl;
            }
            if(matches == 5) std::cout << "(further matches omitted for brevity)" << std::endl; //only print out the top five cities
        }
    }
}

Graph readGraph(std::string node_file, std::string edge_file)
{
    Graph G;// make new graph 
    std::ifstream infile (node_file);// file stream from potd
    std::string currLine;// current line as a sting
    std::string name;// name of node
    std::string latS;//latatude of node
    float lat;// float of latatude
    std::string lonS;//longuatide of node
    float lon;// float of longutude

    std::getline(infile, currLine);// get 1st line for a file
    while(std::getline(infile, currLine)) {// get the acutal lines
        name=currLine.substr(0,currLine.find(","));// name is value until the comma
        currLine=currLine.substr(currLine.find(",")+1,currLine.size());// cut string to remove name
        latS=currLine.substr(0,currLine.find(","));// get the lat in string form
        lat=std::stof(latS);// string to float 
        currLine=currLine.substr(currLine.find(",")+1,currLine.size());// cut string to remove lat
        lonS=currLine;// get long in string form 
        lon=std::stof(lonS);// turn to float form 
        
        G.addNode(name,lat,lon);// call add node 
    }

    std::string city1;//all the data for a edge is here 
    std::string city2;
    std::string  costS;
    int costI;// need to go to string to int then to short no direct convershion 
    short cost;
    std::string  timeS;
    int timeI;
    short time;

    std::string  distS;
    int distI;
    short dist;


    std::ifstream infile2 (edge_file);// new file stream for new file
    std::getline(infile2, currLine);// get first line
    while(std::getline(infile2, currLine)) {
        city1=currLine.substr(0,currLine.find(","));// city 1 is eveything before 1st comma
        currLine=currLine.substr(currLine.find(",")+1,currLine.size());// remove city1 
        city2=currLine.substr(0,currLine.find(","));// get city2 name

        currLine=currLine.substr(currLine.find(",")+1,currLine.size());// remove city 2
        distS=currLine;// dist string is first in csv so first thing we seperate out of the floats
        distI=std::stoi(distS);// string to float convershion
        dist=(short)distI;

        currLine=currLine.substr(currLine.find(",")+1,currLine.size());
        timeS=currLine.substr(0,currLine.find(","));// get the time string out of the currentline
        timeI=std::stoi(timeS);
        time=(short)timeI;
        
        currLine=currLine.substr(currLine.find(",")+1,currLine.size());
        costS=currLine.substr(0,currLine.find(","));// get the cost our of the current line 
        costI=std::stoi(costS);
        cost=(short)costI;
        //std::cout << city1 << ", " << city2 << std::endl;
        G.addEdge(city1,city2,cost,dist,time);// add the edge 
    }
    return G;// return the graph 
}

std::vector<Graph::Edge> runKruskal(Graph G, int choice){
    while(choice <= 0 || choice > 3){
        std::cout << "What would you like to prioritize?" << std::endl;
        std::cout << "1 for cost, 2 for distance, 3 for time: " << std::endl;
        std::cin >> choice;
        if(choice > 0 && choice < 4) break;
        std::cout << "Invalid choice, please try again." << std::endl;
    }
    auto& nodes = G.getNodes();
    auto mst = KruskalMST(G,choice==1,choice==2,choice==3);
    if(mst.size()==0) std::cout << "MST algorithm failed! Is the graph a single connected component?" << std::endl;
    std::sort(mst.begin(), mst.end());
    return mst;
    // for(auto e : mst){
    //     std::cout << nodes[e.node1_id].name << ", " << nodes[e.node2_id].name << std::endl;
    // }
}

std::vector<Graph::Edge> runDijkstra(Graph G){

    auto s = promptForNode("Enter a starting city: ",G);
    auto t = promptForNode("Enter an ending city: ", G);
    while(s==t){
       t = promptForNode("Please enter a different ending city: ", G); 
    }
    int choice = -1;
    while(choice <= 0 || choice > 3){
        std::cout << "What would you like to prioritize?" << std::endl;
        std::cout << "1 for cost, 2 for distance, 3 for time: " << std::endl;
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear cin buffer
        if(choice==1 || choice==2 || choice==3) break;
        std::cout << "Invalid choice, please try again." << std::endl;
    }
    const auto& nodes = G.getNodes();
    const auto& cityIDs = G.getCityIDs();
    
    auto dijkstraout = DijkstraSSSP(G, nodes[s], choice==1,choice==2,choice==3); //
    int backroute = dijkstraout[t].second;
    std::vector<Graph::Node> route; //get route of nodes
    route.push_back(nodes[t]);
    while(backroute != -1){
        route.push_back(nodes[backroute]);
        backroute = dijkstraout[backroute].second;
    }
    std::reverse(route.begin(), route.end());
    std::vector<Graph::Edge> edgeroute;
    for(unsigned i = 0; i < route.size()-1; ++i){
        unsigned short city1 = cityIDs.at(route[i].name);
        unsigned short city2 = cityIDs.at(route[i+1].name);
        edgeroute.push_back(Graph::Edge(city1, city2, 0,0,0));
    }

    return edgeroute;
}

std::vector<Graph::Edge> runBFS(Graph G){
auto s = promptForNode("Enter a starting city: ",G);// get start
auto t = promptForNode("Enter an ending city: ", G);// get end 
while(s==t){
    t = promptForNode("Please enter a different ending city: ", G); // if not vaild end
}
return BFS(G,s,t);// run BFS with given inputs
}

void visualizeRoute(Graph G,std::vector<Graph::Edge> edges, std::string filename){
    float longmin = -64;         //makes it so that the longitude/latitude matches on map
    float latmin = 22;            
    float map_width = -62.9;
    float map_height = 30;
    filename = filename + ".png";
    
    cs225::PNG pathed;
    pathed.readFromFile("USA_map.png");

    int dot_size = 5;

    const auto& ALL_nodes = G.getNodes();
    std::pair<float,float> curr_coord (0,0);
    std::pair<float,float> next_coord (0,0);
    for(unsigned i = 0; i < edges.size(); i++){
        if(curr_coord.first == 0){       //basically checks if this is the first node, if it is it will calc the first node coord
            Graph::Node curr_node = ALL_nodes[edges[i].node1_id];

            if(curr_node.longitude < -150.0 && curr_node.latitude < 24.0){   //checks if its hawaii
                curr_coord.first = pathed.width() / 5.0;
                curr_coord.second = pathed.height() * .9;
            }else if(curr_node.latitude > 50){              //checks if it is alaska
                curr_coord.first = pathed.width() / 14.0;
                curr_coord.second = pathed.height() * (13.0/15.0);
            }else if(curr_node.latitude - 14.0 < 2 && curr_node.longitude - 144.0 < 2){     //checks if northern Mariana islands
                curr_coord.first = pathed.width() / 8.0;
                curr_coord.second = pathed.height() * .9;
            }else{
                float longitude = curr_node.longitude - longmin;            //if no special circumstances, finds the x and y coord in the PNG 
                float latitude = curr_node.latitude - latmin;               //that matches the longitude and latitude
                curr_coord.first = pathed.width() * (longitude / map_width);
                curr_coord.second = pathed.height() * (latitude / map_height);
                curr_coord.first = pathed.width() - curr_coord.first;
                curr_coord.second = pathed.height() - curr_coord.second;
            }
        }

        Graph::Node next_node = ALL_nodes[edges[i].node2_id];       //calc second node coord, same as the first
        if(next_node.longitude < -150.0 && next_node.latitude < 24.0){      //checks if its hawaii
            next_coord.first = pathed.width() / 5.0;
            next_coord.second = pathed.height() * .9;
        }else if(next_node.latitude > 50){              //checks if its alaska
            next_coord.first = pathed.width() / 14.0;
            next_coord.second = pathed.height() * (13.0/15.0);
        }else if(next_node.latitude - 14.0 < 2 && next_node.longitude - 144.0 < 2){         //checks if northern Mariana islands
            next_coord.first = pathed.width() / 8.0;
            next_coord.second = pathed.height() * .9;
        }else{
            float longitude = next_node.longitude - longmin;        //if no special circumstances, finds the x and y coord in the PNG 
            float latitude = next_node.latitude - latmin;           //that matches the longitude and latitude
            next_coord.first = pathed.width() * (longitude / map_width);
            next_coord.second = pathed.height() * (latitude / map_height);
            next_coord.first = pathed.width() - next_coord.first;
            next_coord.second = pathed.height() - next_coord.second;
        }
        

        float x = curr_coord.first;
        float y = curr_coord.second;
        for(int j = -2; j < 3; j++){        //draw first node coord onto map
            for(int k = -2; k < 3; k++){
                cs225::HSLAPixel& pixel = pathed.getPixel(x+j,y+k);
                pixel.h = 315;
                pixel.s = 1;
                pixel.l = .5;
                pixel.a = 1;
            }
        }

        float slope = 1;                                    //calcs slope between current point and next point
        if(next_coord.first == curr_coord.first){
            slope = 2;
        }else{
            slope = (next_coord.second - curr_coord.second)/(next_coord.first - curr_coord.first);
        }

        //checks if coords are outside of bounds, then draws lines between all the points
        if(next_coord != curr_coord && next_coord.first < pathed.width() && curr_coord.first < pathed.width() && next_coord.second < pathed.height() && curr_coord.second < pathed.height()){
            if(slope <= 1.0 && slope >= -1.0){      //checks if slope is too steep, if it is then move to other formula, which is x = f(y) rather than y = f(x)
                int start = (int)curr_coord.first;
                int end = (int)next_coord.first;
                if (start < end){                   //checks if start point is smaller than end point
                    for(int j = start; j < end; j++){       //start point is less than end point
                        cs225::HSLAPixel& pixel = pathed.getPixel(j,(j - curr_coord.first)*slope + curr_coord.second);
                        pixel.h = 315;
                        pixel.s = 1;
                        pixel.l = .5;
                        pixel.a = 1;
                    }
                }else{
                    for(int j = start; j > end; j--){       //end point is less than start point
                        if ((unsigned)((j - curr_coord.first)*slope + curr_coord.second) > pathed.height()){
                            std::cout << next_node.name << std::endl;
                            std::cout << ALL_nodes[edges[i].node1_id].name << std::endl;
                        }
                        cs225::HSLAPixel& pixel = pathed.getPixel(j,(j - curr_coord.first)*slope + curr_coord.second);
                        pixel.h = 315;
                        pixel.s = 1;
                        pixel.l = .5;
                        pixel.a = 1;
                    }
                }
                
            }else{          //x = f(y) formula for steep slopes
                slope = (next_coord.first - curr_coord.first)/(next_coord.second - curr_coord.second);
                int start = (int)curr_coord.second;
                int end = (int)next_coord.second;
                if(start < end){
                    for(int j = start; j < end; j++){       //start point is less than end point
                        cs225::HSLAPixel& pixel = pathed.getPixel((j - curr_coord.second)*slope + curr_coord.first,j);
                        pixel.h = 315;
                        pixel.s = 1;
                        pixel.l = .5;
                        pixel.a = 1;
                    }
                }else{
                    for(int j = start; j > end; j--){       //end point is less than start point
                        cs225::HSLAPixel& pixel = pathed.getPixel((j - curr_coord.second)*slope + curr_coord.first,j);
                        pixel.h = 315;
                        pixel.s = 1;
                        pixel.l = .5;
                        pixel.a = 1;
                    }
                }

            }            
        }

        curr_coord = next_coord;            //make second coord equal to first coord to save on computations
    }
    unsigned x = curr_coord.first;          //colors in the final node
    unsigned y = curr_coord.second;
    for(int j = -2; j < 3; j++){
        for(int k = -2; k < 3; k++){
            cs225::HSLAPixel& pixel = pathed.getPixel(x+j,y+k);
            pixel.h = 315;
            pixel.s = 1;
            pixel.l = .5;
            pixel.a = 1;
        }
    }

    pathed.writeToFile(filename);
}
