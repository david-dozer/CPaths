#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
private:
    map<VertexT, map<VertexT, WeightT>> adjList;
    vector<VertexT> vertices;

public:
    //
    // PathSignature: Define a type to represent a path signature
    //
    struct PathSignature {
        WeightT cost;
        WeightT time;

        PathSignature(WeightT c, WeightT t) : cost(c), time(t) {}

        // Define comparison operators for path signatures
        bool operator<(const PathSignature& other) const {
            return (cost < other.cost) || (cost == other.cost && time > other.time);
        }
    };

    //
    // HeapElement: Define a struct to represent elements stored in the priority queue
    //
    struct HeapElement {
        PathSignature pathSignature;
        VertexT vertex;

        HeapElement(const PathSignature& ps, const VertexT& v) : pathSignature(ps), vertex(v) {}

        // Define comparison operators for heap elements based on path signature
        bool operator<(const HeapElement& other) const {
            return pathSignature < other.pathSignature;
        }
    };

    //
    // NonDominatedPathsSet: Define a type to represent the set S[v] for each vertex v
    //
    using NonDominatedPathsSet = vector<PathSignature>;

    //
    // GraphAlgorithmState: Define a struct to maintain algorithm-specific data during execution
    //
    struct GraphAlgorithmState {
        priority_queue<HeapElement> priorityQueue;
        vector<NonDominatedPathsSet> nonDominatedPaths;

        GraphAlgorithmState(int numVertices) : nonDominatedPaths(numVertices) {}

        // Initialize graph algorithm state at the start of the algorithm
        void initialize(const VertexT& source) {
            // Clear priority queue and initialize with initial path from source
            priorityQueue = priority_queue<HeapElement>();
            priorityQueue.push(HeapElement(PathSignature(0, 0), source));

            // Clear non-dominated paths sets for each vertex
            for (auto& paths : nonDominatedPaths) {
                paths.clear();
            }

            // Add initial path signature at the source vertex
            nonDominatedPaths[source].push_back(PathSignature(0, 0));
        }
    };

    //
    // constructor:
    //
    // Constructs an empty graph.
    //
    graph() {}

    //
    // NumVertices
    //
    // Returns the number of vertices currently in the graph.
    //
    int NumVertices() const {
        return adjList.size();
    }

    //
    // NumEdges
    //
    // Returns the number of edges currently in the graph.
    //
    int NumEdges() const {
        int count = 0;
        for (const auto& i : adjList) {
            count += i.second.size();
        }
        return count;
    }

    //
    // addVertex
    //
    // Adds the vertex v to the graph if it doesn't already exist.
    //
    bool addVertex(const VertexT& v) {
        if (adjList.count(v) > 0) {
            return false; // Vertex already exists
        }
        adjList[v]; // Initialize empty adjacency map for vertex
        vertices.push_back(v); // Add vertex to vertices list
        return true;
    }

    //
    // addEdge
    //
    // Adds an edge from vertex 'from' to vertex 'to' with the given weight.
    // If the vertices don't exist, they are added to the graph.
    //
    bool addEdge(const VertexT& from, const VertexT& to, const WeightT& weight) {
        // Add vertices if they don't already exist
        addVertex(from);
        addVertex(to);

        // Add edge with specified weight
        adjList[from][to] = weight;
        return true;
    }

    //
    // getWeight
    //
    // Returns the weight associated with the edge from vertex 'from' to vertex 'to'.
    // Returns true if the edge exists, false otherwise.
    //
    bool getWeight(const VertexT& from, const VertexT& to, WeightT& weight) const {
        auto it = adjList.find(from);
        if (it != adjList.end() && it->second.find(to) != it->second.end()) {
            weight = it->second.at(to);
            return true;
        }
        return false;
    }

    //
    // neighbors
    //
    // Returns a set containing the neighbors of vertex 'v'.
    //
    set<VertexT> neighbors(const VertexT& v) const {
        set<VertexT> S;
        auto it = adjList.find(v);
        if (it != adjList.end()) {
            for (const auto& pair : it->second) {
                S.insert(pair.first);
            }
        }
        return S;
    }

    //
    // getVertices
    //
    // Returns a vector containing all vertices currently in the graph.
    //
    vector<VertexT> getVertices() const {
        return vertices;
    }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (int i = 0; i < this->NumVertices(); ++i) {
      output << " " << i << ". " << this->vertices[i] << endl;
    }
    int curRow = 0;
    output << endl;
    output << "**Edges:" << endl;
    for (auto const &i : adjList) {
      output << " row " << curRow << ": "; curRow++;
      for (auto const &j : adjList) {
        if (adjList.at(i.first).count(j.first) == 0) {
          output << "F ";
        } else {
          output << "(T," << adjList.at(i.first).at(j.first)
            << ") ";
        }
      }
      output << endl;
    }
    output << "**************************************************" << endl;
  }
};