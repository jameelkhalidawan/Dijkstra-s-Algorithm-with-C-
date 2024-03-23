// Include guard to prevent multiple inclusions of the header file
#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"

#include <vector>
#include <limits>
using std::vector;

// Forward declaration of the Edge class
class Edge;

// Vertex class definition
class Vertex
{
public:
    int label; // Unique identifier of the vertex
    vector<Edge*> edges; // List of edges connected to the vertex

    // Helper variables and structures for path finding algorithms
    bool visited; // Whether the vertex has been visited
    float distanceTo; // Distance from the starting vertex
    Vertex* pathTo; // Pointer to the previous vertex in the shortest path
    Heap<Vertex*>::Locator locator; // Locator for the vertex in the priority queue
    bool operator < (const Vertex& v) const // Overloaded less-than operator for priority queue comparisons
    {
        return distanceTo < v.distanceTo;
    }

    // Constructor for the Vertex class
    Vertex(int l) : label(l), visited(false), distanceTo(std::numeric_limits<float>::max()), pathTo(nullptr) { }
};

// Edge class definition
class Edge
{
public:
    Vertex* v1, * v2; // Pointers to the two vertices connected by the edge
    float weight; // Weight of the edge

    // Constructor for the Edge class
    Edge(Vertex* nv1, Vertex* nv2, float newWeight) : v1(nv1), v2(nv2), weight(newWeight) { }
};

// Graph class definition
class Graph
{
protected:
    vector<Vertex*> v; // List of vertices in the graph
    vector<Edge*> e; // List of edges in the graph

public:
    Graph() {} // Constructor for the Graph class

    // Destructor for the Graph class
    ~Graph()
    {
        for (auto vertex : v) {
            delete vertex;
        }
        for (auto edge : e) {
            delete edge;
        }
    }

    // Method to insert a new vertex into the graph
    void insertVertex(int label)
    {
        v.push_back(new Vertex(label));
    }

    // Method to insert a new edge into the graph
    void insertEdge(int l1, int l2, float weight)
    {
        Vertex* v1 = v[l1];
        Vertex* v2 = v[l2];
        Edge* edge = new Edge(v1, v2, weight);
        v1->edges.push_back(edge);
        v2->edges.push_back(edge);
        e.push_back(edge);
    }

    // Method to find the shortest path between two vertices using Dijkstra's algorithm
    vector<Vertex*> shortestPath(int start, int end)
    {
        Heap<Vertex*> heap; // Priority queue for the algorithm
        v[start]->distanceTo = 0; // Initialize the starting vertex distance
        for (auto vertex : v) {
            vertex->locator = heap.insertElement(vertex);
        }

        // Main loop of Dijkstra's algorithm
        while (!heap.isEmpty()) {
            Vertex* current = heap.removeMin(); // Get the vertex with the smallest distance
            current->visited = true; // Mark the vertex as visited

            // If the end vertex is reached, stop the algorithm
            if (current->label == end) {
                break;
            }

            // Relax edges connected to the current vertex
            for (auto edge : current->edges) {
                Vertex* neighbor = edge->v1 == current ? edge->v2 : edge->v1;

                if (!neighbor->visited) {
                    float newDistance = current->distanceTo + edge->weight;
                    // If the new distance is shorter, update the neighboring vertex's distance
                    if (newDistance < neighbor->distanceTo) {
                        neighbor->distanceTo = newDistance;
                        neighbor->pathTo = current; // Update the previous vertex in the shortest path
                        heap.update(neighbor->locator); // Update the priority queue with the new distance
                    }
                }
            }
        }


        // Reconstruct the shortest path by following the pathTo pointers from the end vertex
        vector<Vertex*> path; // Vector to store the shortest path
        Vertex* pathVertex = v[end]; // Start at the end vertex
        while (pathVertex != nullptr) {
            path.push_back(pathVertex); // Add the vertex to the path
            pathVertex = pathVertex->pathTo; // Move to the previous vertex in the shortest path
        }

        // Reverse the path so that it goes from the start vertex to the end vertex
        reverse(path.begin(), path.end());
        return path; // Return the shortest path
    }
};

#endif
