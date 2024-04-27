#include "graph.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

// Function to read the graph from a file
bool readGraphFromFile(const string &filename, graph<int, int> &g) {
  ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    cerr << "Error: Unable to open input file " << filename << endl;
    return false;
  }

  int numVertices;
  inputFile >> numVertices;

  int u, v, c, t;
  while (inputFile >> u >> v >> c >> t) {
    g.addEdge(u, v, c, t);
  }

  inputFile.close();
  
  return true;
}

// Function to perform the Dijkstra-like algorithm considering both cost and time constraints
void closest_constrained_path(const graph<int, int> &g, int source, int destination, int budget) {
    vector<int> minCost(
        g.NumVertices(),
        numeric_limits<int>::max()); // Minimum cost to reach each vertex
    vector<int> minTime(
        g.NumVertices(),
        numeric_limits<int>::max());       // Minimum time to reach each vertex
    vector<int> prev(g.NumVertices(), -1); // Previous vertex in the shortest path

    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>,
                   greater<pair<pair<int, int>, int>>>
        pq;
    pq.push({{0, 0}, source}); // Initial path with cost = 0 and time = 0 at the source vertex
    minCost[source] = 0;  // Cost at source vertex
    minTime[source] = 0;  // Time at source vertex

    while (!pq.empty()) {
        auto [curWeight, currentVertex] = pq.top();
        auto [currentCost, currentTime] = curWeight;
        pq.pop();

        // Skip paths that exceed the budget or time constraint
        if (currentCost > budget) {
            continue;
        }

        if (currentVertex == destination) {
            // Found the destination vertex
            cout << "Cost: " << minCost[destination]
                << ", Time: " << minTime[destination] << endl;
            return;
        }

        for (int neighbor : g.neighbors(currentVertex)) {
            int edgeCost, edgeTime;
            if (g.getWeight(currentVertex, neighbor, edgeCost, edgeTime)) {
                int newCost = currentCost + edgeCost;
                int newTime = currentTime + edgeTime;

                // Relaxation step
                if (newCost <= budget && newCost < minCost[neighbor]) {
                    minCost[neighbor] = newCost;
                    minTime[neighbor] = newTime;
                    prev[neighbor] = currentVertex;
                    pq.push({{newCost, newTime}, neighbor});
                }
            }
        }
    }

    // If no feasible path exists within the budget and time constraint
    cout << "No feasible path within the budget and time constraint." << endl;
}


int main(int argc, char *argv[]) {
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
