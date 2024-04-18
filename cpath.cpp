#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "graph.h"

using namespace std;

// Function to read the graph from a file
bool readGraphFromFile(const string& filename, graph<int, int>& g) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file " << filename << endl;
        return false;
    }

    int numVertices;
    inputFile >> numVertices;

    int u, v, c, t;
    while (inputFile >> u >> v >> c >> t) {
        g.addVertex(u);
        g.addVertex(v);
        g.addEdge(u, v, c);
    }

    inputFile.close();
    return true;
}

// Function to perform the Dijkstra-like algorithm
void closest_constrained_path(const graph<int, int>& g, int source, int destination, int budget) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<pair<int, int>> minPath(g.NumVertices(), {INT_MAX, INT_MAX});
    pq.push({0, 0}); // Initial path with cost = 0 and time = 0 at the source vertex
    minPath[source] = {0, 0}; // Cost and time at source vertex

    while (!pq.empty()) {
        auto [currentCost, currentTime] = pq.top();
        pq.pop();

        if (currentCost > budget) {
            continue; // Skip paths that exceed the budget
        }

        if (currentCost <= budget && minPath[destination].first > currentCost) {
            minPath[destination] = {currentCost, currentTime};
        }

        for (int neighbor : g.neighbors(destination)) {
            int edgeWeight;
            if (g.getWeight(destination, neighbor, edgeWeight)) {
                int newCost = currentCost + edgeWeight;
                int newTime = currentTime + edgeWeight;

                if (newCost <= budget && minPath[neighbor].first > newCost) {
                    minPath[neighbor] = {newCost, newTime};
                    pq.push({newCost, newTime});
                }
            }
        }
    }

    // Output the result for the destination vertex
    if (minPath[destination].first == INT_MAX) {
        cout << "No feasible path within the budget." << endl;
    } else {
        cout << "Cost: " << minPath[destination].first << ", Time: " << minPath[destination].second << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <file> <s> <d> <budget>" << endl;
        return 1;
    }

    // Parse command line arguments
    string filename = argv[1];
    int source = stoi(argv[2]);
    int destination = stoi(argv[3]);
    int budget = stoi(argv[4]);

    // Create a graph instance
    graph<int, int> g;

    // Read the graph from input file
    if (!readGraphFromFile(filename, g)) {
        return 1;
    }

    // Perform Dijkstra-like algorithm to find the fastest cost-feasible path
    closest_constrained_path(g, source, destination, budget);

    return 0;
}
