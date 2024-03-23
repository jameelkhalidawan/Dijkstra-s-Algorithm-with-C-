#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char* argv[]) {
    // Declare a string variable for the filename
    string filename;

    // Prompt user for the filename of the graph to load
    cout << "Filename of graph to load: ";
    getline(cin, filename);

    // Open the input file
    ifstream inputFile(filename);

    // Check if the input file is open, if not, display error message and return 1
    if (!inputFile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return 1;
    }

    // Declare variables for graph size and number of edges
    int graphSize, numEdges;
    // Read the graph size and number of edges from the input file
    inputFile >> graphSize >> numEdges;

    // Create a Graph object
    Graph graph;

    // Insert vertices into the graph
    for (int i = 0; i < graphSize; i++) {
        graph.insertVertex(i);
    }

    // Declare variables for vertices and edge weight
    int v1, v2;
    float weight;

    // Read edges from the input file and insert them into the graph
    for (int i = 0; i < numEdges; i++) {
        inputFile >> v1 >> v2 >> weight;
        graph.insertEdge(v1, v2, weight);
    }

    // Declare variables for the start and end vertices
    int startVertex, endVertex;
    // Read the start and end vertices from the input file
    inputFile >> startVertex >> endVertex;

    // Close the input file
    inputFile.close();

    // Display the shortest path between start and end vertices
    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    // Get the shortest path using the graph object
    vector<Vertex*> path = graph.shortestPath(startVertex, endVertex);

    // Print the shortest path
    for (auto i : path) {
        cout << i->label << " ";
    }
    cout << endl;

    // Return 0 to indicate successful execution
    return 0;
}
